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

	Create(parentWindow);

	_listViewControl = std::make_unique<ListViewControl>(self, true);
	_listViewControl->AppendColumn("Name", ColumnWidthUltraLong);
	_listViewControl->AppendColumn("Date Started", ColumnWidthMedium);
	_listViewControl->AppendColumn("Attacker's Exhaustion", ColumnWidthLong);
	_listViewControl->AppendColumn("Defender's Exhaustion", ColumnWidthLong);
	_listViewControl->Show(true);

	ObserveUsingMethod(Application::Get(), OnApplicationEvent);

}

WarsPanel::~WarsPanel()
{

	Application::Get().Unsubscribe(this);

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
			_listViewControl->AppendItem({
				war.Name,
				war.StartDate,
				PrettifyNumber(war.AttackerWarExhaustion * 100) + "%",
				PrettifyNumber(war.DefenderWarExhaustion * 100) + "%",
			});

	}

}

void WarsPanel::OnEnable(bool const & enabled)
{

	_listViewControl->Enable(enabled);

}

void WarsPanel::OnSize(int const & width, int const & height)
{

	_listViewControl->Reposition(
		-1,
		-1,
		width,
		height
	);

}

void WarsPanel::Clear()
{

	_listViewControl->ClearItems();

}