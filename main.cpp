/*
Universidade Federal do Rio de Janeiro - UFRJ
Departamento de Engenharia Eletrônica e de Computação - DEL
Disciplina de Linguagens de Programação 2019.1
Trabalho: Gerenciador de Busca de Cifras
Alunas: Fabiana Ferreira e Tamine Alves
*/

#include <iostream>
#include <string>
// #include <iomanip>
#include <algorithm>
#include "functions.h"
#include "lyricsAnalysis.h"

using namespace std;

int opcao = 0;

int main(int argc, char **argv, char **env)
{
	LyricsAnalysis analysis(argc, argv, env, "lyricsAnalysis_v2.pl", "/home/fabiana/Desktop/trabalho-ling-prog/cifras");

	vector<string> selectedFiles;

	string opString;

	cout << "\n\n\nUFRJ - DEL - Disciplina de Linguagens de Programacao 2019.1"
		 << "\nTrabalho Gerenciador de Busca de Cifras"
		 << "\nAlunas: Fabiana Ferreira e Tamine Alves\n\n"
		 << "\n\nPrograma desenvolvido em C++ e Perl para Busca de Cifras Musicais."
		 << "\nAs buscas serão feitas em um banco de dados que contém diretórios organizados por Nome do Artista e sub diretórios com os respectivos nomes de suas músicas, cada uma com suas respectivas cifras.\n"
		 << "\nTodos os arquivos estao localizados no mesmo diretorio que este programa."
		 << endl;

	do
	{
		cout << "\n"
			 << "|--------------------------------------------------------------|\n"
			 << "|                                                              |\n"
			 << "|                             MENU                             |\n"
			 << "|                                                              |\n"
			 << "| 1. Listar músicas com seus respectivos número de acordes;    |\n"
			 << "| 2. Listar músicas com determinado número de acordes;         |\n"
			 << "| 3. Listar músicas com tom específico;                        |\n"
			 << "| 4. Aumentar ou diminuir o tom de uma música;                 |\n"
			 << "| 5. Listar acordes similares em dificuldade de execução;      |\n"
			 << "| 6. Listar músicas que tenham introdução;                     |\n"
			 << "| 7. Listar acordes modificados por sétima ou nona;            |\n"
			 << "| 8. Listar acordes modificados por maior ou menor;            |\n"
			 << "|                                                              |\n"
			 << "| 0. Para sair do programa                                     |\n"
			 << "|--------------------------------------------------------------|\n\n"
			 << endl;

		getline(cin, opString);

		while ((opString.length() != 1 || !isdigit(opString[0])) || (opString[0] - '0') > 8)
		{
			cout << "A opcao digitada nao eh valida. Tente mais uma vez ou tecle 0 para sair: \n";
			getline(cin, opString);
		}

		opcao = opString[0] - '0';

		switch (opcao)
		{

		case 1:
			analysis.ListFiles();
			break;

		case 2:
		{
			int chords;

			cout << "Digite a quantidade de acordes deseja: ";
			cin >> chords;

			analysis.ProcessFileList(chords, selectedFiles, &LyricsAnalysis::SearchLyricsByNumberOfChords);

			for (auto const file : selectedFiles)
			{
				cout << file << endl;
			}
		}
		break;

		case 3:
		{
			string tune;

			cout << "Digite o tom desejado: ";
			cin >> tune;

			analysis.ProcessFileList(tune, selectedFiles, &LyricsAnalysis::SearchLyricsByTune);

			for (auto const file : selectedFiles)
			{
				cout << file << endl;
			}
		}

		break;

		case 4:
		{
			int offset;
			string filename;

			cout << "Digite o offset desejado: ";
			cin >> offset;

			cout << "Digite o caminho completo para o arquivo: ";
			cin >> filename;

			//CHECAR SE CAMINHO EH VALIDO

			if (analysis.ChangeLyricsTune(filename, offset) == 1)
			{
				cout << "Arquivo com alteracao de tom criado com sucesso!" << endl;
			}
			else
			{
				cout << "Nao foi possivel criar o arquivo" << endl;
			}
		}
		break;

		case 5:
		{
			string chord;

			cout << "Digite o acorde para procura de similares no dicionario: ";
			cin >> chord;

			analysis.SearchSimilarChordsInDict(chord);
		}
		break;

		case 6:
		{
		}
		break;

		case 7:
		{
		}
		break;

		case 8:
		{
		}
		break;

		case 0:
			cout << "Programa Encerrado\n\n"
				 << endl;
			break;

		default:
			cout << "Nao eh uma opcao valida. \n"
				 << "Tente novamente.\n";
			break;
		}

	} while (opcao != 0);

	return 0;
}