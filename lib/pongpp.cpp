#include "pongpp.hpp"
#include "dimensions.hpp"

#include <ctime>
#include "raylib.h"

void control_paddle(Rectangle &paddle1, Rectangle &paddle2)
{
	if (IsKeyDown(KEY_S) && (paddle1.y + paddle1.height) <= screen_height)
		paddle1.y += paddle_speed;
	if (IsKeyDown(KEY_W) && paddle1.y >= 0)
		paddle1.y -= paddle_speed;
	if (IsKeyDown(KEY_DOWN) && (paddle2.y + paddle2.height) <= screen_height)
		paddle2.y += paddle_speed;
	if (IsKeyDown(KEY_UP) && (paddle2.y >= 0)) 
		paddle2.y -= paddle_speed;
}

void accelarate(Rectangle &ball)
{
	if (ball.x < 0)
		ball.x -= da;
	if (ball.x > 0)
		ball.x += da;
	if (ball.y < 0)
		ball.y -= da;
	if (ball.y > 0)
		ball.y += da;
}

void reset_speed(Rectangle &ball)
{
	ball.x = 10;
	ball.y = 10;
}

void welcome_screen(Rectangle &wball1, Rectangle &wball2, Vector2 &wball_speed)
{
	if (wball1.x + wball1.width >= screen_width) {
		wball_speed.x = - wball_speed.x;
		wball1.x = screen_width - wball1.width;
	}
	else if (wball1.x <= 0) {
		wball_speed.x = - wball_speed.x;
		wball1.x = 0;
	}

	if (wball1.y + wball1.height >= screen_height) {
		wball_speed.y = - wball_speed.y;
		wball1.y = screen_height - wball1.height;
	}
	else if (wball1.y <= 0) {
		wball_speed.y = - wball_speed.y;
		wball1.y = 0;
	}

	if (wball2.x + wball2.width >= screen_width) {
		wball_speed.x = - wball_speed.x;
		wball2.x = screen_width - wball2.width;
	}
	else if (wball2.x <= 0) {
		wball_speed.x = - wball_speed.x;
		wball2.x = 0;
	}

	if (wball2.y + wball2.height >= screen_height) {
		wball_speed.y = - wball_speed.y;
		wball2.y = screen_height - wball2.height;
	}
	else if (wball2.y <= 0) {
		wball_speed.y = - wball_speed.y;
		wball2.y = 0;
	}

	wball1.x += wball_speed.x;
	wball1.y += wball_speed.y;
	wball2.x -= wball_speed.x;
	wball2.y -= wball_speed.y;
}

namespace doted {
	void drawline_y(int spoint, int epoint, short gap, Color color)
	{
		for (int i = spoint; i < epoint; i += gap) {
			DrawPixel(screen_width/2, i, color);
		}
	}
}

namespace draw {
	void blinking_text(const char *text, int x, int y, int font_size, Color color)
	{
		if (time(0) % 2 == 0)
			DrawText(text, x, y, font_size, color);
	}
}

void draw_score(short p1_score, short p2_score, short font_size, Color color)
{
	DrawText(TextFormat("%d", p1_score), screen_width/2 - 95, screen_height / 2 - 30, font_size, color);
	DrawText(TextFormat("%d", p2_score), screen_width/2 + 60, screen_height / 2 - 30, font_size, color);
}
