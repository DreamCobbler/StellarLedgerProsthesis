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

#include <Utilities/WinAPI.hpp>

std::optional<std::string> ListView_GetSubItemText(
	HWND const & handle,
	int const & subItem,
	LPARAM const & parameter
)
{

	if (!handle || subItem < 0)
		return std::nullopt;

	auto const itemCount = ListView_GetItemCount(handle);
	if (!itemCount)
		return std::nullopt;

	static auto constexpr BufferLength = 1024;
	static char Buffer[BufferLength];
	static LVITEM ItemBuffer;

	for (auto itemIndex = 0; itemIndex < itemCount; ++itemIndex)
	{

		ItemBuffer = {0};
		ItemBuffer.mask = LVIF_PARAM | LVIF_TEXT;
		ItemBuffer.iItem = itemIndex;
		ItemBuffer.iSubItem = subItem;
		ItemBuffer.cchTextMax = BufferLength;
		ItemBuffer.pszText = Buffer;

		ListView_GetItem(handle, &ItemBuffer);

		if (ItemBuffer.lParam == parameter)
			break;

	}

	if (!ItemBuffer.pszText)
		return std::nullopt;

	#pragma warning(push)
	#pragma warning(disable: 6054)

	return std::string(ItemBuffer.pszText);

	#pragma warning(pop)

}