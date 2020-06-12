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
/// Retrieves a value associated with a key from a map - and if the key isn't present, returns the
/// given placeholder value.
///
/// @param map         The map.
/// @param key         The key.
/// @param placeholder The placeholder.
///
/// @return Value associated with key, or the placeholder.
///

template<typename Key, typename Value>
Value const & GetValueOr(
	std::unordered_map<Key, Value> const & map,
	Key const & key,
	Value const & placeholder = Value()
);

///
/// Compares two values.
///
/// @param first  The first value.
/// @param second The second value.
///
/// @return -1 if the first value is smaller - +1 if it's greater. 0 if both values are equal.
///

template<typename Type>
int Compare(Type const & first, Type const & second);

///
/// Count milliseconds that passed between two timepoints.
///
/// @param first  The first timepoint.
/// @param second The second timepoint.
///
/// @return The number of milliseconds between the first and the second timepoints.
///

template<typename Timepoint>
long long CountMilliseconds(Timepoint const & first, Timepoint const & second);

///
/// Sums elements of two maps.
///
/// @param first  The first map.
/// @param second The second map.
///
/// @return The sum.
///

template<typename Key, typename Value>
std::unordered_map<Key, Value> SumMaps(
	std::unordered_map<Key, Value> const & first,
	std::unordered_map<Key, Value> const & second
);

#include "General.inl"