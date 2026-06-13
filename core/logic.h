#ifndef LOGIC_H
#define LOGIC_H

#include "../data/royal.h"

/* --- Traversal & Utility --- */
void         preorder_succession(RoyalMember *node, int *counter);
void         levelorder_generation(RoyalMember *root);
void         display_profile(RoyalMember *node);
RoyalMember* dfs_search_name(RoyalMember *node, char *keyword);
RoyalMember* dfs_search_order(RoyalMember *node, int target_n, int *counter);
int          count_descendants(RoyalMember *node);
void         print_descendants(RoyalMember *node, int *nomor);

/* --- Menu Functions --- */
void menu_succession(RoyalFamilyTree *tree);        /* Menu 1 */
void menu_generation(RoyalFamilyTree *tree);        /* Menu 2 */
void menu_search(RoyalFamilyTree *tree);            /* Menu 3 */
void menu_count_descendants(RoyalFamilyTree *tree); /* Menu 4 */
void menu_simulate_exclusion(RoyalFamilyTree *tree);/* Menu 5 */

#endif