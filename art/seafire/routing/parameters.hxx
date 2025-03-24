#ifndef seafire_routing__parameters_hxx_
#define seafire_routing__parameters_hxx_

#include <map>
#include <optional>
#include <string>
#include <utility>

namespace art::seafire::routing
{

  class parameters_t
  {
  public:
    using map_type = std::map<std::string, std::string>;

    parameters_t() = default;

    parameters_t(map_type values)
      : _values{std::move(values)}
    {}

    map_type&
    map();

    map_type const&
    map() const;

    std::optional<std::string>
    get(std::string const&) const;

  private:
    map_type _values;

  };

  class host_parameters_t
    : public parameters_t
  {
  public:
    using parameters_t::parameters_t;

  };

  class route_parameters_t
    : public parameters_t
  {
  public:
    using parameters_t::parameters_t;

  };

} // namespace art::seafire::routing


#endif
