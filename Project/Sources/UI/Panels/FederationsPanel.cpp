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

	_listViewControl = std::make_unique<ListViewControl>(self, true, true);
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

	_empiresListViewControl = std::make_unique<ListViewControl>(self, true, true);
	_empiresListViewControl->AppendColumn("Name", ColumnWidthVeryLong);
	_empiresListViewControl->AppendColumn("Military", ColumnWidthShort);
	_empiresListViewControl->AppendColumn("Economy", ColumnWidthShort);
	_empiresListViewControl->AppendColumn("Technology", ColumnWidthShort);
	_empiresListViewControl->AppendColumn("Planets", ColumnWidthShort);
	_empiresListViewControl->AppendColumn("Pops", ColumnWidthShort);
	_empiresListViewControl->AppendColumn("Research (Prod.)", ColumnWidthMedium);
	_empiresListViewControl->AppendColumn("Energy (Prod.)", ColumnWidthMedium);
	_empiresListViewControl->AppendColumn("Minerals (Prod.)", ColumnWidthMedium);
	_empiresListViewControl->AppendColumn("Food (Prod.)", ColumnWidthMedium);
	_empiresListViewControl->AppendColumn("Alloys (Prod.)", ColumnWidthMedium);
	_empiresListViewControl->AppendColumn("C. Goods (Prod.)", ColumnWidthMedium);
	_empiresListViewControl->AppendColumn("V. Motes (Prod.)", ColumnWidthMedium);
	_empiresListViewControl->AppendColumn("E. Gases (Prod.)", ColumnWidthMedium);
	_empiresListViewControl->AppendColumn("R. Crystals (Prod.)", ColumnWidthMedium);
	_empiresListViewControl->Show(true);

	ObserveUsingMethod(Application::Get(), OnApplicationEvent);
	ObserveUsingMethod(* _listViewControl, OnListViewControlEvent);

}

FederationsPanel::~FederationsPanel()
{

	Application::Get().Unsubscribe(this);
	_listViewControl->Unsubscribe(this);

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

			auto const itemIdentifier = _listViewControl->AppendItem({
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

			_federationsMapping[itemIdentifier] = &federation;

		}

	}

}

void FederationsPanel::OnListViewControlEvent(
	ListViewControl const & control,
	ListViewControlEvent const & event
)
{

	if (ListViewControlEvent::SelectionChanged == event)
	{

		_empiresListViewControl->ClearItems();

		auto const itemIndex = control.GetSelection();
		if (-1 == itemIndex)
			return;

		auto const itemUID = control.GetUID(itemIndex);
		if (!itemUID.has_value())
			return;

		auto const federationIterator = _federationsMapping.find(itemUID.value());
		if (_federationsMapping.cend() == federationIterator)
			return;

		auto const & federation = (* federationIterator->second);
		auto const & universe = Application::Get().Universe;

		for (auto const & ID : federation.MemberIDs)
		{

			auto const empire = universe.GetEntityOfID<Empire>(ID);
			if (!empire)
				continue;

			auto const & energy = GetValueOr(empire->Income, std::string("energy"));
			auto const & minerals = GetValueOr(empire->Income, std::string("minerals"));
			auto const & food = GetValueOr(empire->Income, std::string("food"));
			auto const & alloys = GetValueOr(empire->Income, std::string("alloys"));
			auto const & consumerGoods = GetValueOr(empire->Income, std::string("consumer_goods"));
			auto const & volatileMotes = GetValueOr(empire->Income, std::string("volatile_motes"));
			auto const & exoticGases = GetValueOr(empire->Income, std::string("exotic_gases"));
			auto const & rareCrystals = GetValueOr(empire->Income, std::string("rare_crystals"));

			_empiresListViewControl->AppendItem({
				empire->Name,
				empire->MilitaryPower,
				empire->EconomyPower,
				empire->TechnologyPower,
				empire->PlanetCount,
				empire->PopCount,
				empire->MonthlyResearch,
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

void FederationsPanel::OnEnable(bool const & enabled)
{

	_listViewControl->Enable(enabled);
	_empiresListViewControl->Enable(enabled);

}

void FederationsPanel::OnSize(int const & width, int const & height)
{

	static auto constexpr EmpiresControlHeightProportion = 0.3;

	auto const empiresControlHeight = static_cast<int>(EmpiresControlHeightProportion * height);
	auto const mainControlHeight = height - empiresControlHeight - StandardMarginWidth;

	_listViewControl->Reposition(
		std::nullopt,
		std::nullopt,
		width,
		mainControlHeight
	);

	_empiresListViewControl->Reposition(
		std::nullopt,
		mainControlHeight + StandardMarginWidth,
		width,
		empiresControlHeight
	);

}

void FederationsPanel::Clear()
{

	_federationsMapping.clear();

	_listViewControl->ClearItems();
	_empiresListViewControl->ClearItems();

}