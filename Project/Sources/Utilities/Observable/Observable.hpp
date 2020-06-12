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

///
/// An *observable* things - one that can send notifications to its observers from time to time.
///

template<typename Observed, typename Event>
class Observable
{

	public:

		using Observer = void const *;
		using Action = std::function<void(Observed const &, Event const &)>;

	public:

		///
		/// The destructor.
		///

		virtual ~Observable() {}

		///
		/// Subscribes an observer to the observable.
		///
		/// @param observer The observer in question.
		/// @param actiion  The action to be called when an event is broadcasted.
		///

		void Subscribe(Observer const & observer, Action const & action);

		///
		/// Unsubscribes an observer from the observable.
		///
		/// @param observer The observer.
		///

		void Unsubscribe(Observer const & observer);

	protected:

		///
		/// Broadcasts an event to all subscribed observers.
		///
		/// @param event The event in question.
		///

		void Broadcast(Event const & event);

	protected:

		///
		/// Collection of all the observers.
		///

		std::unordered_map<Observer, Action> _observers;

};

#define ObserveUsingMethod(observable, method)                                                \
	(observable).Subscribe(                                                                   \
		this,                                                                                 \
		[this](auto const & observed, auto const & event) { return method(observed, event); } \
	)

#include <Utilities/Observable/Observable - Broadcast.hpp>
#include <Utilities/Observable/Observable - Subscribe.hpp>
#include <Utilities/Observable/Observable - Unsubscribe.hpp>