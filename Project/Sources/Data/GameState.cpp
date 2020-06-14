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

	std::unordered_map<std::string, size_t> empireNameOccurrences;

	for (auto const & entry : std::filesystem::directory_iterator(directoryPath))
	{

		if (!std::filesystem::is_directory(entry))
			continue;

		std::string currentEmpireName;

		for (auto const & subdirectoryEntry : std::filesystem::directory_iterator(entry))
		{

			auto const & entryPath = subdirectoryEntry.path();

			auto gameState = GameState(entryPath, "gamestate" == entryPath.filename());
			if (!gameState)
				continue;

			if (currentEmpireName.empty())
			{

				currentEmpireName = gameState.EmpireName;

				auto const empireNameIterator = empireNameOccurrences.find(currentEmpireName);

				if (empireNameOccurrences.end() == empireNameIterator)
				{

					empireNameOccurrences[currentEmpireName] = 1;

				}

				else
				{

					empireNameIterator->second += 1;

					currentEmpireName +=
						" (" + std::to_string(empireNameIterator->second - 1) + ")";

				}

			}

			gameState.EmpireName = currentEmpireName;
			gameStates.push_back(gameState);

		}

	}

	std::sort(
		gameStates.begin(),
		gameStates.end(),
		[](GameState const & left, GameState const & right)
		{

			if (left.EmpireName != right.EmpireName)
				return left.EmpireName < right.EmpireName;

			return left.Date < right.Date;

		}
	);

	return gameStates;

}

GameState::GameState(std::filesystem::path const & filePath, bool const & isIronman):
	_filePath(filePath),
	_isIronman(isIronman)
{

	std::string metadata;

	if (!_isIronman)
	{

		if (!UnpackTextFileFromZIPArchive(_filePath, "meta", metadata))
			return;

	}

	else
	{

		metadata = ReadTextFile(_filePath, 1024);

	}

	auto processor = GameStateProcessor();
	if (!processor.Process(metadata.data()))
		return;

	auto const & itemTree = processor.ViewItemTree();
	EmpireName = itemTree.FindValueOr<std::string>("name", "");
	Date = itemTree.FindValueOr<std::string>("date", "");

}

bool GameState::Load()
{

	if (!self)
		return false;

	if (!_isIronman)
	{

		auto const fileUnpackingResult = UnpackTextFileFromZIPArchive(
			_filePath,
			"gamestate",
			Description
		);

		if (!fileUnpackingResult || Description.empty())
			return false;

	}

	else
	{

		Description = ReadTextFile(_filePath);

	}

	return true;

}

void GameState::Clear()
{

	EmpireName.clear();
	Date.clear();
	Description.clear();

	_filePath.clear();

}

GameState::operator bool() const
{

	return !EmpireName.empty();

}