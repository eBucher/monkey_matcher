// File: GameWin.cpp
// Author: 
// Project: CS215 Project 3 Spring 2015
// Description of file contents:

#include <afxwin.h>
#include "GameWin.h"
#include <iostream>

GameWin::GameWin()
{
	// This function will:

	CString WindowTitle = "Monkey Matcher";
	Create(NULL, WindowTitle);
	numRows = 8;
	numCols = 8;
	numMoves = 25;
	myGame.Init(numRows, numCols, numMoves);
	firstTime = true;
}

afx_msg void GameWin::OnPaint()
{
	// This function will:

	myGame.Display(this);
	if (firstTime)
	{
		myGame.Instructions(this);
		firstTime = false;
	}
}

afx_msg void GameWin::OnLButtonDown(UINT nFlags, CPoint point)
{
	// This function will:
	myGame.Click(point.y, point.x, this);
	if (myGame.Done())
	{
		myGame.Message(this);
		myGame.Init(++numRows, ++numCols, numMoves += 5);
		Invalidate(TRUE);
	}
	if (myGame.modified == true)
	{
		InvalidateRect(myGame.gameRect); // added this to try updating the window
		myGame.modified = false;
	}
}

BEGIN_MESSAGE_MAP(GameWin, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()
