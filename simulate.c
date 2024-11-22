#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "simulate.h"
#include "stack.h"
#include "moves.h"
#include "loc.h"
#include "map.h"

// Function to apply a move and get the new localisation
void applyMove(t_localisation *loc, t_move move, t_localisation *new_loc) {
    // Update orientation
    switch (move) {
        case T_LEFT:
            new_loc->ori = (loc->ori + 3) % 4;
            break;
        case T_RIGHT:
            new_loc->ori = (loc->ori + 1) % 4;
            break;
        case U_TURN:
            new_loc->ori = (loc->ori + 2) % 4;
            break;
        default:
            new_loc->ori = loc->ori;
            break;
    }

    // Update position
    int dx = 0, dy = 0;
    int distance = 0;
    switch (new_loc->ori) {
        case NORTH: dy = -1; break;
        case EAST:  dx = 1;  break;
        case SOUTH: dy = 1;  break;
        case WEST:  dx = -1; break;
    }
    switch (move) {
        case F_10: distance = 1; break;
        case F_20: distance = 2; break;
        case F_30: distance = 3; break;
        case B_10: distance = -1; break;
        default: distance = 0; break; // No movement for turns
    }
    new_loc->pos.x = loc->pos.x + dx * distance;
    new_loc->pos.y = loc->pos.y + dy * distance;
}

// Function to simulate MARC's journey
void simulateMARC(t_map *map, t_localisation start_loc, t_move *random_moves, int num_moves) {
    // Find base camp position (cell with cost 0)
    int base_camp_x = -1, base_camp_y = -1;
    for (int y = 0; y < map->y_max; y++) {
        for (int x = 0; x < map->x_max; x++) {
            if (map->costs[y][x] == 0) {
                base_camp_x = x;
                base_camp_y = y;
                break;
            }
        }
        if (base_camp_x != -1) break;
    }

    if (base_camp_x == -1) {
        printf("Base camp not found on the map.\n");
        return;
    }

    int min_cost = INT_MAX;
    int min_distance = INT_MAX;
    t_move best_sequence[5];
    int best_sequence_length = 0;

    // Iterate over all possible sequences of up to 5 moves
    for (int seq_len = 1; seq_len <= 5; seq_len++) {
        int indices[5];
        for (int i = 0; i < seq_len; i++) {
            indices[i] = i;
        }

        while (1) {
            // Build the sequence of moves
            t_move sequence[5];
            int used_moves[9] = {0}; // To ensure each move is used at most once
            int valid_sequence = 1;
            for (int i = 0; i < seq_len; i++) {
                sequence[i] = random_moves[indices[i]];
                used_moves[indices[i]]++;
                if (used_moves[indices[i]] > 1) {
                    valid_sequence = 0;
                    break; // Move used more than once, invalid sequence
                }
            }
            if (!valid_sequence) {
                goto next_combination; // Skip to the next combination
            }

            int total_cost = 0;
            t_localisation loc = start_loc;
            int valid = 1;

            // Simulate the sequence of moves
            for (int i = 0; i < seq_len; i++) {
                t_localisation new_loc;
                applyMove(&loc, sequence[i], &new_loc);
                int x = new_loc.pos.x;
                int y = new_loc.pos.y;
                if (x < 0 || x >= map->x_max || y < 0 || y >= map->y_max) {
                    valid = 0; // Out of map bounds
                    break;
                }
                int cost = map->costs[y][x];
                if (cost >= 10000 || cost == COST_UNDEF) { // Obstacle or undefined cost
                    valid = 0;
                    break;
                }
                total_cost += cost;
                loc = new_loc;
            }

            if (valid) {
                int distance = abs(loc.pos.x - base_camp_x) + abs(loc.pos.y - base_camp_y);
                if (loc.pos.x == base_camp_x && loc.pos.y == base_camp_y) {
                    if (total_cost < min_cost) {
                        min_cost = total_cost;
                        min_distance = 0;
                        best_sequence_length = seq_len;
                        for (int i = 0; i < seq_len; i++)
                            best_sequence[i] = sequence[i];
                    }
                } else {
                    if (distance < min_distance || (distance == min_distance && total_cost < min_cost)) {
                        min_distance = distance;
                        min_cost = total_cost;
                        best_sequence_length = seq_len;
                        for (int i = 0; i < seq_len; i++)
                            best_sequence[i] = sequence[i];
                    }
                }
            }

            next_combination:
            // Generate next combination
            int i = seq_len - 1;
            while (i >= 0 && indices[i] == num_moves - seq_len + i) {
                i--;
            }
            if (i < 0) break;
            indices[i]++;
            for (int j = i + 1; j < seq_len; j++) {
                indices[j] = indices[j - 1] + 1;
            }
        }
    }

    if (min_distance == INT_MAX) {
        printf("No valid sequence of up to 5 moves found.\n");
    } else {
        printf("Optimal path cost: %d\n", min_cost);
        if (min_distance == 0) {
            printf("Reached the base camp.\n");
        } else {
            printf("Could not reach the base camp. Closest distance: %d\n", min_distance);
        }

        // Use the stack to display moves in correct order
        t_stack move_stack = createStack(best_sequence_length);
        for (int i = 0; i < best_sequence_length; i++) {
            push(&move_stack, best_sequence[i]);
        }

        printf("Moves to base camp or closest point:\n");
        int move_indices[5];
        int idx = 0;
        while (move_stack.nbElts > 0) {
            t_move move = pop(&move_stack);
            move_indices[idx++] = move;
        }

        // Display the chosen moves
        for (int i = best_sequence_length - 1; i >= 0; i--) {
            printf("%s\n", getMoveAsString(move_indices[i]));
        }

        // Display which moves were selected from the 9 random moves
        printf("\nChosen moves from the 9 random moves:\n");
        for (int i = 0; i < best_sequence_length; i++) {
            // Find the index of the move in the random_moves array
            for (int j = 0; j < num_moves; j++) {
                if (best_sequence[i] == random_moves[j]) {
                    printf("Move %d: %s\n", j + 1, getMoveAsString(random_moves[j]));
                    break;
                }
            }
        }
    }
}
