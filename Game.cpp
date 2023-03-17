/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Game.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Hongwei Ruan, Yutong Liu
 * hwruan, merrila
 *
 * Project 4: Battleship
 *
 * Implementation for class Game, make the game process structured.
 */

#include <fstream>

#include "Game.h"


Game::Game() {
    Player p1;
    Player p2;
}

Game::Game(Player player1, string grid1, Player player2, string grid2) {
    // set p1 p2 correctly
    p1 = player1;
    p2 = player2;
    ifstream read_from_grid1(grid1);
    ifstream read_from_grid2(grid2);

    if ((read_from_grid1.is_open()) && (!(read_from_grid1.eof()))) {
        p1.load_grid_file(grid1);
    } else {
        generate_random_grid(p1);
        cout << "Generating random grid for " << p1.get_name();
    } if ((read_from_grid2.is_open()) && (!(read_from_grid2.eof()))) {
        // changed p1 to p2, copying mistake
        p2.load_grid_file(grid2);
    } else {
        generate_random_grid(p2);
        cout << "Generating random grid for " << p2.get_name();
    }
}

Player Game::get_p1() {
    return p1;
}

Player Game::get_p2() {
    return p2;
}

string Game::get_move(string player_name) {
    string move;
    // added space before and after the text
    cout << player_name << " enter your move: ";
    cin >> move;
    cout << endl;
    return move;
}

bool Game::check_valid_move(string move) {
    bool valid_move = false;
    if (move.size() != 2) {
        cout << p1.get_name() << " you entered an invalid input" << endl;
    } else {
        if ((move[0] > '8') || (move[0] < '1') ||
            (tolower(move[1]) < 'a') || (tolower(move[1]) > 'h')) {
            cout << p1.get_name() << " you entered an invalid position" << endl;
        } else {
            valid_move = true;
        }
    }
    return valid_move;
}

void Game::start(char difficulty, int max_num_rounds) {
    int completed_rounds = 0;
    string winner, move;
    
    while ((completed_rounds < max_num_rounds) ||
           (p1.get_remaining_ships() > 0) || (p2.get_remaining_ships() > 0)) {

        move = get_move(p1.get_name());
        
        while (!(check_valid_move(move))) {
            move = get_move(p1.get_name());
        }
        
        Position move_position(move[0],move[1]);
        
        p1.attack(p2, move_position);
        
        if (!(p2.destroyed())) {
            opponent_make_move(difficulty);
        }
            
        cout << "Your grid" << endl << endl;
        p1.print_grid();
        cout << "CPU's grid" << endl << endl;
        p1.print_guess_grid();
        
        completed_rounds ++;
        
        if (p1.destroyed()) {
            winner = p2.get_name();
            cout << "Game over, winner is " << winner << " in "
                 << completed_rounds << " rounds" << endl;
            break;
        } else if (p2.destroyed()) {
            winner = p1.get_name();
            cout << "Game over, winner is " << winner << " in "
                 << completed_rounds << " rounds" << endl;
            break;
        } else if((completed_rounds == max_num_rounds) && (!(p1.destroyed()))
                  && (!(p2.destroyed()))) {
            cout << "Game over, winner is no one in "
                 << completed_rounds << " rounds" << endl;
            break;
        }
    }
}
// Your code goes above this line.
// Don't change the implementations below!

void Game::generate_random_grid(Player &p) {
    // grid to check which position has been taken
    bool grid[MAX_GRID_SIZE][MAX_GRID_SIZE] = {{false}};

    for (int k = 0; k < 10 && p.get_num_ships() < 5; k++) {
        // i is the length of the ship to be made
        // decrementing i to create 2 ships of size 3
        int i = p.get_num_ships() + 1;
        if (i > 2) {
            i--;
        }

        // generate random position 1
        int row = get_random_number() % MAX_GRID_SIZE;
        int col = get_random_number() % MAX_GRID_SIZE;
        Position pos1(row, col);

        if (!grid[row][col]) {
            Position pos2;
            // Check if creating position two is not off the grid relative to
            // position 1 inthe order of bottom, right, left, top
            if (row + i < MAX_GRID_SIZE) {
                pos2 = Position(row + i, col);
            } else if (col + i < MAX_GRID_SIZE) {
                pos2 = Position(row, col + i);
            } else if (col - i >= 0) {
                pos2 = Position(row, col - i);
            } else if (row - i >= 0) {
                pos2 = Position(row - i, col);
            } else {
                continue;
            }

            Ship s(pos1, pos2);

            bool pos2_taken = false;
            if (s.is_horizontal()) {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_col() < pos2.get_col() ?
                            pos1.get_col() : pos2.get_col();
                int end = pos1.get_col() < pos2.get_col() ?
                          pos2.get_col() : pos1.get_col();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[pos1.get_row()][j]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[pos1.get_row()][j] = true;
                }
            } else {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_row() < pos2.get_row() ?
                            pos1.get_row() : pos2.get_row();
                int end = pos1.get_row() < pos2.get_row() ?
                          pos2.get_row() : pos1.get_row();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[j][pos1.get_col()]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[j][pos1.get_col()] = true;
                }
            }

            // Restart from beginning
            if (pos2_taken) {
                continue;
            }

            // Add the ship to p2's ships
            p.add_ship(s);
        }
    }
}

void Game::opponent_make_move(char difficulty) {
    if (difficulty == EMULATE) {
        Position next;
        cout << "Enter CPU emulation move: ";
        cin >> next;
        cout << endl;
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
    } else if (difficulty == EASY) {
#ifndef NOCPU
        int randRow = get_random_number() % MAX_GRID_SIZE;
        int randCol = get_random_number() % MAX_GRID_SIZE;
        Position randCoord(randRow, randCol);
        p2.attack(p1, randCoord);
        cout << "You received an attack at " << randCoord << endl << endl;
#else
        Position next;
        cin >> next;
        if (cin.fail()) {
            cin.clear();
            next = Position(7, 4);
        }
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
#endif
    } else if (difficulty == MEDIUM) {
        // Simple AI that checks right, bottom, left, top of hit position
        // TODO: implement for S'more version
    }
}

