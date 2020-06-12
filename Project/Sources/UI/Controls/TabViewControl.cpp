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

#include <UI/Controls/TabViewControl.hpp>
#include <UI/UI Parameters.hpp>

#include <Utilities/UI.hpp>

TabViewControl::TabViewControl(Window const & parentWindow)
{

	Create(parentWindow);

	_internalWindowHandle = CreateWindowEx(
		WS_EX_COMPOSITED,
		WC_TABCONTROL,
		nullptr,
		TCS_FIXEDWIDTH | WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		0,
		0,
		0,
		0,
		_handle,
		0,
		0,
		0
	);

	SendMessage(
		_internalWindowHandle,
		WM_SETFONT,
		reinterpret_cast<WPARAM>(GetDefaultFontHandle()),
		TRUE
	);

}

void TabViewControl::AppendTab(std::string const & title, Window & window)
{

	TCITEM tabDefinition = {0};
	tabDefinition.mask = TCIF_TEXT;
	tabDefinition.pszText = const_cast<char *>(title.data());

	auto const tabIndex = TabCtrl_GetItemCount(_internalWindowHandle);
	TabCtrl_InsertItem(
		_internalWindowHandle,
		tabIndex,
		&tabDefinition
	);

	_tabs[tabIndex] = &window;

	if (0 == tabIndex)
		window.Show();

}

void TabViewControl::OnEnable(bool const & enabled)
{

	EnableWindow(_internalWindowHandle, enabled? TRUE : FALSE);

}

LRESULT TabViewControl::OnNotify(NMHDR const & notification)
{

	if (TCN_SELCHANGE != notification.code)
		return 0;

	auto const selectedTabIndex = TabCtrl_GetCurSel(_internalWindowHandle);
	auto const tabCount = TabCtrl_GetItemCount(_internalWindowHandle);

	for (auto index = 0; index < tabCount; ++index)
		_tabs.at(index)->Show(selectedTabIndex == index? true : false);

	return 0;

}

void TabViewControl::OnSize(int const & width, int const & height)
{

	SetWindowPos(
		_internalWindowHandle,
		0,
		0,
		0,
		width,
		height,
		SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER
	);

	RECT windowRectangle;
	GetWindowRect(_handle, &windowRectangle);
	MapWindowPoints(
		HWND_DESKTOP,
		GetParent(_handle),
		reinterpret_cast<POINT *>(&windowRectangle),
		2
	);

	static auto constexpr TopPadding = 25;
	for (auto const & tab : _tabs)
		tab.second->Reposition(
			windowRectangle.left + StandardMarginWidth,
			windowRectangle.top + StandardMarginWidth + TopPadding,
			windowRectangle.right - windowRectangle.left - 2 * StandardMarginWidth,
			windowRectangle.bottom - windowRectangle.top - 2 * StandardMarginWidth - TopPadding
		);

}