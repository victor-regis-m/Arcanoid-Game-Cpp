/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "Brick.h"
#include "Ball.h"
#include "Paddle.h"
#include "Wall.h"
#include "Sound.h"

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	void LimitPaddleToScreen();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	FrameTimer frameTimer;
	static constexpr int bricksHorizontal = 12;
	static constexpr int bricksVertical = 9;
	static constexpr int brickWidth = 40;
	static constexpr int brickHeight = 15;
	Brick bricks[bricksHorizontal][bricksVertical];
	Paddle pad;
	Color colors[5] = { Color(210, 40, 90), Color(55, 210, 90), Color(80, 140, 190), Color(40, 40, 210), Color(100, 100, 100)};
	Ball ball;
	RectF walls;
	Wall wall;
	int livesCounter = 3;
	Sound soundPad;
	Sound soundBrick;
	/********************************/
	/*  User Variables              */
	/********************************/
};