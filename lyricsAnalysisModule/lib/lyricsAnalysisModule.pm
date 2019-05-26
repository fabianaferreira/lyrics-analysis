package lyricsAnalysisModule;

use 5.026001;
use strict;
use warnings;
use Carp;

require Exporter;
use AutoLoader;

our @ISA = qw(Exporter);

# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.

# This allows declaration	use lyricsAnalysisModule ':all';
# If you do not need this, moving things directly into @EXPORT or @EXPORT_OK
# will save memory.
our %EXPORT_TAGS = ( 'all' => [ qw(
	
) ] );

our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );

our @EXPORT = qw(
	SearchChordsFromLyrics SearchLyricsByNumberOfChords SearchLyricsByTune ChangeLyricsTune 
    SearchSimilarChordsInDict CheckIfLyricsHaveIntro SearchModifiedChordsInDict 
    SearchMajorOrMinorChordsInDict IdentifyMusicAndArtistName
);

our $VERSION = '0.01';

sub CheckChordsLinesInFile
{

	my $line = $_[0];
	my $length;
	# Splits the line, getting the strings between white spaces
	my @splitString = split(/\s/, $line);

	# If there are only white spaces
	if ($#splitString < 0) {
		return 0;
	}
		
	# If not, tests if there is at least one word with more than three characters 
	# or there is at least one word that doesn't have one of the basic chords
	foreach (@splitString) {
		$length =  length($_);
		if ($_ =~ /(^[^CDEFGAB].+$)/g) {
			return 0;
		}
	}
	return 1;
}

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

sub SearchLyricsByNumberOfChords
{
	my @list = ();
	my $filename = $_[0];
    my $quantity = $_[1];
	open (my $fh, $filename) or die "Error: opening file '$filename'";

	while (my $line = <$fh>)
	{
        my $isChordLine = CheckChordsLinesInFile($line);

        if ($isChordLine == 1) {
            while ($line =~ /([CDEFGAB]?\S+)/g)
            {
                push (@list, ($1));
            }
        }
	}

    close $fh or die "Error: closing file '$filename'";

    my @result = keys %{ { map { $_=> 1 } @list } };
    my $chordsQuantity = @result;

    if ($quantity == $chordsQuantity) {
        return 1;
    }

    # print "\n No match! Chords quantity in lyrics '$filename': $chordsQuantity.\n\n";
    return 0;
}

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

sub getNewChord
{
    my $offset = $_[0];
    my $currentChord = $_[1];


    if ($currentChord eq "Bb") {
        $currentChord = "A#";
    }
    elsif ($currentChord eq "Db") {
        $currentChord = "C#";
    }
    elsif ($currentChord eq "Eb") {
        $currentChord = "D#";
    }
    elsif ($currentChord eq "Gb") {
        $currentChord = "F#";
    }
    elsif ($currentChord eq "Ab") {
        $currentChord = "G#";
    }

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
    my $hasItTune = 0;
	open (my $fh, $filename) or die "Error: opening file '$filename'";

	while (my $line = <$fh>)
	{
        if ($line =~ /(?:tom)\s?:\s?(.+)/gi)
        {
            $lyricsTune = $1;
            $hasItTune = 1;
            last;
        }
	}

    if ($hasItTune == 0) {
        return 0;
    }

    # Creating new file that has the same content that the original one
    # but changing lyrics tune and renamed so as to identify it
    my $resultFile = $filename;
    # Removes extension
    $resultFile =~ s/.txt//g;
    # Concats old filename with string that identify user's offset
    $resultFile = $resultFile . '_tom_offset_' . $offset . '.txt';

    open(my $f, '>', $resultFile) or die "Error: opening file '$resultFile'";
    
    while (my $line = <$fh>) {
        my $isChordLine = CheckChordsLinesInFile($line);
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

sub SearchModifiedChordsInDict
{
	my @list = ();
	my $filename = "./dict.txt";
    my $modification = $_[0];
	
    open (my $fh, $filename) or die "Error: opening file '$filename'";

    while (my $line = <$fh>) 
    {
        while ($line =~ /(.+$modification[^\s]?)\s\d{1}\s\d{1}/g)
        {
            my $chord = $1;
            push (@list, $chord);            
        }
	}
	
	close $fh or die "Error: closing file '$filename'";

	return @list;
}

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

sub IdentifyMusicAndArtistName
{
    my $path = $_[0];
	my @result;

    if ($path =~ /^\.\/cifras\/(.+)\/(.+)\.txt$/g) {
        my $artist = $1;
        my $name = $2;

        # Removing underscores and replacing them with whitespace
        $artist =~ s/_/ /g;
        $name =~ s/_/ /g;

        # Capitalizing first letter
        $artist =~ s/^([a-z])/\U$1/g;
        $name =~ s/^([a-z])/\U$1/g;

        push (@result, $artist);
        push (@result, $name);
    }
	
	return @result;
}

sub AUTOLOAD {
    # This AUTOLOAD is used to 'autoload' constants from the constant()
    # XS function.

    my $constname;
    our $AUTOLOAD;
    ($constname = $AUTOLOAD) =~ s/.*:://;
    croak "&lyricsAnalysisModule::constant not defined" if $constname eq 'constant';
    my ($error, $val) = constant($constname);
    if ($error) { croak $error; }
    {
	no strict 'refs';
	# Fixed between 5.005_53 and 5.005_61
#XXX	if ($] >= 5.00561) {
#XXX	    *$AUTOLOAD = sub () { $val };
#XXX	}
#XXX	else {
	    *$AUTOLOAD = sub { $val };
#XXX	}
    }
    goto &$AUTOLOAD;
}

require XSLoader;
XSLoader::load('lyricsAnalysisModule', $VERSION);

# Preloaded methods go here.

# Autoload methods go after =cut, and are processed by the autosplit program.

1;
__END__
# Below is stub documentation for your module. You'd better edit it!

=head1 NAME

lyricsAnalysisModule - Perl extension for blah blah blah

=head1 SYNOPSIS

  use lyricsAnalysisModule;
  blah blah blah

=head1 DESCRIPTION

Stub documentation for lyricsAnalysisModule, created by h2xs. It looks like the
author of the extension was negligent enough to leave the stub
unedited.

Blah blah blah.

=head2 EXPORT

None by default.



=head1 SEE ALSO

Mention other useful documentation such as the documentation of
related modules or operating system documentation (such as man pages
in UNIX), or any relevant external documentation such as RFCs or
standards.

If you have a mailing list set up for your module, mention it here.

If you have a web site set up for your module, mention it here.

=head1 AUTHOR

Fabiana, E<lt>fabiana@E<gt>

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2019 by Fabiana

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.26.1 or,
at your option, any later version of Perl 5 you may have available.


=cut
