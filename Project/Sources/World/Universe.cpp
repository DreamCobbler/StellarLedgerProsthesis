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

#include <Data/Item.hpp>

#include <Utilities/General.hpp>

#include <World/Universe.hpp>

template<>
std::optional<Empire> Universe::GetEntityOfID(Identifier const & ID) const
{

	auto const iterator = std::find_if(
		Empires.cbegin(),
		Empires.cend(),
		[&ID](Empire const & entity)
		{

			return entity.ID == ID;

		}
	);

	if (Empires.cend() == iterator)
		return std::nullopt;

	return (* iterator);

}

template<>
std::optional<Planet> Universe::GetEntityOfID(Identifier const & ID) const
{

	auto const iterator = std::find_if(
		Planets.cbegin(),
		Planets.cend(),
		[&ID](Planet const & entity)
		{

			return entity.ID == ID;

		}
	);

	if (Planets.cend() == iterator)
		return std::nullopt;

	return (* iterator);

}

template<>
std::optional<Species> Universe::GetEntityOfID(Identifier const & ID) const
{

	auto const iterator = std::find_if(
		Species.cbegin(),
		Species.cend(),
		[&ID](::Species const & entity)
		{

			return entity.ID == ID;

		}
	);

	if (Species.cend() == iterator)
		return std::nullopt;

	return (* iterator);

}

template<>
std::optional<Starbase> Universe::GetEntityOfID(Identifier const & ID) const
{

	auto const iterator = std::find_if(
		Starbases.cbegin(),
		Starbases.cend(),
		[&ID](Starbase const & entity)
		{

			return entity.ID == ID;

		}
	);

	if (Starbases.cend() == iterator)
		return std::nullopt;

	return (* iterator);

}

bool Universe::Create(Item const & itemTree)
{

	Clear();

	// Read the metadata.

	PlayerEmpireName = itemTree.FindValueOr<std::string>("name", "");
	CurrentDate = itemTree.FindValueOr<std::string>("date", "");
	GameVersion = itemTree.FindValueOr<std::string>("version", "");

	// Read the species.

	Identifier speciesIdentifier = 0;

	if (auto const speciesNode = itemTree.Find("species"))
		for (auto const & node : speciesNode->Children)
		{

			::Species species;

			species.ID = speciesIdentifier;
			species.Name = node.Find("name")->Value;
			species.Plural = node.FindValueOr("plural", species.Name);
			species.Adjective = node.FindValueOr("adjective", species.Name);
			species.HomePlanetID = node.FindValueOr<Identifier>("home_planet", -1);

			Species.push_back(species);

			++speciesIdentifier;

		}

	// Read the empires.

	static std::unordered_set<std::string_view> ResearchTypeNodeNames =
	{

		"physics_research",
		"society_research",
		"engineering_research",

	};

	if (auto const countryNode = itemTree.Find("country"))
		for (auto const & node : countryNode->Children)
		{

			if (!node.Find("name"))
				continue;

			Empire empire;

			empire.ID = std::stoll(std::string(node.Name));
			empire.Name = node.Find("name")->Value;
			empire.Adjective = node.FindValueOr("adjective", empire.Name);
			empire.MilitaryPower = node.FindValueOr("military_power", 0);
			empire.EconomyPower = node.FindValueOr("economy_power", 0);
			empire.TechnologyPower = node.FindValueOr("tech_power", 0);

			empire.MonthlyResearch = 0;

			if (auto const budgetNode = node.Find("budget"))
			if (auto const monthlyBudgetNode = budgetNode->Find("current_month"))
			if (auto const monthlyIncomeNode = monthlyBudgetNode->Find("income"))
				for (auto const & incomeSourceNode : monthlyIncomeNode->Children)
					for (auto const & incomeTypeNode : incomeSourceNode.Children)
					{

						auto const incomeTypeName = std::string(incomeTypeNode.Name);
						if (!empire.Income.contains(incomeTypeName))
							empire.Income[incomeTypeName] = 0;

						empire.Income[incomeTypeName] += std::stod(
							std::string(incomeTypeNode.Value)
						);

					}

			Empires.push_back(empire); 

		}

	// Read the planets.

	if (auto const planetsNode = itemTree.Find("planets"))
		for (auto const & node : planetsNode->Find("planet")->Children)
		{

			if (!node.Find("colonize_date"))
				continue;

			Planet planet;

			planet.ID = std::stoll(std::string(node.Name));
			planet.Name = node.Find("name")->Value;
			planet.OwnerID = node.FindValueOr<Identifier>("owner", -1);
			planet.Size = node.FindValueOr("planet_size", -1);
			planet.DateColonized = node.FindValueOr("colonize_date");
			planet.PopCount = node.FindValueOr("num_sapient_pops", -1);

			Planets.push_back(planet);

		}

	// Read the fleets.

	if (auto const fleetNode = itemTree.Find("fleet"))
		for (auto const & node : fleetNode->Children)
		{

			if ("yes" == node.FindValueOr<std::string>("station", "no") || !node.Find("owner"))
				continue;

			Fleet fleet;

			fleet.Name = node.FindValueOr("name");
			fleet.OwnerID = node.FindValueOr<Identifier>("owner", -1);
			fleet.MilitaryPower = node.FindValueOr("military_power", -1);
			fleet.HitPoints = node.FindValueOr("hit_points", -1);

			if (!fleet.HitPoints || !fleet.MilitaryPower)
				continue;

			Fleets.push_back(fleet);

		}

	// Read the federations.

	if (auto const federationNode = itemTree.Find("federation"))
		for (auto const & node : federationNode->Children)
		{

			Federation federation;

			federation.Name = node.FindValueOr("name");
			federation.DateCreated = node.FindValueOr("start_date");
			federation.LeaderID = node.FindValueOr<Identifier>("leader", -1);

			if (auto const membersNode = node.Find("members"))
				for (auto const & memberIDNode : membersNode->Children)
					federation.MemberIDs.push_back(std::stoi(std::string(memberIDNode.Value)));

			Federations.push_back(federation);

		}

	// Read the pops.

	if (auto const popNode = itemTree.Find("pop"))
		for (auto const & node : popNode->Children)
		{

			Pop pop;

			pop.SpeciesID = node.FindValueOr<Identifier>("species_index", -1);
			pop.PlanetID = node.FindValueOr<Identifier>("planet", -1);
			pop.Job = node.FindValueOr("job");

			Pops.push_back(pop);

		}

	// Read the starbases.

	if (auto const managerNode = itemTree.Find("starbase_mgr"))
		if (auto const starbasesNode = managerNode->Find("starbases"))
			for (auto const & node : starbasesNode->Children)
			{

				Starbase starbase;

				starbase.ID = std::stoll(std::string(node.Name));
				starbase.OwnerID = node.FindValueOr<Identifier>("owner", -1);

				Starbases.push_back(starbase);

			}

	// Read the systems.

	if (auto const galacticObjectNode = itemTree.Find("galactic_object"))
		for (auto const & node : galacticObjectNode->Children)
		{

			auto const type = node.FindValueOr("type");
			if ("star" != type)
				continue;

			System system;

			system.Name = node.FindValueOr("name");

			auto const starbaseID = node.FindValueOr<Identifier>("starbase", -1);
			if (-1 == starbaseID)
				continue;

			auto const starbase = GetEntityOfID<Starbase>(starbaseID);
			if (!starbase)
				continue;

			auto const empire = GetEntityOfID<Empire>(starbase->OwnerID);
			if (!empire)
				continue;

			system.OwnerID = empire->ID;

			for (auto const & planetIDNode : node.Children)
			{

				if ("planet" != planetIDNode.Name)
					continue;

				auto const planetID = std::stoll(std::string(planetIDNode.Value));
				if (!GetEntityOfID<Planet>(planetID))
					continue;

				system.PlanetIDs.insert(planetID);

			}

			if (system.PlanetIDs.empty())
				continue;

			Systems.push_back(system);

		}

	// Read the wars.

	if (auto const warNode = itemTree.Find("war"))
		for (auto const & node : warNode->Children)
		{

			if (!node.Find("name"))
				continue;

			War war;

			war.Name = node.FindValueOr("name");
			war.StartDate = node.FindValueOr("start_date");
			war.AttackerWarExhaustion = node.FindValueOr(
				"attacker_war_exhaustion",
				0.0
			);
			war.DefenderWarExhaustion = node.FindValueOr(
				"defender_war_exhaustion",
				0.0
			);

			Wars.push_back(war);

		}

	// Recalculate some things.

	Recalculate();

	// Clean up.

	Species.erase(
		std::remove_if(
			Species.begin(),
			Species.end(),
			[](::Species const & species) { return !species.PopCount; }
		),
		Species.end()
	);

	Empires.erase(
		std::remove_if(
			Empires.begin(),
			Empires.end(),
			[](Empire const & empire) { return !empire.PlanetCount; }
		),
		Empires.end()
	);

	// Rename species with repeating names.

	std::unordered_map<std::string, std::vector<::Species *>> speciesRepeatingNames;

	for (auto & species : Species)
	{

		auto nameIterator = speciesRepeatingNames.find(species.Name);

		if (speciesRepeatingNames.end() == nameIterator)
		{

			speciesRepeatingNames[species.Name] = std::vector<::Species *>();
			speciesRepeatingNames[species.Name].push_back(&species);

		}
		else
		{

			nameIterator->second.push_back(&species);

		}

	}

	for (auto const & speciesDescription : speciesRepeatingNames)
	{

		if (1 == speciesDescription.second.size())
			continue;

		auto index = 1;
		for (auto & species : speciesDescription.second)
		{

			auto const nameAddition = " (" + std::to_string(index) + ")";

			species->Name += nameAddition;
			species->Plural += nameAddition;
			species->Adjective += nameAddition;

			index += 1;

		}

	}

	// Return.

	return true;

}

void Universe::Clear()
{

	Species.clear();
	Empires.clear();
	Planets.clear();
	Fleets.clear();
	Federations.clear();
	Pops.clear();
	Starbases.clear();
	Systems.clear();
	Wars.clear();

	Income.clear();

}

void Universe::Recalculate()
{

	for (auto & empire : Empires)
		empire.Recalculate(self);

	for (auto & federation : Federations)
		federation.Recalculate(self);

	for (auto & planet : Planets)
		planet.Recalculate(self);

	for (auto & species : Species)
		species.Recalculate(self);

	for (auto & system : Systems)
		system.Recalculate(self);

	for (auto const & empire : Empires)
	{

		if (!empire.PlanetCount)
			continue;

		Income = SumMaps(Income, empire.Income);

	}

}