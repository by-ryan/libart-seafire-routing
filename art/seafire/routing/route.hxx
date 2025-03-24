#ifndef art__seafire__routing__route_hxx_
#define art__seafire__routing__route_hxx_

#include <art/seafire/routing/endpoint.hxx>

#include <art/seafire/server/middleware.hxx>
#include <art/seafire/server/request-handler.hxx>

#include <iostream>
#include <list>
#include <optional>
#include <vector>

namespace art::seafire::routing
{

  class route_t
  {
  public:
    route_t();

    explicit
    route_t(std::string);

    route_t(std::string, server::request_handler_t);

    route_t(route_t const&) = delete;
    route_t(route_t&&) = delete;

    std::string const&
    path() const;

    std::vector<server::middleware_t> const&
    middleware() const;

    std::optional<server::request_handler_t> const&
    handler() const;

    std::list<route_t> const&
    children() const;

    void
    use(server::middleware_t);

    route_t&
    add_route();

    route_t&
    add_route(std::string);

    route_t&
    add_route(std::string, server::request_handler_t);

    route_t& operator=(route_t const&) = delete;
    route_t& operator=(route_t&&) = delete;

  private:
    std::string path_;
    std::vector<server::middleware_t> middleware_;
    std::optional<server::request_handler_t> handler_;

    // must be std::list to prevent invalidation of references to
    // individual routes.
    //
    std::list<route_t> children_;

  };

  std::ostream&
  to_stream(std::ostream&, route_t const&, std::size_t);

  std::ostream&
  operator<<(std::ostream&, route_t const&);

} // namespace art::seafire::routing

#endif
