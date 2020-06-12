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
/// A planet.
///

class Planet final
{

	public:

		///
		/// The ID.
		///

		Identifier ID;

		///
		/// The name of the planet.
		///

		std::string Name;

		///
		/// The ID of the empire owning the planet.
		///

		Identifier OwnerID;

		///
		/// The size.
		///

		int Size;

		///
		/// The date when the planet was colonized.
		///

		std::string DateColonized;

		///
		/// The total pop count.
		///

		int PopCount;

		///
		/// The number of different species living on this planet.
		///

		int SpeciesCount;

		///
		/// The main species of the planet. First number is its identifier, the second number the
		/// proportion of population.
		///

		std::pair<Identifier, double> MainSpecies;

	public:

		///
		/// Calculates some of the values.
		///
		/// @param universe The universe in which the planet exists.
		///

		void Recalculate(class Universe const & universe);

};