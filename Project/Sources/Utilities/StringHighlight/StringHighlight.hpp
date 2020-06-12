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
/// A highlighted part of a string. Basically a pair of cursors.
///

class StringHighlight
{

	public:

		///
		/// The constructor.
		///
		/// @param string The string we're highlighting.
		///

		StringHighlight(std::string const & string);

		///
		/// Moves the cursor to selected position and clears the length.
		///
		/// @param position The new cursor position.
		///

		void JumpTo(size_t const & position, size_t const & length = 0);

		///
		/// Increments the highlights length.
		///

		void Increment();

		///
		/// Checks whether the highlight's empty.
		///
		/// @return **true** if it's empty, **false** otherwise.
		///

		bool IsEmpty() const;

		///
		/// Returns a string view.
		///
		/// @return A string view.
		///

		operator std::string_view() const;

		///
		/// Checks whether the highlight's *not* empty.
		///
		/// @return **true** if it's **not** empty, **false** otherwise.
		///

		operator bool() const;

	public:

		///
		/// The string of which we're highlighting parts.
		///

		std::string const * _string = nullptr;

		///
		/// The cursor.
		///

		size_t _start = 0;

		///
		/// The length of the highlighted part.
		///

		size_t _length = 0;

};

///
/// Equality operators for StringHighlight.
///

bool operator==(StringHighlight const & stringHighlight, char const * const & string);
//bool operator==(StringHighlight const & stringHighlight, std::string const & string);