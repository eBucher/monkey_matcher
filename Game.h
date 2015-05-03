// File: Game.h
// Author: Erich Bucher
// Project: CS215 Project 3 Spring 2015
// Description of file contents: This is the .h file that
//   corresponds with Game.cpp to define the Game class.

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

	// Public Functions
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
private:

	// Private Functions
	void FillIn();
	void SetUp(CRect window);
	void FirstClick(int row, int col, CFrameWnd * windowP);
	void SecondClick(int row, int col, CFrameWnd * windowP);
	int Check();
	void Drop(CFrameWnd * windowP);
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
	// Private Variables
	bool firstClickDone;
	bool madeMatches;
	bool showSquareSelector;
	bool startNewGame;
	CBitmap bgImage;
	CBitmap squareSelector;	char highScore;
	CRect dataRect;
	CRect gameRect;
	CRect helpBtnRect;
	CRect NGBtnRect;
	GameSquare ** grid;
	int bottomTileBottomY;
	int clickedRow1, clickedCol1;
	int clickedRow2, clickedCol2;
	int leftTileLeftX;
	int matchesMade;
	int movesLeft;
	int numMoves;
	int numRows, numCols;
	int rightTileRightX;
	int score;
	int sqHeight;
	int sqWidth;
	int topTileTopY;
	int windowHeight;
	int windowWidth;

};

#endif
