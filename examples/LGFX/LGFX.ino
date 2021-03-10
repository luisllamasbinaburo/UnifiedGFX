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

#define LGFX_AUTODETECT
#include <LovyanGFX.hpp>
#include <UnifiedGFX.h>

#include "CommonExample.h"

LGFX screen;
LGFX_Sprite sprite(&screen);

UGFX::Unified_ScreenLGFX<uint16_t> uScreen(&screen);
UGFX::Unified_SpriteLGFX<uint16_t> uSprite(&sprite);

void setup(void)
{
	Serial.begin(115200);

	screen.init();

	uSprite.setColorDepth(16);
	uSprite.createSprite(135, 240);
}

void loop(void)
{
	draw(uSprite, TFT_BLUE, TFT_YELLOW);
	uSprite.pushSprite(0, 0);
}
