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

#include <World/Universe.hpp>

void Species::Recalculate(Universe const & universe)
{

	PopCount = 0;
	PlanetCount = 0;
	MainSpeciesPlanetCount = 0;
	Happiness = 0.0;

	std::unordered_set<Identifier> planetIDs;

	for (auto const & pop : universe.Pops)
	{

		if (pop.SpeciesID != ID)
			continue;

		PopCount += 1;
		Happiness += pop.Happiness;

		planetIDs.insert(pop.PlanetID);

	}

	PlanetCount = static_cast<int>(planetIDs.size());
	Happiness /= PopCount;

	for (auto const & planet : universe.Planets)
	{

		if (planet.MainSpecies.first != ID)
			continue;

		MainSpeciesPlanetCount += 1;

	}

}