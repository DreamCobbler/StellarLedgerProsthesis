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

#include <World/Empire.hpp>
#include <World/Federation.hpp>
#include <World/Fleet.hpp>
#include <World/Planet.hpp>
#include <World/Pop.hpp>
#include <World/Species.hpp>
#include <World/Starbase.hpp>
#include <World/System.hpp>
#include <World/War.hpp>

///
/// A state of the universe.
///

class Universe final
{

	public:

		///
		/// The name of the player's empire.
		///

		std::string PlayerEmpireName;

		///
		/// The current date.
		///

		std::string CurrentDate;

		///
		/// The version of the game used to create the game state.
		///

		std::string GameVersion;

		///
		/// Stores data about all the species.
		///

		std::vector<Species> Species;

		///
		/// Stores data about all the empires.
		///

		std::vector<Empire> Empires;

		///
		/// Stores data about all the planets.
		///

		std::vector<Planet> Planets;

		///
		/// Stores data about all the fleets.
		///

		std::vector<Fleet> Fleets;

		///
		/// Stores data about all the federations.
		///

		std::vector<Federation> Federations;

		///
		/// Stores data about all the pops.
		///

		std::vector<Pop> Pops;

		///
		/// Stores data about all the starbases.
		///

		std::vector<Starbase> Starbases;

		///
		/// Stores data about all the systems.
		///

		std::vector<System> Systems;

		///
		/// Stores data about all the wars.
		///

		std::vector<War> Wars;

		///
		/// The monthly income of all empires, by resource.
		///

		std::unordered_map<std::string, double> Income;

	public:

		///
		/// Retrieves an entity of ID.
		///
		/// @param ID The ID.
		///
		/// @return The entity.
		///

		template<typename Entity>
		std::optional<Entity> GetEntityOfID(Identifier const & ID) const;

		///
		/// Creates universe state from an item tree.
		///

		bool Create(class Item const & itemTree);

		///
		/// Clears all the data about the universe.
		///

		void Clear();

	private:

		///
		/// Recalculates calculable values.
		///

		void Recalculate();

};