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

#include <UI/Panels/FleetsPanel.hpp>
#include <UI/UI Parameters.hpp>

#include <Utilities/Text.hpp>

FleetsPanel::FleetsPanel(Window const & parentWindow)
{

	_backgroundBrushHandle = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

	Create(parentWindow);

	_listViewControl = std::make_unique<ListViewControl>(self, true, true);
	_listViewControl->AppendColumn("Name", ColumnWidthVeryLong);
	_listViewControl->AppendColumn("Owner", ColumnWidthVeryLong);
	_listViewControl->AppendColumn("Power", ColumnWidthShort);
	_listViewControl->AppendColumn("Hit Points", ColumnWidthShort);
	_listViewControl->Show(true);

	ObserveUsingMethod(Application::Get(), OnApplicationEvent);

}

FleetsPanel::~FleetsPanel()
{

	Application::Get().Unsubscribe(this);

}

void FleetsPanel::OnApplicationEvent(
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

		for (auto const & fleet : application.Universe.Fleets)
		{

			auto const empire = application.Universe.GetEntityOfID<Empire>(fleet.OwnerID);

			_listViewControl->AppendItem({
				fleet.Name,
				empire? empire->Name : std::string(),
				fleet.MilitaryPower,
				fleet.HitPoints,
			});

		}

	}

}

void FleetsPanel::OnEnable(bool const & enabled)
{

	_listViewControl->Enable(enabled);

}

void FleetsPanel::OnSize(int const & width, int const & height)
{

	_listViewControl->Reposition(
		std::nullopt,
		std::nullopt,
		width,
		height
	);

}

void FleetsPanel::Clear()
{

	_listViewControl->ClearItems();

}