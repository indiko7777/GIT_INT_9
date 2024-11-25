Mars Rover Navigation Project
Project Overview
This project involves developing a navigation system for a Mars rover (MARC) to efficiently find its way back to the base station while minimizing costs and avoiding hazards like crevasses. The system uses an n-ary tree to evaluate possible moves and select the optimal path based on cost. In cases where the rover cannot reach the base, it identifies the nearest reachable point to the base.

Features
Creation of an n-ary tree:

Represents all possible moves and paths the rover can take.
Allows evaluation of each path to find the optimal route.
Optimal Path Selection:

Evaluates all paths using a cost-based approach.
Selects the path with the minimum total cost to the base station.
Dynamic Rover Localization:

Updates the rover's position and orientation after each phase.
Nearest Reachable Point Detection:

If the rover cannot reach the base station, it calculates the nearest reachable point.
Hazard and Boundary Checks:

Avoids crevasses and prevents the rover from exiting the map boundaries.
Map Parsing and Display:

Loads the map from .map files.
Displays the map visually, highlighting the rover’s current position.
Soil Modifiers:

Incorporates terrain-based costs (e.g., plain, erg, reg, crevasse) to influence navigation.
Move Randomization:

Generates random moves for testing different navigation scenarios.

GIT REPOSITORY: https://github.com/indiko7777/GIT_INT_9.git
