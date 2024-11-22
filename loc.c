#include <stdio.h>
#include "loc.h"

t_localisation loc_init(int x, int y, t_orientation ori)
{
    t_localisation loc;
    loc.pos.x = x;
    loc.pos.y = y;
    loc.ori = ori;
    return loc;
}

int isValidLocalisation(t_position loc, int x_max, int y_max)
{
    return (loc.x >= 0 && loc.x < x_max && loc.y >= 0 && loc.y < y_max);
}

t_position LEFT(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x - 1;
    new_pos.y = pos.y;
    return new_pos;
}

t_position RIGHT(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x + 1;
    new_pos.y = pos.y;
    return new_pos;
}

t_position UP(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x;
    new_pos.y = pos.y - 1;
    return new_pos;
}

t_position DOWN(t_position pos)
{
    t_position new_pos;
    new_pos.x = pos.x;
    new_pos.y = pos.y + 1;
    return new_pos;
}

t_localisation chooseInitialPosition(int map_x_max, int map_y_max) {
    int x, y;
    char orientation_char;
    t_orientation orientation;

    // Prompt the user to enter the position
    printf("Enter initial x position (0-%d): ", map_x_max - 1);
    scanf("%d", &x);
    while (x < 0 || x >= map_x_max) {
        printf("Invalid x position. Enter a value between 0 and %d: ", map_x_max - 1);
        scanf("%d", &x);
    }

    printf("Enter initial y position (0-%d): ", map_y_max - 1);
    scanf("%d", &y);
    while (y < 0 || y >= map_y_max) {
        printf("Invalid y position. Enter a value between 0 and %d: ", map_y_max - 1);
        scanf("%d", &y);
    }

    // Prompt the user to enter the orientation
    printf("Choose orientation (N for North, E for East, S for South, W for West): ");
    scanf(" %c", &orientation_char); // Include space to consume leftover newline
    while (orientation_char != 'N' && orientation_char != 'E' && orientation_char != 'S' && orientation_char != 'W') {
        printf("Invalid orientation. Enter N, E, S, or W: ");
        scanf(" %c", &orientation_char);
    }

    // Map the character to the t_orientation enum
    switch (orientation_char) {
        case 'N': orientation = NORTH; break;
        case 'E': orientation = EAST; break;
        case 'S': orientation = SOUTH; break;
        case 'W': orientation = WEST; break;
    }

    // Use the loc_init function to initialize and return the localisation
    return loc_init(x, y, orientation);
}
