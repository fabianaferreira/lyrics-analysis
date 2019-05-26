use strict;
use warnings;

sub SearchSimilarChordsInDict
{
	my @list = ();
	my $filename = "./dict.txt";
    my $userChord = $_[0];
    my $desiredFingersQnt = 0;
    my $desiredBarreChord = 0;
	
    open (my $fh, $filename) or die "Error: opening file '$filename'";

    # Searching for chord that user typed in and getting    
    # its fingers quantity and if it has barre chord or not
	while (my $line = <$fh>)
	{   
        if ($line =~ /($userChord.*)\s(\d{1})\s(\d{1})/g) 
        {
            $desiredFingersQnt = $2;
            $desiredBarreChord = $3;
            last;
        } 
    }

    # If there is no match for user's chord, it will return an empty array
    if ($desiredFingersQnt == 0) 
    {
        return @list;
    }

    print "Desired quantity: $desiredFingersQnt \n";
    print "Desired barre chord: $desiredBarreChord \n";

    # Given the two variables, now we need to search in the file
    # for the chords that have less or equal quantity of chords and
    # barre chord or not
    while (my $line = <$fh>) 
    {
        while ($line =~ /(.+)\s($desiredFingersQnt)\s($desiredBarreChord)/g)
        {
            my $chord = $1;
            push (@list, $chord);            
        }
	}
	
	close $fh or die "Error: closing file '$filename'";

	return @list;
}