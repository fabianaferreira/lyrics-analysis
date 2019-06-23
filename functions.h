/*
Universidade Federal do Rio de Janeiro - UFRJ
Departamento de Engenharia Eletrônica e de Computação - DEL
Disciplina de Linguagens de Programação 2019.1
Trabalho: Gerenciador de Busca de Cifras
Alunas: Fabiana Ferreira e Tamine Alves
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

std::string GetTabsPath(std::string);
void ClearScreen();
bool GetFilesList(const std::string &, std::vector<std::string> *, const bool);

int getNumberOfChords();
std::string getTune();
int getOffset();
std::string getFileName();
std::string getChord();


#endif
