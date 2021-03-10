/***************************************************
Copyright (c) 2021 Luis Llamas
(www.luisllamas.es)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses
****************************************************/

#pragma once

#include <M5StickCPlus.h>

#include <UnifiedGFX.h>

#include "CommonExample.h"

class MyGraphicClass : public UGFX::Graphic<bool>
{
public:

	std::int_fast16_t width() { return 40; }
	std::int_fast16_t height() { return 40; }

	void drawPixel(int32_t x, int32_t y, bool color) { Serial.printf("x:%d\ty:%d\n", x, y); }
};

MyGraphicClass uScreen;

void setup(void)
{
	Serial.begin(115200);
}

void loop(void)
{
	uScreen.drawCircle(10, 10, 5, true);

	Serial.println();
	delay(10000);
}
