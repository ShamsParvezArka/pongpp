#ifndef PONGPP_HPP_
#define PONGPP_HPP_

#include "raylib.h"

void control_paddle(Rectangle &paddle1, Rectangle &paddle2); // p1, p2 control mechanism
void accelarate(Rectangle &ball);  // accelarate ball after every single hit with paddle
void reset_speed(Rectangle &ball); // reset ball speed
void welcome_screen(Rectangle &wball1, Rectangle &wball2, Vector2 &wball_speed); // welcome screen
void draw_score(short p1_score, short p2_score, short font_size, Color color); // draw p1, p2 score

namespace doted {
	void drawline_y(int spoint, int epoint, short gap, Color color); // draw doted line along Y-axis
}
namespace draw {
	void blinking_text(const char *text, int x, int y, int font_size, Color color); // draw text with blinking effect
}

#endif //PONGPP_HPP_
