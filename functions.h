#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <EXTERN.h>
#include <perl.h>
#include <string>
#include <vector>

int PerlCalc(PerlInterpreter *, int, int);

int SearchLyricsByTune(PerlInterpreter *, string);
void ChangeLyricsTune(PerlInterpreter *, string, int);
void SearchSimilarChordsInDict(PerlInterpreter *, string);
void CheckIfLyricsHaveIntro(PerlInterpreter *, string);
void SearchModifiedChordsInDict(PerlInterpreter *, string);
void SearchMajorOrMinorChordsInDict(PerlInterpreter *, string);
void IdentifyMusicAndArtistName(PerlInterpreter *, string);
void ClearScreen();

#endif
