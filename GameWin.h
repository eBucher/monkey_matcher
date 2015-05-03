// File: GameWin.h
// Author: 
// Project: CS215 Project 3 Spring 2015
// Description of file contents: This is the header file for GameWin.cpp and
//   modifying the GameWin class.

#include <afxwin.h>
#include "Game.h"

class GameWin : public CFrameWnd
{
public:
	GameWin();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
private:
	Game myGame;
	bool firstTime;
	DECLARE_MESSAGE_MAP()
	int numRows;
	int numCols;
	int numMoves;
};
