// File: mopsolver.c
// Source file for functions related to solving 
//    inputted maze in the shortest possible path.
// @author: Aidan Collins (ajc5660)
// @date: 12 APR 2022
// // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "maze.h"

#define USAGE(x) fprintf(x, "Usage:\nmopsolver [-hdsp] [-i INFILE] [-o OUTFILE]\n" \
   "Options:\n" \
   "%2s-h%10sPrint usage and options list to stdoutonly.%5s(Default: off)\n" \
   "%2s-d%10sPretty-print (display) the maze after reading.%2s(Default: off)\n" \
   "%2s-s%10sPrint length of shortest path or 'No solution'.%1s(Default: off)\n" \
   "%2s-p%10sPretty-print maze with the path, if one exists.%1s(Default: off)\n" \
   "%2s-i infile%3sRead maze from infile.%26s(Default: stdin)\n" \
   "%2s-o outfile%2sWrite all output to outfile.%20s(Default: stdout)\n", "", "", "", \
   "", "", "", "", "", "", "", "", "", "", "", "", "", "", "")


/**
 * Structure stores boolean values indicating
 *    if certain flags are being used
 */
struct Flags {
   unsigned char d: 1;
   unsigned char s: 1;
   unsigned char p: 1;
   unsigned char i: 1;
   unsigned char o: 1;
};


/**
 * Find all possible untraversed moves from current coordinate
 * @param maze: Representation of maze
 * @param traversals:  2D boolean (char) array of prior moves
 * @param moves: Empty boolean (char) array representing moves to make
 * @param n: row component of coordinate to determine moves from
 * @param m: column compoent of coordinate to determine moves from
 */
void find_moves(Maze maze, char* moves, int n, int m) {
   // determines moves to open coordinates
   if (m < maze_get_width(maze) - 1
       && maze_get_traversals(maze)[n][m + 1] == '.') { // right
      moves[2] = 1;
   } 
   if (n < maze_get_height(maze) - 1
              && maze_get_traversals(maze)[n + 1][m] == '.') { // down
      moves[3] = 1;
   } 
   if (m > 0 && maze_get_traversals(maze)[n][m - 1] == '.') { // left
      moves[0] = 1;
   } 
   if (n > 0 && maze_get_traversals(maze)[n - 1][m] == '.') { // up
      moves[1] = 1;
   } 
}


/**
 * Determines if coordinate is finish
 * @param maze: Maze to check the finish of
 * @param n: Row component of coordinate to check
 * @param m: Column component of coordinate to check
 * @return: 1 if is finish, else 0
 */
char is_solution(Maze maze, int n, int m) {
   return (maze_get_height(maze) - 1 == n && maze_get_width(maze) - 1 == m);
}


/**
 * Performs next move attempt in maze, checking if at finish, and
 *    enqueueing possible moves from new coordinate
 * @param que: Queue to dequeue and enqueue new moves
 * @param maze: Maze to determine the next move for
 * @param traversals: Data on previously traversed coordinates
 * @return: 1 if reached finish, else 0
 */ 
char next_move(Queue que, Maze maze) {
   int curr[2];
   char moves[4] = {0};
   queue_dequeue(que, curr);
   find_moves(maze, moves, curr[0], curr[1]);
   if (is_solution(maze, curr[0], curr[1])) {
      return 1;
   }
   // enqueues possible moves with a preference for down or right
   if (moves[2]) { // right
      queue_enqueue(que, curr[0], curr[1] + 1);
      maze_get_traversals(maze)[curr[0]][curr[1] + 1] = '2';
   } 
   if (moves[3]) { // down
      queue_enqueue(que, curr[0] + 1, curr[1]);
      maze_get_traversals(maze)[curr[0] + 1][curr[1]] = '3';
   }
   if (moves[0]) { // left
      queue_enqueue(que, curr[0], curr[1] - 1);
      maze_get_traversals(maze)[curr[0]][curr[1] - 1] = '0';
   } 
   if (moves[1]) { // up
      queue_enqueue(que, curr[0] - 1, curr[1]);
      maze_get_traversals(maze)[curr[0] - 1][curr[1]] = '1';
   }
   return 0;
}


/**
 * Takes file or command line input of representation of a maze.
 * Uses breadth-first search to solve the shortest path.
 * Outputs ASCII representation of maze solution, if possible.
 * @param argc: number of program arguments
 * @param argv: program arguments
 * @return: EXIT_SUCCESS if successful, else EXIT_FAILURE
 */
int main(int argc, char** argv) {
   struct Flags flags = {0};
   char* infile;
   char* outfile;
   FILE* in;
   FILE* out;
   // iterate over every program argument
   for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-' || ((argv[i][1] == 'i' || argv[i][1] == 'o')
             && argv[i][2] != '\0' && i == argc - 1))  {
         USAGE(stderr);
         return EXIT_FAILURE;
      } else if (argv[i][1] == 'i') {
         flags.i = 1;
         infile = argv[++i];
      } else if (argv[i][1] == 'o') {
         flags.o = 1;
         outfile = argv[++i];
      } else {
         int j = 1;
         while (argv[i][j] != '\0') {
            switch(argv[i][j]) {
                case 'h':
                   USAGE(stdout);
                   break;
                case 'd':
                   flags.d = 1;
                   break;
                case 's':
                   flags.s = 1;
                   break;
                case 'p':
                   flags.p = 1;
                   break;
                default:
                   USAGE(stderr);
                   return EXIT_FAILURE;
            }
            j++;
         }
      }
   }
   // initialize Maze data structure
   if (flags.i) {
      in = fopen(infile, "r");
   } else {
      in = stdin;
   }
   if (in == NULL) {
      perror("Error: ");
      return EXIT_FAILURE;
   }   
   Maze maze = maze_create(in);
   if (flags.i) {
      fclose(in);
   }
   // open outfile
   if (flags.o) { 
      out = fopen(outfile, "w");
   } else {
      out = stdout;
   }
   if (out == NULL) {
      perror("Error: ");
      maze_destroy(maze);
      return EXIT_FAILURE;
   }
   if (flags.d) {
      maze_print(maze, out);
   }
   // initialize Queue data structure
   Queue que = queue_create();
   // start calculating moves from one left of start to account
   //    for cases when the start is blocked
   queue_enqueue(que, 0, -1);
   // calculate moves until either maze is solved or determined impossible
   while (!queue_is_empty(que)) {
      // path to finish was successfully found
      if (next_move(que, maze)) {
        // path to finish was successfully found
         if (flags.s && flags.p) {
            fprintf(out, "Solution in %d steps.\n", maze_show_path(maze));
            maze_show_empty(maze);
            maze_print(maze, out);
         } else if (flags.s) { 
            fprintf(out, "Solution in %d steps.\n", maze_show_path(maze));
         } else if (flags.p) {
            maze_show_path(maze);
            maze_show_empty(maze);
            maze_print(maze, out);
         }
         maze_destroy(maze);
         queue_destroy(que);
         if (flags.o) {
            fclose(out);
         }
         return EXIT_SUCCESS;
      }
   }
   // no path to finish was found
   if (flags.s) {
      fprintf(out, "No solution.\n");
   }
   maze_destroy(maze);
   queue_destroy(que);
   if (flags.o) {
      fclose(out);
   }
   return EXIT_SUCCESS;
}
