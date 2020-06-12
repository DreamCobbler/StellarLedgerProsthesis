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

template<typename Key, typename Value>
Value const & GetValueOr(
	std::unordered_map<Key, Value> const & map,
	Key const & key,
	Value const & placeholder
)
{

	auto const iterator = map.find(key);
	if (map.cend() == iterator)
		return placeholder;

	return iterator->second;

}

template<typename Type>
int Compare(Type const & first, Type const & second)
{

	if (first < second)
		return -1;

	else if (first > second)
		return +1;

	return 0;

}

template<typename Timepoint>
long long CountMilliseconds(Timepoint const & first, Timepoint const & second)
{

	return std::chrono::duration_cast<std::chrono::milliseconds>(second - first).count();

}

template<typename Key, typename Value>
std::unordered_map<Key, Value> SumMaps(
	std::unordered_map<Key, Value> const & first,
	std::unordered_map<Key, Value> const & second
)
{

	std::unordered_map<Key, Value> sum = first;

	for (auto const & item : second)
		sum[item.first] += item.second;

	return sum;

}