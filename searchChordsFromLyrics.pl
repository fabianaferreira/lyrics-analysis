use strict;
use warnings;
require "./checkChordsLinesInFile.pl";

sub SearchChordFromLyrics
{
	my %list;
	my $filename = $_[0];
	open (my $fh, $filename) or die "Error: opening file '$filename'";

	while (my $line = <$fh>)
	{
		my $isChordLine = checkChordsLinesInFile($line);

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

my %chords = SearchChordFromLyrics("./cifras/imortal.txt");

foreach my $key (sort {$chords{$b} <=> $chords{$a}} keys %chords) {
   print " $key \t\t \t$chords{$key}\n";
}