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
	return  path + "/cifras";
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

int getNumberOfChords(){
    int numberOfChords = 0;

    while (numberOfChords < 0) {
        cout << "Entre com o número de acordes desejado." << endl;
        cout << "Retornaremos uma lista com as músicas que possuem essa quantidade de acordes." << endl;
        cin >> numberOfChords;
        cout << "Entrada inválida." << endl; 
        cout << "\n Entre com um inteiro positivo ou com 0 para voltar ao menu." << endl;
    }
    return numberOfChords;
}

string getTune() {
    string optTune;

    cout << "Insira o tom desejado, procuraremos músicas com esse tom pra você." << endl;
    cin >> optTune;

    return optTune;
}

int getOffset() {
    int offset;

    while (offset < -20 || offset > 20) {
	cout << "Digite o offset desejado (deve ser um inteiro). ";
    cout << "Criaremos um rquivo com alteracao de tom!" << endl;
	cin >> offset;
    cout << "Entrada inválida." << endl; 
    cout << "\n Entre com outro inteiro ou com 0 para voltar ao menu." << endl;
    }
    return offset;
}

string getFileName() {
    string filename;
	
    cout << "Digite o caminho completo para o arquivo: ";		
    cin >> filename;

    return filename;
}

string getChord() {
    string chord;
	
    cout << "Digite o acorde desejado: ";		
    cin >> chord;

    return chord;
}
