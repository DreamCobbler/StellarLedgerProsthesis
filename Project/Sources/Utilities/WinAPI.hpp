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
/// Retrieves a text associated with given sub-item of a given list-view control. The sub-item is
/// identified by the LPARAM value associated with it.
///
/// @param handle    The handle to the control.
/// @param subItem   The index of the column
/// @param parameter The LPARAM value associated with the sub-item.
///
/// @return The text of the subitem.
///

std::optional<std::string> ListView_GetSubItemText(
	HWND const & handle,
	int const & subItem,
	LPARAM const & parameter
);