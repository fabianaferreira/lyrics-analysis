## Lyrics chords analysis program

### Perl
  System to process text based on regular expressions

#### Instructions to create Perl module
  * Ensure you have `libperl-dev` installed. If not, run the command: `sudo apt-get install libperl-dev`

  * Run the command `h2xs -n lyricsAnalysisModule` inside `lyricsAnalysisModule` directory
  
  * Copy the file `lyricsAnalysisModule.pm` inside module directory that was created in previous step
  
  * Create a directory so as to it install the module `mkdir /home/user/modules`
  
  * Go to module's directory `./lyricsAnalysisModule` and run the following commands:
  
          perl Makefile.PL INSTALL_BASE=/home/{user}/modules

          make

          make install
  
  * Now it is necessary to export an environment variable so as to Perl know where to look for this module when using it: `export PERL5LIB=/home/{user}/modules/lib/perl5`
  


### C++
  System that will be responsible for looking into directory and getting the list of files' paths. 

  There is a menu so the user can choose which function to run.

  A C++ class was implemented so as to deal with Perl interpreter, called `perlWrapper`.
