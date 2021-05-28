/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	frameTimer(),
	ball(Vec2(400,300), Vec2(-400, -300)),
	walls(0, Graphics::ScreenWidth, 0, Graphics::ScreenHeight)
{
	for (int j = 0; j < bricksVertical; j++)
	{
		Vec2 startPos = Vec2(120, 30 + j);
		for (int i = 0; i < bricksHorizontal; i++)
		{
			Color c = colors[j%5];
			Vec2 brickPos = Vec2(brickWidth * (i), brickHeight * (j)) + startPos;
			bricks[i][j] = Brick(RectF(brickPos, brickWidth, brickHeight), c);
			startPos += Vec2(2, 0);
		}
	}


}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	float dt = frameTimer.deltaTime();
	ball.Move(dt);
	ball.DetectWallCollision(walls, dt);
	for (int i = 0; i < bricksHorizontal; i++)
		for (int j = 0; j < bricksVertical; j++)
			ball.DetectBrickCollision(bricks[i][j], dt);
}

void Game::ComposeFrame()
{
	ball.Draw(gfx);
	for (int i = 0; i < bricksHorizontal; i++)
		for (int j = 0; j < bricksVertical; j++)
			bricks[i][j].Draw(gfx);
}

