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