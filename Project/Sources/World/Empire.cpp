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

void Empire::Recalculate(Universe const & universe)
{

	static std::unordered_set<std::string_view> ResearchTypeNodeNames =
	{

		"physics_research",
		"society_research",
		"engineering_research",

	};

	PlanetCount = 0;
	PopCount = 0;

	MonthlyResearch = 0;

	for (auto const & planet : universe.Planets)
	{

		if (planet.OwnerID != ID)
			continue;

		PlanetCount += 1;
		PopCount += planet.PopCount;

	}

	for (auto const & incomeItem : Income)
	{

		if (!ResearchTypeNodeNames.contains(incomeItem.first))
			continue;

		MonthlyResearch += static_cast<int>(incomeItem.second);

	}

}