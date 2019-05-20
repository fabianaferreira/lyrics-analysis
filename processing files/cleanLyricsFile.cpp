#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <sstream>
#include <dirent.h>
#include <fstream>

#define EXTENSION "txt"

using namespace std;

string getFileExtension(const string s)
{

  size_t i = s.rfind('.', s.length());
  if (i != string::npos)
  {
    return (s.substr(i + 1, s.length() - i));
  }

  return ("");
}

bool getFilesList(const string &path, vector<string> &files, const bool showHiddenDirs = false)
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
        string extension = getFileExtension(string(epdf->d_name));
        if (extension.compare(EXTENSION) == 0)
          files.push_back(path + "/" + epdf->d_name);
      }
    }
    closedir(dpdf);
    return true;
  }
  return false;
}

int main()
{
  string input;

  cout << endl;

  cout << "Digite o nome do diretorio a ser usado (caminho completo, nao o relativo): ";
  getline(cin, input);

  if (input.length() == 0)
  {
    cout << "Campo invalido" << endl;
  }
  vector<string> files;
  bool listResult = getFilesList(input, files, false);

  fstream fs;
  fs.open("nomesArquivos.txt", fstream::out);

  for (auto file : files)
  {

    fs << file << endl;
  }
  fs.close();

  cout << "Arquivo gerado com sucesso!" << endl;

  return 0;
}
