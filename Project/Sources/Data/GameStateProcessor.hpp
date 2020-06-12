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

#include <Data/Item.hpp>

#include <Utilities/StringHighlight/StringHighlight.hpp>

///
/// A save game processor, capable of processing save files.
///

class GameStateProcessor final
{

	public:

		///
		/// Reads, tokenizes and parses data from string.
		///
		/// @param string The input string.
		///
		/// @return **true** if the string was read correctly, **false** otherwise.
		///

		bool Process(std::string const & string);

	private:

		///
		/// Checks whether given character is a valid character for a node name.
		///
		/// @param character The character in question.
		///
		/// @return **true** if it's a valid name character, **false** otherwise.
		///

		static bool IsValidNameCharacter(char const & character);

		///
		/// Tokenizes raw text data.
		///
		/// @return **true** if data has been tokenized correctly, **false** otherwise.
		///

		bool Tokenize();

		///
		/// Parses tokenized data into an item tree.
		///
		/// @return **true** if data has been parsed correctly, **false** otherwise.
		///

		bool Parse();

	private:

		///
		/// Raw text data.
		///

		std::string _rawText;

		///
		/// Tokenized raw text data.
		///

		std::vector<std::string_view> _tokens;

		///
		/// The item tree generated from read data.
		///

		Item _itemTree;

	public:

		ViewerMethod(ViewItemTree, _itemTree)

};