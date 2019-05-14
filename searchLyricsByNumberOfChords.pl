use strict;
use warnings;

sub SearchLyricsByNumberOfChords
{
	my @list = ();
	my $filename = $_[0];
    my $quantity = $_[1];
	open (my $fh, '<:encoding(UTF-8)', $filename) or die "Error: opening file '$filename'";

	while (my $line = <$fh>)
	{
        while ($line =~ /([CDEFGAB]#?m?7?M?7?\+?\d*)/g)
        {
                push (@list, ($1));       
        }
	}

    my @result = keys %{ { map { $_=> 1 } @list } };

    print "Chords quantity: $#result \n";

    if ($quantity == $#result) {
        print "Match quantity\n";
    }
    else {
        print "Doesnt match quantity\n";
    }
	
	close $fh or die "Error: closing file '$filename'";

	return @list;
}

print "Number of chords: ";

my $number = <STDIN>;

chomp $number;

my @chords = SearchLyricsByNumberOfChords("lyrics.txt", $number);

# debug
# foreach (@chords)
# {
# 	print "$_\n";
# }