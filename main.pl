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
my $arg2 = 0;

if (not TestOption($option)) {
	print ("Invalid option\n");
	WarningMessage();
	exit;
}

if (scalar(@ARGV) >= 2) {
	$arg1 = $ARGV[1];
}

if (scalar(@ARGV) == 3) {
	$arg2 = $ARGV[2];
}

my @result;

# DONE
if ($option eq "chords") {
	if (scalar(@ARGV) < 1) {
		WarningMessage();
		exit;
	}
	foreach (@lyrics) {
        my %chords = SearchChordsFromLyrics($_);
        print "Lyrics: '$_'\n";
        foreach my $key (sort {$chords{$b} <=> $chords{$a}} keys %chords) {
        print " $key \t\t \t$chords{$key}\n";
        }
    }
}

# DONE
if ($option eq "number") {
	if (scalar(@ARGV) < 2) {
		WarningMessage();
		exit;
	}
	# if (not TestType($arg1)) {
	# 	print ("Invalid type\n");
	# 	WarningMessage();
	# 	exit;
	# }
	foreach (@lyrics) {
        my $result = SearchLyricsByNumberOfChords($_, $arg2);
        if ($result == 1) {
            print "\n Match! Lyrics: $_.\n\n";
        }
    }
}

# DONE
if ($option eq "tune") {
	if (scalar(@ARGV) < 2) {
		WarningMessage();
		exit;
	}
	# if (not TestType($arg1)) {
	# 	print ("Invalid type.\n");
	# 	WarningMessage();
	# 	exit;
	# }
	foreach (@lyrics) {
        my $result = SearchLyricsByTune($_, $arg2);

        if ($result == 1) {
            print "Lyrics '$_' have the desired tune. \n";
        }
    }
}

# DONE
if ($option eq "changeTune")
{
	if (scalar(@ARGV) < 2)
	{
		WarningMessage();
		exit;
	}

	# if (($arg1 ne "HP") and ($arg1 ne "Att") and ($arg1 ne "Def") and ($arg1 ne "SA") and ($arg1 ne "SD") and ($arg1 ne "Spd"))
	# {
	# 	print "Invalid stat\n";	
	# 	WarningMessage();
	# 	exit;
	# }

    foreach (@lyrics) {
        my $result = ChangeLyricsTune($_, $arg2);
        if ($result == 1) {
            print "File with new tune created with success\n";
        }
    }
	
}

# DONE
if ($option eq "similar") {
	if (scalar(@ARGV) < 2) {
		WarningMessage();
		exit;
	}
	
	# if (not TestType($arg1)) {
	# 	print ("Invalid type.\n");
	# 	WarningMessage();
	# 	exit;
	# }

    @result = SearchSimilarChordsInDict($arg2);
    foreach (@result) {
        print "$_\n";
    }

}

# DONE
if ($option eq "intro") {
	if (scalar(@ARGV) < 1) {
		WarningMessage();
		exit;
	}
	
	# if (not TestType($arg1)) {
	# 	print ("Invalid type.\n");
	# 	WarningMessage();
	# 	exit;
	# }
	
    foreach (@lyrics) {
	    my $result = CheckIfLyricsHaveIntro($_);
        if ($result == 1) {
            print "Lyrics '$_' have an intro\n";
        }
    }
}

# DONE
if ($option eq "modification") {
	if (scalar(@ARGV) < 2) {
		WarningMessage();
		exit;
	}
	
	# if (not TestType($arg1)) {
	# 	print ("Invalid type.\n");
	# 	WarningMessage();
	# 	exit;
	# }
	
	@result = SearchModifiedChordsInDict($arg2);
	foreach (@result) {
		print "$_\n";	
	}
}

# DONE
if ($option eq "majorMinor") {
	if (scalar(@ARGV) < 2) {
		WarningMessage();
		exit;
	}
	
	# if (not TestType($arg1)) {
	# 	print ("Invalid type.\n");
	# 	WarningMessage();
	# 	exit;
	# }
	
	@result = SearchMajorOrMinorChordsInDict($arg2);
	foreach (@result){
        print "$_\n";
	}
}