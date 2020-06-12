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

#include <Utilities/StringHighlight/StringHighlight.hpp>

StringHighlight::StringHighlight(std::string const & string):
	_string(&string)
{}

void StringHighlight::JumpTo(size_t const & position, size_t const & length)
{

	_start = position;
	_length = length;

}

void StringHighlight::Increment()
{

	_length += 1;

}

bool StringHighlight::IsEmpty() const
{

	return !_length;

}

StringHighlight::operator std::string_view() const
{

	return std::string_view(_string->data() + _start, _length);

}

StringHighlight::operator bool() const
{

	return !IsEmpty();

}

bool operator==(StringHighlight const & stringHighlight, char const * const & string)
{

	return static_cast<std::string_view>(stringHighlight) == string;

}

bool operator==(StringHighlight const & stringHighlight, std::string const & string)
{

	return static_cast<std::string_view>(stringHighlight) == string;

}