use strict;
use warnings;

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

print " Desired tune: ";

my $input = <STDIN>;

chomp $input;

my @lyrics = ("./cifras/eu_sei_que_vou_te_amar.txt", "./cifras/a_lenda.txt", "./cifras/era_uma_vez.txt", "./cifras/imortal.txt", "./cifras/as_quatro_estacoes.txt", "./cifras/sonho_azul.txt");

foreach (@lyrics) {
    my $result = SearchLyricsByTune($_, $input);

    if ($result == 1) {
        print "Lyrics '$_' has the desired tune. \n";
    }
}