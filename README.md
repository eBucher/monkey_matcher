<p align="center">
    <img src="https://raw.githubusercontent.com/eBucher/monkey_matcher/master/readmeAssets/logo.png">
</p>

<h1 align="center">
  Monkey Matcher
</h1>

Monkey Matcher is a Bejeweled style game that was developed for CS 215 in the Spring of 2015. It was developed using C++ with the Microsoft Foundations Class (MFC) graphics library. 

## Gameplay

<img src="https://raw.githubusercontent.com/eBucher/monkey_matcher/master/readmeAssets/gameplay.png">

The goal of Monkey Matcher is to earn as many points as possible by moving monkeys on the board to match three or more of the same color  in a horizontal or vertical line. Monkies can be moved from and to any position on the board, and bonus points are awarded for aligning more than three monkies on the same turn.

If three or more monkies are aligned, they will be cleared from the screen, the monkies on top of them will be shifted down, and new monkies will fill in the gap on top. If any of the shifted or new monkies creates a set of three, they will be scored and the process will be repeated.

If a monkey has been accidentally selected, it can be unselected by clicking on it again.

After twenty moves, the game will end and your final score will be reported.

## Development

This game was written in C++ and used the MFC graphics library. The easiest way to compile it is to [open it in Visual Studio as an MFC application](https://msdn.microsoft.com/en-us/library/9es9d1k4.aspx). From there, it can be compiled as normal in Visual Studio and an executable file will be produced. 

Currently the MFC graphics library is only compatible with Windows machines. As a result, the game cannot be run on a machine running another operating system.

## Technology used
* C++
* Microsoft Foundation Class graphics library
* Visual Studio

## Known issues
* Occasionally the screen will flicker during an animation.  This has been fixed in most cases but may still happen on some computers.