#ifndef NBTROYAL_H
#define NBTROYAL_H

#include "../data/royal.h"

void PreOrder(Tree T);
void PostOrder(Tree T);
void InOrder(Tree T);
void LevelOrder(Tree T);
void PrintTree(Tree T);

address SearchByName(Tree T, char *target_name);
address SearchById(Tree T, int target_id);

int NbElmt(Tree T);
int NbKeturunan(Tree T); 
int Level(Tree T, char *target_name);
int Depth(Tree T);
int Max(int a, int b);

void MenuSuksesi(Tree T);
void MenuGenerasi(Tree T);
void MenuCari(Tree T);
void MenuHitungKeturunan(Tree T);
void MenuSimulasiEksklusi(Tree T);

#endif