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

#include <UI/Controls/Button.hpp>

#include <Utilities/UI.hpp>

Button::Button(Window const & parentWindow)
{

	Create(parentWindow);

	_internalWindowHandle = CreateWindowEx(
		WS_EX_COMPOSITED,
		WC_BUTTON,
		nullptr,
		BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
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

void Button::SetText(std::string const & text)
{

	SetWindowText(_internalWindowHandle, text.data());

}

void Button::OnCommand(WPARAM const & identifier)
{

	if (BN_CLICKED == HIWORD(identifier) && Action)
		Action();

}

void Button::OnEnable(bool const & enabled)
{

	EnableWindow(_internalWindowHandle, enabled? TRUE : FALSE);

}

void Button::OnSize(int const & width, int const & height)
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

}