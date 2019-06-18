#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "functions.h"
#include "exceptions.h"

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

//     Pokemon pokemon;

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
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(tune.c_str(), tune.length()))); // Passa a string e o tamanho
    PUTBACK;
    int count = call_pv("searchLyricsByTune", G_SCALAR);
    SPAGAIN;

    int result = POPi;

    PUTBACK;
    FREETMPS;
    LEAVE;

    return result;
}

void ChangeLyricsTune(PerlInterpreter *my_perl, string filename, int offset)
{
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    XPUSHs(sv_2mortal(newSVpv(filename.c_str(), filename.length())));
    XPUSHs(sv_2mortal(newSViv(offset));
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
    XPUSHs(sv_2mortal(newSVpv(chord.c_str(), chord.length()))); // Passa a string e o tamanho
    PUTBACK;
    int count = call_pv("searchSimilarChordsInDict", G_ARRAY); // Count guarda quantas coisas foram retornadas, cada um é elemento da string
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
    int count = call_pv("CheckIfLyricsHaveIntro", G_SCALAR);
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
    int count = call_pv("SearchModifiedChordsInDict", G_ARRAY);
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
    int count = call_pv("SearchMajorOrMinorChordsInDict", G_ARRAY);
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
    int count = call_pv("IdentifyMusicAndArtistName", G_ARRAY);
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
