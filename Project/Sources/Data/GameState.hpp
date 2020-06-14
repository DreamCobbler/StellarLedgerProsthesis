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
/// A saved game state, as found on the hard drive.
///

class GameState final
{

	public:

		static std::vector<GameState> LocateGameStates(std::filesystem::path const & directoryPath);

	public:

		///
		/// The name of the in-game empire.
		///

		std::string EmpireName;

		///
		/// The in-game date.
		///

		std::string Date;

		///
		/// The entire game state description.
		///

		std::string Description;

	public:

		///
		/// The constructor. Reads metadata from the file.
		///
		/// @param filePath Path to the file containing a saved game state.
		///

		GameState(std::filesystem::path const & filePath, bool const & isIronman);

		///
		/// Loads the entire content of the game state.
		///
		/// @return **true** if the game state has been loaded correctly, **false** otherwise.
		///

		bool Load();

		///
		/// Clears the object entirely.
		///
	
		void Clear();

		///
		/// Determines whether the saved game state exists, i.e. this object isn't empty.
		///
		/// @return **true** if the object's not empty.
		///

		operator bool() const;

	private:

		///
		/// The path to the file containing the saved game state.
		///

		std::filesystem::path _filePath;

		///
		/// Is the save game an ironman save?
		///

		bool _isIronman;

};