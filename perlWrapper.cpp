/*
Universidade Federal do Rio de Janeiro - UFRJ
Departamento de Engenharia Eletrônica e de Computação - DEL
Disciplina de Linguagens de Programação 2019.1
Trabalho: Gerenciador de Busca de Cifras
Alunas: Fabiana Ferreira e Tamine Alves
*/

#include "perlWrapper.h"

/*DynaLoader - Dynamically load C libraries into Perl code*/
EXTERN_C void boot_DynaLoader(pTHX_ CV *cv);
EXTERN_C void xs_init(pTHX)
{
	char *file = __FILE__;
	/* DynaLoader is a special case */
	newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
}

PerlWrapper::PerlWrapper(int argc, char **argv, char **env, char *filename)
{
	my_argv[0] = "";
	my_argv[1] = filename;
	PERL_SYS_INIT3(&argc, &argv, &env);
}

PerlInterpreter *PerlWrapper::alloc()
{
	my_perl = perl_alloc();
	perl_construct(my_perl);
	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

	return my_perl;
}

PerlWrapper::~PerlWrapper()
{
	perl_destruct(my_perl);
	perl_free(my_perl);
	PERL_SYS_TERM();
}

void PerlWrapper::run()
{
	perl_parse(my_perl, xs_init, 2, my_argv, (char **)NULL);
	perl_run(my_perl);
}
