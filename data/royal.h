#ifndef ROYAL_H
#define ROYAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_TITLE 50
#define Nil NULL
#define Id(T)          (T)->id
#define Name(T)        (T)->name
#define BirthYear(T)   (T)->birth_year
#define DeathYear(T)   (T)->death_year
#define Gender(T)      (T)->gender
#define Title(T)       (T)->title
#define BirthOrder(T)  (T)->birth_order
#define Eligible(T)    (T)->eligible
#define Excluded(T)    (T)->excluded_temp
#define FirstSon(T)    (T)->fs
#define NextBrother(T) (T)->nb
#define Parent(T)      (T)->pr

// Deklarasi variabel Pointer
typedef struct RoyalMember* address;
typedef address Tree;

// Struktur Node untuk menyimpan informasi tentang anggota keluarga kerajaan
typedef struct RoyalMember {
    int id; 
    char name[MAX_NAME];
    int birth_year;
    int death_year;
    char gender;
    char title[MAX_TITLE];
    int birth_order;
    int eligible;
    int excluded_temp; // untuk simulasi pengecualian sementara
    
    address fs;
    address nb;
    address pr;
} RoyalMember;

typedef struct {
    RoyalMember *root;
    int size;
} RoyalFamilyTree;

// Fungsi untuk membuat tree baru
void Create_tree(Tree *T);

// Alokasi memori untuk node baru
address Alokasi(int id, char *name, int birth_year, int death_year, char gender, char *title, int birth_order, int eligible);

// Cek apakah tree kosong
int IsEmpty(Tree T);

// Fungsi untuk menambahkan child ke parent
void AddChild(address parent, address child);

// Fungsi untuk dealokasi memori tree
void DeAlokasi(Tree *T);

// Fungsi untuk membangun tree keluarga kerajaan dengan data hardcoded
void BuildTree(RoyalFamilyTree *tree);

#endif