/*
Universidade Federal do Rio de Janeiro - UFRJ
Departamento de Engenharia Eletrônica e de Computação - DEL
Disciplina de Linguagens de Programação 2019.1
Trabalho: Gerenciador de Busca de Cifras
Alunas: Fabiana Ferreira e Tamine Alves
*/

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
