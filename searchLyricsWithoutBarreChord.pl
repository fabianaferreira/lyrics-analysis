use strict;
use warnings;
require "./searchChordsFromLyrics.pl";

sub SearchLyricsWithoutBarreChord
{
	my %list;
	my $filename = $_[0];
    my $dict = "./dict.txt";
    my %hash = SearchChordsFromLyrics($filename);
    my @chords = keys %hash;

	open (my $fh, $dict) or die "Error: opening file '$dict'";

    foreach (@chords) {
        my $chord = $_;

        # In case of having '+' in chord, we need to escape it to
        # use in regex
        $chord =~ s/\+/\\+/g;

        while (my $line = <$fh>)
        {
            if ($line =~ /(?:$chord)(?:\s|\/)(?:.+)?(?:\d{1})\s(\d{1})/g) {
                if ($1 == 1) {
                    print "$line\n";
                    return 1;
                }
            }
        }
    }

    close $fh or die "Error: closing file '$filename'";

    return 0;
}

my $areThereBarreChords = SearchLyricsWithoutBarreChord("./cifras/sandy_junior/inesquecivel.txt");

if ($areThereBarreChords == 0) {
    print "There are no barre chords in lyrics\n";
}
else {
    print "Lyrics has barre chords\n";
}