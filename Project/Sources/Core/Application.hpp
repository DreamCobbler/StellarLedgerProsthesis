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

#include <UI/Windows/MainWindow.hpp>

#include <Utilities/Observable/Observable.hpp>

#include <World/Universe.hpp>

///
/// An event "Application" class can send.
///

enum class ApplicationEvent
{

	UniverseIsChanging,
	UniverseHasChanged, // "The world... is changed. I feel it in the water. I feel it in the earth.
	                    //  I smell it in the air."

};

///
/// The application.
///

class Application final: public Observable<Application, ApplicationEvent>
{

	public:

		///
		/// Retrieves the one and only instance of the class.
		///
		/// @return *the* instance of the class.
		///

		static Application & Get();

	public:

		///
		/// The state of the universe.
		///

		Universe Universe;

		///
		/// The time it took to load the universe, in milliseconds.
		///

		long long UniverseLoadingTime = 0;

	public:

		///
		/// Launches the application.
		///

		void Launch();

		///
		/// Quits the application.
		///

		void Quit();

		///
		/// Loads a saved game state.
		///
		/// @param savedGameState A saved game state.
		///

		void LoadGameState(class GameState & savedGameState);

	private:

		///
		/// The constructor.
		///

		Application();

	private:

		///
		/// The main window.
		///

		std::unique_ptr<MainWindow> _mainWindow;

};