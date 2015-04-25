// File: Game.h
// Author: 
// Project: CS215 Project 3 Spring 2015
// Description of file contents:

#ifndef GAME_H
#define GAME_H

#include <afxwin.h>
#include <string>

#define NUMSYMS 6
#define NUMIMAGES 7

enum flag_types { NONE, SELECTED, POSSIBLE, GOOD };

class Game
{
public:
	// Functions
	Game();
	Game(const Game & other);
	~Game();
	Game & operator = (const Game & other);
	void Init(int R, int C, int M);
	void Instructions(CFrameWnd * windowP);
	void Display(CFrameWnd * windowP);
	void Click(int x, int y, CFrameWnd * windowP);
	void Message(CFrameWnd * windowP);
	bool Done();
	void ShowInformation(CDC * deviceContextP);
	bool modified;
	struct HelpButton
	{
		HelpButton();
		void Display(CDC * deviceContextP);
		CRect where;
		CBitmap HelpButtonImg;
	};
	struct NewGameButton
	{
		NewGameButton();
		void Display(CDC * deviceContextP);
		CRect where;
		CBitmap NGButtonImg;
	};
	HelpButton HButton;
	NewGameButton NGButton;
	CRect gameRect;
	CRect dataRect;
private:
	// Functions
	void FillIn();
	void SetUp(CRect window);
	void FirstClick(int row, int col, CFrameWnd * windowP);
	void SecondClick(int row, int col, CFrameWnd * windowP);
	int Check();
	void Drop();
	void Replace();
	bool IsVerticalMatch(int row_idx, int col_idx);
	bool IsHorizontalMatch(int row_idx, int col_idx);
	bool HandleVerticalMatch(int row_idx, int col_idx);
	bool HandleHorizontalMatch(int row_idx, int col_idx);
	void RandomizeMatches();
	struct GameSquare
	{
		GameSquare();
		void Display(CDC * deviceContextP);
		int what;
		flag_types flag;
		CRect where;
	};
	// Variables
	GameSquare ** grid;
	int numRows, numCols;
	int numMoves;
	int movesLeft;
	int score;
	int clickedRow1, clickedCol1;
	int clickedRow2, clickedCol2;
	bool firstClickDone;
	int sqWidth = 80;
	int sqHeight = 80;
	int windowWidth = 1418;
	int windowHeight = 698;
	int leftTileLeftX = 720;
	int topTileTopY = 28;
	int rightTileRightX = 1361;
	int bottomTileBottomY = 669;
	char highScore;
	bool madeMatches;
	bool startNewGame;
	bool showSquareSelector;
	CRect specialRect;
	CBitmap bgImage;
	CBitmap squareSelector;

};

#endif
