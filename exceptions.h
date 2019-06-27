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
#include <string>

class LyricsAnalysisException
{
    public:
        virtual std::string detailException() const throw() = 0;
};

class InvalidFilePath : public LyricsAnalysisException
{
    public:
        virtual std::string detailException() const throw()
        {
            return "Houve um problema na leitura dos arquivos. Saindo do programa.";
        }

};

class InvalidOption : public LyricsAnalysisException
{
    public:
        virtual std::string detailException() const throw()
        {
            return "Opcao invalida";
        }

};

#endif