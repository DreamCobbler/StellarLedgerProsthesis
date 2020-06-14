#pragma once

///
/// A resource.
///

class Resource final
{

	public:

		///
		/// The name of the resource.
		///

		std::string Name;

		///
		/// The total production of the resource.
		///

		double TotalProduction;

		///
		/// The main producer. First value is the ID of an empire, the second's proportion of
		/// total production.
		///

		std::pair<Identifier, double> MainProducer;

		///
		/// The total consumption of the resource.
		///

		double TotalConsumption;

		///
		/// The main consumer. First value is the ID of an empire, the second's proportion of
		/// total consumption.
		///

		std::pair<Identifier, double> MainConsumer;

		///
		/// The flow of the resource (production - consumption).
		///

		double TotalFlow;

	public:

		///
		/// Describes the main producer in following format: "[Empire Name] ([Percent])".
		///
		/// @param The universe in which the resource exists.
		///
		/// @return The description.
		///

		std::string GetMainProducerDescription(class Universe const & universe) const;

		///
		/// Describes the main consumer in following format: "[Empire Name] ([Percent])".
		///
		/// @param The universe in which the resource exists.
		///
		/// @return The description.
		///

		std::string GetMainConsumerDescription(class Universe const & universe) const;

		///
		/// Calculates some of the values.
		///
		/// @param universe The universe in which the resource exists.
		///

		void Recalculate(class Universe const & universe);

};