/**
 * Copyright 2019 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Hongwei Ruan, Yutong Liu
 * hwruan, merrila
 *
 * Project 4: Battleship
 *
 * Contains functions for testing classes in the project.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "Position.h"
#include "Ship.h"
#include "Player.h"
#include "Game.h"
#include "utility.h"

using namespace std;


void test_position();
void test_ship();
void test_player();
void test_game();

void startTests() {
    test_position();
    test_ship();
    test_player();
    test_game();
    return;
}

void test_position() {
    // testing Position default constructor here
    Position start_pos;
    Position end_pos;
    cout << "Testing Position::Position() - default constructor\n";
    cout << "start_pos, expected output: (1,A) actual output: "
         << start_pos << endl;
    cout << "end_pos, expected output: (1,A) actual output: "
         << end_pos << endl;
    
    // testing Position non-default constructor here
    Position test_pos3('8','D');
    Position test_pos4(-2,9);
    Position test_pos5('3','N');
    Position test_pos6(9,9);
    Position test_pos7('3','d');
    Position test_pos8('9','m');
    cout << "Testing nondefault constructor\n";
    cout << "test pos3，expected output: (8,D) actual output:"
         << test_pos3 << endl;
    cout << "test_pos4,expected output: (1,H) actual output: "
         << test_pos4 << endl;
    cout << "test_pos5expected output: (3,H) actual output: "
         << test_pos5 << endl;
    cout << "test_pos6，expected output: (8,H) actual output: "
         << test_pos6 << endl;
    cout << "test_pos7，expected output: (3,D) actual output: "
         << test_pos7 << endl;
    cout << "test_pos8，expected output: (8,H) actual output: "
         << test_pos6 << endl;
    
    // testing Position setters here
        start_pos.set_row(4);
        start_pos.set_col(5);
        cout << "\nTesting Position::set_row() and Position::set_col()\n";
        cout << "start_pos, expected output: (5,F) actual output: "
             << start_pos << endl;
        
        end_pos.set_row(3);
        end_pos.set_col(2);
        cout << "\nTesting Position::set_row() and Position::set_col()\n";
        cout << "end_pos, expected output: (4,C) actual output: "
             << end_pos << endl;
        
        test_pos3.set_row(1);
        test_pos3.set_col(6);
        cout << "\nTesting Position::set_row() and Position::set_col()\n";
        cout << "test_pos1, expected output: (2,G) actual output: "
             << test_pos3 << endl;
        
        test_pos4.set_row(3);
        test_pos4.set_col(1);
        cout << "\nTesting Position::set_row() and Position::set_col()\n";
        cout << "test_pos2, expected output: (4,B) actual output: "
             << test_pos4 << endl;
        
    
    // testing Position read
    ifstream input_file;
    input_file.open("grid1.txt");
    if (input_file.good()) {

        // can use the Position::read() function directly
        start_pos.read(input_file);

        // or use the extraction operator
        input_file >> end_pos;

        cout << "\nTesting Position::read()\n";
        cout << "start_pos, expected output: (8,B) actual output: "
             << start_pos << endl;
        cout << "end_pos, expected output: (8,C) actual output: "
             << end_pos << endl;
    } else {
        cout << "\nError opening grid1.txt\n";
    }
  
    return;
}

void test_ship() {
    Position start;
     // test of the other constructor
     // test of member function: set_row(int row_in)
     start.set_row(5);
     // test of member function: set_col(int col_in)
     start.set_col(3);

    Position end;
     // test of the other constructor
     // test of member function: set_row(int row_in)
     end.set_row(5);
     // test of member function: set_col(int col_in)
     end.set_col(1);

    Ship ship1;
    Ship ship2(start, end);
    Position shipPosition1;
    Position shipPosition2;
    shipPosition1.set_row(2);
    shipPosition1.set_col(6);
    shipPosition2.set_row(2);
    shipPosition2.set_col(3);
    Ship ship3(shipPosition1, shipPosition2);
    
    cout << "Testing default constructor, Expecting: (1,A) (1,A), Actual: "
         << ship1.get_start() << ship1.get_end() << endl;
    cout << ship1.get_size() << endl;
    cout << "Testing non-default constructor, Expecting: (6,D) (6,B), Actual: "
         << ship2.get_start() << ship2.get_end() << endl;
    cout << ship2.get_size() << endl;

    cout << "Testing has_position" << endl;
    Position test_pos1('1','a');
    Position test_pos2(5,3);
    Position test_pos3(5,2);
    
    cout << "Expected: 011, Actual: " << ship2.has_position(test_pos1)
         << ship2.has_position(test_pos2) << ship2.has_position(test_pos3) << endl;
    
    Position pTEST;
    pTEST.set_row(2);
    pTEST.set_col(9);
    cout << "expected output: 0" << endl;
    cout << ship1.has_position(pTEST) << endl;
    
    cout << "Testing get_size" << endl;
    ship1.get_size();
    ship2.get_size();
    ship3.get_size();

    cout << "Testing hit and has_sunk" << endl;

    ship2.hit();
    cout << "Expected: 0, Actual" << ship2.has_sunk() << endl;
    ship2.hit();
    cout << "Expected: 0, Actual" << ship2.has_sunk() << endl;
    ship2.hit();
    cout << "Expected: 1, Actual" << ship2.has_sunk() << endl;
    ship2.hit();
    cout << "Expected: 1, Actual" << ship2.has_sunk() << endl;
    ship3.hit();
    cout << "Expected: 0, Actual" << ship2.has_sunk() << endl;
    ship3.hit();
    cout << "Expected: 0, Actual" << ship2.has_sunk() << endl;
    ship3.hit();
    cout << "Expected: 0, Actual" << ship2.has_sunk() << endl;
    ship3.hit();
    cout << "Expected: 1, Actual" << ship2.has_sunk() << endl;
    ship3.hit();
    cout << "Expected: 1, Actual" << ship2.has_sunk() << endl;

    return;
}




void test_player() {
    cout << "Testing Player" << endl;
    Player player1;
    Player player2("torralva");
    
    cout << "Testing player non-default constructor" << endl;
    Player player3("Torralva");
    cout << player3.get_name() << endl;
    cout << player3.get_num_ships() << endl;
    cout << player3.get_remaining_ships() << endl;
    player3.print_grid();

    Player player4("Bill");
    cout << player4.get_name() << endl;
    cout << player4.get_num_ships() << endl;
    cout << player4.get_remaining_ships() << endl;
    player4.print_grid();

    Position test_pos3('1','a');
    Position test_pos4('1','b');
    Position test_pos5('2','a');
    Position test_pos6('2','c');
    Position test_pos7(3,0);
    Position test_pos8(3,5);
    Position test_pos9('4','a');
    Position test_pos10('7','A');
    Position test_pos11('1','g');
    Position test_pos12('1','d');
    Position test_pos13('7','h');
    Position test_pos14('5','h');
    Position test_pos15(6,2);
    Position test_pos16(6,6);
    Position test_pos17(3,1);
    Position test_pos18(5,1);
    
    Ship ship1(test_pos3, test_pos4);
    Ship ship2(test_pos5, test_pos6);
    Ship ship3(test_pos7, test_pos8);
    Ship ship4(test_pos9, test_pos10);
    Ship ship5(test_pos11, test_pos12);
    Ship ship6(test_pos13, test_pos14);
    Ship ship7(test_pos15, test_pos16);
    Ship ship8(test_pos17, test_pos18);
    
    cout << ship1.get_start() << ship1.get_end() << endl;
    cout << ship2.get_start() << ship2.get_end() << endl;
    cout << ship3.get_start() << ship3.get_end() << endl;
    cout << ship4.get_start() << ship4.get_end() << endl;
    cout << ship5.get_start() << ship5.get_end() << endl;
    cout << ship6.get_start() << ship6.get_end() << endl;
    cout << ship7.get_start() << ship7.get_end() << endl;
    cout << ship8.get_start() << ship8.get_end() << endl;

    
    player1.add_ship(ship1);
    cout << "Testing add_ship, Expecting 11, Actual: "
         << player1.get_num_ships() << player1.get_remaining_ships() << endl;
    player1.add_ship(ship2);
    cout << "Testing add_ship, Expecting 22, Actual: "
         << player1.get_num_ships() << player1.get_remaining_ships() << endl;
    player1.add_ship(ship3);
    cout << "Testing add_ship, Expecting 33, Actual: "
         << player1.get_num_ships() << player1.get_remaining_ships() << endl;
    player1.add_ship(ship4);
    cout << "Testing add_ship, Expecting 44, Actual: "
         << player1.get_num_ships() << player1.get_remaining_ships() << endl;
    player1.add_ship(ship7);
    cout << "Testing add_ship, Expecting 55, Actual: "
         << player1.get_num_ships() << player1.get_remaining_ships() << endl;
    player1.add_ship(ship8);
    cout << "Testing add_ship, Expecting , Actual: "
         << player1.get_num_ships() << player1.get_remaining_ships() << endl;
    player2.add_ship(ship5);
    cout << "Testing add_ship, Expecting 11, Actual: "
         << player2.get_num_ships() << player2.get_remaining_ships() << endl;
    player2.add_ship(ship6);
    cout << "Testing add_ship, Expecting 22, Actual: "
         << player2.get_num_ships() << player2.get_remaining_ships() << endl;

    
    cout << "Testing attack" << endl;
    // positions which hit
    Player player11("attack");
    Player player22;
    Position start1(4,0);
    Position end1(4,3);
    Ship ship11(start1,end1);
    player11.add_ship(ship11);
    
    Position attack1(4,3);
    cout << "Actual: " << endl;
    player22.attack(player11, attack1);
    cout << player11.get_remaining_ships() << endl;
    player11.print_guess_grid();
    
    Position attack2(8,1);
    cout << "Actual: " << endl;
    player22.attack(player11, attack2);
    cout << player11.get_remaining_ships() << endl;
    player11.print_guess_grid();
    
    Position attack3(4,1);
    cout << "Actual: " << endl;
    player22.attack(player11, attack3);
    cout << player11.get_remaining_ships() << endl;
    player11.print_guess_grid();
    
    Position attack4(4,2);
    cout << "Actual: " << endl;
    player22.attack(player11, attack4);
    cout << player11.get_remaining_ships() << endl;
    player11.print_guess_grid();
    
    Position attack5(4,0);
    cout << "Actual: " << endl;
    player22.attack(player11, attack5);
    cout << player11.get_remaining_ships() << endl;
    player11.print_guess_grid();
    
    Position attack6(4,1);
    cout << "Actual: " << endl;
    player22.attack(player11, attack6);
    cout << player11.get_remaining_ships() << endl;
    player11.print_guess_grid();
    
    Position attack7(8,1);
    cout << "Actual: " << endl;
    player22.attack(player11, attack7);
    cout << player11.get_remaining_ships() << endl;
    player11.print_guess_grid();
    
    cout << "Testing load_grid_file" << endl;
    cout << player1.load_grid_file("grid1.txt");
    cout << player2.load_grid_file("grid2.txt");
    cout << player3.load_grid_file("grid3.txt") << endl;

}

void test_game() {
    cout << "now testing default constructor" << endl;
    Game test_game1;
    test_game1.get_p1().print_grid();
    test_game1.get_p2().print_grid();
    
    cout << "now testing non-default constructor" << endl;
    
    Player player1("testPlayer");
    Player player2("CPU");
    
    Game test_game2(player1, "grid1.txt", player2, "grid2.txt");
    test_game2.get_p1().print_grid();
    test_game2.get_p2().print_grid();
    
    cout << "now testing check_valid_move" << endl;
    cout << test_game1.check_valid_move("1a") << endl;
    cout << test_game1.check_valid_move("2A") << endl;
    cout << test_game1.check_valid_move("1A") << endl;
    cout << test_game1.check_valid_move("10x") << endl;
    cout << test_game1.check_valid_move("4f") << endl;
    cout << test_game2.check_valid_move("7m") << endl;
    cout << test_game2.check_valid_move("7M") << endl;
    
    }


