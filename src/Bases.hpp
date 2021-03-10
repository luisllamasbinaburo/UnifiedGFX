/***************************************************
Copyright (c) 2021 Luis Llamas
(www.luisllamas.es)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses
****************************************************/

#pragma once

namespace UGFX
{
	static constexpr float deg_to_rad = 0.017453292519943295769236907684886;

	const int CORNER_LEFT_TOP = 0x1;
	const int CORNER_RIGHT_TOP = 0x2;
	const int CORNER_RIGHT_BOTTOM = 0x4;
	const int CORNER_LEFT_BOTTOM = 0x8;

	enum ROUND_CORNER : std::uint8_t
	{
		LEFT_TOP,
		RIGHT_TOP,
		RIGHT_BOTTOM,
		LEFT_BOTTOM,
	};

	enum RECT_ROUND_CORNER : std::uint8_t
	{
		TOP,
		BOTTOM,
	};

    enum TEXT_ALIGNMENT : std::uint8_t
    {
		  TOP_LEFT        =  0 
		, TOP_CENTER      =  1 
		, TOP_RIGHT       =  2 
		, MIDDLE_LEFT     =  3 
		, MIDDLE_CENTER   =  4 
		, MIDDLE_RIGHT    =  5 
		, BOTTOM_LEFT     =  6 
		, BOTTOM_CENTER   =  7 
		, BOTTOM_RIGHT    =  8 
		, BASELINE_LEFT   =  9 
		, BASELINE_CENTER = 10 
		, BASELINE_RIGHT  = 11 
    };

	template <typename Tcolor>
	class IBitmap
	{
	public:
		virtual std::int_fast16_t width() = 0;
		virtual std::int_fast16_t height() = 0;

		virtual void drawPixel(int32_t x, int32_t y, Tcolor color) = 0;
	};

	template <typename Tcolor>
	class IReadableBitmap : public IBitmap<Tcolor>
	{
	public:
		virtual Tcolor readPixel(int32_t x, int32_t y) = 0;
	};

	template <typename Tcolor>
	class IGraphic : public IBitmap<Tcolor>
	{
	public:
		virtual void fillScreen(Tcolor color) = 0;

		virtual void drawVerticalLine(int32_t x, int32_t y, int32_t h, Tcolor color) = 0;
		virtual void drawHorizontalLine(int32_t x, int32_t y, int32_t w, Tcolor color) = 0;
		virtual void drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, Tcolor color) = 0;

		virtual void drawRect(int32_t x, int32_t y, int32_t w, int32_t h, Tcolor color) = 0;
		virtual void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, Tcolor color) = 0;
		virtual void drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, Tcolor color) = 0;
		virtual void fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t radius, Tcolor color) = 0;

		virtual void drawCircle(int32_t x, int32_t y, int32_t r, Tcolor color) = 0;
		virtual void fillCircle(int32_t x, int32_t y, int32_t r, Tcolor color) = 0;

		virtual void drawEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, Tcolor color) = 0;
		virtual void fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, Tcolor color) = 0;

		virtual void drawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Tcolor color) = 0;
		virtual void fillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Tcolor color) = 0;

		virtual void drawArc(int32_t x, int32_t y, int32_t r0, int32_t r1, float start, float end, Tcolor color) = 0;
		virtual void fillArc(int32_t x, int32_t y, int32_t r0, int32_t r1, float start, float end, Tcolor color) = 0;
	};

	template <typename Tcolor>
	class IReadableGraphic : public IGraphic<Tcolor>, public IReadableBitmap<Tcolor>
	{
	};

	template <typename Tcolor>
	class ITextable
	{
	public:
	 	virtual void setTextSize(uint8_t s) = 0;
 		virtual void setTextFont(uint8_t f) = 0;

		virtual void drawChar(int32_t x, int32_t y, unsigned char c, Tcolor color, Tcolor bg, uint8_t size) = 0;
        virtual void drawString(const String& string, int32_t x, int32_t y, TEXT_ALIGNMENT alignment, Tcolor color) = 0;
	};

	template <typename Tcolor>
	class ISprite
	{
	public:
		virtual void* setColorDepth(int8_t depth) = 0;

		virtual void* createSprite(int16_t width, int16_t height, uint8_t frames = 1) = 0;
		virtual void deleteSprite(void) = 0;

		virtual void pushSprite(int32_t x, int32_t y) = 0;
		virtual void pushSprite(int32_t x, int32_t y, Tcolor transparent) = 0;

		virtual bool pushRotated(int16_t angle, Tcolor transparent = -1) = 0;
	};

	template <typename Tcolor>
	class Graphic : public IReadableGraphic<Tcolor>, public ITextable<Tcolor>
	{
	public:
		virtual std::int_fast16_t width() = 0;
		virtual std::int_fast16_t height() = 0;

		virtual void drawPixel(int32_t x, int32_t y, Tcolor color) = 0;
		virtual Tcolor readPixel(int32_t x, int32_t y) {}

		virtual void fillScreen(Tcolor color)
		{
			fillRect(0, 0, width(), height(), color);
		};

		virtual void drawHorizontalLine(int32_t x, int32_t y, int32_t w, Tcolor color)
		{
			if ((y < 0) || (x >= width()) || (y >= height())) return;
			if (x < 0) { w += x; x = 0; }
			if ((x + w) > width()) w = width() - x;
			if (w < 1) return;

			for (auto i = 0; i < w; i++)
			{
				drawPixel(x + i, y, color);
			}
		}

		virtual void drawVerticalLine(int32_t x, int32_t y, int32_t h, Tcolor color)
		{
			if ((x < 0) || (x >= width()) || (y >= height())) return;
			if (y < 0) { h += y; y = 0; }
			if ((y + h) > height()) h = height() - y;
			if (h < 1) return;

			for (auto i = 0; i < h; i++)
			{
				drawPixel(x, y + i, color);
			}
		}

		virtual void drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, Tcolor color)
		{
			bool steep = abs(y1 - y0) > abs(x1 - x0);
			if (steep) {
				std::swap(x0, y0);
				std::swap(x1, y1);
			}

			if (x0 > x1) {
				std::swap(x0, x1);
				std::swap(y0, y1);
			}

			int32_t dx = x1 - x0, dy = abs(y1 - y0);;

			int32_t err = dx >> 1, ystep = -1, xs = x0, dlen = 0;

			if (y0 < y1) ystep = 1;

			if (steep) {
				for (; x0 <= x1; x0++) {
					dlen++;
					err -= dy;
					if (err < 0) {
						if (dlen == 1) drawPixel(y0, xs, color);
						else drawVerticalLine(y0, xs, dlen, color);
						dlen = 0;
						y0 += ystep; xs = x0 + 1;
						err += dx;
					}
				}
				if (dlen) drawVerticalLine(y0, xs, dlen, color);
			}
			else
			{
				for (; x0 <= x1; x0++) {
					dlen++;
					err -= dy;
					if (err < 0) {

						if (dlen == 1) drawPixel(xs, y0, color);
						else drawHorizontalLine(xs, y0, dlen, color);
						dlen = 0;
						y0 += ystep; xs = x0 + 1;
						err += dx;
					}
				}
				if (dlen) drawHorizontalLine(xs, y0, dlen, color);
			}
		}

		virtual void drawRect(int32_t x, int32_t y, int32_t w, int32_t h, Tcolor color) {
			drawHorizontalLine(x, y, w, color);
			drawHorizontalLine(x, y + h - 1, w, color);
			drawVerticalLine(x, y + 1, h - 2, color);
			drawVerticalLine(x + w - 1, y + 1, h - 2, color);
		};

		virtual void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, Tcolor color)
		{
			for (auto i = 0; i < h; i++)
			{
				drawHorizontalLine(x, y + i, w, color);
			}
		};

		virtual void drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, Tcolor color)
		{
			drawHorizontalLine(x + r, y, w - r - r, color); // Top
			drawHorizontalLine(x + r, y + h - 1, w - r - r, color); // Bottom
			drawVerticalLine(x, y + r, h - r - r, color); // Left
			drawVerticalLine(x + w - 1, y + r, h - r - r, color); // Right

			drawCircleCorner(x + r, y + r, r, ROUND_CORNER::LEFT_TOP, color);
			drawCircleCorner(x + w - r - 1, y + r, r, ROUND_CORNER::RIGHT_TOP, color);
			drawCircleCorner(x + w - r - 1, y + h - r - 1, r, ROUND_CORNER::RIGHT_BOTTOM, color);
			drawCircleCorner(x + r, y + h - r - 1, r, ROUND_CORNER::LEFT_BOTTOM, color);
		}

		virtual void fillRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, Tcolor color) {
			fillRect(x, y + r, w, h - r - r, color);

			fillRectCircleCorner(x + r, y + h - r - 1, r, RECT_ROUND_CORNER::TOP, w - r - r - 1, color);
			fillRectCircleCorner(x + r, y + r, r, RECT_ROUND_CORNER::BOTTOM, w - r - r - 1, color);
		};

		virtual void drawCircle(int32_t x, int32_t y, int32_t r, Tcolor color)
		{
			if (r <= 0) return;

			int32_t f = 1 - r;
			int32_t ddF_y = -2 * r;
			int32_t ddF_x = 1;
			int32_t xs = -1;
			int32_t xe = 0;
			int32_t len = 0;

			bool first = true;
			do {
				while (f < 0) {
					++xe;
					f += (ddF_x += 2);
				}
				f += (ddF_y += 2);

				if (xe - xs > 1) {
					if (first) {
						len = 2 * (xe - xs) - 1;
						drawHorizontalLine(x - xe, y + r, len, color);
						drawHorizontalLine(x - xe, y - r, len, color);
						drawVerticalLine(x + r, y - xe, len, color);
						drawVerticalLine(x - r, y - xe, len, color);
						first = false;
					}
					else {
						len = xe - xs++;
						drawHorizontalLine(x - xe, y + r, len, color);
						drawHorizontalLine(x - xe, y - r, len, color);
						drawHorizontalLine(x + xs, y - r, len, color);
						drawHorizontalLine(x + xs, y + r, len, color);

						drawVerticalLine(x + r, y + xs, len, color);
						drawVerticalLine(x + r, y - xe, len, color);
						drawVerticalLine(x - r, y - xe, len, color);
						drawVerticalLine(x - r, y + xs, len, color);
					}
				}
				else {
					++xs;
					drawPixel(x - xe, y + r, color);
					drawPixel(x - xe, y - r, color);
					drawPixel(x + xs, y - r, color);
					drawPixel(x + xs, y + r, color);

					drawPixel(x + r, y + xs, color);
					drawPixel(x + r, y - xe, color);
					drawPixel(x - r, y - xe, color);
					drawPixel(x - r, y + xs, color);
				}
				xs = xe;
			} while (xe < --r);
		};

		virtual void fillCircle(int32_t x, int32_t y, int32_t r, Tcolor color)
		{
			int32_t  xx = 0;
			int32_t  dx = 1;
			int32_t  dy = r + r;
			int32_t  p = -(r >> 1);

			drawHorizontalLine(x - r, y, dy + 1, color);

			while (xx < r) {

				if (p >= 0) {
					drawHorizontalLine(x - xx, y + r, dx, color);
					dy -= 2;
					p -= dy;
					drawHorizontalLine(x - xx, y - r, dx, color);
					r--;
				}
				xx++;
				drawHorizontalLine(x - r, y + xx, dy + 1, color);
				dx += 2;
				p += dx;
				drawHorizontalLine(x - r, y - xx, dy + 1, color);
			}
		}

		virtual void drawCircleCorner(int32_t x, int32_t y, int32_t r, uint8_t cornername, Tcolor color)
		{
			if (r <= 0) return;
			int32_t f = 1 - r;
			int32_t ddF_x = 1;
			int32_t ddF_y = -2 * r;
			int32_t xe = 0;
			int32_t xs = 0;
			int32_t len = 0;

			while (xe < r--)
			{
				while (f < 0) {
					++xe;
					f += (ddF_x += 2);
				}
				f += (ddF_y += 2);

				if (xe - xs == 1) {
					if (cornername == ROUND_CORNER::LEFT_TOP) {
						drawPixel(x - xe, y - r, color);
						drawPixel(x - r, y - xe, color);
					}
					if (cornername == ROUND_CORNER::RIGHT_TOP) {
						drawPixel(x + r, y - xe, color);
						drawPixel(x + xs + 1, y - r, color);
					}
					if (cornername == ROUND_CORNER::RIGHT_BOTTOM) {
						drawPixel(x + xs + 1, y + r, color);
						drawPixel(x + r, y + xs + 1, color);
					}
					if (cornername == ROUND_CORNER::LEFT_BOTTOM) {
						drawPixel(x - r, y + xs + 1, color);
						drawPixel(x - xe, y + r, color);
					}
				}
				else {
					len = xe - xs++;
					if (cornername == ROUND_CORNER::LEFT_TOP) {
						drawHorizontalLine(x - xe, y - r, len, color);
						drawVerticalLine(x - r, y - xe, len, color);
					}
					if (cornername == ROUND_CORNER::RIGHT_TOP) {
						drawVerticalLine(x + r, y - xe, len, color);
						drawHorizontalLine(x + xs, y - r, len, color);
					}
					if (cornername == ROUND_CORNER::RIGHT_BOTTOM) {
						drawHorizontalLine(x + xs, y + r, len, color);
						drawVerticalLine(x + r, y + xs, len, color);
					}
					if (cornername == ROUND_CORNER::LEFT_BOTTOM) {
						drawVerticalLine(x - r, y + xs, len, color);
						drawHorizontalLine(x - xe, y + r, len, color);
					}
				}
				xs = xe;
			}
		}

		virtual void fillRectCircleCorner(int32_t x, int32_t y, int32_t r, uint8_t cornername, int32_t delta, uint32_t color)
		{
			int32_t f = 1 - r;
			int32_t ddF_x = 1;
			int32_t ddF_y = -r - r;
			int32_t yy = 0;

			delta++;

			while (yy < r) {
				if (f >= 0) {
					if (cornername == RECT_ROUND_CORNER::TOP) drawHorizontalLine(x - yy, y + r, yy + yy + delta, color);
					ddF_y += 2;
					f += ddF_y;
					if (cornername == RECT_ROUND_CORNER::BOTTOM) drawHorizontalLine(x - yy, y - r, yy + yy + delta, color);
					r--;
				}

				yy++;
				if (cornername == RECT_ROUND_CORNER::TOP) drawHorizontalLine(x - r, y + yy, r + r + delta, color);
				ddF_x += 2;
				f += ddF_x;
				if (cornername == RECT_ROUND_CORNER::BOTTOM) drawHorizontalLine(x - r, y - yy, r + r + delta, color);
			}
		}

		virtual void drawEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, Tcolor color)
		{
			if (rx < 2) return;
			if (ry < 2) return;
			int32_t xx, yy;
			int32_t rx2 = rx * rx;
			int32_t ry2 = ry * ry;
			int32_t fx2 = 4 * rx2;
			int32_t fy2 = 4 * ry2;
			int32_t s;

			for (xx = 0, yy = ry, s = 2 * ry2 + rx2 * (1 - 2 * ry); ry2 * xx <= rx2 * yy; xx++) {
				drawPixel(x + xx, y + yy, color);
				drawPixel(x - xx, y + yy, color);
				drawPixel(x - xx, y - yy, color);
				drawPixel(x + xx, y - yy, color);
				if (s >= 0) {
					s += fx2 * (1 - yy);
					yy--;
				}
				s += ry2 * ((4 * xx) + 6);
			}

			for (xx = rx, yy = 0, s = 2 * rx2 + ry2 * (1 - 2 * rx); rx2 * yy <= ry2 * xx; yy++) {
				drawPixel(x + xx, y + yy, color);
				drawPixel(x - xx, y + yy, color);
				drawPixel(x - xx, y - yy, color);
				drawPixel(x + xx, y - yy, color);
				if (s >= 0)
				{
					s += fy2 * (1 - xx);
					xx--;
				}
				s += rx2 * ((4 * yy) + 6);
			}
		};

		virtual void fillEllipse(int16_t x, int16_t y, int32_t rx, int32_t ry, Tcolor color)
		{
			if (rx < 2) return;
			if (ry < 2) return;
			int32_t xx, yy;
			int32_t rx2 = rx * rx;
			int32_t ry2 = ry * ry;
			int32_t fx2 = 4 * rx2;
			int32_t fy2 = 4 * ry2;
			int32_t s;


			for (xx = 0, yy = ry, s = 2 * ry2 + rx2 * (1 - 2 * ry); ry2 * xx <= rx2 * yy; xx++) {
				drawHorizontalLine(x - xx, y - yy, xx + xx + 1, color);
				drawHorizontalLine(x - xx, y + yy, xx + xx + 1, color);

				if (s >= 0) {
					s += fx2 * (1 - yy);
					yy--;
				}
				s += ry2 * ((4 * xx) + 6);
			}

			for (xx = rx, yy = 0, s = 2 * rx2 + ry2 * (1 - 2 * rx); rx2 * yy <= ry2 * xx; yy++) {
				drawHorizontalLine(x - xx, y - yy, xx + xx + 1, color);
				drawHorizontalLine(x - xx, y + yy, xx + xx + 1, color);

				if (s >= 0) {
					s += fy2 * (1 - xx);
					xx--;
				}
				s += rx2 * ((4 * yy) + 6);
			}
		};

		virtual void drawTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, Tcolor color)
		{
			drawLine(x0, y0, x1, y1, color);
			drawLine(x1, y1, x2, y2, color);
			drawLine(x2, y2, x0, y0, color);
		};

		virtual void fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, Tcolor color)
		{
			int32_t a, b, y, last;

			if (y0 > y1) {
				std::swap(y0, y1); std::swap(x0, x1);
			}
			if (y1 > y2) {
				std::swap(y2, y1); std::swap(x2, x1);
			}
			if (y0 > y1) {
				std::swap(y0, y1); std::swap(x0, x1);
			}

			if (y0 == y2) { // Handle awkward all-on-same-line case as its own thing
				a = b = x0;
				if (x1 < a)      a = x1;
				else if (x1 > b) b = x1;
				if (x2 < a)      a = x2;
				else if (x2 > b) b = x2;
				drawHorizontalLine(a, y0, b - a + 1, color);
				return;
			}

			int32_t
				dx01 = x1 - x0,
				dy01 = y1 - y0,
				dx02 = x2 - x0,
				dy02 = y2 - y0,
				dx12 = x2 - x1,
				dy12 = y2 - y1,
				sa = 0,
				sb = 0;

			if (y1 == y2) last = y1;  // Include y1 scanline
			else         last = y1 - 1; // Skip it

			for (y = y0; y <= last; y++) {
				a = x0 + sa / dy01;
				b = x0 + sb / dy02;
				sa += dx01;
				sb += dx02;

				if (a > b) std::swap(a, b);
				drawHorizontalLine(a, y, b - a + 1, color);
			}

			sa = dx12 * (y - y1);
			sb = dx02 * (y - y0);
			for (; y <= y2; y++) {
				a = x1 + sa / dy12;
				b = x0 + sb / dy02;
				sa += dx12;
				sb += dx02;

				if (a > b) std::swap(a, b);
				drawHorizontalLine(a, y, b - a + 1, color);

			}
		};

		virtual void drawArc(int32_t x, int32_t y, int32_t r0, int32_t r1, float start, float end, Tcolor color)
		{
			if (r0 < r1) std::swap(r0, r1);
			if (r0 < 1) r0 = 1;
			if (r1 < 1) r1 = 1;

			bool equal = fabsf(start - end) < std::numeric_limits<float>::epsilon();
			start = fmodf(start, 360);
			end = fmodf(end, 360);
			if (start < 0) start += 360.0;
			if (end < 0) end += 360.0;

			fill_arc_helper(x, y, r0, r1, start, start, color);
			fill_arc_helper(x, y, r0, r1, end, end, color);
			if (!equal && (fabsf(start - end) <= 0.0001)) { start = .0; end = 360.0; }
			fill_arc_helper(x, y, r0, r0, start, end, color);
			fill_arc_helper(x, y, r1, r1, start, end, color);
		}

		virtual void fillArc(int32_t x, int32_t y, int32_t r0, int32_t r1, float start, float end, Tcolor color)
		{
			if (r0 < r1) std::swap(r0, r1);
			if (r0 < 1) r0 = 1;
			if (r1 < 1) r1 = 1;

			bool equal = fabsf(start - end) < std::numeric_limits<float>::epsilon();
			start = fmodf(start, 360);
			end = fmodf(end, 360);
			if (start < 0) start += 360.0;
			if (end < 0) end += 360.0;
			if (!equal && (fabsf(start - end) <= 0.0001)) { start = .0; end = 360.0; }

			fill_arc_helper(x, y, r0, r1, start, end, color);
			
		}

		virtual void fill_arc_helper(int32_t cx, int32_t cy, int32_t oradius, int32_t iradius, float start, float end, Tcolor color)
		{
			float s_cos = (cosf(start * deg_to_rad));
			float e_cos = (cosf(end * deg_to_rad));
			float sslope = s_cos / (sinf(start * deg_to_rad));
			float eslope = -1000000;
			if (end != 360.0) eslope = e_cos / (sinf(end * deg_to_rad));
			float swidth = 0.5 / s_cos;
			float ewidth = -0.5 / e_cos;
			--iradius;
			int ir2 = iradius * iradius + iradius;
			int or2 = oradius * oradius + oradius;

			bool start180 = !(start < 180);
			bool end180 = end < 180;
			bool reversed = start + 180 < end || (end < start&& start < end + 180);

			int xs = -oradius;
			int y = -oradius;
			int ye = oradius;
			int xe = oradius + 1;
			if (!reversed) {
				if ((end >= 270 || end < 90) && (start >= 270 || start < 90)) xs = 0;
				else if (end < 270 && end >= 90 && start < 270 && start >= 90) xe = 1;
				if (end >= 180 && start >= 180) ye = 0;
				else if (end < 180 && start < 180) y = 0;
			}
			do {
				int y2 = y * y;
				int x = xs;
				if (x < 0) {
					while (x * x + y2 >= or2) ++x;
					if (xe != 1) xe = 1 - x;
				}
				float ysslope = (y + swidth) * sslope;
				float yeslope = (y + ewidth) * eslope;
				int len = 0;
				do {
					bool flg1 = start180 != (x <= ysslope);
					bool flg2 = end180 != (x <= yeslope);
					int distance = x * x + y2;
					if (distance >= ir2
						&& ((flg1 && flg2) || (reversed && (flg1 || flg2)))
						&& x != xe
						&& distance < or2
						) {
						++len;
					}
					else {
						if (len) {
							drawHorizontalLine(cx + x - len, cy + y, len, color);
							len = 0;
						}
						if (distance >= or2) break;
						if (x < 0 && distance < ir2) { x = -x; }
					}
				} while (++x <= xe);
			} while (++y <= ye);
		}

		virtual void setTextSize(uint8_t s) {}
 		virtual void setTextFont(uint8_t f) {}

		virtual void drawChar(int32_t x, int32_t y, unsigned char c, Tcolor color, Tcolor bg, uint8_t size) {}
        virtual void drawString(const String& string, int32_t x, int32_t y, TEXT_ALIGNMENT alignment, Tcolor color) {}
	};

	template <typename Tcolor>
	class Sprite : public Graphic<Tcolor>, public ISprite<Tcolor>
	{
	};
}