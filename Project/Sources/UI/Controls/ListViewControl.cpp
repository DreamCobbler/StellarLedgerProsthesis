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

#include <UI/Controls/ListViewControl.hpp>

#include <Utilities/General.hpp>
#include <Utilities/Text.hpp>
#include <Utilities/UI.hpp>
#include <Utilities/WinAPI.hpp>

#include <Configuration.hpp>

ListViewControl::ListViewControl(
	Window const & parentWindow,
	bool const & singleSelection,
	bool const & sortOnHeaderClick
)
{

	Create(parentWindow);

	_internalWindowHandle = CreateWindowEx(
		WS_EX_COMPOSITED,
		WC_LISTVIEW,
		nullptr,
		LVS_REPORT | LVS_SHOWSELALWAYS |
			(singleSelection? LVS_SINGLESEL : 0) |
			(sortOnHeaderClick? 0 : LVS_NOSORTHEADER) |
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		0,
		0,
		0,
		0,
		_handle,
		0,
		0,
		0
	);

	ListView_SetExtendedListViewStyle(
		_internalWindowHandle,
		LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP
	);

	SendMessage(
		_internalWindowHandle,
		WM_SETFONT,
		reinterpret_cast<WPARAM>(GetDefaultFontHandle()),
		TRUE
	);

}

void ListViewControl::AppendColumn(std::string const & title, int const & width)
{

	LVCOLUMN column;
	column.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	column.iSubItem = 0;
	column.cx = width;
	column.pszText = const_cast<char *>(title.data());

	ListView_InsertColumn(_internalWindowHandle, _columnCount, &column);

	_columnCount += 1;
	_columnSortingOrder.push_back(true);

}

void ListViewControl::AppendItem(std::vector<std::variant<std::string, int>> const & values)
{

	if (values.empty())
		return;

	auto const firstColumValue = GetPrettyString(values[0]);

	LVITEM item;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = ListView_GetItemCount(_internalWindowHandle);
	item.iSubItem = 0;
	item.pszText = const_cast<char *>(firstColumValue.data());
	item.lParam = ++_latestItemIdentifier;

	ListView_InsertItem(_internalWindowHandle, &item);

	for (auto columnIndex = 0; columnIndex < std::min(_columnCount, values.size()); ++columnIndex)
	{

		auto const value = GetPrettyString(values[columnIndex]);

		ListView_SetItemText(
			_internalWindowHandle,
			item.iItem,
			columnIndex,
			const_cast<char *>(value.data())
		)

	}

	_itemData[item.lParam].InputData = values;

}

void ListViewControl::ClearItems()
{

	ListView_DeleteAllItems(_internalWindowHandle);

	_latestItemIdentifier = 0;
	_itemData.clear();

	std::fill(_columnSortingOrder.begin(), _columnSortingOrder.end(), true);

}

int ListViewControl::GetSelection() const
{

	return ListView_GetSelectionMark(_internalWindowHandle);

}

void ListViewControl::OnEnable(bool const & enabled)
{

	EnableWindow(_internalWindowHandle, enabled? TRUE : FALSE);

}

LRESULT ListViewControl::OnNotify(NMHDR const & notification)
{

	if (LVN_COLUMNCLICK == notification.code)
	{

		auto const & translatedNotification = * reinterpret_cast<NMLISTVIEW const *>(&notification);

		SortingData const sortingData = {
			this,
			_internalWindowHandle,
			translatedNotification.iSubItem,
			_columnSortingOrder[translatedNotification.iSubItem],
		};

		_columnSortingOrder[translatedNotification.iSubItem] = !_columnSortingOrder[translatedNotification.iSubItem];

		ListView_SortItems(
			translatedNotification.hdr.hwndFrom,
			ItemComparator,
			reinterpret_cast<LPARAM>(&sortingData)
		);

	}

	return 0;

}

void ListViewControl::OnPaint(PAINTSTRUCT const & paintingData)
{

	RECT clientAreaRectangle;
	GetClientRect(_handle, &clientAreaRectangle);

	static auto const PenHandle = CreatePen(PS_SOLID, 1, BorderColor);
	static auto const BrushHandle = GetStockObject(NULL_BRUSH);

	SelectObject(paintingData.hdc, PenHandle);
	SelectObject(paintingData.hdc, BrushHandle);

	Rectangle(
		paintingData.hdc,
		0,
		0,
		clientAreaRectangle.right,
		clientAreaRectangle.bottom
	);

}

void ListViewControl::OnSize(int const & width, int const & height)
{

	SetWindowPos(
		_internalWindowHandle,
		0,
		1,
		1,
		width - 2,
		height - 2,
		SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER
	);

}

int CALLBACK ListViewControl::ItemComparator(
	LPARAM firstIdentifier,
	LPARAM secondIdentifier,
	LPARAM sortingDataPointer
)
{

	int returnValue = 0;

	auto const sortingData = reinterpret_cast<SortingData const *>(sortingDataPointer);
	if (!sortingData)
		return returnValue;

	auto const & firstValue = sortingData->Control->_itemData[firstIdentifier]
		.InputData[sortingData->ColumnIndex];

	auto const & secondValue = sortingData->Control->_itemData[secondIdentifier]
		.InputData[sortingData->ColumnIndex];

	if (std::holds_alternative<std::string>(firstValue) && std::holds_alternative<std::string>(secondValue))
	{

		auto const & firstString = std::get<std::string>(firstValue);
		auto const & secondString = std::get<std::string>(secondValue);

		returnValue = firstString.compare(secondString);

	}

	else if (std::holds_alternative<int>(firstValue) && std::holds_alternative<int>(secondValue))
	{

		auto const & firstInteger = std::get<int>(firstValue);
		auto const & secondInteger = std::get<int>(secondValue);

		returnValue = Compare(firstInteger, secondInteger);

	}

	return sortingData->SortAscending? returnValue : (-1 * returnValue);

}

std::string ListViewControl::GetPrettyString(ItemValue const & itemValue)
{

	if (std::holds_alternative<std::string>(itemValue))
		return GetSomeText(std::get<std::string>(itemValue));

	else if (std::holds_alternative<int>(itemValue))
		return GetSomeText(PrettifyNumber(std::get<int>(itemValue)));

	return {};

}