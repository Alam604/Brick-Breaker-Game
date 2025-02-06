#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;
HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

const int ROW_SIZE = 24, COL_SIZE = 60;
int paddle_r = 21, paddle_c = 30;
int ball_r = 15, ball_c = 30;
int score = 0, level = 1, brick_count = 0;
bool game = true;
int choice;

void gameloop(char map[][COL_SIZE]);
void level_loop();
void speed_controler(int& ball_speed_limit);
void instructions();
void credit();
int input_validation();
int input_validation_2();
void exit();
void credit();
void hideCursor();
void showCursor();
void moveCursorToTop();
void initializeMap(char map[][COL_SIZE]);
void print_map(char map[][COL_SIZE]);
void paddle(char map[][COL_SIZE]);
void paddle_movement(char map[][COL_SIZE], char direction);
void ball_movement(char map[][COL_SIZE], int& ball_r, int& ball_c, int& ball_dx, int& ball_dy);
void brick(char map[][COL_SIZE], int brick_limit);
void ball(char map[][COL_SIZE]);
void exit();
void looser_screen();
void looser_screen();
void menu();

int main() {
	hideCursor();
	menu();
	return 0;
}

void menu() {   // menu
	SetConsoleTextAttribute(hconsole, 8);
	cout << "\n\n\n\n\n  \t\t\t\t\t\t\tWELCOME TO BRICK BREAKER" << endl;
	SetConsoleTextAttribute(hconsole, 14);
	cout << "\n\n\n  \t\t\t\t\t\t\tGAME IS ABOUT TO START" << endl;
	SetConsoleTextAttribute(hconsole, 11);
	cout << "\n\n  \t\t\t\t\t\t\t\t\t\t1. NEW GMAE \n\n\t\t\t\t\t\t\t\t\t\t2. INSTUCTIONS \n\n\t\t\t\t\t\t\t\t\t\t3. EXIT \n\n\t\t\t\t\t\t\t\t\t\t4. CREDIT " << endl;
	cout << "\n\n\t\t\t\t\t\t\tSelect option (1,2,3,4) : ";
	choice = input_validation();
	for (; choice > 5 || choice < 1;) {
		cin >> choice;
	}
	if (choice == 1) {   // it is starting the game
		system("cls");
		level_loop();
	}
	else if (choice == 2) { //pisplaying the instructions
		system("cls");
		instructions();
	}
	else if (choice == 3) {  // exiting the game
		system("cls");
		exit();
		system("pause");

	}
	else if (choice == 4) {    //project information
		system("cls");
		credit();
	}

}

void hideCursor() {    // hide the cursor
	cout << "\033[?25l" << flush;
}

void showCursor() {	  // Show the cursor
	cout << "\033[?25h\033[?25J" << flush;
}

void moveCursorToTop() { // Move the cursor to the top-left corner
	cout << "\033[H" << flush;
}

int input_validation() {   // function for the validation of input in the main menu
	int number;

	cin >> number;
	for (; cin.fail() || number < 1 || number > 4;) {
		cin.clear();
		cin.ignore();
		cout << "\n \t\t\t\t\t\t\tINVALID! Enter again : ";
		cin >> number;
	}
	return number;
}
int input_validation_2() {   // function for the validation of input in other sections 
	int number;

	cin >> number;
	for (; cin.fail() || number != 1;) {
		cin.clear();
		cin.ignore();
		cout << "\n \t\t\t\t\t\t\tINVALID! Enter again : ";
		cin >> number;
	}
	return number;
}

void instructions() {   //instructions displaying on screen
	int input;
	SetConsoleTextAttribute(hconsole, 14);
	cout << "\n\n\n\n\n  \t\t\t\t\t\t\tYOU CAN MOVE THE BRICK BY FOLLOWING" << endl;
	SetConsoleTextAttribute(hconsole, 11);
	cout << "\n\n  \t\t\t\t\t\t\t\t* PRESS 'a' FOR MOVING THE PADDLE LEFT" << endl;
	cout << "\n  \t\t\t\t\t\t\t\t* PRESS 'd' FOR MOVING THE PADDLE RIGHT" << endl;
	cout << "\n  \t\t\t\t\t\t\t\tSCORE : " << endl;
	cout << "\n  \t\t\t\t\t\t\t\t* Hitting each brick will add up 2 points." << endl;
	cout << "\n  \t\t\t\t\t\t\t\t* score will be reset after every level. " << endl;
	cout << "\n  \t\t\t\t\t\t\t\tLEVEL : " << endl;
	cout << "\n  \t\t\t\t\t\t\t\t* After breaking all the bricks, level will be increased" << endl;
	cout << endl << "\n\t\t\t\t\t\t\t\t* After hitting the floor, all levels will be rest " << endl;
	SetConsoleTextAttribute(hconsole, 14);
	cout << "\n\n\n\n  \t\t\t\t\t\t\tEnter 1 to go back to main menu : ";
	input = input_validation_2();      //input validation
	if (input == 1)
		system("cls");
	menu();
}
void credit() {        // displaying project information
	int input;
	cout << "\n\n\n\n\n" << endl;
	SetConsoleTextAttribute(hconsole, 11);
	cout << "\n  \t\t\t\t\t\t\t\t* NAME : ALAM DAD" << endl;
	cout << "\n  \t\t\t\t\t\t\t\t* ROLL NO. : 24F-3031 " << endl;
	cout << "\n  \t\t\t\t\t\t\t\t* SECTION : 1" << endl;
	cout << "\n  \t\t\t\t\t\t\t\t* BSSE" << endl;
	SetConsoleTextAttribute(hconsole, 14);
	cout << "\n\n\n\n  \t\t\t\t\t\t\tEnter 1 to go back to main menu : ";
	input = input_validation_2();    //input validation
	if (input == 1)
		system("cls");
	menu();
}
void initializeMap(char map[][COL_SIZE]) {
	//////////////////////////////////////////////////

	paddle_r = 21, paddle_c = 30;            // these are initialize here again to initialize the game again in the next levels
	ball_r = 15, ball_c = 30;
	score = 0, level = 1, brick_count = 0;
	game = true;

	//////////////////////////////////////////////////
	for (int i = 0; i < ROW_SIZE; i++) {           // initializing the map boundary
		for (int j = 0; j < COL_SIZE; j++) {
			map[i][j] = ' ';
		}
	}

	for (int i = 0; i < ROW_SIZE; i++) {
		map[i][0] = '|';
		map[i][COL_SIZE - 1] = '|';
	}
	for (int i = 0; i < COL_SIZE; i++) {

		map[0][i] = '-';
		map[ROW_SIZE - 1][i] = '-';
	}
}



void print_map(char map[][COL_SIZE]) {     //printing the map 


	moveCursorToTop();

	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COL_SIZE; j++) {
			if (j == 0)
				cout << "\t\t\t\t\t\t";
			cout << map[i][j];
		}
		cout << endl;
	}
}

void paddle(char map[][COL_SIZE]) {     // paddle to stop the moving towards bottom
	map[paddle_r][paddle_c] = '=';
	map[paddle_r][paddle_c + 1] = '=';
	map[paddle_r][paddle_c - 1] = '=';
	map[paddle_r][paddle_c + 2] = '=';
	map[paddle_r][paddle_c - 2] = '=';
	map[paddle_r][paddle_c + 3] = '=';
	map[paddle_r][paddle_c - 3] = '=';
}
void paddle_movement(char map[][COL_SIZE], char direction) {  // paddle movement
	if (direction == 'd') {
		if (paddle_c < COL_SIZE - 5) // boundary validation for paddle from right
			paddle_c++;
		map[paddle_r][paddle_c - 4] = ' ';  // printing space behind paddle

	}
	else if (direction == 'a') {
		if (paddle_c > 4)  // boundary validation for paddle from lft
			paddle_c--;
		map[paddle_r][paddle_c + 4] = ' ';   // printing space behind paddle
	}

}
void brick(char map[][COL_SIZE], int brick_limit) {    // initializing bricks in the map
	for (int i = 1; i <= brick_limit; i++) {             // brick_limit is number of rows of bricks which are changing in gameloop function
		for (int j = 1; j < COL_SIZE - 1; j++) {
			if (i % 2 != 0 && i < brick_limit) {
				map[i][j] = '#';
				brick_count++;
			}

			else if (j % 2 != 0 && i % 2 == 0) {
				map[i][j] = '#';
				brick_count++;
			}
		}
	}
}

void ball(char map[][COL_SIZE]) {  // ball initialization
	map[ball_r][ball_c] = 'O';
}

// ball_dx is representing X-AXIS and ball_dy is representing Y_AXIS
// ball_r is row of ball and ball_c is column of ball
void ball_movement(char map[][COL_SIZE], int& ball_r, int& ball_c, int& ball_dx, int& ball_dy) {  // ball movement 

	if (map[ball_r][ball_c] == 'O') {
		map[ball_r][ball_c] = ' ';     //printing space behind the ball as the ball moves
	}
	//ball_c + ball_dx is controling left right movement of ball
	if (ball_c + ball_dx < 1 || ball_c + ball_dx > COL_SIZE - 2)
		ball_dx = -ball_dx;

	//ball_r + ball_dy is controling up and down movement of ball
	if (ball_r + ball_dy < 1) {
		ball_dx = -ball_dx;
		ball_dy = -ball_dy;
		map[ball_r][ball_c + 1] = ' ';
		map[ball_r][ball_c - 1] = ' ';
		ball_dx = -ball_dx;
	}

	if (ball_r + ball_dy > ROW_SIZE - 2) {  // ball hitting the bottom 
		game = false;
	}

	if (ball_r + ball_dy == paddle_r && ball_c + ball_dx <= paddle_c + 3 && ball_c + ball_dx >= paddle_c - 3) {   // ball row or column equals paddle row and column
		ball_dy = -ball_dy;
		if (ball_c + ball_dx > paddle_c && ball_c + ball_dx < paddle_c + 3)
			ball_dx = 1;
		else if (ball_c + ball_dx > paddle_c + 2)
			ball_dx = 2;
		else if (ball_c + ball_dx < paddle_c && ball_c + ball_dx > paddle_c - 3)
			ball_dx = -1;
		else if (ball_c + ball_dx < paddle_c - 2)
			ball_dx = -2;
		else  // ball hitting middle paddle 
			ball_dx = 0;

	}

	ball_r += ball_dy;
	ball_c += ball_dx;
	if (map[ball_r][ball_c] == '#') {
		score += 2;
		brick_count--;
		ball_dy = -ball_dy;
	}
	map[ball_r][ball_c] = 'O';


}

void gameloop(char map[][COL_SIZE]) {
	int ball_speed_counter = 0;  // Counter for ball movement
	int ball_speed_limit;  // Number of frames to wait before moving the ball
	int ball_dx = 1, ball_dy = -1;
	char direction = '\0';
	paddle(map);

	while (game) {

		if (_kbhit()) {
			direction = _getch();
			paddle_movement(map, direction);
		}
		speed_controler(ball_speed_limit);
		if (ball_speed_counter >= ball_speed_limit) {
			ball_movement(map, ball_r, ball_c, ball_dx, ball_dy);
			ball_speed_counter = 0;  // Reset counter
		}
		else {
			ball_speed_counter++;  // Increment counter
		}
		paddle(map);
		print_map(map);
		cout << "\t\t\t\t\t\t============================================================" << endl;
		cout << "\t\t\t\t\t\tSCORE : " << score << "\t   BRICK REMANING : " << brick_count << "\t\t LEVEL : " << level << endl;
		cout << "\t\t\t\t\t\t============================================================" << endl;
	}
}

void speed_controler(int& ball_speed_limit) {
	switch (level) {
	case 1:
		ball_speed_limit = 4;
		if (score > 200)
			ball_speed_limit = 3;
		break;

	case 2:
		ball_speed_limit = 3;
		if (score > 200)
			ball_speed_limit = 3;
		break;
	case 3:
		ball_speed_limit = 2;
		break;
	case 4:
		ball_speed_limit = 2;
		break;
	case 5:
		ball_speed_limit = 1;
		break;
	}
}
void exit() {
	cout << "\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t\t\t\t================================" << endl;
	cout << "\t\t\t\t\t\t\t\t|                              |" << endl;
	cout << "\t\t\t\t\t\t\t\t|      THANKS FOR PLAYING      |" << endl;
	cout << "\t\t\t\t\t\t\t\t|                              |" << endl;
	cout << "\t\t\t\t\t\t\t\t================================" << endl;
}
void btw_level_screen() {
	system("cls");
	cout << "\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t\t\t\t================================" << endl;
	cout << "\t\t\t\t\t\t\t\t|                              |" << endl;
	cout << "\t\t\t\t\t\t\t\t|     LEVEL " << level << " COMPLETED        |" << endl;
	cout << "\t\t\t\t\t\t\t\t|                              |" << endl;
	cout << "\t\t\t\t\t\t\t\t================================" << endl;
	cout << "\t\t\t\t\t\t\t\t          SCORE : " << score << endl;
	cout << "\t\t\t\t\t\t\t\t================================" << endl;
	Sleep(1500);
	system("cls");
	cout << "\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t\t\t\t================================" << endl;
	cout << "\t\t\t\t\t\t\t\t|                              |" << endl;
	cout << "\t\t\t\t\t\t\t\t|          NEXT LEVEL          |" << endl;
	cout << "\t\t\t\t\t\t\t\t|                              |" << endl;
	cout << "\t\t\t\t\t\t\t\t================================" << endl;
}
void looser_screen() {
	system("cls");
	cout << "\n\n\n\n";
	cout << "\t\t\t\t\t\t\t\t================================" << endl;
	cout << "\t\t\t\t\t\t\t\t|                              |" << endl;
	cout << "\t\t\t\t\t\t\t\t|\t  GAME OVER\t       |" << endl;
	cout << "\t\t\t\t\t\t\t\t|                              |" << endl;
	cout << "\t\t\t\t\t\t\t\t================================" << endl;
	Sleep(1200);
	SetConsoleTextAttribute(hconsole, 14);
	cout << "\n\n\n\n  \t\t\t\t\t\t\tEnter 1 to go back to main menu : ";
	int input = input_validation_2();
	if (input == 1)
		system("cls");
	menu();
}
void level_loop() {

	char map[ROW_SIZE][COL_SIZE];
	while (level < 6) {
		initializeMap(map);
		int brick_limit = 2;
		brick(map, brick_limit);
		ball(map);
		if (level == 1);

		gameloop(map);
		if (!game) {
			looser_screen();
			break;
		}
		else
			btw_level_screen();
		brick_limit += 2;
		level++;
	}
}