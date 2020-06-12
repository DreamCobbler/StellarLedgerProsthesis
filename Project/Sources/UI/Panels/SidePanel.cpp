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

#include <Data/GameState.hpp>

#include <UI/Panels/SidePanel.hpp>
#include <UI/UI Parameters.hpp>

#include <Utilities/Filesystem.hpp>

#include <Configuration.hpp>

SidePanel::SidePanel(Window const & parentWindow)
{

	Create(parentWindow);

	_savedGameStateListControl = std::make_unique<ListViewControl>(self, true, false);
	_savedGameStateListControl->AppendColumn("Player's Empire", ColumnWidthLong);
	_savedGameStateListControl->AppendColumn("Date", ColumnWidthShort);
	_savedGameStateListControl->Show();

	_loadGameStateButton = std::make_unique<Button>(self);
	_loadGameStateButton->SetText("Load saved game state");
	_loadGameStateButton->Action = [&]()
	{

		auto const selectedSaveGameStateOptionIndex = _savedGameStateListControl->GetSelection();
		if (-1 == selectedSaveGameStateOptionIndex)
			return;

		if (selectedSaveGameStateOptionIndex >= _savedGameStates.size())
			return;

		Application::Get().LoadGameState(_savedGameStates[selectedSaveGameStateOptionIndex]);

	};
	_loadGameStateButton->Show();

	UpdateContent();

	ObserveUsingMethod(Application::Get(), OnApplicationEvent);

}

SidePanel::~SidePanel()
{

	Application::Get().Unsubscribe(this);

}

void SidePanel::OnApplicationEvent(Application const & application, ApplicationEvent const & event)
{

	if (ApplicationEvent::UniverseIsChanging == event)
	{

		_savedGameStateListControl->Enable(false);
		_loadGameStateButton->Enable(false);

	}

	else if (ApplicationEvent::UniverseHasChanged == event)
	{

		_savedGameStateListControl->Enable();
		_loadGameStateButton->Enable();

	}

}

void SidePanel::OnSize(int const & width, int const & height)
{

	auto const listViewHeight = height - StandardMarginWidth - Button::TypicalHeight;

	_savedGameStateListControl->Reposition(
		0,
		0,
		width,
		listViewHeight
	);

	_loadGameStateButton->Reposition(
		0,
		listViewHeight + StandardMarginWidth,
		width,
		Button::TypicalHeight
	);

}

void SidePanel::UpdateContent()
{

	_savedGameStates.clear();
	_savedGameStateListControl->ClearItems();

	auto const gameStatesDirectoryPath = GetGameStatesDirectoryPath();
	if (!std::filesystem::is_directory(gameStatesDirectoryPath))
		MessageBox(
			0,
			"The application couldn't locate the directory containing saved game states.",
			ApplicationName.data(),
			MB_TASKMODAL | MB_ICONERROR
		);

	_savedGameStates = GameState::LocateGameStates(GetGameStatesDirectoryPath());
	for (auto const & gameState : _savedGameStates)
		_savedGameStateListControl->AppendItem({
			gameState.EmpireName,
			gameState.Date
		});

}