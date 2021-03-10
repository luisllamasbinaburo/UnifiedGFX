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

TFT_eSPI screen;
TFT_eSprite sprite(&screen);

UGFX::UnifiedScreen_TFTeSPI uScreen(&screen);
UGFX::UnifiedSprite_TFTeSPI uSprite(&sprite);

void setup(void)
{
	M5.begin();

	screen.setRotation(0);

	uSprite.setColorDepth(16);
	uSprite.createSprite(135, 240);
}

void loop(void)
{
	draw(uSprite, TFT_BLUE, TFT_RED);
	uSprite.pushSprite(0,0);
}
