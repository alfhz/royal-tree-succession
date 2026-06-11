// Deklarasi fungsi seeder/load data

#ifndef ROYAL_H
#define ROYAL_H

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

#endif