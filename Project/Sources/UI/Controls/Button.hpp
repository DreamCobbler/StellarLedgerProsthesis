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

///
/// A push button.
///

class Button final: public Window
{

	public:

		///
		/// The typical height of a button.
		///

		static auto constexpr TypicalHeight = 30;

		///
		/// The function to be called whenever the button's pushed.
		///

		std::function<void()> Action = nullptr;

	public:

		///
		/// The constructor.
		///
		/// @param parentWindow The parent window.
		///

		Button(Window const & parentWindow);

		///
		/// Set's the buttons text.
		///
		/// @param text The text.
		///

		void SetText(std::string const & text);

	protected:

		///
		/// Event handler called whenever the window receives a command.
		///

		virtual void OnCommand(WPARAM const & identifier) override;

		///
		/// Event handler called whenever the window is enable or disabled.
		///

		virtual void OnEnable(bool const & enabled) override;

		///
		/// Event handler called whenever the window's position or size changes.
		///
		/// @param width  The new width of the window.
		/// @param height The new height of the window.

		virtual void OnSize(int const & width, int const & height) override;

	private:

		///
		/// The handle of the actual button control.
		///

		HWND _internalWindowHandle = 0;

};