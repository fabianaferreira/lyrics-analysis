/*
Universidade Federal do Rio de Janeiro - UFRJ
Departamento de Engenharia Eletrônica e de Computação - DEL
Disciplina de Linguagens de Programação 2019.1
Trabalho: Gerenciador de Busca de Cifras
Alunas: Fabiana Ferreira e Tamine Alves
*/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <exception>

struct InvalidFilePath : public std::exception
{
    virtual const char *what() const throw()
    {
        return "Houve um problema na leitura dos arquivos. Saindo do programa.";
    }
};

struct InvalidOption : public std::exception
{
    virtual const char *what() const throw()
    {
        return "Opcao invalida. Digite 'y' ou 'n'";
    }
};

#endif