// File: GameApp.cpp
// Author: 
// Project: CS215 Project 3 Spring 2015
// Description of file contents: This file creates the window for the game.

#include <afxwin.h>
#include "GameApp.h"


BOOL GameApp::InitInstance()
{
	// This function will set up everything for the window to appear.

	m_pMainWnd = new GameWin();
	// This line fixes the window size so that it is the same on
	// every computer.
	m_pMainWnd->MoveWindow(100, 100, 1440, 749);
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

GameApp GameApp;