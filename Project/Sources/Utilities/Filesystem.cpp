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

#include <Utilities/Filesystem.hpp>

std::string ReadTextFile(std::filesystem::path const & filePath)
{

	std::ifstream fileStream(filePath, std::ios::binary);
	if (!fileStream.is_open() || !fileStream.good())
		return {};

	fileStream.seekg(0, std::ios::end);

	auto const fileSize = fileStream.tellg();
	if (!fileSize)
		return {};

	std::string text;
	text.resize(fileSize);

	fileStream.seekg(0);
	fileStream.read(&text[0], fileSize);

	return text;

}

std::vector<char> UnpackFileFromZIPArchive(
	std::filesystem::path const & filePath,
	std::string const & fileNameWithinArchive,
	bool const & isTextFile
)
{

	// Open the archive.

	int errorCode = 0;
	auto const archiveHandle = zip_open(filePath.string().data(), ZIP_RDONLY, &errorCode);

	if (!archiveHandle || errorCode)
		return {};

	BOOST_SCOPE_EXIT_ALL(&)
	{

		zip_close(archiveHandle);

	};

	// Retrieve file information and create the buffer.

	zip_stat_t fileMetadata;
	zip_stat_init(&fileMetadata);

	auto const fileMetadataRetrieval = zip_stat(
		archiveHandle,
		fileNameWithinArchive.data(),
		0,
		&fileMetadata
	);

	if (-1 == fileMetadataRetrieval || !(fileMetadata.flags & ZIP_STAT_SIZE))
		return {};

	auto const bufferSize = static_cast<size_t>(
		isTextFile?
		fileMetadata.size + 1:
		fileMetadata.size
	);

	auto buffer = std::vector<char>(bufferSize);
	if (isTextFile)
		buffer.back() = '\0'; // Mark the end of the text.

	// Open the file within the archive and decompress it into the buffer.

	auto const compressedFile = zip_fopen(archiveHandle, fileNameWithinArchive.data(), 0);
	if (!compressedFile)
		return {};

	BOOST_SCOPE_EXIT_ALL(&)
	{

		zip_fclose(compressedFile);

	};

	auto const readBytesCount = zip_fread(compressedFile, buffer.data(), fileMetadata.size);
	if (-1 == readBytesCount || fileMetadata.size != static_cast<zip_uint64_t>(readBytesCount))
		return {};

	// Return.

	return buffer;

}

std::filesystem::path GetGameStatesDirectoryPath()
{

	PWSTR documentsFolderPathWideCharacters = nullptr;
	auto const documentsFolderPathRetrievalResult = SHGetKnownFolderPath(
		FOLDERID_Documents,
		KF_FLAG_DEFAULT,
		0,
		&documentsFolderPathWideCharacters
	);

	if (S_OK != documentsFolderPathRetrievalResult || !documentsFolderPathWideCharacters)
		return {};

	auto const multiByteStringSize = WideCharToMultiByte(
		CP_UTF8,
		0,
		documentsFolderPathWideCharacters,
		-1,
		nullptr,
		0,
		nullptr,
		nullptr
	);

	if (!multiByteStringSize)
		return {};

	std::vector<char> multiByteStringBuffer(multiByteStringSize);
	WideCharToMultiByte(
		CP_UTF8,
		0,
		documentsFolderPathWideCharacters,
		-1,
		&multiByteStringBuffer[0],
		multiByteStringSize,
		nullptr,
		nullptr
	);

	auto const documentsFolderPath = std::string(&multiByteStringBuffer[0]);

	return std::filesystem::path(
		documentsFolderPath + "\\Paradox Interactive\\Stellaris\\save games"
	);

}