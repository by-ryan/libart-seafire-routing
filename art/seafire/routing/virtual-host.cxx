#include <art/seafire/routing/virtual-host.hxx>

namespace art::seafire::routing
{

  static
  std::string
  validate_host(std::string host)
  {
    if (host.empty()) {
      throw std::invalid_argument{"host must not be empty"};
    }

    if (host.front() == '.') {
      throw std::invalid_argument{"host must not begin with '.'"};
    }

    if (host.back() == '.') {
      throw std::invalid_argument{"host must not end with '.'"};
    }

    return host;
  }

  virtual_host_t::
  virtual_host_t(std::string host)
    : _host{validate_host(std::move(host))}
  {}

  std::string const&
  virtual_host_t::
  host() const
  {
    return _host;
  }

  std::vector<server::middleware_t> const&
  virtual_host_t::
  middleware() const
  {
    return _middleware;
  }

  std::list<route_t> const&
  virtual_host_t::
  routes() const
  {
    return _routes;
  }

  void
  virtual_host_t::
  use(server::middleware_t m)
  {
    _middleware.emplace_back(std::move(m));
  }

  route_t&
  virtual_host_t::
  add_route()
  {
    _routes.emplace_back();
    return _routes.back();
  }

  route_t&
  virtual_host_t::
  add_route(std::string path)
  {
    _routes.emplace_back(std::move(path));
    return _routes.back();
  }

  route_t&
  virtual_host_t::
  add_route(std::string path, server::request_handler_t handler)
  {
    _routes.emplace_back(std::move(path), std::move(handler));
    return _routes.back();
  }

  std::ostream&
  to_stream(std::ostream& o, virtual_host_t const& vhost)
  {
    o << "virtual host: '" << vhost.host() << "'\n";

    for (auto const& r : vhost.routes()) {
      to_stream(o, r, 2);
    }

    return o;
  }

  std::ostream&
  operator<<(std::ostream& o, virtual_host_t const& vhost)
  {
    return to_stream(o, vhost);
  }

} // namespace art::seafire::routing
