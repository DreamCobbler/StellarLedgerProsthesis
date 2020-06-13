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

#include <UI/Controls/Label.hpp>

///
/// The header panel, in the upper part of the main window.
///

class HeaderPanel final: public Window
{

	public:

		///
		/// The constructor.
		///
		/// @param parentWindow The parent window.
		///

		HeaderPanel(Window const & parentWindow);

	protected:

		///
		/// Event handler called whenever the window's position or size changes.
		///
		/// @param width  The new width of the window.
		/// @param height The new height of the window.

		virtual void OnSize(int const & width, int const & height) override;

	private:

		///
		/// The application name label.
		///

		std::unique_ptr<Label> _applicationLabel;

};