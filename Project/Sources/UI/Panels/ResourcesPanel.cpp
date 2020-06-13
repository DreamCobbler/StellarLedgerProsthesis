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
	_listViewControl->AppendColumn("Name", ColumnWidthMedium);
	_listViewControl->AppendColumn("Production", ColumnWidthShort);
	_listViewControl->AppendColumn("Main Producer", ColumnWidthVeryLong);
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

		if (auto const resource = application.Universe.GetEntityOfName<Resource>("energy"))
			_listViewControl->AppendItem({
				"Energy",
				static_cast<int>(resource->TotalProduction),
				resource->GetMainProducerDescription(application.Universe),
			});

		if (auto const resource = application.Universe.GetEntityOfName<Resource>("minerals"))
			_listViewControl->AppendItem({
				"Minerals",
				static_cast<int>(resource->TotalProduction),
				resource->GetMainProducerDescription(application.Universe),
			});

		if (auto const resource = application.Universe.GetEntityOfName<Resource>("food"))
			_listViewControl->AppendItem({
				"Food",
				static_cast<int>(resource->TotalProduction),
				resource->GetMainProducerDescription(application.Universe),
			});

		if (auto const resource = application.Universe.GetEntityOfName<Resource>("alloys"))
			_listViewControl->AppendItem({
				"Alloys",
				static_cast<int>(resource->TotalProduction),
				resource->GetMainProducerDescription(application.Universe),
			});

		if (auto const resource = application.Universe.GetEntityOfName<Resource>("consumer_goods"))
			_listViewControl->AppendItem({
				"C. Goods",
				static_cast<int>(resource->TotalProduction),
				resource->GetMainProducerDescription(application.Universe),
			});

		if (auto const resource = application.Universe.GetEntityOfName<Resource>("volatile_motes"))
			_listViewControl->AppendItem({
				"V. Motes",
				static_cast<int>(resource->TotalProduction),
				resource->GetMainProducerDescription(application.Universe),
			});

		if (auto const resource = application.Universe.GetEntityOfName<Resource>("exotic_gases"))
			_listViewControl->AppendItem({
				"E. Gases",
				static_cast<int>(resource->TotalProduction),
				resource->GetMainProducerDescription(application.Universe),
			});

		if (auto const resource = application.Universe.GetEntityOfName<Resource>("rare_crystals"))
			_listViewControl->AppendItem({
				"R. Crystals",
				static_cast<int>(resource->TotalProduction),
				resource->GetMainProducerDescription(application.Universe),
			});

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