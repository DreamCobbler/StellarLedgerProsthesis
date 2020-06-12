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

#include <Utilities/UI.hpp>

HFONT const & GetDefaultFontHandle(int const & size)
{

	static std::unordered_map<int, HFONT> FontHandlesBySize;

	if (FontHandlesBySize.empty())
	{

		NONCLIENTMETRICS metrics = {sizeof(metrics), 0};
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0);

		auto const handle = CreateFontIndirect(&metrics.lfMessageFont);
		FontHandlesBySize[-1] = handle;

	}

	if (!FontHandlesBySize.contains(size))
		FontHandlesBySize[size] = CopyFontWithNewSize(FontHandlesBySize[-1], size);

	return FontHandlesBySize[size];

}

HFONT CopyFontWithNewSize(
	HFONT const & handle,
	int const & size,
	HDC const & deviceContextHandle
)
{

	if (!handle)
		return 0;

	LOGFONT logicalFont;
	if (!GetObject(handle, sizeof(logicalFont), &logicalFont))
		return 0;

	logicalFont.lfQuality = PROOF_QUALITY;
	logicalFont.lfHeight = -MulDiv(size, GetDeviceCaps(deviceContextHandle, LOGPIXELSY), 72);

	return CreateFontIndirect(&logicalFont);

}