#include <art/seafire/routing/flatten.hxx>

namespace art::seafire::routing
{

  static
  std::string
  join_path(std::vector<std::string> const& segments)
  {
    std::string path{"/"};

    bool first{true};

    for (auto const& j : segments) {
      if (j.empty()) {
        continue;
      }

      if (first) {
        first = false;
      }
      else {
        path += "/";
      }

      path += j;
    }

    return path;
  }

  void
  flatten(std::vector<endpoint_t>& endpoints,
          std::string const& vhost,
          std::vector<server::middleware_t> middlewares,
          route_t const& route,
          std::vector<std::string> segments)
  {
    segments.emplace_back(route.path());

    // append any middlewares if we have any.
    //
    for (auto const& m : route.middleware()) {
      middlewares.emplace_back(m);
    }

    // generate an endpoint for this route if we have a handler.
    //
    if (auto const& h = route.handler()) {
      endpoints.emplace_back(vhost, join_path(segments), server::make_middleware(middlewares, *h));
    }

    // flatten any child routes.
    //
    for (auto const& child_route : route.children()) {
      flatten(endpoints,
              vhost,
              middlewares,
              child_route,
              segments);
    }
  }

  void
  flatten(std::vector<endpoint_t>& endpoints,
          std::string const& vhost,
          std::vector<server::middleware_t> middlewares,
          route_t const& r)
  {
    flatten(endpoints, vhost, middlewares, r, {});
  }

  std::vector<endpoint_t>
  flatten(std::string const& vhost, route_t const& r)
  {
    std::vector<endpoint_t> endpoints;
    flatten(endpoints, vhost, {}, r);
    return endpoints;
  }

} // namespace art::seafire::routing
