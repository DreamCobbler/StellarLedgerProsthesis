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

#include <UI/Panels/WarsPanel.hpp>
#include <UI/UI Parameters.hpp>

#include <Utilities/Text.hpp>

WarsPanel::WarsPanel(Window const & parentWindow)
{

	_backgroundBrushHandle = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

	Create(parentWindow);

	_listViewControl = std::make_unique<ListViewControl>(self, true, true, false);
	_listViewControl->AppendColumn("Name", ColumnWidthUltraLong);
	_listViewControl->AppendColumn("Date Started", ColumnWidthMedium);
	_listViewControl->AppendColumn("Attacker's Exhaustion", ColumnWidthLong);
	_listViewControl->AppendColumn("Defender's Exhaustion", ColumnWidthLong);
	_listViewControl->Show(true);

	_empiresListViewControl = std::make_unique<ListViewControl>(self, true, true, false);
	_empiresListViewControl->AppendColumn("Empire", ColumnWidthVeryLong);
	_empiresListViewControl->AppendColumn("Side", ColumnWidthMedium);
	_empiresListViewControl->AppendColumn("Military", ColumnWidthShort);
	_empiresListViewControl->Show();

	ObserveUsingMethod(Application::Get(), OnApplicationEvent);
	ObserveUsingMethod(* _listViewControl, OnListViewControlEvent);

}

WarsPanel::~WarsPanel()
{

	Application::Get().Unsubscribe(this);
	_listViewControl->Unsubscribe(this);

}

void WarsPanel::OnApplicationEvent(
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

		for (auto const & war : application.Universe.Wars)
		{

			auto const itemIdentifier = _listViewControl->AppendItem({
				war.Name,
				war.StartDate,
				PrettifyNumber(war.AttackerWarExhaustion * 100) + "%",
				PrettifyNumber(war.DefenderWarExhaustion * 100) + "%",
			});

			_warsMapping[itemIdentifier] = &war;

		}

	}

}

void WarsPanel::OnListViewControlEvent(
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

		auto const warIterator = _warsMapping.find(itemUID.value());
		if (_warsMapping.cend() == warIterator)
			return;

		auto const & war = (* warIterator->second);
		auto const & universe = Application::Get().Universe;

		for (auto const & ID : war.AttackerIDs)
		{

			auto const empire = universe.GetEntityOfID<Empire>(ID);
			if (!empire)
				continue;

			_empiresListViewControl->AppendItem({
				empire->Name,
				"attacker",
				empire->MilitaryPower,
			});

		}

		for (auto const & ID : war.DefenderIDs)
		{

			auto const empire = universe.GetEntityOfID<Empire>(ID);
			if (!empire)
				continue;

			_empiresListViewControl->AppendItem({
				empire->Name,
				"defender",
				empire->MilitaryPower,
			});

		}

	}

}

void WarsPanel::OnEnable(bool const & enabled)
{

	_listViewControl->Enable(enabled);
	_empiresListViewControl->Enable(enabled);

}

void WarsPanel::OnSize(int const & width, int const & height)
{

	static auto constexpr EmpiresControlHeightProportion = 0.3;

	auto const empiresControlHeight = static_cast<int>(EmpiresControlHeightProportion * height);
	auto const mainControlHeight = height - empiresControlHeight - StandardMarginWidth;

	_listViewControl->Reposition(
		-1,
		-1,
		width,
		mainControlHeight
	);

	_empiresListViewControl->Reposition(
		-1,
		mainControlHeight + StandardMarginWidth,
		width,
		empiresControlHeight
	);

}

void WarsPanel::Clear()
{

	_warsMapping.clear();

	_listViewControl->ClearItems();
	_empiresListViewControl->ClearItems();

}