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

#pragma once

#include <Configuration.hpp>

///
/// Retrieves the handle of the "default" UI font.
///
/// @param size The font's size. -1 means the default size.
///
/// @return The font handle.
///

HFONT const & GetDefaultFontHandle(int const & size = DefaultFontSize);

///
/// Creates a copy of a font, with its size changed to given value.
///
/// @param handle              The handle of the original font.
/// @param size                Size of the copy.
/// @param deviceContextHandle Handle to a device context.

HFONT CopyFontWithNewSize(
	HFONT const & handle,
	int const & size,
	HDC const & deviceContextHandle = GetDC(0)
);