/*
Universiade Federal do Rio de Janeiro - UFRJ
Departamento de Engenharia Eletrônica e de Computação - DEL 
Disciplina de Linguagens de Programação 2019.1
Trabalho Gerenciador de Busca de Cifras
Alunas: Fabiana Ferreira e Tamine Alves
*/

#include <iostream>
#include <string>


using namespace std;

int main () {
    //inicialização

    //invocação do perl

    int opcao = 0;
    string opString;


    cout << "\n\n\nUFRJ - DEL - Disciplina de Linguagens de Programacao 2019.1"
    << "\nTrabalho Gerenciador de Busca de Cifras"
    << "\nAlunas: Fabiana Ferreira e Tamine Alves\n\n"
	<< "\n\nPrograma desenvolvido em C++ e Perl para Busca de Cifras Musicais."
    << "\nAs buscas serão feitas em um banco de dados que contém diretórios organizados por Nome do Artista e sub diretórios com os respectivos nomes de suas músicas, cada uma com suas respectivas cifras.\n"
    << "\nTodos os arquivos estao localizados no mesmo diretorio que este programa."
	<< "\n\nBuscando arquivos...\n" << endl;

    //função que faz a busca dos diretórios e sub diretórios

    cout << "\nBusca Concluída! Vamos começar.\n\n" <<endl;

    do {
        cout << "\n" 
        <<"|--------------------------------------------------------------|\n"
        <<"|                                                              |\n"
        <<"|                             MENU                             |\n"
        <<"|                                                              |\n"
        <<"| 1. Listar músicas com seus respectivos número de acordes;    |\n"
        <<"| 2. Listar músicas com determinado número de acordes;         |\n"
        <<"| 3. Listar música tom específico;                             |\n"
        <<"| 4. Aumentar ou diminuir o tom de uma música;                 |\n"
        <<"| 5. Listar acordes similares em dificuldade de execução;      |\n"
        <<"| 6. Listar músicas que tenham introdução;                     |\n"
        <<"| 7. Listar acordes modificados por sétima ou nona;            |\n"
        <<"| 8. Listar acordes modificados por maior ou menor;            |\n"
        <<"|                                                              |\n"
        <<"| 0. Para sair do programa                                     |\n"
        <<"|--------------------------------------------------------------|\n\n" << endl;

        getline(cin, opString);

        while ((opString.length() != 1 || !isdigit(opString[0])) || (opString[0] - '0') > 8) {
			cout << "A opcao digitada nao eh valida. Tente mais uma vez ou tecle 0 para sair: \n";
			getline(cin, opString);
		}

        opcao = opString[0] - '0';

        switch (opcao) {

			case 1: 
				cout << "Funcao"<< endl;
				//chamar  
				break;

			case 2: 
				cout << "Funcao"<< endl;
				//chamar  
				break;
				
			case 3: 
				cout << "Funcao"<< endl;
				//chamar  
				break;

			case 4: 
				cout << "Funcao"<< endl;
				//chamar  
				break;

			case 5: 
				cout << "Funcao"<< endl;
				//chamar  
				break;

			case 6: 
				cout << "Funcao"<< endl;
				//chamar  
				break;

			case 7: 
				cout << "Funcao"<< endl;
				//chamar  
				break;

			case 8: 
				cout << "Funcao"<< endl;
				//chamar  
				break;

			case 0:
				cout << "Programa Encerrado\n\n" << endl;
				break;
			
			default:
				cout << "Nao eh uma opcao valida. \n"
				<< "Tente novamente.\n";
				break;
		}
	} while (opcao != 0);


    return 0;
}