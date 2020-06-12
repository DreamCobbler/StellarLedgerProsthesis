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

#include <Data/GameState.hpp>
#include <Data/GameStateProcessor.hpp>

#include <Utilities/Filesystem.hpp>

std::vector<GameState> GameState::LocateGameStates(std::filesystem::path const & directoryPath)
{

	if (!std::filesystem::is_directory(directoryPath))
		return {};

	std::vector<GameState> gameStates;

	for (auto const & entry : std::filesystem::directory_iterator(directoryPath))
	{

		if (!std::filesystem::is_directory(entry))
			continue;

		for (auto const & subdirectoryEntry : std::filesystem::directory_iterator(entry))
		{

			auto const & entryPath = subdirectoryEntry.path();

			if ("gamestate" == entryPath.filename()) // Exclude ironman saves.
				continue;

			gameStates.emplace_back(entryPath);

		}

	}

	gameStates.erase(
		std::remove_if(
			gameStates.begin(),
			gameStates.end(),
			[](GameState const & gameState)
			{

				return !gameState;

			}
		),
		gameStates.end()
	);

	std::sort(
		gameStates.begin(),
		gameStates.end(),
		[](GameState const & left, GameState const & right)
		{

			if (left.EmpireName != right.EmpireName)
				return left.EmpireName < right.EmpireName;

			else
				return left.Date < right.Date;

		}
	);

	return gameStates;

}

GameState::GameState(std::filesystem::path const & filePath)
{

	Preload(filePath);

}

bool GameState::Preload(std::filesystem::path const & filePath)
{

	Clear();

	// Read the "meta" file from the archive.

	auto const fileContent = UnpackFileFromZIPArchive(filePath, "meta", true);
	if (fileContent.empty())
		return false;

	// Process its content and read the metadata.

	auto processor = GameStateProcessor();
	if (!processor.Process(fileContent.data()))
		return false;

	auto const & itemTree = processor.ViewItemTree();

	EmpireName = itemTree.FindValueOr<std::string>("name", "");
	Date = itemTree.FindValueOr<std::string>("date", "");

	// Set the file path and return.

	_filePath = filePath;

	return true;

}

bool GameState::Load()
{

	if (!self)
		return false;

	// Read the "gamestate" file from the archive.

	auto const fileContent = UnpackFileFromZIPArchive(_filePath, "gamestate", true);
	if (fileContent.empty())
		return false;

	// Set the description and return.

	Description = std::string(fileContent.data());
	if (Description.empty())
		return false;

	return true;

}

void GameState::Clear()
{

	self = GameState();

}

GameState::operator bool() const
{

	return !EmpireName.empty();

}