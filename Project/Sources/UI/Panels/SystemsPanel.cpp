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

#include <UI/Panels/SystemsPanel.hpp>
#include <UI/UI Parameters.hpp>

#include <Utilities/Text.hpp>

SystemsPanel::SystemsPanel(Window const & parentWindow)
{

	_backgroundBrushHandle = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

	Create(parentWindow);

	_listViewControl = std::make_unique<ListViewControl>(self, true, true);
	_listViewControl->AppendColumn("Name", ColumnWidthVeryLong);
	_listViewControl->AppendColumn("Empire", ColumnWidthVeryLong);
	_listViewControl->AppendColumn("Planets", ColumnWidthShort);
	_listViewControl->AppendColumn("Pops", ColumnWidthShort);
	_listViewControl->AppendColumn("Species", ColumnWidthShort);
	_listViewControl->AppendColumn("Main Species", ColumnWidthVeryLong);
	_listViewControl->Show(true);

	ObserveUsingMethod(Application::Get(), OnApplicationEvent);

}

SystemsPanel::~SystemsPanel()
{

	Application::Get().Unsubscribe(this);

}

void SystemsPanel::OnApplicationEvent(
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

		for (auto const & system : application.Universe.Systems)
		{

			auto const mainSpecies = application.Universe.GetEntityOfID<Species>(
				system.MainSpecies.first
			);

			std::stringstream mainSpeciesStream;
			mainSpeciesStream
				<< mainSpecies->Name << ": " << FormatPercent(system.MainSpecies.second);

			_listViewControl->AppendItem({
				system.Name,
				application.Universe.GetEntityOfID<Empire>(system.OwnerID)->Name,
				static_cast<int>(system.PlanetIDs.size()),
				system.PopCount,
				system.SpeciesCount,
				mainSpeciesStream.str(),
			});

		}

	}

}

void SystemsPanel::OnEnable(bool const & enabled)
{

	_listViewControl->Enable(enabled);

}

void SystemsPanel::OnSize(int const & width, int const & height)
{

	_listViewControl->Reposition(
		std::nullopt,
		std::nullopt,
		width,
		height
	);

}

void SystemsPanel::Clear()
{

	_listViewControl->ClearItems();

}