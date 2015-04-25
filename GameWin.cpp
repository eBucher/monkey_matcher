// File: GameWin.cpp
// Author: 
// Project: CS215 Project 3 Spring 2015
// Description of file contents:

#include <afxwin.h>
#include "GameWin.h"
#include <iostream>
#include <mmsystem.h>


GameWin::GameWin()
{
	// This function will:

	CString WindowTitle = "Monkey Matcher";
	// This makes it so the window cannot change sizes.
	DWORD fixedWindow = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	Create(NULL, WindowTitle, fixedWindow);
	numRows = 8;
	numCols = 8;
	numMoves = 20;
	myGame.Init(numRows, numCols, numMoves);
	firstTime = true;
	myGame.Display(this);
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
	// See if the game is over
	myGame.Click(point.y, point.x, this);
	if (myGame.Done())
	{
		myGame.Message(this);
		myGame.Init(numRows, numCols, numMoves);
		Invalidate(FALSE);
	}
	// If the game has changed from the user making a click
	// This is to update the entire window
	if (myGame.modified == true)
	{
		Invalidate(FALSE);
		myGame.modified = false;
	}
}

BEGIN_MESSAGE_MAP(GameWin, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()
