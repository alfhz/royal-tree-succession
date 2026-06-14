#include "nbtRoyal.h"

// Menampilkan tree secara pre-order (Root -> First Son -> Next Brother)
void PreOrder(Tree T) {
    if (!IsEmpty(T)) {
        printf("- %s (%s)\n", Name(T), Title(T));
        PreOrder(FirstSon(T));    
        PreOrder(NextBrother(T)); 
    }
}

// Menampilkan tree secara post-order (First Son -> Next Brother -> Root)
void PostOrder(Tree T) {
    if (!IsEmpty(T)) {
        PostOrder(FirstSon(T));    
        PostOrder(NextBrother(T)); 
        printf("- %s (%s)\n", Name(T), Title(T)); 
    }
}

// Menampilkan tree secara in-order (First Son -> Root -> Next Brother)
void InOrder(Tree T) {
    if (!IsEmpty(T)) {
        InOrder(FirstSon(T));
        printf("- %s (%s)\n", Name(T), Title(T));
        InOrder(NextBrother(T));
    }
}

// Menampilkan tree berdasarkan level atau generasi menggunakan antrian array inline
void LevelOrder(Tree T) {
    if (IsEmpty(T)) return;
    
    address queue[100];
    int front = 0, rear = 0;
    
    queue[rear++] = T;
    
    while (front < rear) {
        address current = queue[front++];
        printf("- %s (%s)\n", Name(current), Title(current));
        
        address child = FirstSon(current);
        while (child != Nil) {
            queue[rear++] = child;
            child = NextBrother(child);
        }
    }
}

// Menampilkan informasi detail struktur node dan hubungannya secara rekursif
void PrintTree(Tree T) {
    if (IsEmpty(T)) return;

    printf("========================================\n");
    printf("ID          : %d\n", Id(T));
    printf("Nama        : %s %s\n", Title(T), Name(T));
    
    if (FirstSon(T) != Nil)
        printf("Anak Sulung : %s\n", Name(FirstSon(T)));
    else
        printf("Anak Sulung : [Tidak ada]\n");
        
    if (NextBrother(T) != Nil)
        printf("Saudara Next: %s\n", Name(NextBrother(T)));
    else
        printf("Saudara Next: [Tidak ada]\n");
        
    if (Parent(T) != Nil)
        printf("Orang Tua   : %s\n", Name(Parent(T)));
    else
        printf("Orang Tua   : [Leluhur Utama]\n");
        
    printf("========================================\n\n");

    PrintTree(FirstSon(T));
    PrintTree(NextBrother(T));
}

// Mencari node anggota kerajaan berdasarkan nama
address SearchByName(Tree T, char *target_name) {
    if (IsEmpty(T)) return Nil;
    
    if (strcmp(Name(T), target_name) == 0) return T;
    
    address found = SearchByName(FirstSon(T), target_name);
    if (found != Nil) return found;
    
    return SearchByName(NextBrother(T), target_name);
}

// Mencari node anggota kerajaan berdasarkan ID
address SearchById(Tree T, int target_id) {
    if (IsEmpty(T)) return Nil;
    if (Id(T) == target_id) return T;
    
    address found = SearchById(FirstSon(T), target_id);
    if (found != Nil) return found;
    
    return SearchById(NextBrother(T), target_id);
}

// Menghitung jumlah total elemen atau node dalam tree
int NbElmt(Tree T) {
    if (IsEmpty(T)) return 0;
    return 1 + NbElmt(FirstSon(T)) + NbElmt(NextBrother(T));
}

// Menghitung total seluruh keturunan dari sebuah node
int NbKeturunan(Tree T) {
    if (IsEmpty(T) || FirstSon(T) == Nil) return 0;
    
    int count = 0;
    address anak = FirstSon(T);
    
    while (anak != Nil) {
        count = count + 1 + NbKeturunan(anak);
        anak = NextBrother(anak);
    }
    return count;
}

// Mencari kedalaman level atau generasi dari seorang anggota berdasarkan nama
int Level(Tree T, char *target_name) {
    if (IsEmpty(T)) return 0;
    if (strcmp(Name(T), target_name) == 0) return 1;

    int down = Level(FirstSon(T), target_name);
    if (down != 0) return 1 + down;

    return Level(NextBrother(T), target_name);
}

// Mengembalikan nilai tertinggi antara dua angka
int Max(int a, int b) {
    return (a > b) ? a : b;
}

// Menghitung kedalaman maksimum dari tree
int Depth(Tree T) {
    if (IsEmpty(T)) return 0;
    return Max(1 + Depth(FirstSon(T)), Depth(NextBrother(T)));
}

/*
Prosedur Menu-Menu
*/
void MenuSuksesi(Tree T) {
    printf("tes\n");
}

void MenuGenerasi(Tree T) {
    printf("tes\n");
}

void MenuCari(Tree T) {
    printf("tes\n");
}

void MenuHitungKeturunan(Tree T) {
    printf("tes\n");
}

void MenuSimulasiEksklusi(Tree T) {
    printf("tes\n");
}