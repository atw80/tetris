/*
Copyright (C) 2013, Dmitry Ivanov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>



//If you set the width of the height to small, something bad will happen!!!!!!
#define HEIGHT 30//The height of the board
#define WIDTH 10 //The width of the board


class Board {
	public:	
	float color[HEIGHT][WIDTH][3]; //Used for coloring the board
	bool squares[HEIGHT][WIDTH];  //Tells me which squares are occupied
};

class Piece {
	public:
	bool squares[5][5]; //The current piece	

bool tmpSquares[5][5]; //Used as a place holder for rotation

	float color[3];
	//The mid coordinatees of the current piece
	int x;
	int y;
};

class Tetris {
	private:

	
	//The tetris board
	Board board;

	//The active block that is falling
	Piece piece;

	//The different Piece templates
	bool MoveUpdate();

	void NewGame();
	void NewPiece();
	
	void FreeLines();

	void transfer();
	public:
	Tetris();
	void MoveLeft();
	void MoveRight();
	void MoveUp();	
	void MoveDown();
	
	void MoveDrop();

	void MoveRotate();

	void displayTetris();
	void displayScore();
	//Deals with the levels
	unsigned int msecs;
	unsigned int lines;
};

//The following are the pieces
static bool pieces[7][5][5] = 
{
//The I Piece
		{
			{false, false, false, false, false},
			{false, false, false, false, false},
			{false, true , true , true , true},
			{false, false, false, false, false},
			{false, false, false, false, false}
		},{
//The J Piece
			{false, false, false, false, false},
			{false, true , false, false, false},
			{false, true , true , true , false},
			{false, false, false, false, false},
			{false, false, false, false, false}
		},{
//The L Piece
			{false, false, false, false, false},
			{false, false, false, true, false},
			{false, true , true , true , false},
			{false, false, false, false, false},
			{false, false, false, false, false}
		},{
//The O Piece
			{false, false, false, false, false},
			{false, false, true , true , false},
			{false, false, true , true , false},
			{false, false, false, false, false},
			{false, false, false, false, false}
		},{
//The S Piece
			{false, false, false, false, false},
			{false, false, true , true , false},
			{false, true , true , false, false},
			{false, false, false, false, false}
		},{
//The T Piece
			{false, false, false, false, false},
			{false, false, true , false, false},
			{false, true, true, true, false},
			{false, false, false, false, false},
			{false, false, false, false, false}
		},{
//The Z Piece
			{false, false, false, false, false},
			{false, true, true , false, false},
			{false, false, true , true, false},
			{false, false, false, false, false},
			{false, false, false, false, false}
		}
};


