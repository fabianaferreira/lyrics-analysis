#include "functions.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// void SearchChordsFromLyrics(PerlInterpreter *my_perl, string filename, string chord)
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

int SearchLyricsByTune(PerlInterpreter *my_perl, string tune)
{
    string filename = "/home/fabiana/Desktop/trabalho-ling-prog/cifras/sandy_junior/no_fundo_do_coracao.txt";
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

int ChangeLyricsTune(PerlInterpreter *my_perl, string filename, int offset)
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

void SearchSimilarChordsInDict(PerlInterpreter *my_perl, string chord)
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

void CheckIfLyricsHaveIntro(PerlInterpreter *my_perl, string filename)
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

    if (result == 1)
    {
        cout << "Lyrics with intro: " << filename << endl;
    }

    PUTBACK;
    FREETMPS;
    LEAVE;
}

void SearchModifiedChordsInDict(PerlInterpreter *my_perl, string modification)
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

void SearchMajorOrMinorChordsInDict(PerlInterpreter *my_perl, string modification)
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

void IdentifyMusicAndArtistName(PerlInterpreter *my_perl, string path)
{
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(path.c_str(), path.length())));
    PUTBACK;
    int count = call_pv("identifyMusicAndArtistName", G_ARRAY);
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

void ClearScreen()
{
    cout << string(100, '\n');
}

bool GetFilesList(const std::string &path, std::vector<std::string> &files, const bool showHiddenDirs = false)
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
                files.push_back(path + "/" + epdf->d_name);
            }
        }
        closedir(dpdf);
        return true;
    }
    return false;
}
