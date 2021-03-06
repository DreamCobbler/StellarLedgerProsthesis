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

#include <UI/Controls/ListViewControl.hpp>

///
/// The "Wars" panel in the main tab view.
///

class WarsPanel final: public Window
{

	public:

		///
		/// The constructor.
		///
		/// @param parentWindow The parent window.
		///

		WarsPanel(Window const & parentWindow);

		///
		/// The destructor.
		///

		~WarsPanel();

		///
		/// Event handler called in reaction to Application's event.
		///
		/// @param application The application that has called the handler.
		/// @param event       The event that has happened.
		///

		void OnApplicationEvent(
			class Application const & application,
			enum class ApplicationEvent const & event
		);

		///
		/// Event handler called in reaction to a List-View Control's event.
		///
		/// @param application The application that has called the handler.
		/// @param event       The event that has happened.
		///

		void OnListViewControlEvent(
			class ListViewControl const & control,
			enum class ListViewControlEvent const & event
		);

	protected:

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
		/// Removes all data from the panel.
		///

		void Clear();

	private:

		///
		/// Mapping between the main control's item identifiers and actual wars.
		///

		std::unordered_map<LPARAM, class War const *> _warsMapping;

		///
		/// The main list view of this panel.
		///

		std::unique_ptr<ListViewControl> _listViewControl;

		///
		/// The list view containing empires participating in the war.
		///

		std::unique_ptr<ListViewControl> _empiresListViewControl;

};