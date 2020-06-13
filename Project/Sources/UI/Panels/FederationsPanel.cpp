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

#include <UI/Panels/FederationsPanel.hpp>
#include <UI/UI Parameters.hpp>

#include <Utilities/General.hpp>
#include <Utilities/Text.hpp>

FederationsPanel::FederationsPanel(Window const & parentWindow)
{

	_backgroundBrushHandle = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

	Create(parentWindow);

	_listViewControl = std::make_unique<ListViewControl>(self, true);
	_listViewControl->AppendColumn("Name", ColumnWidthVeryLong);
	_listViewControl->AppendColumn("Date Created", ColumnWidthMedium);
	_listViewControl->AppendColumn("Current Leader", ColumnWidthVeryLong);
	_listViewControl->AppendColumn("Military", ColumnWidthShort);
	_listViewControl->AppendColumn("Economy", ColumnWidthShort);
	_listViewControl->AppendColumn("Technology", ColumnWidthShort);
	_listViewControl->AppendColumn("Planets", ColumnWidthShort);
	_listViewControl->AppendColumn("Pops", ColumnWidthShort);
	_listViewControl->AppendColumn("Research (Prod.)", ColumnWidthMedium);
	_listViewControl->AppendColumn("Energy (Prod.)", ColumnWidthMedium);
	_listViewControl->AppendColumn("Minerals (Prod.)", ColumnWidthMedium);
	_listViewControl->AppendColumn("Food (Prod.)", ColumnWidthMedium);
	_listViewControl->AppendColumn("Alloys (Prod.)", ColumnWidthMedium);
	_listViewControl->AppendColumn("C. Goods (Prod.)", ColumnWidthMedium);
	_listViewControl->AppendColumn("V. Motes (Prod.)", ColumnWidthMedium);
	_listViewControl->AppendColumn("E. Gases (Prod.)", ColumnWidthMedium);
	_listViewControl->AppendColumn("R. Crystals (Prod.)", ColumnWidthMedium);
	_listViewControl->Show(true);

	ObserveUsingMethod(Application::Get(), OnApplicationEvent);

}

FederationsPanel::~FederationsPanel()
{

	Application::Get().Unsubscribe(this);

}

void FederationsPanel::OnApplicationEvent(
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

		for (auto const & federation : application.Universe.Federations)
		{

			auto const leader = application.Universe.GetEntityOfID<Empire>(federation.LeaderID);
			auto const & energy = GetValueOr(federation.Income, std::string("energy"));
			auto const & minerals = GetValueOr(federation.Income, std::string("minerals"));
			auto const & food = GetValueOr(federation.Income, std::string("food"));
			auto const & alloys = GetValueOr(federation.Income, std::string("alloys"));
			auto const & goods = GetValueOr(federation.Income, std::string("consumer_goods"));
			auto const & motes = GetValueOr(federation.Income, std::string("volatile_motes"));
			auto const & gases = GetValueOr(federation.Income, std::string("exotic_gases"));
			auto const & crystals = GetValueOr(federation.Income, std::string("rare_crystals"));

			_listViewControl->AppendItem({
				federation.Name,
				federation.DateCreated,
				leader? leader->Name : std::string(),
				federation.MilitaryPower,
				federation.EconomyPower,
				federation.TechnologyPower,
				federation.PlanetCount,
				federation.PopCount,
				federation.MonthlyResearch,
				static_cast<int>(energy),
				static_cast<int>(minerals),
				static_cast<int>(food),
				static_cast<int>(alloys),
				static_cast<int>(goods),
				static_cast<int>(motes),
				static_cast<int>(gases),
				static_cast<int>(crystals),
			});

		}

	}

}

void FederationsPanel::OnEnable(bool const & enabled)
{

	_listViewControl->Enable(enabled);

}

void FederationsPanel::OnSize(int const & width, int const & height)
{

	_listViewControl->Reposition(
		-1,
		-1,
		width,
		height
	);

}

void FederationsPanel::Clear()
{

	_listViewControl->ClearItems();

}