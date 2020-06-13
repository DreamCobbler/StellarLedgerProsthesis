/*
 *
 * Stellar Ledger Prosthesis
 * Copyright (C) 2020 Benedykt Synakiewicz (dreamcobbler@outlook.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <Precompiled Headers.hpp>

#include <UI/Controls/Label.hpp>

#include <Utilities/UI.hpp>

Label::Label(Window const & parentWindow)
{

	_backgroundPenHandle = reinterpret_cast<HPEN>(GetStockObject(NULL_PEN));
	_backgroundBrushHandle = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

	Create(parentWindow);

	SetFont(GetDefaultFontHandle());

}

std::pair<int, int> Label::GetMinimumWindowSize() const
{

	return std::make_pair(_minimumWidth, _minimumHeight);

}

void Label::SetFont(HFONT const & fontHandle)
{

	_fontHandle = fontHandle;

}

void Label::SetFont(int const & fontSize)
{

	_fontHandle = GetDefaultFontHandle(fontSize);

}

void Label::SetText(std::string const & text)
{

	// Set the text.

	_text = text;

	// Recalculate minimum window dimensions.

	auto const deviceContextHandle = GetDC(_handle);
	SelectObject(deviceContextHandle, _fontHandle);

	SIZE textSize;
	if (!GetTextExtentPoint32(
		deviceContextHandle,
		_text.data(),
		static_cast<int>(_text.length()),
		&textSize
	))
	{

		_minimumWidth = 0;
		_minimumHeight = 0;

		ReleaseDC(_handle, deviceContextHandle);

		return;

	}

	_minimumWidth = static_cast<int>(textSize.cx);
	_minimumHeight = static_cast<int>(textSize.cy);

	// Repaint the window.

	Repaint();

	// Clean up.

	ReleaseDC(_handle, deviceContextHandle);

}

void Label::OnPaint(PAINTSTRUCT const & paintingData)
{

	// Paint the text.

	if (_text.empty())
		return;

	SelectObject(paintingData.hdc, _fontHandle);

	RECT clientAreaRectangle;
	GetClientRect(_handle, &clientAreaRectangle);

	DrawText(
		paintingData.hdc,
		_text.data(),
		static_cast<int>(_text.length()),
		&clientAreaRectangle,
		DT_CENTER | DT_VCENTER
	);

}