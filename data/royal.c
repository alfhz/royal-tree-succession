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
    /* ── 1. Root ── */
    address elizabeth = Alokasi(1, "Elizabeth Alexandra Mary", 1926, 2022, 'F', "Queen", 1, 0);

    /* ── 2. Garis Keturunan Charles (Kiri Pertama) ── */
    address charles   = Alokasi(2, "Charles Philip Arthur George", 1948, 0, 'M', "King", 1, 0); 
    
    address william   = Alokasi(3, "William Arthur Philip Louis", 1982, 0, 'M', "Prince of Wales", 1, 1);
    address george    = Alokasi(4, "George Alexander Louis", 2013, 0, 'M', "Prince", 1, 1);
    address charlotte = Alokasi(5, "Charlotte Elizabeth Diana", 2015, 0, 'F', "Princess", 2, 1);
    address louis     = Alokasi(6, "Louis Arthur Charles", 2018, 0, 'M', "Prince", 3, 1);
    
    address henry     = Alokasi(7, "Henry Charles Albert David", 1984, 0, 'M', "Duke of Sussex", 2, 0);
    address archie    = Alokasi(8, "Archie Harrison", 2019, 0, 'M', "Prince", 1, 0);
    address lilibet   = Alokasi(9, "Lilibet Diana", 2021, 0, 'F', "Princess", 2, 0);

    /* ── 3. Garis Keturunan Anne (Kiri Kedua) ── */
    address anne      = Alokasi(10, "Anne Elizabeth Alice Louise", 1950, 0, 'F', "Princess Royal", 2, 1);
    
    address peter     = Alokasi(11, "Peter Mark Andrew Phillips", 1977, 0, 'M', "Mr", 1, 1);
    address savannah  = Alokasi(12, "Savannah Phillips", 2010, 0, 'F', "Miss", 1, 1);
    address isla      = Alokasi(13, "Isla Phillips", 2012, 0, 'F', "Miss", 2, 1);
    
    address zara      = Alokasi(14, "Zara Anne Elizabeth Phillips", 1981, 0, 'F', "Mrs", 2, 1);
    address mia       = Alokasi(15, "Mia Grace Tindall", 2014, 0, 'F', "Miss", 1, 1);
    address lena      = Alokasi(16, "Lena Elizabeth Tindall", 2018, 0, 'F', "Miss", 2, 1);
    address lucas     = Alokasi(17, "Lucas Tindall", 2021, 0, 'M', "Master", 3, 1);

    /* ── 4. Garis Keturunan Andrew (Kiri Ketiga) ── */
    address andrew    = Alokasi(18, "Andrew Albert Christian Edward", 1960, 0, 'M', "Duke of York", 3, 1);
    
    address beatrice  = Alokasi(19, "Beatrice Elizabeth Mary Windsor", 1988, 0, 'F', "Princess", 1, 1);
    address sienna    = Alokasi(20, "Sienna Elizabeth Mapelli Mozzi", 2021, 0, 'F', "Miss", 1, 1);
    
    address eugenie   = Alokasi(21, "Eugenie Victoria Helena Windsor", 1990, 0, 'F', "Princess", 2, 1);
    address august    = Alokasi(22, "August Philip Hawke Brooksbank", 2021, 0, 'M', "Master", 1, 1);

    /* ── 5. Garis Keturunan Edward (Paling Kanan) ── */
    address edward    = Alokasi(23, "Edward Antony Richard Louis", 1964, 0, 'M', "Duke of Edinburgh", 4, 1);
    
    // Berdasarkan gambarmu, Louise ditaruh di kiri, James di kanan
    address louise    = Alokasi(24, "Louise Alice Mountbatten-Windsor", 2003, 0, 'F', "Lady", 1, 1);
    address james     = Alokasi(25, "James Alexander Mountbatten-Windsor", 2007, 0, 'M', "Viscount", 2, 1);


    /* ── Susun Hubungan (Wajib Urut Kiri ke Kanan) ── */
    
    // Anak Elizabeth II
    AddChild(elizabeth, charles);
    AddChild(elizabeth, anne);
    AddChild(elizabeth, andrew);
    AddChild(elizabeth, edward);

    // Anak Charles
    AddChild(charles, william);
    AddChild(charles, henry);

    // Anak William
    AddChild(william, george);
    AddChild(william, charlotte);
    AddChild(william, louis);

    // Anak henry
    AddChild(henry, archie);
    AddChild(henry, lilibet);

    // Anak Anne
    AddChild(anne, peter);
    AddChild(anne, zara);

    // Anak Peter
    AddChild(peter, savannah);
    AddChild(peter, isla);

    // Anak Zara
    AddChild(zara, mia);
    AddChild(zara, lena);
    AddChild(zara, lucas);

    // Anak Andrew
    AddChild(andrew, beatrice);
    AddChild(andrew, eugenie);

    // Anak Beatrice & Eugenie
    AddChild(beatrice, sienna);
    AddChild(eugenie, august);

    // Anak Edward
    AddChild(edward, louise);
    AddChild(edward, james);

    tree->root = elizabeth;
    tree->size = 25;
}