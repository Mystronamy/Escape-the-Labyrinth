/*-------------------------------------------
Program 6: Escape the Labyrinth
Course: CS 211, Fall 2023, UIC
System: Advanced zyLab
Author: William Nguyen
------------------------------------------- */

#include <random>
#include <set>
#include <utility>

#include "grid.h"
#include "maze.h"
using namespace std;

const string kYourNetID = "wnguy4";

const string kPathOutOfRegularMaze = "EEEWWWSEESWS";
const string kPathOutOfTwistyMaze = "SEWNSESNWNSSS";

//
// isPathToFreedom:
//
// Purpose: Determines if a given sequence of moves leads to freedom in a maze
// game.
//          The function traverses the maze based on the moves provided and
//          checks if the player picks up the required items (Spellbook, Wand,
//          Potion) along the way.
// Parameters: MazeCell *start - The starting point in the maze.
//             const string& moves - A string representing a series of moves (N,
//             S, E, W).
// Returns: bool - True if the path leads to freedom (collects all required
// items), false otherwise.
//
bool isPathToFreedom(MazeCell* start, const string& moves) {
 set<string> itemsPicked;  // To keep track of items picked up during the moves
 MazeCell* current = start;

 // Iterating through each move and updating the current position
 for (char move : moves) {
  // Checking and picking up items at the current location
  if (!current->whatsHere.empty()) {
   itemsPicked.insert(current->whatsHere);
  }

  // Moving to the next cell based on the move direction
  switch (move) {
   case 'N':
    if (current->north == nullptr) return false;
    current = current->north;
    break;
   case 'S':
    if (current->south == nullptr) return false;
    current = current->south;
    break;
   case 'E':
    if (current->east == nullptr) return false;
    current = current->east;
    break;
   case 'W':
    if (current->west == nullptr) return false;
    current = current->west;
    break;
   default:
    return false;  // Invalid move
  }
 }

 // Checking and picking up items at the final location
 if (!current->whatsHere.empty()) {
  itemsPicked.insert(current->whatsHere);
 }

 // Checking if all required items are picked up
 return itemsPicked.count("Spellbook") > 0 && itemsPicked.count("Wand") > 0 &&
        itemsPicked.count("Potion") > 0;
}