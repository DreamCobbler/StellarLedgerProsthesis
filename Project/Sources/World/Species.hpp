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
/// A species.
///
/// Needs to be recalculated after Planets were recalculated.
///

class Species final
{

	public:

		///
		/// The ID of the species.
		///

		Identifier ID;

		///
		/// The (singular) name of the species.
		///

		std::string Name;

		///
		/// The (plural) name of the species.
		///

		std::string Plural;

		///
		/// The adjective for the species.
		///

		std::string Adjective;

		///
		/// The ID of the home planet.
		///

		Identifier HomePlanetID;

		///
		/// The total number of pops of this species.
		///

		int PopCount = 0;

		///
		/// The number of planets on which this species can be found.
		///

		int PlanetCount = 0;

		///
		/// The number of planets on which this species is the main species.
		///

		int MainSpeciesPlanetCount = 0;

	public:

		///
		/// Calculates some of the values.
		///
		/// @param universe The universe in which the species exists.
		///

		void Recalculate(class Universe const & universe);

};