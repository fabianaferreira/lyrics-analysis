#ifndef PERLWRAPPER_H
#define PERLWRAPPER_H

#include "/usr/lib/x86_64-linux-gnu/perl/5.26/CORE/EXTERN.h"
#include "/usr/lib/x86_64-linux-gnu/perl/5.26/CORE/perl.h"

class PerlWrapper
{
	public:
		PerlWrapper(int, char **, char **, char *);
		~PerlWrapper();
		PerlInterpreter *alloc();
		void run();

	private:
		PerlInterpreter *my_perl;
		//char *my_argv[] = {"", "calc.pl"};
		char *my_argv[2];
};

#endif
