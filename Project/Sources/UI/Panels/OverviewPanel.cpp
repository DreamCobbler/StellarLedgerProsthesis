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

#include <UI/Panels/OverviewPanel.hpp>
#include <UI/UI Parameters.hpp>

#include <Utilities/General.hpp>
#include <Utilities/Text.hpp>

OverviewPanel::OverviewPanel(Window const & parentWindow)
{

	_backgroundBrushHandle = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

	Create(parentWindow);

	_listViewControl = std::make_unique<ListViewControl>(self, true, true);
	_listViewControl->AppendColumn("Parameter", ColumnWidthVeryLong);
	_listViewControl->AppendColumn("Value", ColumnWidthVeryLong);
	_listViewControl->Show(true);

	ObserveUsingMethod(Application::Get(), OnApplicationEvent);

}

OverviewPanel::~OverviewPanel()
{

	Application::Get().Unsubscribe(this);

}

void OverviewPanel::OnApplicationEvent(
	Application const & application,
	ApplicationEvent const & event
)
{

	if (ApplicationEvent::UniverseIsChanging == event)
	{

		Clear();
		Enable(false);

	}

	else if (ApplicationEvent::UniverseHasChanged == event)
	{

		Enable(true);

		_listViewControl->AppendItem({
			"Player's Empire",
			application.Universe.PlayerEmpireName
		});

		_listViewControl->AppendItem({
			"Current Date",
			application.Universe.CurrentDate
		});

		_listViewControl->AppendItem({
			"Game Version",
			application.Universe.GameVersion
		});

		_listViewControl->AppendItem({
			"Empires",
			static_cast<int>(application.Universe.Empires.size())
		});

		_listViewControl->AppendItem({
			"Federations",
			static_cast<int>(application.Universe.Federations.size())
		});

		_listViewControl->AppendItem({
			"Inhabited Planets",
			static_cast<int>(application.Universe.Planets.size())
		});

		_listViewControl->AppendItem({
			"Inhabited Systems",
			static_cast<int>(application.Universe.Systems.size())
		});

		_listViewControl->AppendItem({
			"Species",
			static_cast<int>(application.Universe.Species.size())
		});

		_listViewControl->AppendItem({
			"Pops",
			static_cast<int>(application.Universe.Pops.size())
		});

		_listViewControl->AppendItem({
			"Total Energy Production",
			static_cast<int>(GetValueOr(application.Universe.Income, std::string("energy")))
		});

		_listViewControl->AppendItem({
			"Total Minerals Production",
			static_cast<int>(GetValueOr(application.Universe.Income, std::string("minerals")))
		});

		_listViewControl->AppendItem({
			"Total Food Production",
			static_cast<int>(GetValueOr(application.Universe.Income, std::string("food")))
		});

		_listViewControl->AppendItem({
			"Total Alloys Production",
			static_cast<int>(GetValueOr(application.Universe.Income, std::string("alloys")))
		});

		_listViewControl->AppendItem({
			"Total C. Goods Production",
			static_cast<int>(GetValueOr(application.Universe.Income, std::string("consumer_goods")))
		});

		_listViewControl->AppendItem({
			"Total V. Motes Production",
			static_cast<int>(GetValueOr(application.Universe.Income, std::string("volatile_motes")))
		});

		_listViewControl->AppendItem({
			"Total E. Gases Production",
			static_cast<int>(GetValueOr(application.Universe.Income, std::string("exotic_gases")))
		});

		_listViewControl->AppendItem({
			"Total R. Crystals Production",
			static_cast<int>(GetValueOr(application.Universe.Income, std::string("rare_crystals")))
		});

	}

}

void OverviewPanel::OnEnable(bool const & enabled)
{

	_listViewControl->Enable(enabled);

}

void OverviewPanel::OnSize(int const & width, int const & height)
{

	_listViewControl->Reposition(
		std::nullopt,
		std::nullopt,
		width,
		height
	);

}

void OverviewPanel::Clear()
{

	_listViewControl->ClearItems();

}