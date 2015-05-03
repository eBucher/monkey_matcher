// File: GameWin.cpp
// Author: Erich Bucher
// Project: CS215 Project 3 Spring 2015
// Description of file contents: This file handles the event handling.

#include <afxwin.h>
#include "GameWin.h"
#include <iostream>
#include <mmsystem.h>


GameWin::GameWin()
{
	// This function will create a new window and set values to variables in
	// the GameWin class.
	CString WindowTitle = "Monkey Matcher";
	// This makes it so the window cannot change sizes.
	DWORD fixedWindow = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	Create(NULL, WindowTitle, fixedWindow);
	// Rows, columns, and the number of moves for a game are set here.
	numRows = 8;
	numCols = 8;
	numMoves = 20;
	myGame.Init(numRows, numCols, numMoves);
	firstTime = true;
	myGame.Display(this);
}

afx_msg void GameWin::OnPaint()
{
	// This function will be called when the screen updates.
	myGame.Display(this);
	if (firstTime)
	{
		myGame.Instructions(this);
		firstTime = false;
	}
}

afx_msg void GameWin::OnLButtonDown(UINT nFlags, CPoint point)
{
	// This function will be called when the user presses the left mouse button.
	// See if the game is over
	myGame.Click(point.y, point.x, this);
	if (myGame.Done())
	{
		myGame.Message(this);
		myGame.Init(numRows, numCols, numMoves);
		Invalidate(FALSE);
	}
}

// Include any new event handles in the message map.
BEGIN_MESSAGE_MAP(GameWin, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()
