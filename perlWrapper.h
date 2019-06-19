#ifndef PERLWRAPPER_H
#define PERLWRAPPER_H

#include <EXTERN.h>
#include <perl.h>

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
