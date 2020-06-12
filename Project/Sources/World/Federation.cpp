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

#include <Utilities/General.hpp>

#include <World/Universe.hpp>

void Federation::Recalculate(Universe const & universe)
{

	MilitaryPower = 0;
	EconomyPower = 0;
	TechnologyPower = 0;

	Income.clear();

	for (auto const & ID : MemberIDs)
	{

		auto const empire = universe.GetEntityOfID<Empire>(ID);
		if (!empire)
			continue;

		MilitaryPower += empire->MilitaryPower;
		EconomyPower += empire->EconomyPower;
		TechnologyPower += empire->TechnologyPower;

		PlanetCount += empire->PlanetCount;
		PopCount += empire->PopCount;
		MonthlyResearch += empire->MonthlyResearch;

		Income = SumMaps(Income, empire->Income);

	}

}