// File: maze.c
// Source file for functions related to Maze data structure
// @author: Aidan Collins (ajc5660)
// @date: 13 APR 2022
// // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/**
 * Structure representing Maze
 * @variable traversals: Array of char arrays representing
 *    maze, with all its open, traversed, and blocked coordinates
 *    .: untraversed
 *    #: blocked path
 *    0: traversed, came from right
 *    1: traversed, came from below
 *    2: traversed, came from left
 *    3: traversed, came from above
 * @variable height: number of rows in maze
 * @variable width: number of columns in maze
 */
struct MazeADT {
   char** traversals;
   int height;
   int width;
};


/**
 * Create and initialize a MazeADT data structure
 * @param input: File to get input for maze from
 * @return: created MazeADT*
 */
Maze maze_create(FILE* input) {
   Maze maze = malloc(sizeof(struct MazeADT));
   char* buffer = calloc(sizeof(char), 8192);
   // get first line of input
   fgets(buffer, 8192, input);
   // determine width of maze
   for (int i = 0; i < 8192; i++) {
      if (buffer[i] == '\n') {
         break;
      } if (buffer[i] != ' ') {
         maze->width++;
      }
   }
   // get and store each row of maze, converting 1 -> #, 0 -> .
   char** rows = calloc(sizeof(char*), 8192);
   char* row = calloc(sizeof(char), maze->width);
   for (int i = 0; i < maze->width; i++) {
      row[i] = buffer[i * 2] == '1' ? '#' : '.';
   }
   rows[maze->height] = row;
   maze->height++;
   while (fgets(buffer, 4096, input)) {
      row = calloc(sizeof(char), maze->width);
      for (int i = 0; i < maze->width; i++) {
         row[i] = buffer[i * 2] == '1' ? '#' : '.';
      }
      rows[maze->height] = row;
      maze->height++;
   }
   // store rows and columns in maze
   maze->traversals = calloc(sizeof(char*), maze->height);
   int i = 0;
   while (rows[i] != 0) {
      maze->traversals[i] = rows[i];
      i++;
   }
   free(rows);
   free(buffer);
   return maze;
}


/**
 * Gets the width of Maze
 * @param maze: Maze to get the width of
 * @return: width of Maze
 */
int maze_get_width(Maze maze) {
   return maze->width;
}


/**
 * Gets the height of Maze
 * @param maze: Maze to get the height of
 * @return: height of Maze
 */
int maze_get_height(Maze maze) {
   return maze->height;
}


/**
 * Gets the traversals of Maze
 * @param maze: Maze to get the traversals of
 * @return: traversals of Maze
 */
char** maze_get_traversals(Maze maze) {
   return maze->traversals;
}


/**
 * Show path as trail of '+' in maze
 * @param maze: maze to change
 * @return: number of coordinates in path
 */
int maze_show_path(Maze maze) {
   int p = 0;
   // get coordinate of finish node
   int n = maze->height - 1;
   int m = maze->width - 1;
   char curr;
   // find the direction that path to coordinate came from, set 
   //    coordinate to path char, move coordinate in direction found
   while (n + m >= 0) {
      curr = maze->traversals[n][m];
      maze->traversals[n][m] = '+';
      switch(curr) {
         case '0': // right
            m++;
            break;
         case '1': // down
            n++;
            break;
         case '2': // left
            m--;
            break;
         case '3': // up
            n--;
            break;
      }
      p++;
   }
   return p;
}


/**
 * Changes numerical coordinate entries to empty char
 * @param maze: maze to change
 */
void maze_show_empty(Maze maze) {
   // show each non-path traversable coordinate as '.'
   for (int n = 0; n < maze->height; n++) {
      for (int m = 0; m < maze->width; m++) {
         if (maze->traversals[n][m] != '#'
             && maze->traversals[n][m] != '+') {
             maze->traversals[n][m] = '.';
         }
      }
   }
}


/**
 * Print the top or bottom border of maze
 * @param width: number of columns in maze
 * @param output: file to send output to
 */
void maze_print_border(int width, FILE* output) {
   fputc('|', output);
   for (int i = 0; i < width * 2 + 1; i++) {
      fputc('-', output);
   }
   fputs("|\n", output);
}


/**
 * Print current representation of maze with borders
 * @param maze: maze with representation to print stored
 * @param output: file to send output to
 */
void maze_print(Maze maze, FILE* output) {
   maze_print_border(maze->width, output);
   for (int n = 0; n < maze->height; n++) {
      if (n) {
         fputs("| ", output);
      } else {
         fputs("  ", output);
      }
      for (int m = 0; m < maze->width; m++) {
          fprintf(output, "%c ", maze->traversals[n][m]);
          
      }
      if (maze->height - n - 1) {
         putc('|', output);
      }
      fputc('\n', output);
   }
   maze_print_border(maze->width, output);
}


/**
 * Free all dynamically allocated memory associated with MazeADT
 * @param maze: maze to destroy
 */
void maze_destroy(Maze maze) {
   for (int n = 0; n < maze->height; n++) {
      free(maze->traversals[n]);
   }
   free(maze->traversals);
   free(maze);
}
