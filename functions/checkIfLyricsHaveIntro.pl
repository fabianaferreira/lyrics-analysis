use strict;
use warnings;

sub CheckIfLyricsHaveIntro
{
	my $filename = $_[0];
    my $foundIntro = 0;
	open (my $fh, $filename) or die "Error: opening file '$filename'";

	while (my $line = <$fh>)
	{
        if ($line =~ /^(?:intro)\s?:\s?.*$/gi)
        {
            $foundIntro = 1;
            last;
        }
	}

    close $fh or die "Error: closing file '$filename'";

    return $foundIntro;
}