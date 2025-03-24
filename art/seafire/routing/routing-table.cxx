#include <art/seafire/routing/routing-table.hxx>

#include <art/seafire/routing/match.hxx>

namespace art::seafire::routing
{

  routing_table_t::
  routing_table_t(std::vector<endpoint_t> endpoints)
    : endpoints_{std::move(endpoints)}
  {}

  std::vector<endpoint_t> const&
  routing_table_t::
  endpoints() const
  {
    return endpoints_;
  }

  std::optional<routing_table_t::find_result_t>
  routing_table_t::
  find_route(std::string const& host, std::string const& path) const
  {
    for (auto const& e : endpoints()) {
      host_parameters_t host_params;

      if (!match(host, e.host(), '.', host_params)) {
        continue;
      }

      route_parameters_t route_params;

      if (match(path, e.path(), '/', route_params)) {
        return find_result_t{
          std::move(host_params),
          std::move(route_params),
          e.handler()
        };
      }
    }

    return std::nullopt;
  }

} // namespace art::seafire::routing
