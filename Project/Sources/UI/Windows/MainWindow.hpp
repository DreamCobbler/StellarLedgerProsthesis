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

#pragma once

#include <UI/Controls/Button.hpp>
#include <UI/Controls/TabViewControl.hpp>
#include <UI/Panels/EmpiresPanel.hpp>
#include <UI/Panels/FederationsPanel.hpp>
#include <UI/Panels/FleetsPanel.hpp>
#include <UI/Panels/HeaderPanel.hpp>
#include <UI/Panels/InformationPanel.hpp>
#include <UI/Panels/OverviewPanel.hpp>
#include <UI/Panels/PlanetsPanel.hpp>
#include <UI/Panels/ResourcesPanel.hpp>
#include <UI/Panels/SidePanel.hpp>
#include <UI/Panels/SpeciesPanel.hpp>
#include <UI/Panels/SystemsPanel.hpp>
#include <UI/Panels/WarsPanel.hpp>

///
/// The main window of the application.
///

class MainWindow final: public Window
{

	public:

		///
		/// The constructor.
		///

		MainWindow();

		///
		/// The destructor.
		///

		~MainWindow();

		///
		/// Event handler called in reaction to Application's event.
		///
		/// @param application The application that has called the handler.
		/// @param event       The event that has happened.
		///

		void OnApplicationEvent(
			class Application const & application,
			enum class ApplicationEvent const & event
		);

	protected:

		///
		/// Event handler called whenever the window is destroyed.
		///

		virtual void OnDestroy() override;

		///
		/// Event handler called whenever the window's position or size changes.
		///
		/// @param width  The new width of the window.
		/// @param height The new height of the window.

		virtual void OnSize(int const & width, int const & height) override;

	private:

		///
		/// Enables/disables all panels (with the exception of the Header panel and the Side panel).
		///
		/// @param enable Enable/disable panels.
		///

		void EnablePanels(bool const & enable = true);

	private:

		///
		/// The header of the window.
		///

		std::unique_ptr<HeaderPanel> _headerPanel;

		///
		/// The sidebar.
		///

		std::unique_ptr<SidePanel> _sidePanel;

		///
		/// The status bar.
		///

		std::unique_ptr<InformationPanel> _informationPanel;

		///
		/// The tab control that contains all the the data to be displayed.
		///

		std::unique_ptr<TabViewControl> _mainTabViewControl;

		///
		/// The "Empires" panel.
		///

		std::unique_ptr<EmpiresPanel> _empiresPanel;

		///
		/// The "Federations" panel.
		///

		std::unique_ptr<FederationsPanel> _federationsPanel;

		///
		/// The "Fleets" panel.
		///

		std::unique_ptr<FleetsPanel> _fleetsPanel;

		///
		/// The "Overview" panel.
		///

		std::unique_ptr<OverviewPanel> _overviewPanel;

		///
		/// The "Planets" panel.
		///

		std::unique_ptr<PlanetsPanel> _planetsPanel;

		///
		/// The "Species" panel.
		///

		std::unique_ptr<SpeciesPanel> _speciesPanel;

		///
		/// The "Systems" panel.
		///

		std::unique_ptr<SystemsPanel> _systemsPanel;

		///
		/// The "Resources" panel.
		///

		std::unique_ptr<ResourcesPanel> _resourcesPanel;

		///
		/// The "Wars" panel.
		///

		std::unique_ptr<WarsPanel> _warsPanel;

};