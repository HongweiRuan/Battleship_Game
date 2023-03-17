/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Ship.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Hongwei Ruan, Yutong Liu
 * hwruan, merrila
 *
 * Project 4: Battleship
 *
 * Use to implement related information for ships in the game.
 */

#include <cmath>

#include "Ship.h"


Ship::Ship() {
    start = get_start();
    end = get_end();
    size = 0;
    num_hits = 0;
}

Ship::Ship(Position start_in, Position end_in) {

    start = start_in;
    end = end_in;
    if (is_horizontal()) {
        size = abs(end.get_col() - start.get_col()) + 1;
    } else {
        size = abs(end.get_row() - start.get_row()) + 1;
    }
    num_hits = 0;
}

Position Ship::get_start() {
    return start;
}

Position Ship::get_end() {
    return end;
}

int Ship::get_size() {
    return size;
}

bool Ship::is_horizontal() {
    if (start.get_row() == end.get_row()) {
        return true;
    } else {
        return false;
    }
}

bool Ship::has_position(Position pos) {
    
    if (is_horizontal())  {
        // check if two coordinates makes a ship(not diagonal or L-shaped)
        if (start.get_row() == pos.get_row() && end.get_row() == pos.get_row()) {
            if (start.get_col() > end.get_col()) {
                if (pos.get_col() <= start.get_col() && pos.get_col() >= end.get_col()) {
                    return true;
                } else {
                    return false;
                }
            } else {
                if (pos.get_col() >= start.get_col() && pos.get_col() <= end.get_col()) {
                    return true;
                } else {
                    return false;
                }
            }
        } else {
            return false;
        }
    } else {
        if (start.get_col() == pos.get_col() && end.get_col() == pos.get_col()) {
            if (start.get_row() > end.get_row()) {
                if (pos.get_row() <= start.get_row() && pos.get_row() >= end.get_row()) {
                    return true;
                } else {
                    return false;
                }
            } else {
                if (pos.get_row() >= start.get_row() && pos.get_row() <= end.get_row()) {
                    return true;
                } else {
                    return false;
                }
            }
        } else {
            return false;
        }
    }
}

void Ship::hit() {
    if (num_hits < size) {
        num_hits++;
    }
    return;
}

bool Ship::has_sunk() {
    bool has_sunk_value = false;
    if (num_hits >= size) {
        has_sunk_value = true;
    }
    return has_sunk_value;
}

