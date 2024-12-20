#include <stdlib.h> // For malloc and free
#include <stdio.h>
#include <time.h>
#include "map.h"
#include "loc.h"
#include "moves.h"
#include "simulate.h"

int main() {
    
    srand(time(NULL));

   
    t_map map;

    
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    // Display the map costs before the robot's position is chosen
    printf("Map costs:\n");
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%d ", map.costs[i][j]); // Display costs as generated by map logic
        }
        printf("\n");
    }

    // Choose initial position and orientation
    t_localisation start_loc = chooseInitialPosition(map.x_max, map.y_max);

    // Display the chosen position and orientation with an arrow
    const char *orientations[] = {"^", ">", "v", "<"}; // Arrows for N, E, S, W
    printf("\nInitial Position: (%d, %d) %s\n", start_loc.pos.x, start_loc.pos.y, orientations[start_loc.ori]);

    // Highlight the robot's position on the map with an arrow
    printf("\nMap with Robot's Initial Position:\n");
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            if (i == start_loc.pos.y && j == start_loc.pos.x) {
                printf("%s ", orientations[start_loc.ori]); // Mark the robot's position with an arrow
            } else {
                printf("%d ", map.costs[i][j]); // Regular map cost
            }
        }
        printf("\n");
    }

    // Generate 9 random moves
    printf("\nFirst 9 Random Moves:\n");
    t_move random_moves[9];
    for (int i = 0; i < 9; i++) {
        random_moves[i] = (t_move)(rand() % 7); // Randomly generate a move
        printf("%s ", getMoveAsString(random_moves[i])); // Print move name
    }
    printf("\n");

    // Simulate MARC's journey, passing the start location and random moves
    simulateMARC(&map, start_loc, random_moves, 9);
    return 0;
}
