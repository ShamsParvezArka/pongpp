#include <iostream>
#include <chrono>
#include <ctime>

#include "raylib.h"
#include "lib/pongpp.hpp"
#include "lib/dimensions.hpp"

const float sballx = (float) screen_width/2 - 400;
const float sbally = (float) screen_height/2;

Rectangle ball = {sballx, sbally, bsize, bsize};
Rectangle paddle1 = {10.0, 10.0, 20.0, 90.0};
Rectangle paddle2 = {screen_width - 30.0, screen_height - 70.0, 20.0, 90.0};
Rectangle wball1 = {(float) screen_width/2 - 400.0f, (float) screen_height/2, 15.0f, 15.0f};
Rectangle wball2 = {(float) screen_width/2 + 400.0f, (float) screen_height/2, 15.0f, 15.0f};

Vector2 ball_speed = {10, 10};
Vector2 wball_speed = {10.0f, 10.0f};

// game_state(0, 1, 2, 3) = (normal, puse, resume, win)
short game_state = 0;

short p1_score = 0;
short p2_score = 0;
int tick = 0;

int main(void)
{
	// INITIALIZATION
	InitWindow(screen_width, screen_height, "pong++");
	SetTargetFPS(60);

	InitAudioDevice();
	Sound paddle_hit = LoadSound("assets/paddle_hit.wav");
	Sound wall_hit   = LoadSound("assets/wall_hit.wav");
	Sound score      = LoadSound("assets/score.wav");
	Sound welcome    = LoadSound("assets/welcome.wav");
	Sound win        = LoadSound("assets/win.wav");

	PlaySound(welcome);

	while (!WindowShouldClose()) {
		// UPDATE
		if (IsMouseButtonPressed(0)) {
			game_state = 2;
			StopSound(welcome);
		}

		if (game_state == 0)
			welcome_screen(wball1, wball2, wball_speed);

		if (IsKeyPressed(KEY_SPACE) && game_state != 0) {
			if (game_state == 1)
				game_state = 2;
			else 
				game_state = 1;
		}

		if (IsKeyPressed(KEY_R)) {
			game_state = 2;

			ball.x = sballx;
			ball.y = sbally;

			ball_speed.x = 10;
			ball_speed.y = 10;
			p1_score = 0;
			p2_score = 0;
		}

		if (game_state == 2) {
			control_paddle(paddle1, paddle2);

			// Chunk: Collision Detection
			if (CheckCollisionRecs(paddle1, ball)) {
				PlaySound(paddle_hit);
				accelarate(ball);

				ball_speed.x = -ball_speed.x;
				ball.x += ball_speed.x;
			}
			if (CheckCollisionRecs(paddle2, ball)) {
				PlaySound(paddle_hit);
				accelarate(ball);

				ball_speed.x = -ball_speed.x;
				ball.x += ball_speed.x;
			}

			// Chunk: Boundary detection
			if (ball.x + ball.width >= screen_width) {
				PlaySound(score);
				p1_score++;
				reset_speed(ball);

				ball.x = (float) screen_width/2 - 400.0f;
				ball.y = (float) screen_height/2;
			}
			if (ball.x <= 0) {
				PlaySound(score);
				p2_score++;
				reset_speed(ball);

				ball.x = (float) screen_width/2 + 400.0f;
				ball.y = (float) screen_height/2;
			}
			if (ball.y + ball.height >= screen_height) {
				PlaySound(wall_hit);

				ball_speed.y = -ball_speed.y;
				ball.y = screen_height - ball.height;
			}
			if (ball.y <= 0) {
				PlaySound(wall_hit);

				ball_speed.y = -ball_speed.y;
				ball.y = 0;
			}

			ball.x += ball_speed.x;
			ball.y += ball_speed.y;
		}

		if (p1_score == 10 || p2_score == 10) {
			game_state = 3;
			if (IsSoundPlaying(win) == false)
				PlaySound(win);
		}

		// RENDER
		BeginDrawing();
		{
			ClearBackground(BLACK);

			if (game_state == 0) {
				DrawText("PONG++", screen_width/2 - 165, screen_height/2 - 60, 100, YELLOW);
				draw::blinking_text("left click to start", screen_width/2 - 165, screen_height/2 + 30, 30, GRAY);
				DrawRectangleRec(wball1, WHITE);
				DrawRectangleRec(wball2, WHITE);
			}

			if (game_state == 1) {
				draw::blinking_text("paused", screen_width/2 + 20, screen_height/2 + 200, 80, WHITE);
				doted::drawline_y(0, screen_height, 3, GRAY);
				draw_score(p1_score, p2_score, 80, GRAY);
				DrawRectangleRec(ball, WHITE);
				DrawRectangleRec(paddle1, WHITE);
				DrawRectangleRec(paddle2, WHITE);
			}

			if (game_state == 2) {
				doted::drawline_y(0, screen_height, 3, GRAY);
				draw_score(p1_score, p2_score, 80, GRAY);
				DrawRectangleRec(ball, WHITE);
				DrawRectangleRec(paddle1, WHITE);
				DrawRectangleRec(paddle2, WHITE);
			}

			if (game_state == 3) {
				if (p1_score == 10) {
					DrawText(TextFormat("%d", p1_score), screen_width/2 - 95, screen_height/2 - 30, 80, GREEN);
					DrawText(TextFormat("%d", p2_score), screen_width/2 + 60, screen_height/2 - 30, 80, GRAY);
				}
				if (p2_score == 10) {
					DrawText(TextFormat("%d", p1_score), screen_width/2 - 95, screen_height/2 - 30, 80, GRAY);
					DrawText(TextFormat("%d", p2_score), screen_width/2 + 60, screen_height/2 - 30, 80, GREEN);
				}
				draw::blinking_text("press R to restart", screen_width/2 + 20, screen_height/2 + 150, 40, PURPLE);

				doted::drawline_y(0, screen_height, 3, GRAY);
				DrawRectangleRec(ball, WHITE);
				DrawRectangleRec(paddle1, WHITE);
				DrawRectangleRec(paddle2, WHITE);
			} 
		}
		EndDrawing();
	}
	CloseWindow();

	return 0;
}

