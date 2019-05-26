use strict;
use warnings;
require "./checkChordsLinesInFile.pl";

sub getNewChord
{
    my $offset = $_[0];
    my $currentChord = $_[1];
    my @chords = ("C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B");

    # Finds chord index in array
    my ($tuneIndex) = grep $chords[$_] eq $currentChord, 0 .. $#chords;

    # Normalizes indexes in array range
    $offset = $offset > 0 ? $offset % 12 :  -(abs($offset) % 12);

    my $newIndex = $tuneIndex + $offset;
    if ($newIndex < 0) {
        $newIndex = $newIndex + 12;
    }
    elsif ($newIndex > 11) {
        $newIndex = $newIndex - 12;
    }
    return $chords[$newIndex];
}

sub ChangeLyricsTune
{
	my $filename = $_[0];
    my $offset = $_[1];
    my $lyricsTune;
	open (my $fh, $filename) or die "Error: opening file '$filename'";

	while (my $line = <$fh>)
	{
        if ($line =~ /(?:tom)\s?:\s?(.+)/gi)
        {
            $lyricsTune = $1;
            last;
        }
	}

    print "Lyrics tune: $lyricsTune \n";

    # Creating new file that has the same content that the original one
    # but changing lyrics tune and renamed so as to identify it
    my $resultFile = $filename;
    # Removes extension
    $resultFile =~ s/.txt//g;
    # Concats old filename with string that identify user's offset
    $resultFile = $resultFile . '_tom_offset_' . $offset . '.txt';

    open(my $f, '>', $resultFile) or die "Error: opening file '$resultFile'";
    
    while (my $line = <$fh>) {
        my $isChordLine = checkChordsLinesInFile($line);
        my $modifiedLine = $line;
        if ($isChordLine == 1) {
            # For each line, we need to find the first part of the chord, so as to 
            # replace for the new tune
            # For example: A#m7 -> tune is A#. If we want to change it to Gb, we need
            # to replace 'A#' for 'Gb'
            while ($line =~ /([CDEFGAB]?\S+)/g)
            {            
                my $basicChord;
                if ($1 =~ /([CDEFGAB][#b]?)/) {
                    $basicChord = $1;
                    my $newChord = getNewChord($offset, $basicChord);
                    $modifiedLine =~ s/\Q$basicChord/$newChord/g;
                }
            }
        }

        print $f "$modifiedLine";
    }

    close $f or die "Error: closing file '$resultFile'";  
    close $fh or die "Error: closing file '$filename'";

    return 1;
}