#include "nbtRoyal.h"
#include <ctype.h>

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

// Menampilkan informasi detail struktur node
void PrintTree(Tree T) {
    if (IsEmpty(T)) return;

    printf("========================================\n");
    printf("ID          : %d\n", Id(T));
    printf("Nama        : %s %s\n", Title(T), Name(T));
    printf("Tahun Lahir : %d\n", BirthYear(T));
    if (DeathYear(T) != 0) {
        printf("Tahun Wafat : %d\n", DeathYear(T));
    } else {
        printf("Tahun Wafat : [Masih Hidup]\n");
    }
    if (Gender(T) == 'M') {
        printf("Jenis Kelamin: Laki-laki\n");
    } else if (Gender(T) == 'F') {
        printf("Jenis Kelamin: Perempuan\n");
    }
    printf("Urutan Lahir : %d\n", BirthOrder(T));
    printf("Kelayakan Suksesi: %s\n", Eligible(T) ? "Layak" : "Tidak Layak");
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
}

// Helper untuk membandingkan string tanpa mempedulikan huruf besar/kecil
int IsEqualIgnoreCase(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2)) {
            return 0;
        }
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
}

// Modul Pencarian Nama yang sudah Case-Insensitive
address SearchByName(Tree T, char *target_name) {
    if (IsEmpty(T)) return Nil;

    if (IsEqualIgnoreCase(Name(T), target_name)) return T;

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

// Helper Menu 3: Traversal khusus mencari posisi ke-N di garis suksesi
address CariUrutan(Tree node, int target_N, int *counter) {
    if (IsEmpty(node)) {
        return Nil;
    }

    // Cek kelayakan suksesi
    if (Eligible(node) == 1 && DeathYear(node) == 0 && Excluded(node) == 0) {
        *counter = *counter + 1;
        if (*counter == target_N) {
            return node;
        }
    }

    address hasil = Nil;
    
    // Telusuri first_child jika cabang ini tidak dieksklusi
    if (Excluded(node) == 0) {
        hasil = CariUrutan(FirstSon(node), target_N, counter);
    }
    
    if (hasil != Nil) {
        return hasil;
    }

    // Telusuri next_sibling
    return CariUrutan(NextBrother(node), target_N, counter);
}

void TampilkanSuksesi(Tree T, int *pos){
    if(IsEmpty(T)) return;
    if(Eligible(T) == 1 && DeathYear(T) == 0 && Excluded(T) == 0){
        (*pos)++;
        printf("Posisi ke-%d: %s %s\n", *pos, Title(T), Name(T));
    }
    if(Excluded(T) == 0){
        TampilkanSuksesi(FirstSon(T), pos);
    }
    TampilkanSuksesi(NextBrother(T),pos);
}
void ResetEkslusi(Tree T){
    if(IsEmpty(T)) return;
    Excluded(T) = 0;
    ResetEkslusi(FirstSon(T));
    ResetEkslusi(NextBrother(T));
}

/*
Prosedur Menu-Menu
*/

void MenuSuksesi(Tree T) {
    int pos = 0;
    TampilkanSuksesi(T, &pos);
}

void MenuGenerasi(Tree T) {
    printf("tes\n");
}

// Implementasi Menu
void MenuCari(Tree T) {
    int pilihan;
    printf("Pilih metode pencarian:\n");
    printf("1. Berdasarkan Nama\n");
    printf("2. Berdasarkan Nomor Urut Suksesi\n");
    printf("Pilihan: ");
    
    // Validasi input angka
    if (scanf("%d", &pilihan) != 1) {
        printf("\n[!] Input tidak valid. Masukkan angka.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    // Cari berdasarkan nama
    if (pilihan == 1) {
        char keyword[MAX_NAME];
        printf("Masukkan nama anggota kerajaan: ");
        
        // Input nama
        if (fgets(keyword, sizeof(keyword), stdin) != NULL) {
            keyword[strcspn(keyword, "\n")] = 0;
            
            address hasil = SearchByName(T, keyword);
            
            if (hasil != Nil) {
                printf("\n[!] Ditemukan\n");
                PrintTree(hasil);
            } else {
                printf("\n[!] Anggota tidak ditemukan\n");
            }
        }
    }
    // Cari berdasarkan nomor urut suksesi
    else if (pilihan == 2) {
        int target_N;
        int counter = 0;
        
        // Input nomor urut suksesi
        printf("Masukkan angka urutan: ");
        if (scanf("%d", &target_N) != 1) {
            printf("\n[!] Input tidak valid.\n");
            while (getchar() != '\n');
            return;
        }
        while (getchar() != '\n');
        
        address hasil = CariUrutan(T, target_N, &counter);
        
        if (hasil != Nil) {
            printf("\n[!] Ditemukan\n");
            printf("Posisi ke-%d adalah %s %s\n", target_N, Title(hasil), Name(hasil));
            printf("Detail informasi:\n");
            PrintTree(hasil);
        } else {
            printf("\n[!] Posisi ke-%d tidak ditemukan\n", target_N);
        }
    } else {
        printf("\n[!] Pilihan menu tidak tersedia.\n");
    }
}

// Implementasi Menu 4
void MenuHitungKeturunan(Tree T) {
    char nama[MAX_NAME];
    printf("Masukkan nama anggota kerajaan: ");
    
    // Input nama dengan validasi
    if (fgets(nama, sizeof(nama), stdin) != NULL) {
        nama[strcspn(nama, "\n")] = 0; 
        
        address target = SearchByName(T, nama);
        
        if (target == Nil) {
            printf("\n[!] Anggota tidak ditemukan\n");
            return; 
        }
        
        int total = NbKeturunan(target);
        printf("\n%s memiliki %d keturunan.\n", Name(target), total);
        
        if (total > 0) {
            printf("Daftar keturunan:\n");
            PreOrder(FirstSon(target)); 
        }
    }
}

void MenuSimulasiEksklusi(Tree T) {
    char nama[MAX_NAME];
    printf("Masukkan nama anggota kerajaan yang akan dieksklusi: ");
    if(fgets(nama,sizeof(nama),stdin)== Nil) return;
    nama[strcspn(nama, "\n")] = 0;

    address target = SearchByName(T, nama);
    if (target == Nil){
        printf("\n Anggota tidak ditemukan\n");
        return;
    }
    printf("\n Simulasi Ekslusi: %s %s & seluruh keturunannya\n\n", Title(target), Name(target));
    Excluded(target) = 1;
    int pos = 0;
    TampilkanSuksesi(T, &pos);
    ResetEkslusi(T);
    printf("\n Simulasi selesai. Garis suksesi kembali normal.\n");
}
