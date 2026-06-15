#include "royal.h"

// Fungsi untuk membuat tree baru
void Create_tree(Tree *T) {
    *T = Nil;
}

// Alokasi memori untuk node baru
address Alokasi(int id, char *name, int birth_year, int death_year, char gender, char *title, int birth_order, int eligible) {
    address P = (address) malloc(sizeof(RoyalMember));
    if (P != Nil) {
        Id(P)          = id;
        BirthYear(P)   = birth_year;
        DeathYear(P)   = death_year;
        Gender(P)      = gender;
        BirthOrder(P)  = birth_order;
        Eligible(P)    = eligible;
        Excluded(P)    = 0; // Inisialisasi default tidak dieksklusi

        strncpy(Name(P),  name,  MAX_NAME  - 1);
        strncpy(Title(P), title, MAX_TITLE - 1);
        Name(P)[MAX_NAME   - 1] = '\0';
        Title(P)[MAX_TITLE - 1] = '\0';

        FirstSon(P)    = Nil;
        NextBrother(P) = Nil;
        Parent(P)      = Nil;
    }
    return P;
}

// Cek apakah tree kosong
int IsEmpty(Tree T) {
    return (T == Nil);
}

// Fungsi untuk menambahkan child ke parent
void AddChild(address parent, address child) {
    if (parent != Nil && child != Nil) {
        Parent(child) = parent;
        if (FirstSon(parent) == Nil) {
            /* Jika parent belum punya anak sama sekali */
            FirstSon(parent) = child;
        } else {
            /* Jika sudah ada anak, tambahkan di ujung sibling */
            address temp = FirstSon(parent);
            while (NextBrother(temp) != Nil) {
                temp = NextBrother(temp);
            }
            NextBrother(temp) = child;
        }
    }
}

// Fungsi untuk dealokasi memori tree
void DeAlokasi(Tree *T) {
    if (*T != Nil) {
        DeAlokasi(&(FirstSon(*T)));
        DeAlokasi(&(NextBrother(*T)));
        free(*T);
        *T = Nil;
    }
}

// Fungsi untuk membangun tree keluarga kerajaan dengan data hardcoded
void BuildTree(RoyalFamilyTree *tree) {
 
    /* ── Generasi 0: Root ── */
    address elizabeth = Alokasi(1,  "Queen Elizabeth II", 1926, 2022, 'F', "Queen",    0, 1);
 
    /* ── Generasi 1: Anak Elizabeth II ── */
    address charles  = Alokasi(2,  "King Charles III",   1948, 0, 'M', "King",     1, 1);
    address anne     = Alokasi(3,  "Princess Anne",      1950, 0, 'F', "Princess", 2, 1);
    address andrew   = Alokasi(4,  "Prince Andrew",      1960, 0, 'M', "Prince",   3, 1);
    address edward   = Alokasi(5,  "Prince Edward",      1964, 0, 'M', "Prince",   4, 1);
 
    /* ── Generasi 2: anak Charles ── */
    address william  = Alokasi(6,  "Prince William",     1982, 0, 'M', "Prince",   1, 1);
    address harry    = Alokasi(7,  "Prince Harry",       1984, 0, 'M', "Prince",   2, 1);
 
    /* ── Generasi 2: anak Anne ── */
    address peter    = Alokasi(8,  "Peter Phillips",     1977, 0, 'M', "Mr",       1, 1);
    address zara     = Alokasi(9,  "Zara Tindall",       1981, 0, 'F', "Mrs",      2, 1);
 
    /* ── Generasi 2: anak Andrew ── */
    address beatrice = Alokasi(10, "Princess Beatrice",  1988, 0, 'F', "Princess", 1, 1);
    address eugenie  = Alokasi(11, "Princess Eugenie",   1990, 0, 'F', "Princess", 2, 1);
 
    /* ── Generasi 2: anak Edward ── */
    address louise   = Alokasi(12, "Lady Louise Windsor",   2003, 0, 'F', "Lady", 1, 1);
    address james    = Alokasi(13, "James Viscount Severn", 2007, 0, 'M', "Mr",   2, 1);
 
    /* ── Generasi 3: anak William ── */
    address george    = Alokasi(14, "Prince George",      2013, 0, 'M', "Prince",   1, 1);
    address charlotte = Alokasi(15, "Princess Charlotte", 2015, 0, 'F', "Princess", 2, 1);
    address louis     = Alokasi(16, "Prince Louis",       2018, 0, 'M', "Prince",   3, 1);
 
    /* ── Generasi 3: anak Harry ── */
    address archie   = Alokasi(17, "Archie Mountbatten-Windsor",  2019, 0, 'M', "Mr", 1, 1);
    address lilibet  = Alokasi(18, "Lilibet Mountbatten-Windsor", 2021, 0, 'F', "Ms", 2, 1);
 
    /* ── Susun hubungan parent-child ── */
    AddChild(elizabeth, charles);
    AddChild(elizabeth, anne);
    AddChild(elizabeth, andrew);
    AddChild(elizabeth, edward);
 
    AddChild(charles, william);
    AddChild(charles, harry);
 
    AddChild(anne, peter);
    AddChild(anne, zara);
 
    AddChild(andrew, beatrice);
    AddChild(andrew, eugenie);
 
    AddChild(edward, louise);
    AddChild(edward, james);
 
    AddChild(william, george);
    AddChild(william, charlotte);
    AddChild(william, louis);
 
    AddChild(harry, archie);
    AddChild(harry, lilibet);
 
    tree->root = elizabeth;
    tree->size = 18;
}