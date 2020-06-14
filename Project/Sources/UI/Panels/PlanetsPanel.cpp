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

#include <UI/Panels/PlanetsPanel.hpp>
#include <UI/UI Parameters.hpp>

#include <Utilities/Text.hpp>

PlanetsPanel::PlanetsPanel(Window const & parentWindow)
{

	_backgroundBrushHandle = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

	Create(parentWindow);

	_listViewControl = std::make_unique<ListViewControl>(self, true, true, false);
	_listViewControl->AppendColumn("Name", ColumnWidthMedium);
	_listViewControl->AppendColumn("Owner", ColumnWidthVeryLong);
	_listViewControl->AppendColumn("Size", ColumnWidthShort);
	_listViewControl->AppendColumn("Date Colonized", ColumnWidthMedium);
	_listViewControl->AppendColumn("Pops", ColumnWidthShort);
	_listViewControl->AppendColumn("Species", ColumnWidthShort);
	_listViewControl->AppendColumn("Main Species", ColumnWidthVeryLong);
	_listViewControl->Show(true);

	ObserveUsingMethod(Application::Get(), OnApplicationEvent);

}

PlanetsPanel::~PlanetsPanel()
{

	Application::Get().Unsubscribe(this);

}

void PlanetsPanel::OnApplicationEvent(
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

		for (auto const & planet : application.Universe.Planets)
		{

			auto const empire = application.Universe.GetEntityOfID<Empire>(planet.OwnerID);

			auto const mainSpecies = application.Universe.GetEntityOfID<Species>(
				planet.MainSpecies.first
			);
			auto const mainSpeciesName = mainSpecies->Name;
			auto const mainSpeciesPercent = 100 * planet.MainSpecies.second;

			std::stringstream mainSpeciesStream;
			mainSpeciesStream
				<< mainSpeciesName << ": "
				<< PrettifyNumber(mainSpeciesPercent) << "%";

			_listViewControl->AppendItem({
				planet.Name,
				empire? empire->Name : std::string(),
				planet.Size,
				planet.DateColonized,
				planet.PopCount,
				planet.SpeciesCount,
				mainSpeciesStream.str(),
			});

		}

	}

}

void PlanetsPanel::OnEnable(bool const & enabled)
{

	_listViewControl->Enable(enabled);

}

void PlanetsPanel::OnSize(int const & width, int const & height)
{

	_listViewControl->Reposition(
		-1,
		-1,
		width,
		height
	);

}

void PlanetsPanel::Clear()
{

	_listViewControl->ClearItems();

}