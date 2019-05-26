use strict;
use warnings;

sub validateFilesInDirectory
{
	my $filename = $_[0];
    my $correctTuneLine = 1;
	open (my $fh, $filename) or die "Error: opening file '$filename'";

	while (my $lyricsFile = <$fh>)
	{
        $correctTuneLine = 1;
        open (my $currentFile, $lyricsFile) or die "Error: opening file '$lyricsFile'";

        while (my $line = <$currentFile>) {
            if ($line =~ /(?:tom)\s?:\s?([ABCDEFG].*)/gi)
            {
                print "$1\n";
                my @splitString = split(/\s/, $1);
                if ($#splitString > 1) {
		            $correctTuneLine = 0;
                    last;
	            }
            }
        }

        close $currentFile or die "Error: closing file";

        if ($correctTuneLine == 0) {
            my $resultFile = 'filesToRemove.txt';
            open(my $f, '>>', $resultFile) or die "NError: opening file '$resultFile'";
            print $f "$lyricsFile";
            close $f;            
        } 
	}

    close $fh or die "Error: closing file '$filename'";
}

my $file = "./nomesArquivos.txt";

validateFilesInDirectory($file);
