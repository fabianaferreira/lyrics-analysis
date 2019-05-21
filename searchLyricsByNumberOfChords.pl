use strict;
use warnings;
require "./checkChordsLinesInFile.pl";

sub SearchLyricsByNumberOfChords
{
	my @list = ();
	my $filename = $_[0];
    my $quantity = $_[1];
	open (my $fh, $filename) or die "Error: opening file '$filename'";

	while (my $line = <$fh>)
	{
        my $isChordLine = checkChordsLinesInFile($line);

        if ($isChordLine == 1) {
            while ($line =~ /([CDEFGAB]?\S+)/g)
            {
                push (@list, ($1));       
            }
        }
	}

    close $fh or die "Error: closing file '$filename'";

    my @result = keys %{ { map { $_=> 1 } @list } };
    my $chordsQuantity = @result;

    if ($quantity == $chordsQuantity) {
        return 1;
    }

    print "\n No match! Chords quantity in lyrics '$filename': $chordsQuantity.\n\n";
    return 0;
}

print " Number of desired chords: ";

my $number = <STDIN>;

chomp $number;

my @lyrics = ("./cifras/era_uma_vez.txt", "./cifras/imortal.txt", "./cifras/as_quatro_estacoes.txt");

foreach (@lyrics) {
    my $isAMatch = SearchLyricsByNumberOfChords($_, $number);
    if ($isAMatch == 1) {
        print "\n Match! Lyrics: $_.\n\n";
    }
}