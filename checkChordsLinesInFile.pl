use strict;
use warnings;

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

1;