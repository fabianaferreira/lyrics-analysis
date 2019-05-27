use strict;
use warnings;
require "./checkChordsLinesInFile.pl";

sub SearchChordsFromLyrics
{
	my %list;
	my $filename = $_[0];
	open (my $fh, $filename) or die "Error: opening file '$filename'";

	while (my $line = <$fh>)
	{
		my $isChordLine = CheckChordsLinesInFile($line);

		if ($isChordLine == 1) {
			while ($line =~ /([CDEFGAB]?\S+)/g)
			{
				my $chord = $1;
				if ($list{$chord}) {
					$list{$chord}++;
				}
				else {
					$list{$chord} = 1;
				}
			}
		}
	}

	close $fh or die "Error: closing file '$filename'";

	return %list;
}

1;