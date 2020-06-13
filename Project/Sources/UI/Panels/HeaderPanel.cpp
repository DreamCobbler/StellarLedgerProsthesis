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

#include <UI/Panels/HeaderPanel.hpp>
#include <UI/UI Parameters.hpp>

#include <Configuration.hpp>

HeaderPanel::HeaderPanel(Window const & parentWindow)
{

	_backgroundBrushHandle = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

	Create(parentWindow);

	_applicationLabel = std::make_unique<Label>(self);
	_applicationLabel->SetFont(20);
	_applicationLabel->SetText(ApplicationName + " v" + ApplicationVersion);
	_applicationLabel->Show();

}

void HeaderPanel::OnSize(int const & width, int const & height)
{

	auto const minimumLabelSize = _applicationLabel->GetMinimumWindowSize();
	auto const labelWidth = std::min(width, minimumLabelSize.first);
	auto const labelHeight = std::min(height, minimumLabelSize.second);

	_applicationLabel->Reposition(
		StandardMarginWidth,
		(height - labelHeight) / 2,
		labelWidth,
		labelHeight
	);

}