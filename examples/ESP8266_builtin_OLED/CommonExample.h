/***************************************************
Copyright (c) 2021 Luis Llamas
(www.luisllamas.es)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses
****************************************************/

#pragma once

void draw(UGFX::IGraphic<uint16_t>& screen, uint16_t background, uint16_t color)
{
	screen.fillScreen(background);

	screen.drawLine(20, 20, 40, 40,  color);
	screen.drawVerticalLine(60, 20, 20,  color);
	screen.drawHorizontalLine(80, 20, 20,  color);

	screen.fillRect(20, 60, 20, 20, color);
	screen.drawRoundRect(60, 60, 20, 20, 5,  color);
	screen.fillRoundRect(100, 60, 20, 20, 5,  color);

	screen.drawCircle(30, 100, 10, color);
	screen.fillCircle(70, 100, 10,  color);

	screen.drawEllipse(30, 140, 15, 8, color);
	screen.fillEllipse(70, 140, 15, 8, color);

	screen.drawTriangle(20, 180, 30, 180, 20, 200,  color);
	screen.fillTriangle(60, 180, 70, 180, 70, 200,  color);

	screen.drawPixel(40, 220,  color);

	screen.fillArc(100, 200, 10, 20, 45, 135, color);

	screen.drawChar(100, 180, 'A', color,  background, 3);
}