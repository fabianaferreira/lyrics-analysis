/*
Universidade Federal do Rio de Janeiro - UFRJ
Departamento de Engenharia Eletrônica e de Computação - DEL
Disciplina de Linguagens de Programação 2019.1
Trabalho: Gerenciador de Busca de Cifras
Alunas: Fabiana Ferreira e Tamine Alves
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "functions.h"
#include "exceptions.h"
#include "lyricsAnalysis.h"

using namespace std;

int optMenu = 0;

int main(int argc, char **argv, char **env)
{
	string path, opString;
	char directoryOption;
	vector<string> selectedFiles;

	LyricsAnalysis analysis(argc, argv, env, "lyricsAnalysis_v2.pl");

	try
	{
		path = getTabsPath(argv[0]);
		cin.ignore();
	}
	catch (InvalidOption &e)
	{
		cout << e.detailException() << endl;
		cout << "Saindo do programa.";
		getKeyPressed();
		exit(-1);
	}

	try
	{
		analysis.SetFilesList(path);
	}

	catch (InvalidDirectory &e)
	{
		cout << e.detailException() << endl;
		exit(-1);
	}

	/*-------------------------------------- HEADER --------------------------------------*/
	cout << "\n\n\nUFRJ - DEL - Disciplina de Linguagens de Programacao 2019.1"
		 << "\nTrabalho Gerenciador de Busca de Cifras"
		 << "\nAlunas: Fabiana Ferreira e Tamine Alves\n\n"
		 << "\n\nPrograma desenvolvido em C++ e Perl para Busca de Cifras Musicais."
		 << "\nAs buscas serão feitas em um banco de dados que contém diretórios organizados por Nome do Artista e sub diretórios com os respectivos nomes de suas músicas, cada uma com suas respectivas cifras.\n"
		 << "\nTodos os arquivos estao localizados no mesmo diretorio que este programa."
		 << endl;
	/*------------------------------------------------------------------------------------*/

	do
	{
		/*-------------------------------------- MENU --------------------------------------*/
		cout << "\n"
			 << "|--------------------------------------------------------------|\n"
			 << "|                                                              |\n"
			 << "|                             MENU                             |\n"
			 << "|                                                              |\n"
			 << "| 1. Listar músicas com seus respectivos número de acordes;    |\n"
			 << "| 2. Listar músicas com determinado número de acordes;         |\n"
			 << "| 3. Listar músicas com tom específico;                        |\n"
			 << "| 4. Aumentar ou diminuir o tom de uma música;                 |\n"
			 << "| 5. Listar músicas que tenham introdução;                     |\n"
			 << "| 6. Checar se determinada música tem introdução;              |\n"
			 << "| 7. Listar acordes similares em dificuldade de execução;      |\n"
			 << "| 8. Listar acordes modificados por sétima ou nona;            |\n"
			 << "| 9. Listar acordes modificados por maior ou menor;            |\n"
			 << "|                                                              |\n"
			 << "| 0. Para sair do programa                                     |\n"
			 << "|--------------------------------------------------------------|\n\n";
		/*----------------------------------------------------------------------------------*/

		cout << "Opcao: ";
		// getline(cin, opString);
		cin >> opString;
		// cin.ignore();

		while ((opString.length() != 1 || !isdigit(opString[0])) || (opString[0] - '0') > 9)
		{
			cout << "A opcao digitada nao eh valida. Tente mais uma vez ou tecle 0 para sair: \n";
			getline(cin, opString);
		}

		optMenu = opString[0] - '0';

		switch (optMenu)
		{

		case 1:
		{
			analysis.ProcessFileList(&LyricsAnalysis::SearchChordsFromLyrics);

			getKeyPressed();
		}
		break;

		case 2:
		{
			cout << "Entre com o número de acordes desejado: ";
			int number = getNumberOfChords();

			while (number < 0)
				number = getNumberOfChords();

			//Back to main menu
			if (number == 0)
				break;

			analysis.ProcessFileList(number, selectedFiles, &LyricsAnalysis::SearchLyricsByNumberOfChords);

			if (selectedFiles.size() > 0)
			{
				cout << "\nArquivos com o numero de acordes desejado:" << endl;
				for (auto const file : selectedFiles)
				{
					cout << file << endl;
				}
				getKeyPressed();
			}
			else
			{
				cout << "Nao foram encontrados arquivos com o numero desejado de acordes ";
				getKeyPressed();
			}
		}
		break;

		case 3:
		{
			analysis.ProcessFileList(getTune(), selectedFiles, &LyricsAnalysis::SearchLyricsByTune);

			if (selectedFiles.size() > 0)
			{
				cout << "\nArquivos com o tom desejado:" << endl;
				for (auto const file : selectedFiles)
				{
					cout << file << endl;
				}
				getKeyPressed();
			}
			else
			{
				cout << "Nao foram encontrados arquivos com o tom desejado. ";
				getKeyPressed();
			}
		}

		break;

		case 4:
		{
			string lyrics;
			try
			{
				lyrics = getFileName();
			}
			catch (InvalidFileExtension &e)
			{
				cout << e.detailException() << endl;
				getKeyPressed();
				break;
			}
			catch (InvalidFilePath &e)
			{
				cout << e.detailException() << endl;
				getKeyPressed();
				break;
			}
			int offset = getOffset();

			while (offset == 20)
				offset = getOffset();

			//Back to main menu
			if (offset == 0)
				break;

			if (analysis.ChangeLyricsTune(lyrics, offset) == 1)
			{
				cout << "Arquivo criado com sucesso! ";
				getKeyPressed();
			}
			else
			{
				cout << "Nao foi possivel criar o arquivo. ";
				getKeyPressed();
			}
		}
		break;

		case 5:
		{
			analysis.ProcessFileList(selectedFiles, &LyricsAnalysis::CheckIfLyricsHaveIntro);

			if (selectedFiles.size() > 0)
			{
				cout << "As seguintes musicas tem introducao: " << endl;
				for (auto const file : selectedFiles)
				{
					vector<string> musicAndArtist = analysis.IdentifyMusicAndArtistName(file);
					cout << "(" << musicAndArtist.at(0) << " | " << musicAndArtist.at(1) << ")" << endl;
				}
				getKeyPressed();
			}
			else
			{
				cout << "Nao foram encontradas musicas com introducao. ";
				getKeyPressed();
			}
		}
		break;

		case 6:
		{
			string filename;
			try
			{
				filename = getFileName();
			}
			catch (InvalidFileExtension &e)
			{
				cout << e.detailException() << endl;
				getKeyPressed();
				break;
			}
			catch (InvalidFilePath &e)
			{
				cout << e.detailException() << endl;
				getKeyPressed();
				break;
			}

			if (analysis.CheckIfLyricsHaveIntro(filename))
			{
				vector<string> musicAndArtist = analysis.IdentifyMusicAndArtistName(filename);
				cout << "A musica "
					 << " (" << musicAndArtist.at(0) << " | " << musicAndArtist.at(1)
					 << ") tem introducao" << endl;
			}
			else
			{
				cout << "A musica informada nao tem introducao." << endl;
			}
			getKeyPressed();
		}
		break;

		case 7:
		{
			analysis.SearchSimilarChordsInDict(getChord());
			getKeyPressed();
		}

		break;

		case 8:
		{
			char modification = getModification(false);

			while (modification == 'E')
				modification = getModification(false);

			//Back to main menu
			if (modification == '0')
				break;

			analysis.SearchModifiedChordsInDict(modification);

			getKeyPressed();
		}
		break;

		case 9:
		{
			char modification = getModification(true);

			while (modification == 'E')
				modification = getModification(true);

			//Back to main menu
			if (modification == '0')
				break;

			analysis.SearchMajorOrMinorChordsInDict(modification);

			getKeyPressed();
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
	} while (optMenu != 0);

	return 0;
}