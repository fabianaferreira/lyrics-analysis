/*
Universidade Federal do Rio de Janeiro - UFRJ
Departamento de Engenharia Eletrônica e de Computação - DEL
Disciplina de Linguagens de Programação 2019.1
Trabalho: Gerenciador de Busca de Cifras
Alunas: Fabiana Ferreira e Tamine Alves
*/

#ifndef LYRICSANALYSIS_H
#define LYRICSANALYSIS_H

#include <string>
#include <vector>
#include <iostream>
#include "perlWrapper.h"

class LyricsAnalysis
{
public:
    LyricsAnalysis(int, char **, char **, char *, const std::string &);
    ~LyricsAnalysis();

    void SearchChordsFromLyrics(std::string, std::string);
    int SearchLyricsByTune(std::string);
    int ChangeLyricsTune(std::string, int);
    void SearchSimilarChordsInDict(std::string);
    void CheckIfLyricsHaveIntro(std::string);
    void SearchModifiedChordsInDict(std::string);
    void SearchMajorOrMinorChordsInDict(std::string);
    void IdentifyMusicAndArtistName(std::string);
    void ListFiles();

private:
    std::vector<std::string> *files;
    PerlWrapper *wrapper;
    PerlInterpreter *my_perl;
};

#endif