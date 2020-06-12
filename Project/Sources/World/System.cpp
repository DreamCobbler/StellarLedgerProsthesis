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

void System::Recalculate(Universe const & universe)
{

	PopCount = 0;
	SpeciesCount = 0;
	MainSpecies = std::make_pair(-1, 0.0);

	std::unordered_map<Identifier, int> speciesData;

	for (auto const & planetID : PlanetIDs)
	{

		auto const planet = universe.GetEntityOfID<Planet>(planetID);
		if (!planet)
			continue;

		PopCount += planet->PopCount;

	}

	for (auto const & pop : universe.Pops)
	{

		auto isInSystem = false;
		for (auto const & planetID : PlanetIDs)
			if (planetID == pop.PlanetID)
			{

				isInSystem = true;

				break;

			}

		if (!isInSystem)
			continue;

		if (!speciesData.contains(pop.SpeciesID))
			speciesData.emplace(pop.SpeciesID, 1);
		else
			speciesData[pop.SpeciesID] += 1;

	}

	SpeciesCount = static_cast<int>(speciesData.size());

	auto const mainSpeciesIterator = std::max_element(
		speciesData.cbegin(),
		speciesData.cend(),
		[](std::pair<Identifier, int> const & left, std::pair<Identifier, int> const & right)
		{

			return left.second < right.second;

		}
	);

	MainSpecies.first = mainSpeciesIterator->first;
	MainSpecies.second = static_cast<double>(mainSpeciesIterator->second) / PopCount;

}