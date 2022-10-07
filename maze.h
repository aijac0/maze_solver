// File: maze.h
// Header file for functions related to Maze data structure
// @author: Aidan Collins (ajc5660)
// @date: 13 APR 2022
// // // // // // // // // // // // // // // // // // // // //

#ifndef _MAZE_HEADER_
#define _MAZE_HEADER_

typedef struct MazeADT* Maze;


/**
 * Create and initialize a MazeADT data structure
 * @param input: File to get input for maze from
 * @return: created MazeADT*
 */
Maze maze_create(FILE* input);


/**
 * Gets the width of Maze
 * @param maze: Maze to get the width of
 * @return: width of Maze
 */
int maze_get_width(Maze maze);


/**
 * Gets the height of Maze
 * @param maze: Maze to get the height of
 * @return: height of Maze
 */
int maze_get_height(Maze maze);


/**
 * Gets the traversals of Maze
 * @param maze: Maze to get the traversals of
 * @return: traversals of Maze
 */
char** maze_get_traversals(Maze maze);


/**
 * Show path as trail of '+' in maze
 * @param maze: maze to change
 * @return: number of coordinates in path
 */
int maze_show_path(Maze maze);


/**
 * Changes numerical coordinate entries to empty char
 * @param maze: maze to change
 */
void maze_show_empty(Maze maze);


/**
 * Print the top or bottom border of maze
 * @param width: number of columns in maze
 * @param output: file to send output to
 */
void maze_print_border(int width, FILE* output);


/**
 * Print current representation of maze with borders
 * @param maze: maze with representation to print stored
 * @param output: file to send output to
 */
void maze_print(Maze maze, FILE* output);


/**
 * Free all dynamically allocated memory associated with MazeADT
 * @param maze: maze to destroy
 */
void maze_destroy(Maze maze);


#endif
