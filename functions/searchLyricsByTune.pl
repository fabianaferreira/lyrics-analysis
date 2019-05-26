use strict;
use warnings;

sub SearchLyricsByTune
{
	my $filename = $_[0];
    my $userTune = $_[1];
    my $foundTune = 0;
	open (my $fh, $filename) or die "Error: opening file '$filename'";

	while (my $line = <$fh>)
	{
        if ($line =~ /(?:tom)\s?:\s?($userTune)/gi)
        {
            $foundTune = 1;
            last;
        }
	}

    close $fh or die "Error: closing file '$filename'";

    return $foundTune;
}