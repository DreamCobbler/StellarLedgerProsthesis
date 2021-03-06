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

#include <Utilities/Text.hpp>

bool IsVisuallyEmpty(std::string const & inputString)
{

	return inputString.empty() || std::all_of(inputString.cbegin(), inputString.cend(), ::isspace);

}

std::string const & GetSomeText(
	std::string const & inputString,
	std::string const & placeholder
)
{

	if (IsVisuallyEmpty(inputString))
		return placeholder;

	return inputString;

}

std::string FormatPercent(double const & number)
{

	return PrettifyNumber(100 * number) + "%";

}