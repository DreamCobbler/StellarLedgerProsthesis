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

#include <Data/GameStateProcessor.hpp>

bool GameStateProcessor::Process(std::string const & string)
{

	if (string.empty())
		return false;

	_rawText = string;

	if (!Tokenize() || !Parse())
		return false;

	return true;

}

bool GameStateProcessor::IsValidNameCharacter(char const & character)
{

	if (character >= 65 && character <= 90) // A -> Z
		return true;

	else if (character >= 97 && character <= 122) // a -> z
		return true;

	else if (46 == character || 95 == character) // . and _
		return true;

	else if (character >= 48 && character <= 57) // 0 -> 9
		return true;

	return false;
}

bool GameStateProcessor::Tokenize()
{

	if (_rawText.empty())
		return false;

	bool currentlyReadingString = false;

	StringHighlight highlight(_rawText);

	auto const rawTextLength = _rawText.length();
	for (size_t index = 0; index < rawTextLength; ++index)
	{

		auto const & character = _rawText[index];

		if (currentlyReadingString)
		{

			if ('"' == character && (!highlight || '\\' != highlight.Back()))
			{

				_tokens.push_back(highlight);
				highlight.JumpTo(index + 1);

				currentlyReadingString = false;

			}

			else
			{

				highlight.Increment();

			}

		}

		else
		{

			if ('"' == character)
			{

				currentlyReadingString = true;

				highlight.JumpTo(index + 1);

			}

			else if ('=' == character || '{' == character || '}' == character)
			{

				if (highlight)
					_tokens.push_back(highlight);

				highlight.JumpTo(index, 1);

				if (highlight)
					_tokens.push_back(highlight);

				highlight.JumpTo(index + 1);

			}

			else if (!IsValidNameCharacter(character))
			{

				if (highlight)
					_tokens.push_back(highlight);

				highlight.JumpTo(index + 1);

			}

			else
			{

				highlight.Increment();

			}

		}

	}

	return !_tokens.empty();

}

bool GameStateProcessor::Parse()
{

	if (_tokens.empty())
		return false;

	std::stack<Item *> itemStack;
	itemStack.push(&_itemTree);

	auto const tokenCount = _tokens.size();
	for (auto index = 0; index < tokenCount; ++index)
	{

		auto const & previousToken = (index != 0)? _tokens[index - 1] : _tokens[index];
		auto const & token = _tokens[index];
		auto const & nextToken = (index != tokenCount - 1)? _tokens[index + 1] : _tokens[index];

		if ("=" == nextToken)
		{

			itemStack.push(&itemStack.top()->Children.emplace_back(token));

		}

		else if ("{" == token)
		{

			if ("=" == previousToken)
				continue;
			else
				itemStack.push(&itemStack.top()->Children.emplace_back());

		}

		else if ("}" == token)
		{

			itemStack.pop();

		}

		else if ("=" == token)
		{

			continue;

		}

		else
		{

			if ("=" == previousToken)
			{

				itemStack.top()->Value = token;
				itemStack.pop();

			}

			else
			{

				itemStack.top()->Children.emplace_back().Value = token;

			}

		}

	}

	return true;

}