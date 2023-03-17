/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Position.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Hongwei Ruan, Yutong Liu
 * hwruan, merrila
 *
 * Project 4: Battleship
 *
 * Find and set position of points
 */

#include "Position.h"
#include "utility.h"


Position::Position() {
    set_row(0);
    set_col(0);
}

Position::Position(int row_in, int col_in) {
    row = check_range(row_in);
    col = check_range(col_in);
}

Position::Position(char row_in, char col_in) {
    row = check_range(row_in - '1');
    col = check_range(toupper(col_in) - 'A');
}

int Position::get_row() {
    return row;
}

void Position::set_row(int row_in) {
    row = check_range(row_in);
    return;
}

int Position::get_col() {
    return col;
}

void Position::set_col(int col_in) {
    col = check_range(col_in);
    return;
}

void Position::read(istream &is) {
    char inputTest, input_num1, input_num2;
    is >> inputTest;
    if (inputTest != '(') {
        is >> input_num2;
        set_row(inputTest - '1');
    } else {
        is >> input_num1 >> inputTest >> input_num2 >> inputTest;
        set_row(input_num1 - '1');
    }
    set_col(toupper(input_num2) - 'A');
}

void Position::write(ostream &os) {
    int row_num = get_row() + 1;
    char col_char = get_col() + 'A';
    os << "(" << row_num << "," << col_char << ")";
    return;
}

int Position::check_range(int val) {
    int final_number = 0;
    if (val >= 0 && val < MAX_GRID_SIZE){
        final_number = val;
    } else {
        if (val < 0) {
            final_number = 0;
        } else {
            final_number = MAX_GRID_SIZE - 1;
        }
    }
    return final_number;
}


// Your code goes above this line.
// Don't change the implementations below!

istream &operator>>(istream &is,  Position &pos) {
    pos.read(is);
    return is;
}

ostream &operator<<(ostream &os, Position pos) {
    pos.write(os);
    return os;
}

