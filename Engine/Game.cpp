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
	ball(Vec2(400,515), Vec2(-200, -150)),
	pad(Vec2(400,530)),
	wall(RectF(150,650,10,590), 10 ,Color(200,100,140)),
	soundPad(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav"),
	soundShot(L"Sounds\\laser_shot.wav"),
	lostLifeSound(L"Sounds\\loss_sound.wav"),
	gameOverSound(L"Sounds\\game_over.wav"),
	powerup(false, Vec2(400,300)),
	powerupWall(RectF(148, 652, 8, 555), 6, Color(200, 100, 140)),
	leftShot(Vec2(0,0), false),
	rightShot(Vec2(0,0), false)
{
	for (int i = 0; i < 3; i++)
		tripleBall[i] = Ball(Vec2(0, 0), Vec2(1, 1));
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
	powerupWalls = powerupWall.GetInnerBounds();
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
	if (!gameStarted && !gameOver)
	{
		GameReseter();
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			gameStarted = true;
	}
	if (!gameOver && gameStarted)
	{
		float dt = frameTimer.deltaTime();
		pad.Move(wnd, dt);
		LimitPaddleToScreen();
		MoveBalls(dt);
		if (wnd.kbd.KeyIsPressed(VK_SPACE))
		{
			if (!ball.GetThownState())
				StartGame();
			if (pad.isWeaponActive && !leftShot.isActive && !rightShot.isActive)
			{
				leftShot = Shot(pad.GetLeftCannonPos(), true);
				rightShot = Shot(pad.GetRightCannonPos(), true);
				ammoCounter--;
				soundShot.Play();
			}
		}
		CheckAmmo();
		ShotMovement(dt);
		CheckBrickDestruction(dt);
		BallsWallsCollision(dt);
		BallPadCollision(dt);
		CheckForDeath();
		CheckPowerupPosition();
		if (powerup.IsActive())
		{
			powerup.Move(dt);
			if (pad.PickUpPowerUp(powerup))
				CheckPowerupType();
		}
		TripleBallManager();
	}
	if (gameStarted && gameOver)
	{
		gameStarted = false;
		gameOverSound.Play();
	}
	if (!gameStarted && gameOver)
	{
		if (resetScreenTimer <= 6.0f)
			resetScreenTimer += frameTimer.deltaTime();
		else
			gameOver = false;
	}
}

void Game::ComposeFrame()
{
	if (!gameStarted)
	{
		if(!gameOver)
			SpriteCodex::DrawTitle(340, 240, gfx);
	}
	else
	{
		if (!gameOver)
			DrawBalls();
		wall.Draw(gfx);
		for (int i = 0; i < bricksHorizontal; i++)
			for (int j = 0; j < bricksVertical; j++)
				bricks[i][j].Draw(gfx);
		pad.Draw(gfx);
		ShowLivesLeft();
		powerup.Draw(gfx);
		if (pad.isWallActive)
			powerupWall.Draw(gfx);
		if (leftShot.isActive)
			leftShot.Draw(gfx, walls.top);
		if (rightShot.isActive)
			rightShot.Draw(gfx, walls.top);
	}
	if(gameOver)
		SpriteCodex::DrawGameOver(340, 300, gfx);
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

void Game::StartGame()
{
	gameStarted = true;
	Vec2 direction = (Vec2(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()) - ball.GetPosition()).GetNormalized();
	ball.SetVelocity(direction * ballSpeed);
	ball.ThrowBall();
}

void Game::ShowLivesLeft()
{
	for (int i = 0; i < livesCounter; i++)
		SpriteCodex::DrawBall(Vec2(Graphics::ScreenWidth - 40 - 30 * i, 20), gfx);
}

void Game::CheckForDeath()
{
	if (!tripleBallMode)
	{
		if (ball.GetPosition().y > Graphics::ScreenHeight - 35)
		{
			livesCounter--;
			if (livesCounter >= 0)
			{
				ball = Ball{ Vec2(pad.PaddlePos().x, 515), Vec2(0,0) };
				lostLifeSound.Play();
			}
			else
				gameOver = true;
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			if (tripleBall[i].GetPosition().y > Graphics::ScreenHeight - 35)
			{
				tripleBall[i].isActive = false;
			}
		}
		pad.isTripleBallActive = (tripleBall[0].isActive && tripleBall[1].isActive) 
			|| (tripleBall[0].isActive && tripleBall[2].isActive)
			|| (tripleBall[1].isActive && tripleBall[2].isActive);
	}
}

void Game::CheckPowerupPosition()
{
	if (powerup.GetPosition().y > Graphics::ScreenHeight - 30)
		powerup.Deactivate();
}

void Game::CheckPowerupType()
{
	int type = powerup.GetType();
	if (type == 0)
	{
		pad.isWallActive = true;
		powerupWallLives = 3;
	}
	else if (type == 1)
		pad.isTripleBallActive = true;
	else if (type == 2)
	{
		pad.isWeaponActive = true;
		ammoCounter = 10;
	}
}

void Game::ShotMovement(float dt)
{
	if (leftShot.isActive)
		leftShot.Move(dt, walls.top);
	if (rightShot.isActive)
		rightShot.Move(dt, walls.top);
}

void Game::CheckAmmo()
{
	if (ammoCounter <= 0)
		pad.isWeaponActive = false;

}

void Game::CheckBrickDestruction(float dt)
{
	for (int i = 0; i < bricksHorizontal; i++)
		for (int j = 0; j < bricksVertical; j++)
		{
			if (!tripleBallMode)
			{
				if (ball.DetectBrickCollision(bricks[i][j], dt))
				{
					soundBrick.Play();
					if (Powerups::GeneratePowerUp() && !powerup.IsActive())
						powerup = Powerups(true, bricks[i][j].GetPosition());
				}
			}
			else
			{
				for(int k = 0; k < 3; k++)
					if (tripleBall[k].DetectBrickCollision(bricks[i][j], dt) && tripleBall[k].isActive)
					{
						soundBrick.Play();
						if (Powerups::GeneratePowerUp() && !powerup.IsActive())
							powerup = Powerups(true, bricks[i][j].GetPosition());
					}
			}
			if (rightShot.isActive)
				if (bricks[i][j].isInsideBrick(rightShot.position))
				{
					bricks[i][j].DestroyBrick();
					rightShot.isActive = false;
					if (Powerups::GeneratePowerUp() && !powerup.IsActive())
						powerup = Powerups(true, bricks[i][j].GetPosition());
				}
			if (leftShot.isActive)
				if (bricks[i][j].isInsideBrick(leftShot.position))
				{
					bricks[i][j].DestroyBrick();
					leftShot.isActive = false;
					if (Powerups::GeneratePowerUp() && !powerup.IsActive())
						powerup = Powerups(true, bricks[i][j].GetPosition());
				}
		}
}

void Game::TripleBallManager()
{
	if (pad.isTripleBallActive && !tripleBallMode)
	{
		tripleBallMode = true;
		tripleBall[0] = Ball(ball.GetPosition(), ball.GetSpeed());
		tripleBall[1] = Ball(ball.GetPosition(), ball.GetLeftTripleBallSpeed());
		tripleBall[2] = Ball(ball.GetPosition(), ball.GetRightTripleBallSpeed());
		for (int i = 0; i < 3; i++)
		{
			tripleBall[i].isActive = true;
			tripleBall[i].ThrowBall();
		}
	}
	if (!pad.isTripleBallActive && tripleBallMode)
	{
		tripleBallMode = false;
		for (int i = 0; i < 3; i++)
			if (tripleBall[i].isActive)
				ball = Ball(tripleBall[i].GetPosition(), tripleBall[i].GetSpeed());
		ball.ThrowBall();
	}
}

void Game::DrawBalls()
{
	if (tripleBallMode)
	{
		for (int i = 0; i < 3; i++)
			if (tripleBall[i].isActive)
				tripleBall[i].Draw(gfx);
	}
	else
		ball.Draw(gfx);
}

void Game::MoveBalls(float dt)
{
	if (!tripleBallMode)
		ball.Move(dt, pad);
	else
		for (int i = 0; i < 3; i++)
			if(tripleBall[i].isActive)
				tripleBall[i].Move(dt, pad);
}

void Game::BallsWallsCollision(float dt)
{
	if (!tripleBallMode)
	{
		if (ball.DetectWallCollision(walls, dt))
			soundPad.Play();
		if (pad.isWallActive)
			if (ball.DetectWallCollision(powerupWalls, dt))
			{
				soundPad.Play();
				powerupWallLives--;
			}
	}
	else
		for (int i = 0; i < 3; i++)
		{
			if (tripleBall[i].DetectWallCollision(walls, dt) && tripleBall[i].isActive)
				soundPad.Play();
			if (pad.isWallActive)
				if (tripleBall[i].DetectWallCollision(powerupWalls, dt) && tripleBall[i].isActive)
				{
					soundPad.Play();
					powerupWallLives--;
				}
		}
	if (powerupWallLives <= 0)
		pad.isWallActive = false;
}
void Game::BallPadCollision(float dt)
{
	if (!tripleBallMode)
	{
		if (ball.DetectPadCollision(pad))
			soundPad.Play();
	}
	else
		for (int i = 0; i < 3; i++)
			if (tripleBall[i].DetectPadCollision(pad) && tripleBall[i].isActive)
				soundPad.Play();
}

void Game::GameReseter()
{
	resetScreenTimer = 0;
	livesCounter = 3;
	pad.SetPos(Vec2(400, 530));
	pad.isTripleBallActive = false;
	pad.isWallActive = false;
	pad.isWeaponActive = false;
	victory = false;
	powerup.Deactivate();
	for (int i = 0; i < bricksHorizontal; i++)
		for (int j = 0; j < bricksVertical; j++)
			bricks[i][j].ResetBrick();
	ball = Ball(Vec2(400, 515), Vec2(-200, -150));
}

