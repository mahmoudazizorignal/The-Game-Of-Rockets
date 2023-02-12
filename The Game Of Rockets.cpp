/*
 * Assignment 3 - OOP - problem 5&6 in sheet 3 
 *  
 * This code is written by Mahmoud Mamdouh a student at Faculty of Computer Science - Cairo University
 * 		copyright © Mahmoud Mamdouh Abdelaziz
 */


#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <Windows.h>
using namespace std;



#define Human1 1
#define Human2 2
#define Computer -1

int n;
vector<vector<string>> board;
vector<pair<int,int>> First_Rock, Second_Rock;

void display_board();
void set_board();
void set_rock();
bool TakeMove(int Rock, int P);
bool IsThererValidMove(int P);
int isWinner() ;
int minimax(int P, int alpha, int beta);
int PlayAnyGame()
void MainProgram();



int main()
{
	MainProgram();
	return 0;
}











void MainProgram() {
	cout << "****WELCOME TO THE ROCKET GAME****\n";
	cout << "\n" << "Please Determine The Board Size(at least 2): ";
	cin >> n;

	set_rock();
	set_board();
	Sleep(1000);
	system("cls");

	pair<string, int> Player1, Player2;
	cout << "Please Enter Your Name: ";
	cin >> Player1.first;
	Player1.second = Human1;
	Sleep(1000);
	system("cls");

	int option;
	cout << "HI " << Player1.first << ", Do You Want To Play Against:\n";
	cout << "[1] Another Player\n";
	cout << "[2] The Computer\n=> ";
	cin >> option;

	Sleep(1000);
	system("cls");
	if (option == 1)
	{
		cout << "Please Enter The Name Of The Another Player: ";
		cin >> Player2.first;
		Player2.second = Human2;
	}
	else
	{
		cout << "Computer: Let's Go!, " << Player1.first << endl;
		Player2.first = "Computer";
		Player2.second = Computer;
	}
	Sleep(2000);
	system("cls");

	while (true)
	{
		display_board();
		int R;
		cout << "Enter the number of the rock you want to move\n";
		cout << Player1.first << " Turn: ";
		cin >> R;
		Sleep(3000);
		system("cls");

		if (IsThererValidMove(Human1)) {
			while (!TakeMove(R, Human1))
			{
				display_board();
				cout << Player1.first << ", You can't move this rock now!\n";
				cout << "Try another rock, " << Player1.first << ": ";
				cin >> R;
				Sleep(3000);
				system("cls");
			}
		}
		else {
			cout << Player1.first << ", You cannot move rock in this turn\n";
			Sleep(3000);
			system("cls");
		}
		if (isWinner() == 2)
		{
			cout << Player1.first << " Wins!\n";
			display_board();
			break;
		}
		display_board();

		if (!IsThererValidMove(Human2)) {
			cout << Player2.first << ", You cannot move rock in this turn\n";
			Sleep(3000);
			system("cls");
			continue;
		}

		if (Player2.second == Human2) {
			cout << "Enter the number of the rock you want to move\n";
			cout << Player2.first << " Turn: ";
			cin >> R;
			Sleep(3000);
			system("cls");

			while (!TakeMove(R, Human2)) {
				display_board();
				cout << "You can't move this rock now!\n";
				cout << "Try another rock, " << Player2.first << ": ";
				cin >> R;
				Sleep(3000);
				system("cls");
			}
			if (isWinner() == -2)
			{
				cout << Player2.first << " Wins!\n";
				display_board();
				break;
			}
		}
		else {
			cout << "Computer Playing...\n";
			Sleep(2000);
			system("cls");

			
			int BestMove = PlayAnyGame();
			if (BestMove == 0 && !IsThererValidMove(Computer)) {
				cout << "AI cannot make move\n";
				Sleep(3000);
				system("cls");
				continue;
			}
			else if (BestMove == 0) {
				for (int i = 1; i < n - 1; i++)
				{
					if (TakeMove(i, Computer)) {
						BestMove = i;
						break;
					}
				}
			}
			else TakeMove(BestMove, Computer);

			cout << "AI moves Rock " << BestMove << endl;

			Sleep(2000);
			system("cls");

			if (isWinner() == -2)
			{
				cout << Player2.first << " Wins!\n";
				display_board();
				break;
			}
		}
	}
}






void display_board()
{
	cout << setw(5 * n + 2) << setfill('=') << "\n";
	for (int i = 0; i < n; i++)
	{
		cout << "| ";
		for (int j = 0; j < n; j++)
		{
			cout << board[i][j] << " | ";
		}
		cout << endl;
		if (i < n - 1) cout << setw(5 * n + 2) << setfill('-') << "\n";
	}
	cout << setw(5 * n + 2) << setfill('=') << "\n";
}

void set_board()
{
	board.resize(n);
	for (int i = 0; i < board.size(); i++) board[i].resize(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == 0 && i > 0 && i < n - 1) board[i][j] = " >";
			else if (i == 0 && j > 0 && j < n - 1) board[i][j] = "\\/";
			else board[i][j] = "--";
		}
	}
}
void set_rock()
{
	First_Rock.resize(n - 2);
	Second_Rock.resize(n - 2);

	for (int i = 1; i < n - 1; i++)
	{
		First_Rock[i - 1] = { i, 0 };
		Second_Rock[i - 1] = { 0, i };
	}
}
bool TakeMove(int Rock, int P)
{
	int r, c;
	if (P == Human1) {
		r = First_Rock[Rock - 1].first;
		c = First_Rock[Rock - 1].second;

		if (c == n - 1) return false;
		if (c < n - 2 && board[r][c + 1] != "--" && board[r][c + 2] != "--") return false;

		if (board[r][c + 1] == "--") {
			swap(board[r][c], board[r][c + 1]);
			First_Rock[Rock - 1].second++;
		}
		else if (board[r][c + 2] == "--") {
			swap(board[r][c], board[r][c + 2]);
			First_Rock[Rock - 1].second += 2;
		}
	}
	else {
		r = Second_Rock[Rock - 1].first;
		c = Second_Rock[Rock - 1].second;

		if (r == n - 1) return false;
		if (r < n - 2 && board[r + 1][c] != "--" && board[r + 2][c] != "--") return false;

		if (board[r + 1][c] == "--") {
			swap(board[r][c], board[r + 1][c]);
			Second_Rock[Rock - 1].first++;
		}
		else if (board[r + 2][c] == "--") {
			swap(board[r][c], board[r + 2][c]);
			Second_Rock[Rock - 1].first += 2;
		}
	}

	return true;
}
bool IsThererValidMove(int P)
{
	bool check = false;
	if (P == Human1)
	{
		for (int i = 0; i < n - 2; i++)
		{
			int r = First_Rock[i].first;
			int c = First_Rock[i].second;

			if (c < n - 1 && board[r][c + 1] == "--") check = true;
			else if (c < n - 2 && board[r][c + 2] == "--") check = true;
		}
	}
	else
	{
		for (int i = 0; i < n - 2; i++)
		{
			int r = Second_Rock[i].first;
			int c = Second_Rock[i].second;

			if (r < n - 1 && board[r + 1][c] == "--") check = true;
			else if (r < n - 2 && board[r + 2][c] == "--") check = true;
		}
	}

	return check;
}

int isWinner() {
	int cnt1 = 0, cnt2 = 0;
	for (int i = 1; i < n - 1; i++)
	{
		if (board[i][n - 1] != "--") cnt1++;
		if (board[n - 1][i] != "--") cnt2++;
	}
	if (cnt1 == n - 2) return 2;
	if (cnt2 == n - 2) return -2;
	return 0;
}

int PlayAnyGame()
{
	int BestScore = 1000, BestMove = 0;
	
	for (int i = 0; i < n - 2; i++)
	{
		int r = Second_Rock[i].first;
		int c = Second_Rock[i].second;

		if (r == n - 1) continue;
		if (r < n - 2 && board[r + 1][c] != "--" && board[r + 2][c] != "--") continue;

		if (board[r + 1][c] == "--") {
			swap(board[r][c], board[r + 1][c]);
			Second_Rock[i].first++;

			int score = minimax(Human1, -1000, 1000);
			if (score < BestScore) {
				BestScore = score;
				BestMove = i + 1;
			}

			Second_Rock[i].first--;
			swap(board[r][c], board[r + 1][c]);
		}
		else if (board[r + 2][c] == "--") {
			swap(board[r][c], board[r + 2][c]);
			Second_Rock[i].first += 2;

			int score = minimax(Human1, -1000, 1000);
			if (score < BestScore) {
				BestScore = score;
				BestMove = i + 1;
			}

			Second_Rock[i].first -= 2;
			swap(board[r][c], board[r + 2][c]);
		}

	}
	return BestMove;
}

int minimax(int P, int alpha, int beta)
{
	if (isWinner() == 2) return 3;
	if (isWinner() == -2) return -3;

	if (!IsThererValidMove(P)) return (P == Human1 ? Computer : Human1) * 2;

	if (P == Human1) {
		int BestScore = -1000;
		for (int i = 0; i < n - 2; i++)
		{
			int r = First_Rock[i].first;
			int c = First_Rock[i].second;

			if (c == n - 1) continue;
			if (c < n - 2 && board[r][c + 1] != "--" && board[r][c + 2] != "--") continue;

			if (board[r][c + 1] == "--") {
				swap(board[r][c], board[r][c + 1]);
				First_Rock[i].second++;

				int score = minimax(Computer, alpha, beta);
				BestScore = max(BestScore, score);

				First_Rock[i].second--;
				swap(board[r][c], board[r][c + 1]);

				alpha = max(alpha, BestScore);
				if (beta <= alpha) break;
			}
			else if (board[r][c + 2] == "--") {
				swap(board[r][c], board[r][c + 2]);
				First_Rock[i].second += 2;

				int score = minimax(Computer, alpha, beta);
				BestScore = max(BestScore, score);

				First_Rock[i].second -= 2;
				swap(board[r][c], board[r][c + 2]);

				alpha = max(alpha, BestScore);
				if (beta <= alpha) break;
			}
		}
		return BestScore;
	}
	else {
		int BestScore = 1000;
		for (int i = 0; i < n - 2; i++)
		{
			int r = Second_Rock[i].first;
			int c = Second_Rock[i].second;
			
			if (r == n - 1) continue;
			if (r < n - 2 && board[r + 1][c] != "--" && board[r + 2][c] != "--") continue;

			if (board[r + 1][c] == "--") {
				swap(board[r][c], board[r + 1][c]);
				Second_Rock[i].first++;

				int score = minimax(Human1, alpha, beta);
				BestScore = min(BestScore, score);

				Second_Rock[i].first--;
				swap(board[r][c], board[r + 1][c]);

				beta = min(beta, BestScore);
				if (beta <= alpha) break;
			}
			else if (board[r + 2][c] == "--") {
				swap(board[r][c], board[r + 2][c]);
				Second_Rock[i].first += 2;

				int score = minimax(Human1, alpha, beta);
				BestScore = min(BestScore, score);

				Second_Rock[i].first -= 2;
				swap(board[r][c], board[r + 2][c]);

				beta = min(beta, BestScore);
				if (beta <= alpha) break;
			}
		}
		return BestScore;
	}
}