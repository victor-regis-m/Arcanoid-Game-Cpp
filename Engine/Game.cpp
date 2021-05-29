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
	ball(Vec2(400,510), Vec2(-200, -150)),
	pad(Vec2(400,530)),
	wall(RectF(150,650,10,590), 10 ,Color(200,100,140)),
	soundPad(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav")
{
	for (int j = 0; j < bricksVertical; j++)
	{
		Vec2 startPos = Vec2(160, 30);
		for (int i = 0; i < bricksHorizontal; i++)
		{
			Color c = colors[j%5];
			Vec2 brickPos = Vec2(brickWidth * (i), brickHeight * (j)) + startPos;
			bricks[i][j] = Brick(RectF(brickPos, brickWidth, brickHeight), c);
		}
	}
	walls = wall.GetInnerBounds();
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
	pad.Move(wnd, dt);
	LimitPaddleToScreen();
	ball.Move(dt, pad);
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
		ball.ThrowBall();
	if(ball.DetectWallCollision(walls, dt))
		soundPad.Play();
	for (int i = 0; i < bricksHorizontal; i++)
		for (int j = 0; j < bricksVertical; j++)
			if(ball.DetectBrickCollision(bricks[i][j], dt))
				soundBrick.Play();
	if(ball.DetectPadCollision(pad))
		soundPad.Play();
	if (ball.GetYPosition() > Graphics::ScreenHeight - 20)
	{
		ball.Copy(Ball{ Vec2(pad.PaddlePos().x, 510), Vec2(-200, -150) });
		livesCounter--;
	}
}

void Game::ComposeFrame()
{
	ball.Draw(gfx);
	wall.Draw(gfx);
	for (int i = 0; i < bricksHorizontal; i++)
		for (int j = 0; j < bricksVertical; j++)
			bricks[i][j].Draw(gfx);
	pad.Draw(gfx);
	for (int i = 0; i < livesCounter; i++)
		SpriteCodex::DrawBall(Vec2(Graphics::ScreenWidth - 40 - 30 * i, 20), gfx);
}

void Game::LimitPaddleToScreen()
{
	float padLeftEdge = pad.GetLeftEdgePos();
	float padRightEdge = pad.GetRightEdgePos();
	if (padLeftEdge <= walls.left)
		pad.AdjustPadPosition(walls.left - padLeftEdge);
	if (padRightEdge >= walls.right)
		pad.AdjustPadPosition(walls.right - padRightEdge);

}

