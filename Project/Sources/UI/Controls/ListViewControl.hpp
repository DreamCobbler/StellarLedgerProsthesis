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

#include <UI/Concepts/Window.hpp>

#include <Utilities/Observable/Observable.hpp>

///
/// An event "ListViewControl" class can send.
///

enum class ListViewControlEvent
{

	SelectionChanged,

};

///
/// A list-view control.
///

class ListViewControl: public Observable<ListViewControl, ListViewControlEvent>, public Window
{

	public:

		///
		/// A value type used for setting items.
		///

		using ItemValue = std::variant<std::string, int>;

	public:

		///
		/// The constructor.
		///
		/// @param parentWindow    The parent window.
		/// @param singleSelection If **true**, only one item can be selected at a time.
		///

		ListViewControl(
			Window const & parentWindow,
			bool const & singleSelection,
			bool const & sortOnHeaderClick = true,
			bool const & border = true
		);

		///
		/// Appends a column to the list.
		///
		/// @param title Column title.
		/// @param width The initial width of the column.
		///

		void AppendColumn(std::string const & title, int const & width);

		///
		/// Appends an item.
		///
		/// @param A vector with values to be inserted in columns.
		///
		/// @return The unique identifier of the appended item.
		///

		LPARAM AppendItem(std::vector<std::variant<std::string, int>> const & values);

		///
		/// Deletes all items.
		///

		void ClearItems();

		///
		/// Retrieves the index of the first selected item.
		///
		/// @return The index of a selected item.
		///

		int GetSelection() const;

		///
		/// Retrieves item UID from its index.
		///
		/// @param index Item index.
		///
		/// @return Item UID.
		///

		std::optional<LPARAM> GetUID(int const & index) const;

	protected:

		///
		/// Event handler called whenever the window is enable or disabled.
		///

		virtual void OnEnable(bool const & enabled) override;

		///
		/// Event handler called whenever a notification arrives.
		///
		/// @return Whatever its supposed to return.
		///

		virtual LRESULT OnNotify(NMHDR const & notification) override;

		///
		/// Event handler called whenever the window's position or size changes.
		///
		/// @param width  The new width of the window.
		/// @param height The new height of the window.

		virtual void OnSize(int const & width, int const & height) override;

	private:

		///
		/// Stores original values for given item.
		///

		struct ItemData final
		{

			std::vector<ItemValue> InputData;

		};

		///
		/// Stores data used for sorting items.
		///

		struct SortingData final
		{

			ListViewControl * Control = nullptr;
			HWND ListViewHandle = 0;

			int ColumnIndex = 0;
			bool SortAscending = true;

		};

	private:

		///
		/// Used for comparing two items when sorting a list.
		///

		static int CALLBACK ItemComparator(
			LPARAM firstIdentifier,
			LPARAM secondIdentifier,
			LPARAM sortingDataPointer
		);

		///
		/// Generates a pretty string from item value.
		///
		/// @param itemValue Input item value.
		///
		/// @return A pretty string.
		///

		static std::string GetPrettyString(ItemValue const & itemValue);

	private:

		///
		/// Whether the control has a border.
		///

		bool _hasBorder;

		///
		/// The latest item identifier used.
		///

		LPARAM _latestItemIdentifier = 0;

		///
		/// Sorting order for columns. **true** means that given column is sorted ascending.
		///

		std::vector<bool> _columnSortingOrder;

		///
		/// Item data map.
		///

		std::unordered_map<LPARAM, ItemData> _itemData;

		///
		/// The handle of the actual list-view control.
		///

		HWND _internalWindowHandle = 0;

		///
		/// Current column count of the header.
		///

		size_t _columnCount = 0;


};