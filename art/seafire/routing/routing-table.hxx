#ifndef art__seafire__routing__routing_table_hxx_
#define art__seafire__routing__routing_table_hxx_

#include <art/seafire/routing/endpoint.hxx>
#include <art/seafire/routing/parameters.hxx>
#include <art/seafire/routing/route.hxx>

#include <art/seafire/server/request-handler.hxx>

#include <list>
#include <optional>
#include <string>
#include <vector>

namespace art::seafire::routing
{

  class routing_table_t
  {
  public:
    struct find_result_t
    {
      host_parameters_t host_params;
      route_parameters_t route_params;

      server::request_handler_t const& handler;

    };

    explicit
    routing_table_t(std::vector<endpoint_t>);

    std::vector<endpoint_t> const&
    endpoints() const;

    std::optional<find_result_t>
    find_route(std::string const&, std::string const&) const;

  private:
    static
    bool
    match_host(std::string const&, std::string const&);

    std::vector<endpoint_t> endpoints_;

  };

} // namespace art::seafire::routing

#endif
