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

#pragma warning(push, 0)

	// C++ Standard Library.

	#include <algorithm>
	#include <chrono>
	#include <cctype>
	#include <cstdlib>
	#include <filesystem>
	#include <fstream>
	#include <functional>
	#include <list>
	#include <locale>
	#include <memory>
	#include <optional>
	#include <sstream>
	#include <stack>
	#include <string>
	#include <string_view>
	#include <unordered_map>
	#include <unordered_set>
	#include <variant>
	#include <vector>

	// libzip.

	#undef _WIN32

	#include <zip.h>

	#define _WIN32

	// Windows API.

	#include <Windows.h>

	#include <CommCtrl.h>
	#pragma comment(lib, "Comctl32")

	#include <ShlObj.h>

	#undef max
	#undef min

#pragma warning(pop)

// Self.

#include <Utilities/Macros.hpp>
#include <Utilities/Types.hpp>