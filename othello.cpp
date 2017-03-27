/*
 * othello.cpp
 *
 *  Created on: Feb 9, 2017
 *      Author: Austin
 */
#include <iostream>
#include <cstring>
#include "othello.hpp"
using namespace std;

//Member Function Definitions

// board: get size from user
void othello_board::get_size(){
	int input_size;
	cout << "Enter board size: ";
	cin >> input_size;
	othello_board::size = input_size;
}

// board: allocate board size and set up starting 4 pieces
void othello_board::allocate_board_size(){
	int size = othello_board::size;
	this->board = new chip*[othello_board::size];
	for(int i = 0; i < othello_board::size; i++){
		board[i] = new chip[othello_board::size];
	}

	int mid = size / 2;
	othello_board::board[mid - 1][mid - 1].chip_color = 'W';
	othello_board::board[mid - 1][mid].chip_color = 'B';
	othello_board::board[mid][mid - 1].chip_color = 'B';
	othello_board::board[mid][mid].chip_color = 'W';
}

// board: display board to console
void othello_board::display_board(){
	//rows
	for(int i = 0;i < othello_board::size; i++){
		//columns
		for(int j = 0; j < othello_board::size; j++){
			switch(othello_board::board[i][j].chip_color){
			case 'O' : cout << "_ ";
					   break;
			case 'W' : cout << "O ";
					   break;
			case 'B' : cout << "X ";
					   break;
			default : cout << "Error"; break;
			}
		}
		cout << "\n";
	}
}

// board: check offset position then count and return how many chips to flip by checking until a chip of the same color is found.
//	  (or no matching color is found in which case the function returns 0)
int othello_board::to_check(char color, int x, int y, int x_off, int y_off){

	int new_x = x + x_off;
	int new_y = y + y_off;
	int count = 0;
	int temporary_count;

	while(1){
		if((new_x >= othello_board::size) || (new_x < 0) || (new_y >= othello_board::size) || (new_y < 0)){
			count = 0;
			break;
		}else if(othello_board::board[new_x][new_y].chip_color == color){
			break;
		}else if(othello_board::board[new_x][new_y].chip_color == 'O' ){
			count = 0;
			break;
		}
		count++;

		new_x += x_off;
		new_y += y_off;
	}

	temporary_count = count;

	new_x = x + x_off;
	new_y = y + y_off;

	while(count != 0){
		othello_board::board[new_x][new_y].chip_color = color;
		count--;
		new_x += x_off;
		new_y += y_off;
	}
	return temporary_count;
}

// board: check each of the 8 offset postions necessary to determine a legal move/flip
//	  then return the amount of chips flipped. (actual flipping takes place in 
//	  to_check function that is called for each position)
int othello_board::check(char color, int x, int y){
	int count = 0;

	//check each offset position
	count += to_check(color, x, y, -1, 0);

	count += to_check(color, x, y, 1, 0);

	count += to_check(color, x, y, 0, -1);

	count += to_check(color, x, y, 0, 1);

	count += to_check(color, x, y, -1, -1);

	count += to_check(color, x, y, 1, -1);

	count += to_check(color, x, y, -1, 1);

	count += to_check(color, x, y, 1, 1);

	if(count == 0){
		cout << "Invalid Move.\n";
	}else{
		othello_board::board[x][y].chip_color = color;
		cout << "Number of chips flipped: " << count << "\n";
	}

	display_board();
	return count;

}

//othello game: play function that executes actual gameplay. Sets up board and 
//		controls player turns.
void othello_game::play(){
	int row, col;
	char current_color;

	board.get_size();
	board.allocate_board_size();
	board.display_board();

	while(1){
		//Player 1 turn
		cout << "Player 1(White('O')) Enter Board Position [-1 -1 if board is full]: ";
		cin >> row >> col;
		current_color = 'W';
		row -= 1;
		col -= 1;

		if((row < 0) || (row > board.size) || (col < 0) || (col > board.size)){
			if((row == -2) && (col == -2)){
				cout << "Board is full! Game Over!\n";
				break;
			}else{
				cout << "Invalid Input.\n";
				break;
			}
		}else{

			board.check(current_color, row, col);
		}

		//Player 2 turn
		cout << "Player 2(Black('X')) Enter Board Position [-1 -1 if board is full]: ";
		cin >> row >> col;
		current_color = 'B';
		row -= 1;
		col -= 1;

		if((row < 0) || (row > board.size) || (col < 0) || (col > board.size)){
			if((row == -1) && (col == -1)){
				cout << "Board is full! Game Over!\n";
				break;
			}else{
				cout << "Invalid Input.\n";
				break;
			}
		}else{

			board.check(current_color, row, col);
		}

	}

}

//Main function that creates a new game object and executes a game.
int main(){
	othello_game Game;
	Game.play();
	return 0;
}

