#pragma once
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace domain
{
using UUID = boost::uuids::uuid;
UUID GenerateUUID() { return boost::uuids::random_generator(); };
} // namespace domain