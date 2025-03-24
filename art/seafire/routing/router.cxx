#include <art/seafire/routing/router.hxx>
#include <art/seafire/routing/diagnostics.hxx>

#include <art/seafire/protocol/rfc7230/host.hxx>

namespace art::seafire::routing
{

  static
  std::string
  normalize_path(std::string const& path)
  {
    std::stringstream ipath{path};
    std::vector<std::string> segments;

    for (std::string segment; std::getline(ipath, segment, '/');) {
      if (segment.empty()) {
        continue;
      }

      if (segment == ".") {
        continue;
      }

      if (segment == "..") {
        if (!segments.empty()) {
          segments.pop_back();
        }
        continue;
      }

      segments.push_back(segment);
    }

    std::string normalized;

    for (auto const& j : segments) {
      normalized += '/';
      normalized += j;
    }

    return normalized.empty() ? "/" : normalized;
  }

  router_t::
  router_t(common::diagnostics_t& diagnostics, routing_table_t table)
    : diagnostics_{diagnostics}, rt_{std::move(table)}
  {}

  routing_table_t const&
  router_t::
  routing_table() const
  {
    return rt_;
  }

  void
  router_t::
  on_request(server::request_t& req, server::response_t& res) const
  {
    trace() << "on_request(...)";

    auto host = get<art::seafire::protocol::rfc7230::host_t>(req);

    if (!host) {
      trace() << "host not present on request!";
      res.send(server::common_error_t::not_found);
      return;
    }

    auto hostname = host->hostname();
    auto path = normalize_path(req.get_message().target_uri().path_str());

    trace() << "locating endpoint:\n"
            << "  -> hostname: " << hostname << '\n'
            << "  -> path    : " << path
            ;

    auto result = routing_table().find_route(hostname, path);

    if (!result) {
      trace() << "endpoint for [" << path << "] not found";
      res.send(server::common_error_t::not_found);
      return;
    }

    auto trace_endpoint = [&result](common::diagnostics_t::proxy_t proxy)
    {
      proxy << "endpoint found!";

      for (auto const& j : result->host_params.map())
        proxy << "\n -> host param : " << j.first << " = " << j.second << '\n';

      for (auto const& j : result->route_params.map())
        proxy << "\n -> route param: " << j.first << " = " << j.second << '\n';
    };

    trace_endpoint(trace());

    req.extensions().extend(&res.memory().alloc(result->host_params));
    req.extensions().extend(&res.memory().alloc(result->route_params));

    result->handler.invoke(req, res);
  }

  void
  router_t::
  operator()(server::request_t& req, server::response_t& res) const
  {
    on_request(req, res);
  }

  common::diagnostics_t::proxy_t
  router_t::
  trace() const
  {
    return diagnostics_ << routing_category();
  }

} // namespace art::seafire::routing
