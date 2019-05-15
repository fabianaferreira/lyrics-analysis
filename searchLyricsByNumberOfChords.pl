use strict;
use warnings;
require "./checkChordsLinesInFile.pl";

sub SearchLyricsByNumberOfChords
{
	my @list = ();
	my $filename = $_[0];
    my $quantity = $_[1];
    my $chordsLinesCounter = 0;
	open (my $fh, $filename) or die "Error: opening file '$filename'";

	while (my $line = <$fh>)
	{
        my $isChordLine = checkChordsLinesInFile($line);

        if ($isChordLine == 1) {
            $chordsLinesCounter = $chordsLinesCounter + 1;
            while ($line =~ /([CDEFGAB]#?m?7?M?7?\+?\d*)/g)
            {
                push (@list, ($1));       
            }
        }
	}

    my @result = keys %{ { map { $_=> 1 } @list } };

    print "DEBUG: Chords lines quantity: $chordsLinesCounter \n";

    print "DEBUG: Chords quantity: $#result \n";

    if ($quantity == $#result) {
        print "Match quantity\n";
    }
    else {
        print "Doesnt match quantity\n";
    }
	
	close $fh or die "Error: closing file '$filename'";

	return @list;
}

print "Number of desired chords: ";

my $number = <STDIN>;

chomp $number;

my @chords = SearchLyricsByNumberOfChords("./cifras/a_lenda.txt", $number);