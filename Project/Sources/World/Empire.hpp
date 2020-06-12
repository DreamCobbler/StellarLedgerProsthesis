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
/// An empire.
///

class Empire final
{

	public:

		///
		/// The ID of the empire.
		///

		Identifier ID;

		///
		/// The name of the empire.
		///

		std::string Name;

		///
		/// The adjective.
		///

		std::string Adjective;

		///
		/// The total military estimate of the empire.
		///

		int MilitaryPower;

		///
		/// The total economy estimate of the empire.
		///

		int EconomyPower;

		///
		/// The total technology estimate of the empire.
		///

		int TechnologyPower;

		///
		/// The total montly research.
		///

		int MonthlyResearch;

		///
		/// The total planet count of the empire.
		///

		int PlanetCount;

		///
		/// The total pop count of the empire.
		///

		int PopCount;

		///
		/// The monthly income of the empire, by resource.
		///

		std::unordered_map<std::string, double> Income;

	public:

		///
		/// Calculates some of the values.
		///
		/// @param universe The universe in which the empire exists.
		///

		void Recalculate(class Universe const & universe);

};