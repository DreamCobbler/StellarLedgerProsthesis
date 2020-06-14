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
/// Reads a text file to string.
///
/// @param filePath The file path.
///
/// @return The file's content.
///

std::string ReadTextFile(std::filesystem::path const & filePath);

///
/// Unpacks a text file from a ZIP-compressed archive.
///
/// @param filePath              The file path.
/// @param fileNameWithinArchive The name of the file to be unpacked.
/// @param buffer                The buffer to which file contents is decompressed.
///
/// @return A string containing file contents.
///

bool UnpackTextFileFromZIPArchive(
	std::filesystem::path const & filePath,
	std::string const & fileNameWithinArchive,
	std::string & buffer
);

///
/// Generates directory path to the folder containing saved game states.
///
/// @return The directory path.
///

std::filesystem::path GetGameStatesDirectoryPath();
