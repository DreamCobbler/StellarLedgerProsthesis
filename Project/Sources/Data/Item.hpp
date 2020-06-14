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
/// Represents a single data item.
///

class Item final
{

	public:

		///
		/// The name of the item.
		///

		std::string_view Name;

		///
		/// The value of the item.
		///

		std::string_view Value;

		///
		/// The item's children.
		///

		std::vector<Item> Children;

	public:

		///
		/// The constructor.
		///
		/// @param name  The name.
		/// @param value The value.
		///

		Item(
			std::string_view const & name = std::string_view(),
			std::string_view const & value = std::string_view()
		);

		///
		/// Finds a child of name.
		///
		/// @param The name.
		///
		/// @return Pointer to the appropriate child node, or **nullptr**.
		///

		Item const * Find(std::string const & name) const;

		///
		/// Finds a child of name and returns it values. If they child's not found, returns provided
		/// alternative value.
		///
		/// @param The name.
		///
		/// @return The child's value, or the alternative.
		///

		template<typename Type = std::string>
		Type FindValueOr(
			std::string const & childNodeName,
			Type const & alternativeValue = Type()
		) const;

};