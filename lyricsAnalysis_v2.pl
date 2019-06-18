use open IN => ':std', ':encoding(UTF-8)';  #Using these lines to print special characters correctly
use open OUT => ':utf8';
use strict;
use warnings;
use lyricsAnalysisModule;

# sub searchChordsFromLyrics
# {
# 	my %hash = SearchChordsFromLyrics ($_[0]);
# }

sub searchLyricsByTune
{
	return SearchLyricsByTune($_[0]);	
}

sub changeLyricsTune
{
	return ChangeLyricsTune($_[0], $_[1]);
}

sub searchSimilarChordsInDict
{
	return SearchSimilarChordsInDict($_[0]);
}

sub checkIfLyricsHaveIntro
{
	return CheckIfLyricsHaveIntro($_[0]);
}

sub searchModifiedChordsInDict
{
	return SearchModifiedChordsInDict($_[0]);
}

sub searchMajorOrMinorChordsInDict
{
	return SearchMajorOrMinorChordsInDict($_[0]);
}

sub identifyMusicAndArtistName
{
	return IdentifyMusicAndArtistName($_[0]);
}