#ifndef MOVES_H
#define MOVES_H

#include "loc.h"

/**
 * @brief Enum for the possible moves
 */
typedef enum {
    F_10,
    F_20,
    F_30,
    B_10,
    T_LEFT,
    T_RIGHT,
    U_TURN
} t_move;

/**
 * @brief Rotates the orientation based on the move
 * @param ori Current orientation
 * @param move Move to apply
 * @return New orientation
 */
t_orientation rotate(t_orientation ori, t_move move);

/**
 * @brief Translates the position based on the move
 * @param pos Current position
 * @param move Move to apply
 * @return New position
 */
t_position translate(t_position pos, t_move move);

/**
 * @brief Updates the localisation based on the move
 * @param loc Pointer to the localisation to update
 * @param move Move to apply
 */
void updateLocalisation(t_localisation *loc, t_move move);

/**
 * @brief Gets the string representation of a move
 * @param move Move to get the string for
 * @return String representation
 */
const char* getMoveAsString(t_move move);

#endif // MOVES_H
