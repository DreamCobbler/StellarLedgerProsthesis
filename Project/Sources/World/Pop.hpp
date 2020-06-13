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
/// A pop.
///

class Pop final
{

	public:

		///
		/// The ID of the species this pop belongs to.
		///

		Identifier SpeciesID;

		///
		/// The ID of the planet on which this pop is located.
		///

		Identifier PlanetID;

		///
		/// The identifier of the job.
		///

		std::string Job;

		///
		/// The happiness, from 0.0 to 1.0.
		///

		double Happiness;

};