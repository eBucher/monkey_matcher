// File: Game.h
// Author: 
// Project: CS215 Project 3 Spring 2015
// Description of file contents:

#ifndef GAME_H
#define GAME_H

#include <afxwin.h>

#define NUMSYMS 6
#define NUMIMAGES 7

enum flag_types { NONE, SELECTED, POSSIBLE, GOOD };

class Game
{
public:
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
private:
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
	struct GameSquare
	{
		GameSquare();
		void Display(CDC * deviceContextP);
		int what;
		flag_types flag;
		CRect where;
	};
	GameSquare ** grid;
	int numRows, numCols;
	int numMoves;
	int movesLeft;
	int score;
	int multiplier;
	int clickedRow1, clickedCol1;
	int clickedRow2, clickedCol2;
	bool firstClickDone;
	int sqWidth = 80;
	int sqHeight = 80;
	int margin = 15;
	int windowWidth = 1418;
	int windowHeight = 698;
	int leftTileLeftX = 720;
	int topTileTopY = 28;
	int rightTileRightX = 1361;
	int bottomTileBottomY = 669;
	int gameBorder = 5;
	CRect gameRect;
	CRect dataRect;
	CRect specialRect;
	CRect scoreRect;
	CBitmap bgImage;
	CBitmap testImage;
	CBitmap thirdImage;
};

#endif
