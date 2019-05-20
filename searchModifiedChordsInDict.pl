use strict;
use warnings;

sub searchModifiedChordsInDict
{
	my @list = ();
	my $filename = "./dict.txt";
    my $modification = $_[0];
	
    open (my $fh, $filename) or die "Error: opening file '$filename'";

    # Given the two variables, now we need to search in the file
    # for the chords that have less or equal quantity of chords and
    # barre chord or not
    while (my $line = <$fh>) 
    {
        while ($line =~ /(.+$modification[^\s]?)/g)
        {
            my $chord = $1;
            push (@list, $chord);            
        }
	}
	
	close $fh or die "Error: closing file '$filename'";

	return @list;
}

print "Type which modification you are searching for (4th, 5th, 7th and 9th): ";

my $input = <STDIN>;

chomp $input;

my @chordsWithModification = searchModifiedChordsInDict($input);
foreach (@chordsWithModification)
{
	print "$_\n";
}