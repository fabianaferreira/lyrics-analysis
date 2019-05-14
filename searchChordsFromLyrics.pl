use strict;
use warnings;

sub SearchChordFromLyrics
{
	my @list = ();
	my $filename = $_[0];
	open (my $fh, '<:encoding(UTF-8)', $filename) or die "Error: opening file '$filename'";

	while (my $line = <$fh>)
	{
  	while ($line =~ /([CDEFGAB]#?m?7?M?7?\+?\d*)/g)
    {
			print "Current match: $1 \n";
			my $chord = $1;
			push (@list, $chord);
    }
	}
	
	close $fh or die "Error: closing file '$filename'";

	return @list;
}

print "Result: ";

my $file = <STDIN>;

chomp $file;

my @chords = SearchChord("lyrics.txt");
foreach (@chords)
{
	print "$_\n";
}