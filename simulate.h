#ifndef SIMULATE_H
#define SIMULATE_H

#include "moves.h"
#include "map.h"

/**
 * @brief Simulates MARC's journey based on the provided map.
 * @param map Pointer to the map structure.
 * @param start_loc Starting localisation of MARC.
 * @param random_moves Array of random moves.
 * @param num_moves Number of random moves.
 */
void simulateMARC(t_map *map, t_localisation start_loc, t_move *random_moves, int num_moves);

#endif // SIMULATE_H
