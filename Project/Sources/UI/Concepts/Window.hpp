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
/// A top-level window.
///

class Window
{

	public:

		///
		/// The constructor.
		///

		Window();

		///
		/// Changes the position and/or size of the window.
		///
		/// @param x      Horizontal position.
		/// @param y      Vertical position.
		/// @param width  Width.
		/// @param height Height.
		///

		virtual void Reposition(
			std::optional<int> x,
			std::optional<int> y,
			std::optional<int> width,
			std::optional<int> height
		) final;

		///
		/// Enables or disables the window.
		///
		/// @param show Are we supposed to enable the window (**true**), or to disable it
		/// (**false**)?
		///

		virtual void Enable(bool const & enable = true) final;

		///
		/// Shows or hides the window.
		///
		/// @param show Are we supposed to show the window (**true**), or to hide it (**false**)?
		///

		virtual void Show(bool const & show = true) final;

		///
		/// Repaints the whole window.
		///

		virtual void Repaint() final;

		///
		/// Repositions child controls.
		///

		virtual void RepositionChildren() final;

		///
		/// Retrieves the window handle.
		///
		/// @return The window handle.
		///

		virtual operator HWND const &() const final;

	protected:

		///
		/// Creates a window of given parameters.
		///
		/// @param title The title of the window.
		/// @param x      Horizontal position.
		/// @param y      Vertical position.
		/// @param width  Width.
		/// @param height Height.
		///

		void Create(
			HWND const & parentWindowHandle = 0,
			std::string const & title = std::string(),
			int const & x = CW_USEDEFAULT,
			int const & y = CW_USEDEFAULT,
			int const & width = CW_USEDEFAULT,
			int const & height = CW_USEDEFAULT
		);

		#pragma warning(push)
		#pragma warning(disable: 4100)

		///
		/// Event handler called whenever the window receives a command.
		///

		virtual void OnCommand(WPARAM const & identifier) {}

		///
		/// Event handler called whenever the window is destroyed.
		///

		virtual void OnDestroy() {}

		///
		/// Event handler called whenever the window is enable or disabled.
		///

		virtual void OnEnable(bool const & enabled) {}

		///
		/// Event handler called whenever the window is required to erase its background.
		///
		/// @param deviceContextHandle The handle of the window's device context.
		/// @param width               The width of the client area.
		/// @param height              The height of the client area.
		///
		/// @return 1 if the background has been erased, 0 otherwise.
		///

		virtual LRESULT OnEraseBackground(
			HDC const & deviceContextHandle,
			int const & width,
			int const & height
		);

		///
		/// Event handler called whenever a notification arrives.
		///
		/// @return Whatever its supposed to return.
		///

		virtual LRESULT OnNotify(NMHDR const & notification) { return 0; }

		///
		/// Event handler called whenever the window's content needs to be repainted.
		///

		virtual void OnPaint(PAINTSTRUCT const & paintingData) {}

		///
		/// Event handler called whenever the window's position or size changes.
		///
		/// @param width  The new width of the window.
		/// @param height The new height of the window.
		///

		virtual void OnSize(int const & width, int const & height) {}

		#pragma warning(pop)

	protected:

		///
		/// The window handle.
		///

		HWND _handle = 0;

		///
		/// The handle of the background brush. It's used by the OnEraseBackground method.
		///

		HBRUSH _backgroundBrushHandle = 0;

		///
		/// The handle of the background pen. It's used by the OnEraseBackground method.
		///

		HPEN _backgroundPenHandle = 0;

	private:

		///
		/// The window procedure.
		///
		/// @param windowHandle  The handle of the window.
		/// @param message       Message code.
		/// @param wordParameter The WORD-sized parameter.
		/// @param longParameter The LONG-sized parameter.
		///
		/// @return ...whatever it is that a window procedure is supposed to return, I think?
		///

		static LRESULT CALLBACK WindowProcedure(
			HWND windowHandle,
			UINT message,
			WPARAM wordParameter,
			LPARAM longParameter
		);

		///
		/// Registers *the* window class used by all windows of the application.
		///

		static void RegisterWindowClass();

};