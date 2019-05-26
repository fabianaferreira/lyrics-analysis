use strict;
use warnings;

sub SearchModifiedChordsInDict
{
	my @list = ();
	my $filename = "./dict.txt";
    my $modification = $_[0];
	
    open (my $fh, $filename) or die "Error: opening file '$filename'";

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