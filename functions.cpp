/*
Universidade Federal do Rio de Janeiro - UFRJ
Departamento de Engenharia Eletrônica e de Computação - DEL
Disciplina de Linguagens de Programação 2019.1
Trabalho: Gerenciador de Busca de Cifras
Alunas: Fabiana Ferreira e Tamine Alves
*/

#include "functions.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void ClearScreen()
{
    cout << string(100, '\n');
}

string GetTabsPath(string executablePath) {
	size_t found = executablePath.find_last_of("/");
	string path = executablePath.substr(0,found);
	return  path + "/cifraaas";
}

bool GetFilesList(const std::string &path, std::vector<std::string> *files, const bool showHiddenDirs = false)
{
    DIR *dpdf;
    struct dirent *epdf;
    dpdf = opendir(path.c_str());
    if (dpdf != NULL)
    {
        while ((epdf = readdir(dpdf)) != NULL)
        {
            if (showHiddenDirs ? (epdf->d_type == DT_DIR && string(epdf->d_name) != ".." && string(epdf->d_name) != ".") : (epdf->d_type == DT_DIR && strstr(epdf->d_name, "..") == NULL && strstr(epdf->d_name, ".") == NULL))
            {
                GetFilesList(path + "/" + epdf->d_name, files, showHiddenDirs);
            }
            if (epdf->d_type == DT_REG)
            {
                // string extension = getFileExtension(string(epdf->d_name));
                // if (extension.compare(EXTENSION) == 0)
                files->push_back(path + "/" + epdf->d_name);
            }
        }
        closedir(dpdf);
        return true;
    }
    return false;
}