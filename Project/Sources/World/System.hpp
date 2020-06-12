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
/// A star system.
///

class System final
{

	public:

		///
		/// The name of the system.
		///

		std::string Name;

		///
		/// ID of the empire that owns the system.
		///

		Identifier OwnerID;

		///
		/// IDs of planets belonging in the system.
		///

		std::unordered_set<Identifier> PlanetIDs;

		///
		/// The total pop count.
		///

		int PopCount;

		///
		/// The total species count.
		///

		int SpeciesCount;

		///
		/// The main species of the system. First number is its identifier, the second number the
		/// proportion of population.
		///

		std::pair<Identifier, double> MainSpecies;

	public:

		///
		/// Calculates some of the values.
		///
		/// @param universe The universe in which the system exists.
		///

		void Recalculate(class Universe const & universe);

};