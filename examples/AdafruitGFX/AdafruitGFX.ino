/***************************************************
Copyright (c) 2021 Luis Llamas
(www.luisllamas.es)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses
****************************************************/
#pragma once

#include <SPI.h>
#include <Wire.h>

#include "UnifiedGFX.h"
#include <Adafruit_SSD1306.h>

#include "CommonExample.h"

const int OLED_RESET = 4;
Adafruit_SSD1306 screen(OLED_RESET);

UGFX::UnifiedAdafruitGFX<uint16_t> uScreen(&screen);

void setup(void)
{
	Serial.begin(115200);
}

void loop(void)
{
	draw(uScreen, SSD1306_BLACK, SSD1306_WHITE);
}
