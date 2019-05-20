use strict;
use warnings;

sub SearchChordFromLyrics
{
	my @list = ();
	my $filename = $_[0];
	open (my $fh, $filename) or die "Error: opening file '$filename'";

	while (my $line = <$fh>)
	{
  	while ($line =~ /([CDEFGAB]?\S+)/g)
    {
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

my @chords = SearchChordFromLyrics("a_lenda.txt");
foreach (@chords)
{
	print "$_\n";
}