## Lyrics chords analysis program

### Perl
  System to process text based on regular expressions

#### Instructions to create Perl module
  * Run the command `h2xs -n lyricsAnalysisModule` inside project's directory
  
  * Copy the file `lyricsAnalysisModule.pm` inside module directory that was created in previous step
  
  * Create a directory so as to it install the module `mkdir /home/user/modules`
  
  * Go to module's directory `./lyricsAnalysisModule` and run the following commands:
  
          perl Makefile.PL INSTALL_BASE=/home/lucas/modules

          make

          make install
  
  * Now it is necessary to export an environment variable so as to Perl know where to look for this module when using it: `export PERL5LIB=/home/user/modules/lib/perl5`
  


### C++
  System that will be responsible for looking into directory and passing to Perl module lyrics files' paths.
