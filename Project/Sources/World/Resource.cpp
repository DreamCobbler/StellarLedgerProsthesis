#include <Precompiled Headers.hpp>

#include <Utilities/Text.hpp>

#include <World/Universe.hpp>

std::string Resource::GetMainProducerDescription(Universe const & universe) const
{

	auto const empire = universe.GetEntityOfID<Empire>(MainProducer.first);
	if (!empire)
		return {};

	auto const percent = PrettifyNumber(100 * MainProducer.second) + "%";

	return empire->Name + " (" + percent + ")";

}

std::string Resource::GetMainConsumerDescription(Universe const & universe) const
{

	auto const empire = universe.GetEntityOfID<Empire>(MainConsumer.first);
	if (!empire)
		return {};

	auto const percent = PrettifyNumber(100 * MainConsumer.second) + "%";

	return empire->Name + " (" + percent + ")";

}

void Resource::Recalculate(class Universe const & universe)
{

	TotalProduction = 0;
	MainProducer = {-1, 0.0};

	TotalConsumption = 0;
	MainConsumer = {-1, 0.0};

	// Calculate the total production.

	for (auto const & empire : universe.Empires)
	{

		auto const resourceIterator = empire.Income.find(Name);
		if (empire.Income.cend() == resourceIterator)
			continue;

		TotalProduction += resourceIterator->second;

	}

	// Calculate the total consumption.

	for (auto const & empire : universe.Empires)
	{

		auto const resourceIterator = empire.Expenses.find(Name);
		if (empire.Expenses.cend() == resourceIterator)
			continue;

		TotalConsumption += resourceIterator->second;

	}

	// Find the main producer.

	auto const producerIterator = std::max_element(
		universe.Empires.cbegin(),
		universe.Empires.cend(),
		[&](Empire const & left, Empire const & right)
		{

			auto leftValue = 0.0;
			auto rightValue = 0.0;

			auto const leftResourceItem = left.Income.find(Name);
			if (left.Income.cend() != leftResourceItem)
				leftValue = leftResourceItem->second;

			auto const rightResourceItem = right.Income.find(Name);
			if (right.Income.cend() != rightResourceItem)
				rightValue = rightResourceItem->second;

			return leftValue < rightValue;

		}
	);

	if (universe.Empires.cend() == producerIterator || !producerIterator->Income.contains(Name))
	{

		MainProducer = {-1, 0.0};

	}

	else
	{

		MainProducer.first = producerIterator->ID;
		MainProducer.second = producerIterator->Income.at(Name) / TotalProduction;

	}

	// Find the main consumer.

	auto const consumerIterator = std::max_element(
		universe.Empires.cbegin(),
		universe.Empires.cend(),
		[&](Empire const & left, Empire const & right)
		{

			auto leftValue = 0.0;
			auto rightValue = 0.0;

			auto const leftResourceItem = left.Expenses.find(Name);
			if (left.Expenses.cend() != leftResourceItem)
				leftValue = leftResourceItem->second;

			auto const rightResourceItem = right.Expenses.find(Name);
			if (right.Expenses.cend() != rightResourceItem)
				rightValue = rightResourceItem->second;

			return leftValue < rightValue;

		}
	);

	if (universe.Empires.cend() == consumerIterator || !consumerIterator->Expenses.contains(Name))
	{

		MainConsumer = {-1, 0.0};

	}

	else
	{

		MainConsumer.first = consumerIterator->ID;
		MainConsumer.second = consumerIterator->Expenses.at(Name) / TotalConsumption;

	}

}