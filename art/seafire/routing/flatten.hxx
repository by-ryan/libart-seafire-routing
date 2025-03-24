#ifndef art__seafire__routing__flatten_route_hxx_
#define art__seafire__routing__flatten_route_hxx_

#include <art/seafire/routing/endpoint.hxx>
#include <art/seafire/routing/route.hxx>

#include <art/seafire/server/middleware.hxx>

#include <vector>

namespace art::seafire::routing
{

  void
  flatten(std::vector<endpoint_t>& endpoints,
          std::string const&,
          std::vector<server::middleware_t>,
          route_t const& r,
          std::vector<std::string>);

  void
  flatten(std::vector<endpoint_t>&,
          std::string const&,
          std::vector<server::middleware_t>,
          route_t const&);

  std::vector<endpoint_t>
  flatten(std::string const&, route_t const&);

} // namespace art::seafire::routing

#endif
