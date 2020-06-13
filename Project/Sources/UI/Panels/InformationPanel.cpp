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

#include <UI/Panels/InformationPanel.hpp>
#include <UI/UI Parameters.hpp>

#include <Utilities/Text.hpp>

#include <Configuration.hpp>

InformationPanel::InformationPanel(Window const & parentWindow)
{

	_backgroundBrushHandle = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

	Create(parentWindow);

	_loadingTimeLabel = std::make_unique<Label>(self);
	_loadingTimeLabel->SetText("No saved game state has been loaded yet.");
	_loadingTimeLabel->Show();

	_copyrightNoticeLabel = std::make_unique<Label>(self);
	_copyrightNoticeLabel->SetText(
		"© (" + CreationYears + ") " + CreatorName + " (" + CreatorContact + ")"
	);
	_copyrightNoticeLabel->Show();

	ObserveUsingMethod(Application::Get(), OnApplicationEvent);

}

InformationPanel::~InformationPanel()
{

	Application::Get().Unsubscribe(this);

}

void InformationPanel::OnApplicationEvent(
	Application const & application,
	ApplicationEvent const & event
)
{

	if (ApplicationEvent::UniverseIsChanging == event)
	{

		_loadingTimeLabel->SetText("Loading selected game state…");

		RepositionChildren();

	}

	if (ApplicationEvent::UniverseHasChanged == event)
	{

		auto const loadingTimeText = PrettifyNumber(application.UniverseLoadingTime);
		_loadingTimeLabel->SetText("Loading the game state took " + loadingTimeText + " ms.");

		RepositionChildren();

	}

}

void InformationPanel::OnSize(int const & width, int const & height)
{

	auto const loadingTimeLabelSize = _loadingTimeLabel->GetMinimumWindowSize();
	_loadingTimeLabel->Reposition(
		StandardMarginWidth,
		(height - loadingTimeLabelSize.second) / 2,
		loadingTimeLabelSize.first,
		loadingTimeLabelSize.second
	);

	auto const copyrightNoticeLabelSize = _copyrightNoticeLabel->GetMinimumWindowSize();
	_copyrightNoticeLabel->Reposition(
		width - StandardMarginWidth - copyrightNoticeLabelSize.first,
		(height - copyrightNoticeLabelSize.second) / 2,
		copyrightNoticeLabelSize.first,
		copyrightNoticeLabelSize.second
	);

}