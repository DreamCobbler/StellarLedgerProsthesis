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
		/// The total production of it.
		///

		double TotalProduction;

		///
		/// The main producer. First value is the ID of an empire, the second's proportion of
		/// total production.
		///

		std::pair<Identifier, double> MainProducer;

	public:

		///
		/// Describes the main producer in following format: "[Empire Name] ([Percent])".
		///
		/// @param The universe in which the resource exists.
		///
		/// @return The description.
		///

		std::string GetMainProducerDescription(class Universe const & universe) const;

};