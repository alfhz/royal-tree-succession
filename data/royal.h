#ifndef ROYAL_H
#define ROYAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_TITLE 50

// Deklarasi variabel Pointer
typedef struct RoyalMember* address;

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
    
    address *fs;
    address *nb;
    address *pr;
} RoyalMember;

typedef struct {
    RoyalMember *root;
    int size;
} RoyalFamilyTree;

// Fungsi untuk membuat node baru
RoyalMember* create_node(int id, char *name, int birth_year, int death_year, char gender, char *title, int birth_order, int eligible);

// Fungsi untuk menambahkan anggota keluarga kerajaan ke dalam pohon
void add_child(RoyalMember *parent, RoyalMember *child);

// Fungsi untuk membebaskan memori yang digunakan oleh pohon keluarga kerajaan
void free_tree(RoyalMember *node);

// Fungsi untuk membangun pohon keluarga kerajaan Inggris
void build_tree(RoyalFamilyTree *tree);

#endif