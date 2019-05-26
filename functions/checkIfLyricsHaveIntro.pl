use strict;
use warnings;

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

# my @lyrics = ("./cifras/sandy_junior/era_uma_vez.txt", "./cifras/sandy_junior/imortal.txt", "./cifras/sandy_junior/as_quatro_estacoes.txt", "./cifras/sandy_junior/no_fundo_do_coracao.txt");

# foreach (@lyrics) {
#     my $result = CheckIfLyricsHaveIntro($_);

#     if ($result == 1) {
#         print "Lyrics '$_' have an intro\n";
#     }
# }