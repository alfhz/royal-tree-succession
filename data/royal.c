// Inisialisasi data silsilah asli Inggris

//Hard Code data silsilah keluarga kerjaan inggris
#include "royal.h"

// Fungsi untuk membuat node baru
RoyalMember* create_node(int id, char *name, int birth_year, int death_year, char gender, char *title, int birth_order, int eligible) {
    RoyalMember *node = (RoyalMember*) malloc(sizeof(RoyalMember));
    if (!node) {
        printf("gagal alokasi memori\n");
        return NULL;
    }

    node->id            = id;
    node->birth_year    = birth_year;
    node->death_year    = death_year;
    node->gender        = gender;
    node->birth_order   = birth_order;
    node->eligible      = eligible;

    strncpy(node->name,  name,  MAX_NAME  - 1);
    strncpy(node->title, title, MAX_TITLE - 1);
    node->name[MAX_NAME   - 1] = '\0';
    node->title[MAX_TITLE - 1] = '\0';

    node->fs = NULL;
    node->nb = NULL;
    node->pr = NULL;

    return node;
}

void add_child(RoyalMember *parent, RoyalMember *child) {
    if (!parent || !child) return;

    child->pr = parent;

    if (parent->fs == NULL) {
        parent->fs = child;
        return;
    }

    RoyalMember *curr = parent->fs;
    RoyalMember *prev = NULL;

    while (curr != NULL && curr->birth_order < child->birth_order) {
        prev = curr;
        curr = curr->nb;
    }

    if (prev == NULL) {
        child->nb = parent->fs;
        parent->fs = child;
    } else {
        child->nb = curr;
        prev->nb  = child;
    }
}

void free_tree(RoyalMember *node) {
    if (!node) return;
    free_tree(node->fs);
    free_tree(node->nb);
    free(node);
}

void build_tree(RoyalFamilyTree *tree) {
    if (!tree) return;

    // Membuat node untuk setiap anggota keluarga kerajaan
    RoyalMember *william = create_node(1, "William I", 1028, 1087, 'M', "King of England", 1, 1);
    RoyalMember *henry1   = create_node(2, "Henry I", 1068, 1135, 'M', "King of England", 2, 1);
    RoyalMember *robert   = create_node(3, "Robert Curthose", 1054, 1134, 'M', "Duke of Normandy", 3, 0);
    RoyalMember *matilda  = create_node(4, "Matilda", 1102, 1167, 'F', "Empress of the Holy Roman Empire", 1, 0);
    RoyalMember *stephen  = create_node(5, "Stephen", 1092, 1154, 'M', "King of England", 1, 1);

    // Membangun pohon keluarga kerajaan
    tree->root = william;
    tree->size = 5;

    add_child(william, henry1);
    add_child(william, robert);
    add_child(henry1, matilda);
    add_child(henry1, stephen);
}