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
/// A piece of rendered text.
///

class Label final: public Window
{

	public:

		///
		/// The constructor.
		///
		/// @param parentWindow The parent window.
		///

		Label(Window const & parentWindow);

		///
		/// Returns the minimum size of the window allowing the whole text to be shown.
		///
		/// @return A pair consisting of minimum window width and minimum window height, in that
		///         order.
		///

		std::pair<int, int> GetMinimumWindowSize() const;

		///
		/// Sets the font used for rendering the text. The control does *not* take responsibility
		/// for freeing given font after its destroyed itself.
		///
		/// @param fontHandle The font's handle.
		///

		void SetFont(HFONT const & fontHandle);

		///
		/// Sets the font used for rendering the text. The control does *not* take responsibility
		/// for freeing given font after its destroyed itself.
		///
		/// @param fontSize The size of the default font.
		///

		void SetFont(int const & fontSize);

		///
		/// Sets the control's text.
		///
		/// @param text The text to be rendered.
		///

		void SetText(std::string const & text);

	protected:

		///
		/// Event handler called whenever the window's content needs to be repainted.
		///

		virtual void OnPaint(PAINTSTRUCT const & paintingData) override;

	private:

		///
		/// The handle to the font used for rendering.
		///

		HFONT _fontHandle = 0;

		///
		/// The text to be rendered.
		///

		std::string _text;

		///
		/// The minimum window width for the whole text to be shown.
		///

		int _minimumWidth = 0;

		///
		/// The minimum window height for the whole text to be shown.
		///

		int _minimumHeight = 0;

};