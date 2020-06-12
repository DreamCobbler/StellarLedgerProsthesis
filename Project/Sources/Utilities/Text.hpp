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

///
/// The default empty string placeholder.
///

inline std::string const EmptyStringPlaceholder = "—";

///
/// Formats a number for printing/display.
///
/// @param number The input number.
///
/// @return The formatted number.
///

template<typename Number>
std::string PrettifyNumber(Number const & number, int const & precision = 0);

///
/// Checks whether a string is visually empty: either actually empty, or composed solely of
/// whitespace.
///
/// @param inputString The input string.
///
/// @return **true** if the string's empty, **false** otherwise.
///

bool IsVisuallyEmpty(std::string const & inputString);

///
/// Returns a non-empty string: either the input string, or a provided placeholder.
///
/// @param inputString The input string.
///
/// @return A non-empty string.
///

std::string const & GetSomeText(
	std::string const & inputString,
	std::string const & placeholder = EmptyStringPlaceholder
);

#include "Text.inl"