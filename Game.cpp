// File: Game.cpp
// Author: Erich Bucher
// Project: CS215 Project 3 Spring 2015
// Description of file contents:

#include "Game.h"
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>


static CBitmap images[NUMIMAGES];

using namespace std;

Game::GameSquare::GameSquare()
{
	// This function will initially set every what value to 0
	// and every flag to NONE.

	what = 0;
	flag = NONE;
	// Each GameSquare is positioned in the init function.
	// The position of the square is not changed - only the what value
	// for determining which color it should show and the flag
	// for determining if it was part of a match and needs replaced.

}

void Game::GameSquare::Display(CDC * deviceContextP)
{
	// This function will:
	CDC memDC;
	memDC.CreateCompatibleDC(deviceContextP);
	memDC.SelectObject(&images[what]);
	deviceContextP->TransparentBlt(where.left + 1, where.top + 1,
	where.Width() - 1, where.Height() - 1, &memDC, 0, 0,
		80, 80, RGB(82, 82, 82));
}

Game::Game()
{
	// This function will:

	numRows = 1;
	numCols = 1;
	grid = new GameSquare *[3];
	for (int r = 0; r < 3; r++)
		grid[0] = new GameSquare[3];
	int res = bgImage.LoadBitmap(CString("BACKGROUND_BMP"));
	int res0 = images[0].LoadBitmapW(CString(""));
	int res1 = images[1].LoadBitmapW(CString("RED_BMP"));
	int res2 = images[2].LoadBitmapW(CString("ORANGE_BMP"));
	int res3 = images[3].LoadBitmapW(CString("YELLOW_BMP"));
	int res4 = images[4].LoadBitmapW(CString("GREEN_BMP"));
	int res5 = images[5].LoadBitmapW(CString("BLUE_BMP"));
	int res6 = images[6].LoadBitmapW(CString("PURPLE_BMP"));

}

Game::~Game()
{
	// This function will:

	for (int r = 0; r < numRows + 2; r++)
		delete[] grid[r];
	delete[] grid;
}

void Game::Init(int R, int C, int M)
{
	// This function will:

	// Reset all of the variables from the last game
	numRows = R;
	numCols = C;
	numMoves = M;
	movesLeft = M;
	score = 0;
	clickedRow1 = clickedCol1 = clickedRow2 = clickedCol2 = 0;
	// Create Grid, which is a 2d array of gridsquares
	grid = new GameSquare *[numRows + 2];
	for (int r = 0; r < numRows + 2; r++)
	{
		grid[r] = new GameSquare[numCols + 2];
	}
	// Position each gamesquare
	for (int r = 1; r <= numRows; r++)
	{
		for (int c = 1; c <= numCols; c++)
		{
			grid[r][c].where.left = leftTileLeftX + (sqWidth)* (c - 1);
			grid[r][c].where.top = topTileTopY + sqHeight * (r - 1);
			grid[r][c].where.right = leftTileLeftX + (sqWidth)* c + 1;
			grid[r][c].where.bottom = topTileTopY + (sqHeight)* r + 1;

		}
	}
	// Put your code for generating a maze here (nothing is added here yet)
	FillIn();

}

void Game::Instructions(CFrameWnd * windowP)
{
	// This function will:

	CString message = "GOAL: Make as many combinations of three identical\n"
		"colors either vertically or horizontally within the\n"
		"allotted number of moves.\n\n"
		"MOVEMENT: When prompted, type in the column letter\n"
		"and MORE INSTRUCTIONS GO HERE!!!!";

	CString title = "Instructions";
	windowP->MessageBox(message, title);
}

void Game::FillIn()
{
	// This function will fill in each GridSquare.what with a random number
	// that will correspond with a color.
	for (int r = 1; r <= numRows; r++)
		for (int c = 1; c <= numCols; c++)
			grid[r][c].what = 1 + rand() % NUMSYMS;

}

void Game::Display(CFrameWnd * windowP)
{
	// This function will:

	CPaintDC dc(windowP);
	CRect rect;
	windowP->GetClientRect(&rect);
	SetUp(rect);
	dc.SetBkMode(TRANSPARENT);
	CDC memDC;
	// Paints the background
	int res = memDC.CreateCompatibleDC(&dc);
	memDC.SelectObject(&bgImage);
	dc.TransparentBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, 1418, 698, SRCCOPY);
	DeleteDC(memDC);

	// This paints the gamesquares
	for (int r = 1; r <= numRows; r++)
		for (int c = 1; c <= numCols; c++)
			grid[r][c].Display(&dc);
	SetTextColor(dc, RGB(248, 234, 220));
	ShowInformation(&dc);
}

void Game::ShowInformation(CDC * deviceContextP)
{
	// This function is called to put the text on the left side of the screen.
	CDC memDC;
	memDC.CreateCompatibleDC(deviceContextP);
	// Create a new font that will be used for the text
	HFONT newfont = CreateFont(100, 0, 0, 0, 0, FALSE, 0, 0, 0, 1, 1, 1, DEFAULT_QUALITY, L"Arial Black");
	deviceContextP->SelectObject(newfont);
	// These CStrings are for converting integer values to CStrings so they can be displayed on the screen
	CString scoreCString;
	scoreCString.Format(_T("%i"), score);
	CString movesLeftCString;
	movesLeftCString.Format(_T("%i"), movesLeft);
	// This is where all the text gets put on the screen.
	CString Message = "Score: " + scoreCString + "\nMoves Left: " + movesLeftCString;
	deviceContextP->DrawText(Message, CRect(25, 130, 700, 800), DT_LEFT); // Draws text on the screen in a rectangle
}

void Game::Click(int y, int x, CFrameWnd * windowP)
{
	// This function will handle everything that needs to happen when the user makes a click.
	float col = 0; // col starts as 0 by default.
	// If the click is within the game's borders, col changes to which square is clicked.
	if (leftTileLeftX <= x <= rightTileRightX)
	{
		col = ceil((x - leftTileLeftX * 1.0) / sqWidth);
	}

	int row = 0; // row starts as 0 by default.
	// If the click is within the game's borders, row changes to which square is clicked.
	if (topTileTopY <= y <= bottomTileBottomY)
	{
		row = ceil((y - topTileTopY * 1.0) / sqHeight);
	}

	// If the click wasn't in the game, then this function ends in this if statement.
	if (row < 1 || row > numRows || col < 1 || col > numCols)
	{
		return;
	}
	// This is just here for testing purposes.
	AfxTrace(_T("YOU CLICKED IN THE GAME SECTION\n"));
	// This handles the click differently depending on if was valid and whether
	// it is the first or second click that the user makes.
	if (firstClickDone == false)
		FirstClick(row, col, windowP);
	else
		SecondClick(row, col, windowP);
}

void Game::Message(CFrameWnd * windowP)
{
	// This function will pop up a window at the end of a game.

	CString message = "Put your end of game message here.\nUse backslash and n to create\nmultiple lines.";
	CString title = "Winner";
	windowP->MessageBox(message, title);
}


bool Game::Done()
{
	// This function will:

	return false;
}



void Game::SetUp(CRect rect)
{
	// This function will:

	windowHeight = rect.Height();
	windowWidth = rect.Width();
	// Creates the area that the game will be played in
	gameRect = CRect(leftTileLeftX, topTileTopY, rightTileRightX, bottomTileBottomY);
	dataRect = CRect(0, 0, leftTileLeftX, bottomTileBottomY);


}

void Game::FirstClick(int row, int col, CFrameWnd * windowP)
{
	// This function will handle the first click that the user
	// makes on a turn.
	firstClickDone = true;
	clickedRow1 = row;
	clickedCol1 = col;

}

void Game::SecondClick(int row, int col, CFrameWnd * windowP)
{
	// This function will:
	// Check to see if the user clicked the same gamesquare twice.
	// If they did, the first one is unselected.
	if (row == clickedRow1 && col == clickedCol1)
	{
		clickedRow1 = clickedRow2 = clickedCol1 = clickedCol2 = 0;
		firstClickDone = false;
	}
	// If the click was valid and not the same as the first, this section is run:
	else
	{
		// update the variables storing which squares are clicked.
		clickedRow2 = row;
		clickedCol2 = col;
		swap(grid[clickedRow1][clickedCol1].what,
			grid[clickedRow2][clickedCol2].what);
		swap(grid[clickedRow1][clickedCol1].flag,
			grid[clickedRow2][clickedCol2].flag);
		// Update the screen
		Display(windowP);
		modified = true;
		AfxTrace(_T("WE'RE IN THE SECOND CLICK FUNCTION\n"));
		//system("sleep 2"); // FIGURE OUT A WAY TO LAG IT
		firstClickDone = false;
		while (Check()) // While there is atleast one match
		{
			Drop();
			//system("sleep 1");
			Replace();
			//system("sleep 1");
		}
		clickedRow1 = clickedRow2 = clickedCol1 = clickedCol2 = 0;
		movesLeft--;
	}

}

int Game::Check()
{
	// This function will check every game square and see if it is part
	// of either a vertical or horizontal match. At the end it will
	// return the number of matches.
	int matches = 0;
	for (int i = 1; i <= numRows; i++)
		for (int j = 1; j <= numCols; j++)
		{
			if (IsVerticalMatch(i, j))
			{
				HandleVerticalMatch(i, j);
				matches++;
			}
			if (IsHorizontalMatch(i, j))
			{
				HandleHorizontalMatch(i, j);
				matches++;
			}
		}
	if (matches > 0)
		score += pow(3, matches);
	return matches;
}

void Game::Drop()
{
	// This function will shift down gamesquares in each column to fill in any
	// gaps. Empty GameSquares at the top are filled by the Replace Function.
	bool shiftDown;
	int checkingRow;
	int i, j;
	// Loop through each column
	for (j = 1; j <= numCols; j++)
	{
		// Loop through each row backwards to move NONEs down.
		for (i = numRows - 1; i >= 1; i--)
		{
			shiftDown = true;
			checkingRow = i;
			while (shiftDown && checkingRow < numRows)
			{
				if (grid[checkingRow][j].flag == GOOD)
				{
					shiftDown = false;
				}
				else if (grid[checkingRow][j].flag == NONE &&
					grid[checkingRow + 1][j].flag == GOOD)
				{
					swap(grid[checkingRow][j].what,
						grid[checkingRow + 1][j].what);
					swap(grid[checkingRow][j].flag,
						grid[checkingRow + 1][j].flag);
					//Display();
					//system("sleep .2");
				}
				else
				{
					shiftDown = false;
				}
				checkingRow++;
			}
		}
	}

}

void Game::Replace()
{
	// This function will go through every square and see if its flag is marked
	// to GOOD. If it is, the square's what value will be randomly changed
	// as if a new square had dropped down.
	for (int i = 1; i <= numRows; i++)
		for (int j = 1; j <= numRows; j++)
		{
			if (grid[i][j].flag == GOOD)
			{
				grid[i][j].what = 1 + rand() % NUMSYMS;
				grid[i][j].flag = NONE;
			}
		}
	//Display();

}

bool Game::IsVerticalMatch(int row_idx, int col_idx)
{
	// Given a coordinate, this function will see if it is the center of a vertical
	// match and return true if it is. Otherwise, it will return false.
	int what_value = grid[row_idx][col_idx].what;
	if (grid[row_idx - 1][col_idx].what == what_value &&
		grid[row_idx + 1][col_idx].what == what_value &&
		what_value != 0)
	{
		return true;
	}
	return false;
}

bool Game::IsHorizontalMatch(int row_idx, int col_idx)
{
	// Given a coordinate, this function will see if it is the center of a
	// horizontal match and return true if it is. Otherwise, it will return false.
	int what_value = grid[row_idx][col_idx].what;
	if (grid[row_idx][col_idx - 1].what == what_value &&
		grid[row_idx][col_idx + 1].what == what_value &&
		what_value != 0)
	{
		return true;
	}
	return false;
}

bool Game::HandleVerticalMatch(int row_idx, int col_idx)
{
	// Given a specific game square, this function will see if it is
	// in the middle of a vertical match. Squares that are part
	// of a match will have their flag set to GOOD so
	// they will be removed and replaced.
	grid[row_idx - 1][col_idx].flag = GOOD;
	grid[row_idx][col_idx].flag = GOOD;
	grid[row_idx + 1][col_idx].flag = GOOD;
	return false;
}

bool Game::HandleHorizontalMatch(int row_idx, int col_idx)
{
	// Given a specific game square, this function will see if it is
	// in the middle of a horizontal match. Squares that are part
	// of a match will have their flag values set to GOOD so
	// they will be removed and replaced.
	grid[row_idx][col_idx - 1].flag = GOOD;
	grid[row_idx][col_idx].flag = GOOD;
	grid[row_idx][col_idx + 1].flag = GOOD;
	return false;
}