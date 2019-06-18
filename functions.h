#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "EXTERN.h"
#include "perl.h"
#include <string>
#include <vector>

int PerlCalc(PerlInterpreter *, int, int);

int SearchLyricsByTune(PerlInterpreter *, std::string);
int ChangeLyricsTune(PerlInterpreter *, std::string, int);
void SearchSimilarChordsInDict(PerlInterpreter *, std::string);
void CheckIfLyricsHaveIntro(PerlInterpreter *, std::string);
void SearchModifiedChordsInDict(PerlInterpreter *, std::string);
void SearchMajorOrMinorChordsInDict(PerlInterpreter *, std::string);
void IdentifyMusicAndArtistName(PerlInterpreter *, std::string);
void ClearScreen();

#endif
