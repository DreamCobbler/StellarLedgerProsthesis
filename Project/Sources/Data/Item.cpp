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

#include <Data/Item.hpp>

Item::Item(std::string_view const & name, std::string_view const & value):
	Name(name),
	Value(value)
{}

Item const * Item::Find(std::string const & name) const
{

	auto const iterator = std::find_if(
		Children.cbegin(),
		Children.cend(),
		[&name](Item const & childNode)
		{

			return childNode.Name == name;

		}
	);

	if (Children.cend() == iterator)
		return nullptr;

	return &(* iterator);

}

template<>
std::string Item::FindValueOr(
	std::string const & childNodeName,
	std::string const & alternativeValue
) const
{

	auto const childNode = Find(childNodeName);
	if (!childNode)
		return alternativeValue;

	return std::string(childNode->Value);

}

template<>
int Item::FindValueOr<int>(
	std::string const & childNodeName,
	int const & alternativeValue
) const
{

	auto const node = Find(childNodeName);
	if (!node)
		return alternativeValue;

	return std::stoi(std::string(node->Value));

}

template<>
long long Item::FindValueOr<long long>(
	std::string const & childNodeName,
	long long const & alternativeValue
) const
{

	auto const node = Find(childNodeName);
	if (!node)
		return alternativeValue;

	return std::stoll(std::string(node->Value));

}

template<>
double Item::FindValueOr<double>(
	std::string const & childNodeName,
	double const & alternativeValue
) const
{

	auto const node = Find(childNodeName);
	if (!node)
		return alternativeValue;

	return std::stod(std::string(node->Value));

}