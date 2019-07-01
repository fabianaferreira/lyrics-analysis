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

class InvalidDirectory : public LyricsAnalysisException
{
public:
    virtual std::string detailException() const throw()
    {
        return "ERRO: Caminho para o diretorio dos arquivos de cifras invalido.";
    }
};

class InvalidFilePath : public LyricsAnalysisException
{
    public:
        virtual std::string detailException() const throw()
        {
            return "ERRO: Caminho de arquivo digitado eh invalido.";
        }

};

class InvalidFileExtension : public LyricsAnalysisException
{
public:
    virtual std::string detailException() const throw()
    {
        return "ERRO: Extensao do arquivo invalida";
    }
};

class InvalidOption : public LyricsAnalysisException
{
    public:
        virtual std::string detailException() const throw()
        {
            return "ERRO: Opcao invalida";
        }

};

#endif