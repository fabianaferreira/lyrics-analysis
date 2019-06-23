/*
Universidade Federal do Rio de Janeiro - UFRJ
Departamento de Engenharia Eletrônica e de Computação - DEL
Disciplina de Linguagens de Programação 2019.1
Trabalho: Gerenciador de Busca de Cifras
Alunas: Fabiana Ferreira e Tamine Alves
*/

#include "functions.h"
#include "lyricsAnalysis.h"

using namespace std;

LyricsAnalysis::LyricsAnalysis(int argc, char **argv, char **env, char *filename, const std::string &path)
{
    wrapper = new PerlWrapper(argc, argv, env, filename);
    my_perl = wrapper->alloc();
    wrapper->run();

    files = new vector<string>();

    //Getting files' list
    cout << "\n\nBuscando arquivos..." << endl;
    if (GetFilesList(path, files, false))
    {
        cout << "\nBusca Concluída! Vamos começar.\n\n"
             << endl;
    }
    else
    {
        cout << "Houve um problema na leitura do arquivo" << endl;
        //JOGAR EXCECAO
    }
}
LyricsAnalysis::~LyricsAnalysis()
{
    delete wrapper;
    delete files;
}

void LyricsAnalysis::ListFiles()
{
    vector<string>::iterator it;
    for (it = files->begin(); it != files->end(); ++it)
    {
        cout << (*it) << endl;
    }
}

// void LyricsAnalysis::SearchChordsFromLyrics(string filename, string chord)
// {
//     dSP;
//     ENTER;
//     SAVETMPS;
//     PUSHMARK(SP);
//     XPUSHs(sv_2mortal(newSVpv(filename.c_str(), filename.length()))); // Passa a string e o tamanho
//     XPUSHs(sv_2mortal(newSVpv(chord.c_str(), chord.length())));       // Passa a string e o tamanho

//     PUTBACK;
//     int count = call_pv("searchChordsFromLyrics", G_ARRAY); // Count guarda quantas coisas foram retornadas, cada um é elemento da string
//     SPAGAIN;

//     for (int i = 0; i < count; i++)
//     {
//         string return_value = POPp;
//         cout << return_value << endl;
//     }

//     PUTBACK;
//     FREETMPS;
//     LEAVE;
// }

int LyricsAnalysis::SearchLyricsByNumberOfChords(string filename, int number)
{
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(filename.c_str(), filename.length())));
    XPUSHs(sv_2mortal(newSVuv(number)));
    PUTBACK;
    int count = call_pv("searchLyricsByNumberOfChords", G_SCALAR);
    SPAGAIN;

    int result = POPi;

    PUTBACK;
    FREETMPS;
    LEAVE;

    return result;
}

int LyricsAnalysis::SearchLyricsByTune(string filename, string tune)
{
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(filename.c_str(), filename.length())));
    XPUSHs(sv_2mortal(newSVpv(tune.c_str(), tune.length())));
    PUTBACK;
    int count = call_pv("searchLyricsByTune", G_SCALAR);
    SPAGAIN;

    int result = POPi;

    PUTBACK;
    FREETMPS;
    LEAVE;

    return result;
}

int LyricsAnalysis::ChangeLyricsTune(string filename, int offset)
{
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(filename.c_str(), filename.length())));
    XPUSHs(sv_2mortal(newSViv(offset)));
    PUTBACK;
    int count = call_pv("changeLyricsTune", G_SCALAR);
    SPAGAIN;

    int result = POPi;

    PUTBACK;
    FREETMPS;
    LEAVE;

    return result;
}

int LyricsAnalysis::CheckIfLyricsHaveIntro(string filename)
{
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(filename.c_str(), filename.length())));
    PUTBACK;
    int count = call_pv("checkIfLyricsHaveIntro", G_SCALAR);
    SPAGAIN;

    int result = POPi;

    return result;

    PUTBACK;
    FREETMPS;
    LEAVE;
}

int LyricsAnalysis::IdentifyMusicAndArtistName(string path)
{
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(path.c_str(), path.length())));
    PUTBACK;
    int count = call_pv("identifyMusicAndArtistName", G_ARRAY);
    SPAGAIN;

    if (count > 0)
    {
        for (int i = 0; i < count; i++)
        {
            char *return_value = POPp;
            cout << return_value << endl;
        }
        return 1;
    }
    return 0;

    PUTBACK;
    FREETMPS;
    LEAVE;
}

void LyricsAnalysis::SearchSimilarChordsInDict(string chord)
{
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(chord.c_str(), chord.length())));
    PUTBACK;
    int count = call_pv("searchSimilarChordsInDict", G_ARRAY);
    SPAGAIN;

    for (int i = 0; i < count; i++)
    {
        char *return_value = POPp;
        cout << return_value << endl;
    }

    PUTBACK;
    FREETMPS;
    LEAVE;
}

void LyricsAnalysis::SearchModifiedChordsInDict(string modification)
{
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(modification.c_str(), modification.length())));
    PUTBACK;
    int count = call_pv("searchModifiedChordsInDict", G_ARRAY);
    SPAGAIN;

    for (int i = 0; i < count; i++)
    {
        char *return_value = POPp;
        cout << return_value << endl;
    }

    PUTBACK;
    FREETMPS;
    LEAVE;
}

void LyricsAnalysis::SearchMajorOrMinorChordsInDict(string modification)
{
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(modification.c_str(), modification.length())));
    PUTBACK;
    int count = call_pv("searchMajorOrMinorChordsInDict", G_ARRAY);
    SPAGAIN;

    for (int i = 0; i < count; i++)
    {
        char *return_value = POPp;
        cout << return_value << endl;
    }

    PUTBACK;
    FREETMPS;
    LEAVE;
}

void LyricsAnalysis::ProcessFileList(int argument, vector<string> &selectedFiles,
                                     int (LyricsAnalysis::*f)(string, int))
{
    // Clears vector, so as not to contains previous results as elements
    selectedFiles.clear();
    for (auto const string file : *files)
    {
        if ((this->*f)(file, argument) == 1)
        {
            selectedFiles.push_back(file);
        }
    }
}

void LyricsAnalysis::ProcessFileList(string argument, vector<string> &selectedFiles,
                                     int (LyricsAnalysis::*f)(string, string))
{
    // Clears vector, so as not to contains previous results as elements
    selectedFiles.clear();
    for (auto const string file : *files)
    {
        if ((this->*f)(file, argument) == 1)
        {
            selectedFiles.push_back(file);
        }
    }
}