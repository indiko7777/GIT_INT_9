#include "moves.h"

const char* move_names[] = {"F 10m", "F 20m", "F 30m", "B 10m", "T left", "T right", "U-turn"};

t_orientation rotate(t_orientation ori, t_move move) {
    switch (move) {
        case T_LEFT:
            return (t_orientation)((ori + 3) % 4);
        case T_RIGHT:
            return (t_orientation)((ori + 1) % 4);
        case U_TURN:
            return (t_orientation)((ori + 2) % 4);
        default:
            return ori;
    }
}

t_position translate(t_position pos, t_move move) {
    int dx = 0, dy = 0;
    int distance = 0;
    t_orientation ori = NORTH; // Default orientation

    switch (move) {
        case F_10: distance = 1; break;
        case F_20: distance = 2; break;
        case F_30: distance = 3; break;
        case B_10: distance = -1; break;
        default: distance = 0; break;
    }

    switch (ori) {
        case NORTH: dy = -1; break;
        case EAST:  dx = 1;  break;
        case SOUTH: dy = 1;  break;
        case WEST:  dx = -1; break;
    }

    pos.x += dx * distance;
    pos.y += dy * distance;
    return pos;
}

void updateLocalisation(t_localisation *loc, t_move move) {
    loc->ori = rotate(loc->ori, move);
    loc->pos = translate(loc->pos, move);
}

const char* getMoveAsString(t_move move) {
    return move_names[move];
}
