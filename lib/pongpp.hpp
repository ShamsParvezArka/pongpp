#ifndef PONGPP_HPP_
#define PONGPP_HPP_

#include "raylib.h"

void control_paddle(Rectangle &paddle1, Rectangle &paddle2);

void accelarate(Rectangle &ball);
void reset_speed(Rectangle &ball);

void start_game();
void welcome_screen(Rectangle &wball1, Rectangle &wball2, Vector2 &wball_speed);

namespace doted {
	void drawline_y(int spoint, int epoint, short gap, Color color);
}
namespace draw {
	void blinking_text(const char *text, int x, int y, int font_size, Color color);
}
void draw_score(short p1_score, short p2_score, short font_size, Color color);

#endif //PONGPP_HPP_
