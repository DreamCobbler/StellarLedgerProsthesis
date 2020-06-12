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

#include <Core/Application.hpp>

#include <Data/GameStateProcessor.hpp>

#include <Utilities/General.hpp>

Application & Application::Get()
{

	static auto instance = Application();

	return instance;

}

void Application::Launch()
{

	_mainWindow = std::make_unique<MainWindow>();
	_mainWindow->Show();

	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{

		TranslateMessage(&message);
		DispatchMessage(&message);

	}

}

void Application::Quit()
{

	PostQuitMessage(EXIT_SUCCESS);

}

void Application::LoadGameState(GameState & savedGameState)
{

	if (!savedGameState.Load())
		return;

	Broadcast(ApplicationEvent::UniverseIsChanging);

	auto const startTimepoint = std::chrono::steady_clock::now();

	auto processor = GameStateProcessor();
	if (!processor.Process(savedGameState.Description))
		return;

	if (!Universe.Create(processor.ViewItemTree()))
		return;

	UniverseLoadingTime = CountMilliseconds(startTimepoint, std::chrono::steady_clock::now());

	Broadcast(ApplicationEvent::UniverseHasChanged);

}

Application::Application()
{

	INITCOMMONCONTROLSEX commonControlsInitialization;
	commonControlsInitialization.dwSize = sizeof(commonControlsInitialization);
	commonControlsInitialization.dwICC = ICC_LISTVIEW_CLASSES | ICC_TAB_CLASSES;

	InitCommonControlsEx(&commonControlsInitialization);

}