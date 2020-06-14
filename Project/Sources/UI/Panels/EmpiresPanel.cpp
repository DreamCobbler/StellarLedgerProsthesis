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

#include <UI/Panels/EmpiresPanel.hpp>
#include <UI/UI Parameters.hpp>

#include <Utilities/General.hpp>
#include <Utilities/Text.hpp>

EmpiresPanel::EmpiresPanel(Window const & parentWindow)
{

	_backgroundBrushHandle = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

	Create(parentWindow);

	_listViewControl = std::make_unique<ListViewControl>(self, true, true);
	_listViewControl->AppendColumn("Name", ColumnWidthVeryLong);
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

EmpiresPanel::~EmpiresPanel()
{

	Application::Get().Unsubscribe(this);

}

void EmpiresPanel::OnApplicationEvent(
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

		for (auto const & empire : application.Universe.Empires)
		{

			auto const & energy = GetValueOr(empire.Income, std::string("energy"));
			auto const & minerals = GetValueOr(empire.Income, std::string("minerals"));
			auto const & food = GetValueOr(empire.Income, std::string("food"));
			auto const & alloys = GetValueOr(empire.Income, std::string("alloys"));
			auto const & consumerGoods = GetValueOr(empire.Income, std::string("consumer_goods"));
			auto const & volatileMotes = GetValueOr(empire.Income, std::string("volatile_motes"));
			auto const & exoticGases = GetValueOr(empire.Income, std::string("exotic_gases"));
			auto const & rareCrystals = GetValueOr(empire.Income, std::string("rare_crystals"));

			_listViewControl->AppendItem({
				empire.Name,
				empire.MilitaryPower,
				empire.EconomyPower,
				empire.TechnologyPower,
				empire.PlanetCount,
				empire.PopCount,
				empire.MonthlyResearch,
				static_cast<int>(energy),
				static_cast<int>(minerals),
				static_cast<int>(food),
				static_cast<int>(alloys),
				static_cast<int>(consumerGoods),
				static_cast<int>(volatileMotes),
				static_cast<int>(exoticGases),
				static_cast<int>(rareCrystals),
			});

		}

	}

}

void EmpiresPanel::OnEnable(bool const & enabled)
{

	_listViewControl->Enable(enabled);

}

void EmpiresPanel::OnSize(int const & width, int const & height)
{

	_listViewControl->Reposition(
		std::nullopt,
		std::nullopt,
		width,
		height
	);

}

void EmpiresPanel::Clear()
{

	_listViewControl->ClearItems();

}