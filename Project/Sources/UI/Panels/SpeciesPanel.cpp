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

#include <UI/Panels/SpeciesPanel.hpp>
#include <UI/UI Parameters.hpp>

#include <Utilities/Text.hpp>

SpeciesPanel::SpeciesPanel(Window const & parentWindow)
{

	Create(parentWindow);

	_listViewControl = std::make_unique<ListViewControl>(self, true);
	_listViewControl->AppendColumn("Name", ColumnWidthVeryLong);
	_listViewControl->AppendColumn("Home Planet", ColumnWidthMedium);
	_listViewControl->AppendColumn("Pops", ColumnWidthShort);
	_listViewControl->AppendColumn("Planets", ColumnWidthShort);
	_listViewControl->AppendColumn("Planets (Main Species)", ColumnWidthVeryLong);
	_listViewControl->Show(true);

	ObserveUsingMethod(Application::Get(), OnApplicationEvent);

}

SpeciesPanel::~SpeciesPanel()
{

	Application::Get().Unsubscribe(this);

}

void SpeciesPanel::OnApplicationEvent(
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

		for (auto const & species : application.Universe.Species)
		{

			auto const homePlanet = application.Universe.GetEntityOfID<Planet>(
				species.HomePlanetID
			);

			_listViewControl->AppendItem({
				species.Plural,
				homePlanet? homePlanet->Name : std::string(),
				species.PopCount,
				species.PlanetCount,
				species.MainSpeciesPlanetCount,
			});

		}

	}

}

void SpeciesPanel::OnEnable(bool const & enabled)
{

	_listViewControl->Enable(enabled);

}

void SpeciesPanel::OnSize(int const & width, int const & height)
{

	_listViewControl->Reposition(
		-1,
		-1,
		width,
		height
	);

}

void SpeciesPanel::Clear()
{

	_listViewControl->ClearItems();

}