
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "map.h"
#include "moves.h"
#include "loc.h"

// Node structure for tree
typedef struct TreeNode {
    int cost;
    t_move move;
    struct TreeNode *children[9];
} TreeNode;

// Function to create a new TreeNode
TreeNode *createNode(int cost, t_move move) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed for TreeNode.\n");
        exit(1);
    }
    node->cost = cost;
    node->move = move;
    for (int i = 0; i < 9; i++) node->children[i] = NULL;
    return node;
}

// Recursive function to build tree and find minimum path
int buildTree(TreeNode *root, t_localisation loc, int depth, int max_depth, t_move *best_path, t_map map) {
    if (depth == max_depth) return root->cost;

    int min_cost = INT_MAX;
    t_move moves[7] = {F_10, F_20, F_30, B_10, T_LEFT, T_RIGHT, U_TURN};

    for (int i = 0; i < 7; i++) {
        t_localisation new_loc = loc;
        updateLocalisation(&new_loc, moves[i]);

        if (new_loc.pos.y < 0 || new_loc.pos.y >= map.y_max || new_loc.pos.x < 0 || new_loc.pos.x >= map.x_max) {
            continue;  // Skip moves that go out of map bounds
        }

        int new_cost = map.costs[new_loc.pos.y][new_loc.pos.x]; // Directly access map costs
        root->children[i] = createNode(new_cost, moves[i]);

        int cost = buildTree(root->children[i], new_loc, depth + 1, max_depth, best_path, map);

        if (cost < min_cost) {
            min_cost = cost;
            if (depth == 0) *best_path = moves[i];  // Update best path from root node
        }
    }
    return min_cost;
}

int main() {
    t_map map;

    // Load map based on operating system
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);

    // Use the calculateCosts function from map.c
    calculateCosts(map);

    // Display the soils and costs after calculating
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }

    displayMap(map);

    // Initialize starting position for MARC
    t_localisation start_loc = {.pos = {.x = 1, .y = 1}, .ori = NORTH};
    t_move best_path[5];

    // Create root node and calculate optimal path
    TreeNode *root = createNode(map.costs[start_loc.pos.y][start_loc.pos.x], -1);
    int min_cost = buildTree(root, start_loc, 0, 5, best_path, map);

    // Output the minimum cost and best path
    printf("Minimum cost to reach target: %d\n", min_cost);
    printf("Optimal sequence of moves: ");
    for (int i = 0; i < 5; i++) {
        printf("%s ", getMoveAsString(best_path[i]));
    }
    printf("\n");

    return 0;
}
