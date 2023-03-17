/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Player.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Hongwei Ruan, Yutong Liu
 * hwruan, merrila
 *
 * Project 4: Battleship
 *
 * Set related information to players of the game.
 */

#include <fstream>

#include "Player.h"


Player::Player() {
    name = "";
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

Player::Player(string name_val) {
    name = name_val;
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

void Player::init_grid() {
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            grid[i][j] = EMPTY_LETTER;
            guess_grid[i][j] = EMPTY_LETTER;
        }
    }
    return;
}

string Player::get_name() {
    return name;
}

int Player::get_num_ships() {
    return num_ships;
}

int Player::get_remaining_ships() {
    return remaining_ships;
}

char Player::get_grid_at(int row, int col) {
    return grid[row][col];
}

char Player::get_guess_grid_at(int row, int col) {
    return guess_grid[row][col];
}

void Player::add_ship(Ship ship) {
    if (num_ships < MAX_NUM_SHIPS) {
        // switched the order of the following lines
        ships[num_ships] = ship;
        num_ships ++;
        remaining_ships ++;
        
        
        if (ship.is_horizontal()){
            if (ship.get_start().get_col() < ship.get_end().get_col()) {
                for (int i = 0; i < ship.get_size(); i++) {
                    grid[ship.get_start().get_row()][ship.get_start().get_col() + i] = SHIP_LETTER;
                }
            } else {
                for (int i = 0; i < ship.get_size(); i++) {
                    grid[ship.get_start().get_row()][ship.get_end().get_col() + i] = SHIP_LETTER;
                }
            }
        } else {
            if (ship.get_start().get_row() < ship.get_end().get_row()) {
                for (int i = 0; i < ship.get_size(); i++) {
                    grid[ship.get_start().get_row() + i][ship.get_start().get_col()] = SHIP_LETTER;
                }
            } else {
                for (int i = 0; i < ship.get_size(); i++) {
                    grid[ship.get_end().get_row() + i][ship.get_start().get_col()] = SHIP_LETTER;
                }
            }
        }
    }
}

void Player::attack(Player &opponent, Position pos) {
    
    if (opponent.grid[pos.get_row()][pos.get_col()] == SHIP_LETTER) {
        opponent.grid[pos.get_row()][pos.get_col()] = HIT_LETTER;
        guess_grid[pos.get_row()][pos.get_col()] = HIT_LETTER;
        for (int i = 0; i < opponent.num_ships; i++) {
            if (opponent.ships[i].has_position(pos)) {
                opponent.ships[i].hit();
                cout << name << " " << pos << " " << "hit" << endl;
                if (opponent.ships[i].has_sunk()) {
                    opponent.remaining_ships --;
                    announce_ship_sunk(opponent.ships[i].get_size());
                }
                break;
            }
        }
    } else if (opponent.grid[pos.get_row()][pos.get_col()] == EMPTY_LETTER) {
        opponent.grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
        guess_grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
        cout << name << " " << pos << " " << "miss" << endl;
    } else {
        cout << name << " " << pos << " " << "miss" << endl;
    }
}

void Player::announce_ship_sunk(int size) {
    if (size == 2) {
        cout << "Congratulations " << name << "! You sunk a Destroyer" << endl;
    }
    if (size == 3) {
        cout << "Congratulations " << name << "! You sunk a Submarine" << endl;
    }
    if (size == 4) {
        cout << "Congratulations " << name << "! You sunk a Battleship" << endl;
    }
    if (size == 5) {
        cout << "Congratulations " << name << "! You sunk a Carrier" << endl;
    }
    return;
}

bool Player::load_grid_file(string filename) {
    ifstream load;
    load.open(filename);
    bool open_status = false;
    
    if (load.is_open()) {
        open_status = true;
        while (!load.eof()) {
            Position start, end;
            load >> start >> end;
            if (load.good()) {
                Ship adding_ship(start, end);
                add_ship(adding_ship);
            } else if (!load.eof()) {
                open_status = false;
                break;
            }
        }
        load.close();
    }
    else {
    }
    return open_status;
}

bool Player::destroyed() {
    bool destroy_value = false;
    if (remaining_ships == 0) {
        destroy_value = true;
    }
    return destroy_value;
}

// Your code goes above this line.
// Don't change the implementations below!

void Player::print_grid() {
    ::print_grid(grid);
}

void Player::print_guess_grid() {
    ::print_grid(guess_grid);
}
