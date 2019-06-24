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
	LyricsAnalysis(int, char **, char **, char *);
	~LyricsAnalysis();

	//Methods that use lyrics files processing
	std::vector<std::string> SearchChordsFromLyrics(std::string);
	int SearchLyricsByTune(std::string, std::string);
	int SearchLyricsByNumberOfChords(std::string, int);
	int ChangeLyricsTune(std::string, int);
	int CheckIfLyricsHaveIntro(std::string);
	std::vector<std::string> IdentifyMusicAndArtistName(std::string);

	//Methods that use dictionary processing
	void SearchSimilarChordsInDict(std::string);
	void SearchModifiedChordsInDict(char);
	void SearchMajorOrMinorChordsInDict(char);

	//Debug function
	void ListFiles();
	void SetFilesList(const std::string &);

	/*Overloaded functions that have as parameter a pointer to a non-static class method
      It is used so as not to write in main function repeated loops and using the fact
      that there is a private attribute that contains the filenames, which avoids using getters
    */
	void ProcessFileList(std::vector<std::string> &, int (LyricsAnalysis::*)(std::string));

	void ProcessFileList(std::vector<std::string> (LyricsAnalysis::*)(std::string));

	void ProcessFileList(int, std::vector<std::string> &,
						 int (LyricsAnalysis::*)(std::string, int));

	void ProcessFileList(std::string, std::vector<std::string> &,
						 int (LyricsAnalysis::*)(std::string, std::string));

private:
	std::vector<std::string> *files;
	PerlWrapper *wrapper;
	PerlInterpreter *my_perl;
};

#endif