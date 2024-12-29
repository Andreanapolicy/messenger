#include <boost/signals2.hpp>

using Connection = boost::signals2::connection;

using VoidSignal = boost::signals2::signal<void()>;
using VoidSlot = VoidSignal::slot_type;

using BoolSignal = boost::signals2::signal<bool()>;
using BoolSlot = BoolSignal::slot_type;