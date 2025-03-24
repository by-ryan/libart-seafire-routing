#include <art/seafire/routing/parameters.hxx>

namespace art::seafire::routing
{

  parameters_t::map_type&
  parameters_t::
  map()
  {
    return _values;
  }

  parameters_t::map_type const&
  parameters_t::
  map() const
  {
    return _values;
  }

  std::optional<std::string>
  parameters_t::
  get(std::string const& key) const
  {
    if (auto it = map().find(key); it != map().end())
      return it->second;

    return std::nullopt;
  }

} // namespace art::seafire::routing
