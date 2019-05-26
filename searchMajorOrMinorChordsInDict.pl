use strict;
use warnings;

sub SearchMajorOrMinorChordsInDict
{
	my @list = ();
	my $filename = "./dict.txt";
    my $modification = $_[0];
	
    open (my $fh, $filename) or die "Error: opening file '$filename'";

    while (my $line = <$fh>) 
    {
        if ($modification eq 'M' or $modification eq '+') {
            while ($line =~ /(.+(?:M|\+)[^\s]?)/g)
            {
                my $chord = $1;
                push (@list, $chord);            
            }
        }
        elsif ($modification eq 'm') {
            while ($line =~ /(.+(?:m)[^\s]?)/g)
            {
                my $chord = $1;
                push (@list, $chord);            
            }
        }
	}
	
	close $fh or die "Error: closing file '$filename'";

	return @list;
}