#include "logic/nbtRoyal.h"

int main() {
    RoyalFamilyTree tree;
    Create_tree(&tree.root);
    BuildTree(&tree);

    int pilihan;

    do {
        printf("\n");
        printf("============================================\n");
        printf("   ROYAL FAMILY TREE - LINE OF SUCCESSION  \n");
        printf("============================================\n");
        printf("  [1] Tampilkan Urutan Suksesi\n");
        printf("  [2] Tampilkan Silsilah per Generasi\n");
        printf("  [3] Cari Anggota Kerajaan\n");
        printf("  [4] Hitung Total Keturunan\n");
        printf("  [5] Simulasi Eksklusi Garis Keturunan\n");
        printf("  [0] Keluar\n");
        printf("============================================\n");
        printf("[!] catatan: program hanya mencangkup data dari Queen Elizabeth II sebagai leluhur utama.\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar();

        printf("\n");

        switch (pilihan) {
            case 1: MenuSuksesi(tree.root); break;
            case 2: MenuGenerasi(tree.root); break;
            case 3: MenuCari(tree.root); break;
            case 4: MenuHitungKeturunan(tree.root); break;
            case 5: MenuSimulasiEksklusi(tree.root); break;
            case 0: printf("Program selesai.\n"); break;
            default: printf("Pilihan tidak valid.\n"); break;
        }

    } while (pilihan != 0);

    DeAlokasi(&tree.root);
    return 0;
}