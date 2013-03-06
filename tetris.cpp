#/*
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
include "tetris.h"


void Tetris::NewPiece(){
	//The standard templates
	int ran = rand() % 7;
	memcpy(&piece.squares, &(pieces[ran]), sizeof(piece.squares));

	float r = (float)rand()/(float)RAND_MAX;
	float g = (float)rand()/(float)RAND_MAX;
	float b = (float)rand()/(float)RAND_MAX;
	
	piece.color[0] = r;
	piece.color[1] = g;
	piece.color[2] = b;

	piece.y  = 0;
	piece.x = WIDTH/2;

	if(!MoveUpdate()){
		piece.y++;
		if(!MoveUpdate()){
			NewGame(); //Game is lost
		}
	}
}


void Tetris::NewGame(){
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			board.squares[i][j]=false;

		}
	}


	lines = 0;	
	msecs = 2000;

	NewPiece();
}

void Tetris::MoveLeft(){
	piece.x--;	
	if(!MoveUpdate()){
		piece.x++;
	}
}

void Tetris::MoveRight(){
	piece.x++;	
	if(!MoveUpdate()){
		piece.x--;
	}
}

void Tetris::MoveUp(){
	piece.y--;
	if(!MoveUpdate()){
		piece.y++;
	}
}

void Tetris::MoveDown(){
	piece.y++;
	if(!MoveUpdate()){
		piece.y--;
		//Transfers the current piece to the board
		for(int i = -2;	i <= 2; i++){
			for(int j = -2; j <= 2; j++){
				if(piece.squares[i+2][j+2]){
					board.squares[piece.y + i][piece.x + j] = true;
					board.color[piece.y + i][piece.x + j][0] = piece.color[0];
					board.color[piece.y + i][piece.x + j][1] = piece.color[1];
					board.color[piece.y + i][piece.x + j][2] = piece.color[2];
				}
			}
		}
		FreeLines();
		NewPiece();
	}	
}

void Tetris::FreeLines(){
	//Are there are any new lines to be cleared
	for(int i = HEIGHT-1; i > 0; i--){
		bool lineClear = true;	
		for(int j = 0; j < WIDTH && lineClear; j++){
			if(!board.squares[i][j])
				lineClear = false;
		}


		if(lineClear){
			lines++;
			if(lines%10 == 0){
				msecs=msecs/2;
			}
			for(int j = i; j > 0; j--){
				memcpy(&(board.squares[j]), &(board.squares[j-1]), sizeof(board.squares[j]));
				memcpy(&(board.color[j]), &(board.color[j-1]), sizeof(board.color[j]));	
			}
			i++;
		}
	}
}

//Rotates the current piece by 90 degrees clockwise
void Tetris::MoveRotate(){
	
	memcpy(&piece.tmpSquares, &piece.squares, sizeof(piece.squares));
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			piece.squares[j][4-i]= piece.tmpSquares[i][j];
		}
	}
	
	if(!MoveUpdate()){
		memcpy(&piece.squares, &piece.tmpSquares, sizeof(piece.squares));
	}
/*
(0, 0) -> (0,4) 
(0, 1) -> (1,4)
(0, 2) -> (2,4)
(0, 3) -> (3,4)
(0, 4) -> (4,4) 

(1, 0) -> (0,3)
(1, 1) -> (1,3)
(1, 2) -> (2,3)
(1, 3) -> (3,3)
(1, 4) -> (4,3) 

(2, 0) -> (0,2)
(2, 1) -> (1,2)
(2, 2) -> (2,2)
(2, 3) -> (3,2)
(2, 4) -> (4,2)

(3, 0) -> (0,1) 
(3, 1) -> (1,1)
(3, 2) -> (2,1)
(3, 3) -> (3,1)
(3, 4) -> (4,1)

(4, 0) -> (0,0) 
(4, 1) -> (1,0)
(4, 2) -> (2,0)
(4, 3) -> (3,0) 
(4, 4) -> (4,0) 
*/

}

//Returns true if piece does not intersects the board, otherwise false
bool Tetris::MoveUpdate(){
	for(int i = -2; i <= 2; i++){
		for(int j = -2; j <= 2; j++){
			if(piece.squares[i+2][j+2]){
				if((piece.y+i) < 0 || (piece.y+i) >= HEIGHT  || (piece.x+j) < 0 || (piece.x+j) >= WIDTH){
					return false;
				}
				if(board.squares[piece.y+i][piece.x+j]){
					return false;
				}
			}
		}
	}
return true;
}


void Tetris::displayTetris(){
	glPushMatrix();	

	glScalef(1, -1, 1);
	glTranslatef(-WIDTH/2, -HEIGHT/2, 0);	
	
	
	//Draws the piece
	glColor3fv(piece.color);
	for(int i = -2; i <= 2; i++){
		for(int j = -2; j <= 2; j++){
			if(piece.squares[i+2][j+2]){
				glRectf(piece.x + j, piece.y + i, piece.x + j + 1 , piece.y + i + 1);	
			}
		}
	}


	//Draws the board
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			
			if(board.squares[i][j]){
				glColor3fv(board.color[i][j]);
				glRectf(j, i, j+1, i+1);
			}
			
			glColor3f(0.4, 0.4, 0.4);
			glBegin(GL_LINE_LOOP);
			glVertex2f(j, i);
			glVertex2f(j, i+1);
			glVertex2f(j+1, i+1);
			glVertex2f(j+1, i);
			glEnd();
		}
	}

	glPopMatrix();
	
	displayScore();
}

void Tetris::displayScore(){
	glPushMatrix();
	glTranslatef(4*WIDTH/3, 0, 0);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-1.5, 3);


	char str[30];
	sprintf(str, "Lines: %d\n", lines);

	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)str);
	
	
	sprintf(str, "Level: %d\n", lines/10);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)str);
	glPopMatrix();
}



Tetris::Tetris(){
	srand(time(NULL)); //Seed the random variable


	NewGame();
}
