#ifndef seafire_routing__virtual_host_hxx_
#define seafire_routing__virtual_host_hxx_

#include <art/seafire/routing/route.hxx>

#include <art/seafire/server/middleware.hxx>
#include <art/seafire/server/request-handler.hxx>

#include <iostream>
#include <list>
#include <optional>
#include <vector>

namespace art::seafire::routing
{

  class virtual_host_t
  {
  public:
    explicit
    virtual_host_t(std::string);

    virtual_host_t(virtual_host_t const&) = delete;
    virtual_host_t(virtual_host_t&&) = delete;

    std::string const&
    host() const;

    std::vector<server::middleware_t> const&
    middleware() const;

    std::list<route_t> const&
    routes() const;

    void
    use(server::middleware_t);

    route_t&
    add_route();

    route_t&
    add_route(std::string);

    route_t&
    add_route(std::string, server::request_handler_t);

    virtual_host_t& operator=(virtual_host_t const&) = delete;
    virtual_host_t& operator=(virtual_host_t&&) = delete;

  private:
    std::string _host;
    std::vector<server::middleware_t> _middleware;
    std::list<route_t> _routes;

  };

  std::ostream&
  to_stream(std::ostream&, virtual_host_t const&);

  std::ostream&
  operator<<(std::ostream&, virtual_host_t const&);

} // namespace art::seafire::routing

#endif
