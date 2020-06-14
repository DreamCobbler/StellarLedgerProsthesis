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

#include <UI/Windows/MainWindow.hpp>
#include <UI/UI Parameters.hpp>

#include <Configuration.hpp>

MainWindow::MainWindow()
{

	Create(0, ApplicationName);

	_headerPanel = std::make_unique<HeaderPanel>(self);
	_headerPanel->Show();

	_sidePanel = std::make_unique<SidePanel>(self);
	_sidePanel->Show();

	_informationPanel = std::make_unique<InformationPanel>(self);
	_informationPanel->Show();

	_overviewPanel = std::make_unique<OverviewPanel>(self);
	_speciesPanel = std::make_unique<SpeciesPanel>(self);
	_empiresPanel = std::make_unique<EmpiresPanel>(self);
	_federationsPanel = std::make_unique<FederationsPanel>(self);
	_systemsPanel = std::make_unique<SystemsPanel>(self);
	_planetsPanel = std::make_unique<PlanetsPanel>(self);
	_fleetsPanel = std::make_unique<FleetsPanel>(self);
	_warsPanel = std::make_unique<WarsPanel>(self);
	_resourcesPanel = std::make_unique<ResourcesPanel>(self);

	_mainTabViewControl = std::make_unique<TabViewControl>(self);
	_mainTabViewControl->AppendTab("Overview", * _overviewPanel);
	_mainTabViewControl->AppendTab("Species", * _speciesPanel);
	_mainTabViewControl->AppendTab("Empires", * _empiresPanel);
	_mainTabViewControl->AppendTab("Federations", * _federationsPanel);
	_mainTabViewControl->AppendTab("Systems", * _systemsPanel);
	_mainTabViewControl->AppendTab("Planets", * _planetsPanel);
	_mainTabViewControl->AppendTab("Fleets", * _fleetsPanel);
	_mainTabViewControl->AppendTab("Wars", * _warsPanel);
	_mainTabViewControl->AppendTab("Resources", * _resourcesPanel);
	_mainTabViewControl->Show();

	EnablePanels(false);

	ObserveUsingMethod(Application::Get(), OnApplicationEvent);

}

MainWindow::~MainWindow()
{

	Application::Get().Unsubscribe(this);

}

void MainWindow::OnApplicationEvent(Application const &, ApplicationEvent const & event)
{

	switch (event)
	{

		case ApplicationEvent::UniverseIsChanging:
			EnablePanels(false);
			break;

		case ApplicationEvent::UniverseHasChanged:
			EnablePanels(true);
			break;

	}

}

void MainWindow::OnDestroy()
{

	Application::Get().Quit();

}

void MainWindow::OnSize(int const & width, int const & height)
{

	static auto constexpr HeaderHeight = 50;
	static auto constexpr SidePanelWidth = 325;
	static auto constexpr InformationPanelHeight = 30;

	// Position the header.

	_headerPanel->Reposition(
		std::nullopt,
		std::nullopt,
		width,
		HeaderHeight
	);

	// Position the side panel.

	_sidePanel->Reposition(
		StandardMarginWidth,
		HeaderHeight + LargeMarginWidth,
		SidePanelWidth,
		height - (HeaderHeight + LargeMarginWidth) -
			(2 * StandardMarginWidth) - InformationPanelHeight
	);

	// Position the information panel.

	_informationPanel->Reposition(
		std::nullopt,
		height - InformationPanelHeight,
		width,
		InformationPanelHeight
	);

	// Position the tab view control.

	_mainTabViewControl->Reposition(
		StandardMarginWidth + SidePanelWidth + LargeMarginWidth,
		HeaderHeight + LargeMarginWidth,
		width - (StandardMarginWidth + SidePanelWidth + LargeMarginWidth) - StandardMarginWidth,
		height - (2 * StandardMarginWidth) -
			(HeaderHeight + LargeMarginWidth) - InformationPanelHeight
	);

}

void MainWindow::EnablePanels(bool const & enable)
{

	_overviewPanel->Enable(enable);
	_speciesPanel->Enable(enable);
	_empiresPanel->Enable(enable);
	_federationsPanel->Enable(enable);
	_systemsPanel->Enable(enable);
	_planetsPanel->Enable(enable);
	_fleetsPanel->Enable(enable);
	_warsPanel->Enable(enable);
	_resourcesPanel->Enable(enable);

}