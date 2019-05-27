use open IN => ':std', ':encoding(UTF-8)';  #Using these lines to print special characters correctly
use open OUT => ':utf8';
use strict;
use warnings;
use lyricsAnalysisModule;

sub WarningMessage {
        print "Run the program using one of the following options:\n";
        print "perl main.pl chords\n";
        print "perl main.pl number {number of chords}\n";
        print "perl main.pl tune {tune}\n";
        print "perl main.pl changeTune {offset}\n";
        print "perl main.pl similar {chord}\n";
        print "perl main.pl intro\n";
        print "perl main.pl modification {modification}\n";
        print "perl main.pl majorMinor {type}\n";
}

# Subroutine to check the argument that chooses the analysis
sub TestOption {
	my $optionToTest = $_[0];
	if (($optionToTest ne "chords") and ($optionToTest ne "number") and ($optionToTest ne "tune") and ($optionToTest ne "changeTune") and ($optionToTest ne "similar") and ($optionToTest ne "intro") and ($optionToTest ne "modification") and ($optionToTest ne "majorMinor")) {
		return 0;
	}
	return 1;
}

sub TestNumber {
	my $optionToTest = $_[0];
	if ($optionToTest =~ /^[+-]?\d+$/) {
		return 1;
	}
	return 0;
}

sub TestModification {
	my $optionToTest = $_[0];
	if ($optionToTest =~ /^[+Mm]$/) {
		return 1;
	}
	return 0;
}

if (not @ARGV) {
	WarningMessage();
	exit;
}



# As a way of testing the code without needing to write lyrics' paths, we will use 
# an array of paths so as to reproduce what it will come from C++ system
my @lyrics = ("./cifras/sandy_junior/aprender_a_amar.txt", "./cifras/sandy_junior/era_uma_vez.txt", 
		     "./cifras/sandy_junior/imortal.txt", "./cifras/sandy_junior/as_quatro_estacoes.txt", 
			 "./cifras/sandy_junior/ilusao.txt", "./cifras/sandy_junior/inesquecivel.txt",
			 "./cifras/sandy_junior/nao_ter.txt", "./cifras/sandy_junior/no_fundo_do_coracao.txt",
			 "./cifras/sandy_junior/olha_o_que_o_amor_me_faz.txt", "./cifras/sandy_junior/youre_my_number_one.txt");
my $option = $ARGV[0];
my $arg1 = 0;

if (not TestOption($option)) {
	print ("Invalid option\n");
	WarningMessage();
	exit;
}

if (scalar(@ARGV) >= 2) {
	$arg1 = $ARGV[1];
}

my @result;

# SearchChordsFromLyrics
if ($option eq "chords") {
	if (scalar(@ARGV) < 1) {
		WarningMessage();
		exit;
	}
	foreach (@lyrics) {
        my %chords = SearchChordsFromLyrics($_);
		my @nameArtist = IdentifyMusicAndArtistName($_);

		my $artist = $nameArtist[0];
		my $music = $nameArtist[1];

        print " Lyrics: '$_'\n";
		print " Details (music | artist): $music | $artist \n\n";
        foreach my $key (sort {$chords{$b} <=> $chords{$a}} keys %chords) {
        print " $key \t\t \t$chords{$key}\n";
        }
		print "\n";
    }
}

# SearchLyricsByNumberOfChords
if ($option eq "number") {
	if (scalar(@ARGV) < 2) {
		WarningMessage();
		exit;
	}
	my $atLeastOne = 0;
	if (not TestNumber($arg1)) {
		print "Invalid number of chords. It needs to be a positive integer\n";
		WarningMessage();
		exit;
	}
	foreach (@lyrics) {
        my $result = SearchLyricsByNumberOfChords($_, $arg1);
		my @nameArtist = IdentifyMusicAndArtistName($_);
		my $artist = $nameArtist[0];
		my $music = $nameArtist[1];

        if ($result == 1) {

            print "\n Match! Lyrics: '$_' \n\n";
			print " Details (music | artist): $music | $artist \n\n";
			$atLeastOne = 1;
        }
    }

	if ($atLeastOne == 0) {
		print "\nThere are no lines with $arg1 chords\n\n";
	}
}

# SearchLyricsByTune
if ($option eq "tune") {
	if (scalar(@ARGV) < 2) {
		WarningMessage();
		exit;
	}
	my $atLeastOne = 0;
	foreach (@lyrics) {
        my $result = SearchLyricsByTune($_, $arg1);
		my @nameArtist = IdentifyMusicAndArtistName($_);
		my $artist = $nameArtist[0];
		my $music = $nameArtist[1];

        if ($result == 1) {
			$atLeastOne = 1;
            print "\n Lyrics '$_' have the desired tune. \n";
			print " Details (music | artist): $music | $artist \n\n";
        }
    }
	if ($atLeastOne == 0) {
		print "\n There are no lyrics with desired tune.\n\n"
	}
}

# ChangeLyricsTune
if ($option eq "changeTune")
{
	if (scalar(@ARGV) < 2)
	{
		WarningMessage();
		exit;
	}
	if (not TestNumber($arg1)) {
		print "\n Invalid chord offset. It needs to be an integer\n\n";
		WarningMessage();
		exit;
	}
    foreach (@lyrics) {
        my $result = ChangeLyricsTune($_, $arg1);
		my @nameArtist = IdentifyMusicAndArtistName($_);
		my $artist = $nameArtist[0];
		my $music = $nameArtist[1];

        if ($result == 1) {
            print "\n File with new tune created with success\n";
			print " Details (music | artist | new tune): $music | $artist | $arg1 \n\n";
        }
		else {
			print "\n File $_ does not have tune line \n";
		}
    }
}

# SearchSimilarChordsInDict
if ($option eq "similar") {
	if (scalar(@ARGV) < 2) {
		WarningMessage();
		exit;
	}
    @result = SearchSimilarChordsInDict($arg1);
	if ($#result + 1 == 0) {
		print "\n No similar chords were found in dictionary\n\n";
	}
	else {
		print "\n Similar chords to $arg1 \n\n";
		foreach (@result) {
			print "$_\n";
		}
		print "\n";
	}
}

# CheckIfLyricsHaveIntro
if ($option eq "intro") {
	if (scalar(@ARGV) < 1) {
		WarningMessage();
		exit;
	}
	my $atLeastOne = 0;
    foreach (@lyrics) {
	    my $result = CheckIfLyricsHaveIntro($_);
		my @nameArtist = IdentifyMusicAndArtistName($_);
		my $artist = $nameArtist[0];
		my $music = $nameArtist[1];

        if ($result == 1) {
			$atLeastOne = 1;
            print " Lyrics '$_' have an intro\n";
			print " Details (music | artist): $music | $artist \n\n";
        }
    }
	if ($atLeastOne == 0) {
		print "\n No lyrics with intro were found\n\n";
	}
}

# SearchModifiedChordsInDict
if ($option eq "modification") {
	if (scalar(@ARGV) < 2) {
		WarningMessage();
		exit;
	}

	if (not TestNumber($arg1)) {
		print "\n Invalid type\n\n";
		WarningMessage();
		exit;
	}

	@result = SearchModifiedChordsInDict($arg1);

	# Checks if result array is empty, which corresponds to no occurrences found
	if ($#result + 1 == 0) {
		print "\n No chords were found in dictionary with selected modification\n\n";
	}
	else {
		print "\n Chords that are modified by $arg1 th\n\n";
		foreach (@result) {
			print "$_\n";	
		}
		print "\n";
	}	
}

# SearchMajorOrMinorChordsInDict
if ($option eq "majorMinor") {
	if (scalar(@ARGV) < 2) {
		WarningMessage();
		exit;
	}

	if (not TestModification($arg1)) {
		print "\n Invalid type\n\n";
		WarningMessage();
		exit;
	}

	@result = SearchMajorOrMinorChordsInDict($arg1);
	my $modification = ($arg1 eq "+" or $arg1 eq "M") ? "major" : "minor";
	print "\n Chords that are modified by $modification\n\n";
	foreach (@result){
        print "$_\n";
	}
	print "\n";
}