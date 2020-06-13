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

#include <UI/Panels/ResourcesPanel.hpp>
#include <UI/UI Parameters.hpp>

#include <Utilities/Text.hpp>

ResourcesPanel::ResourcesPanel(Window const & parentWindow)
{

	Create(parentWindow);

	_listViewControl = std::make_unique<ListViewControl>(self, true);
	_listViewControl->AppendColumn("Name", ColumnWidthLong);
	_listViewControl->AppendColumn("Production", ColumnWidthMedium);
	_listViewControl->AppendColumn("Main Producer", ColumnWidthVeryLong);
	_listViewControl->AppendColumn("Consumption", ColumnWidthMedium);
	_listViewControl->AppendColumn("Main Consumer", ColumnWidthVeryLong);
	_listViewControl->Show(true);

	ObserveUsingMethod(Application::Get(), OnApplicationEvent);

}

ResourcesPanel::~ResourcesPanel()
{

	Application::Get().Unsubscribe(this);

}

void ResourcesPanel::OnApplicationEvent(
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

		static std::unordered_map<std::string, std::string> const NamingScheme =
		{

			{"energy", "Energy"},
			{"minerals", "Minerals"},
			{"food", "Food"},
			{"alloys", "Alloys"},
			{"consumer_goods", "Consumer Goods"},
			{"volatile_motes", "Volatile Motes"},
			{"exotic_gases", "Exotic Gases"},
			{"rare_crystals", "Rare Crystals"},
			{"nanites", "Nanites"},
			{"sr_zro", "Zro"},
			{"sr_living_metal", "Living Metal"},
			{"sr_dark_matter", "Dark Matter"},

		};

		for (auto const & resource : application.Universe.Resources)
		{

			auto const nameIterator = NamingScheme.find(resource.Name);
			if (NamingScheme.cend() == nameIterator)
				continue;

			_listViewControl->AppendItem({
				NamingScheme.at(resource.Name),
				static_cast<int>(resource.TotalProduction),
				resource.GetMainProducerDescription(application.Universe),
				static_cast<int>(resource.TotalConsumption),
				resource.GetMainConsumerDescription(application.Universe),
			});

		}

	}

}

void ResourcesPanel::OnEnable(bool const & enabled)
{

	_listViewControl->Enable(enabled);

}

void ResourcesPanel::OnSize(int const & width, int const & height)
{

	_listViewControl->Reposition(
		-1,
		-1,
		width,
		height
	);

}

void ResourcesPanel::Clear()
{

	_listViewControl->ClearItems();

}