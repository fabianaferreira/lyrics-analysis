use strict;
use warnings;

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
        $artist =~ s/^([a-z])/\U$1/;
        $name =~ s/^([a-z])/\U$1/;

        push (@result, $artist);
        push (@result, $name);
    }
	
	return @result;
}


my @list = IdentifyMusicAndArtistName("./cifras/sandy_junior/no_fundo_do_coracao.txt");

foreach (@list)  {
    print "$_ \n";
}