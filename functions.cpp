/*
Universidade Federal do Rio de Janeiro - UFRJ
Departamento de Engenharia Eletrônica e de Computação - DEL
Disciplina de Linguagens de Programação 2019.1
Trabalho: Gerenciador de Busca de Cifras
Alunas: Fabiana Ferreira e Tamine Alves
*/

#include <iostream>
#include <string>
#include <vector>
#include "functions.h"

using namespace std;

void clearScreen()
{
    cout << string(100, '\n');
}

void getKeyPressed()
{
    cin.ignore();
    cout << "\n\nPressione qualquer tecla para exibir o menu novamente...";
    getchar();
}

string getTabsPath(string executablePath)
{
    string path;
    char directoryOption;

    cout << "Voce deseja selecionar um diretorio existente das cifras? (y/n) ";
    cin >> directoryOption;

    if (directoryOption == 'y')
    {
        cout << "Digite o caminho completo do diretorio: ";
        cin >> path;
        return path;
    }
    if (directoryOption == 'n')
    {
        size_t found = executablePath.find_last_of("/");
        string path = executablePath.substr(0, found);
        return path + "/cifras";
    }
    throw InvalidOption();
}

bool getFilesList(const string &path, vector<string> *files, const bool showHiddenDirs = false)
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
                getFilesList(path + "/" + epdf->d_name, files, showHiddenDirs);
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

int getNumberOfChords()
{
    int numberOfChords;

    cin >> numberOfChords;

    if (numberOfChords < 0)
    {
        cout << "Entrada invalida. Entre com um inteiro positivo ou com 0 para voltar ao menu: ";

        return -1;
    }
    return numberOfChords;
}

string getLyrics()
{
    string lyrics;
    cout << "Qual musica voce deseja mudar o tom (caminho completo, inclusive a extensao '.txt') ? ";
    cin >> lyrics;
}

string getTune()
{
    string optTune;

    cout << "Insira o tom desejado, procuraremos músicas com esse tom pra você: ";
    cin >> optTune;

    return optTune;
}

int getOffset()
{
    int offset;

    cout << "Entre com o offset desejado: ";
    cin >> offset;

    if (offset < -11 || offset > 11)
    {
        cout << "Entrada invalida. Entre com um inteiro entre -11 e 11 ou com 0 para voltar ao menu: ";
        return 20;
    }
    return offset;
}

string getFileName()
{
    string filename;

    cout << "Digite o caminho completo para o arquivo: ";
    cin >> filename;

    size_t found = filename.find(".txt");

    if (found != string::npos)
    {
        ifstream infile(filename.c_str());
        if (infile.good())
            return filename;
        throw InvalidFilePath();
    }
    throw InvalidFileExtension();
}

string getChord()
{
    string chord;

    cout << "Digite o acorde desejado: ";
    cin >> chord;

    return chord;
}

char getModification(bool isMajorMinor)
{
    char modification;

    string specificModification = isMajorMinor ? "maior (M/+) ou menor (m)" : "setima (7) ou nona (9)";

    cout << "Digite a modificacao " << specificModification << " a ser procurada: ";
    cin >> modification;

    if (isMajorMinor)
    {
        if (modification != 'M' && modification != '+' && modification != 'm' && modification != '0')
        {
            cout << "Entrada invalida. Digite um caractere correto (M, + ou m) ou 0 para voltar ao menu: ";
            return 'E';
        }
    }
    else
    {
        if (modification != '7' && modification != '9' && modification != '0')
        {
            cout << "Entrada invalida. Digite um caractere correto (7 ou 9) ou 0 para voltar ao menu: ";
            return 'E';
        }
    }

    return modification;
}