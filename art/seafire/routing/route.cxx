#include <art/seafire/routing/route.hxx>

#include <stdexcept>

namespace art::seafire::routing
{

  static
  std::string
  validate_path(std::string path)
  {
    if (!path.empty()) {
      if (path.front() == '/') {
        throw std::invalid_argument{"route path must not begin with '/'"};
      }

      if (path.back() == '/') {
        throw std::invalid_argument{"route path must not end with '/'"};
      }
    }

    return path;

  }

  route_t::
  route_t() = default;

  route_t::
  route_t(std::string path)
    : path_{validate_path(std::move(path))}
  {}

  route_t::
  route_t(std::string path, server::request_handler_t handler)
    : path_{validate_path(std::move(path))}, handler_{std::move(handler)}
  {}

  std::string const&
  route_t::
  path() const
  {
    return path_;
  }

  std::vector<server::middleware_t> const&
  route_t::
  middleware() const
  {
    return middleware_;
  }

  std::optional<server::request_handler_t> const&
  route_t::
  handler() const
  {
    return handler_;
  }

  std::list<route_t> const&
  route_t::
  children() const
  {
    return children_;
  }

  void
  route_t::
  use(server::middleware_t m)
  {
    middleware_.emplace_back(std::move(m));
  }

  route_t&
  route_t::
  add_route()
  {
    children_.emplace_back();
    return children_.back();
  }

  route_t&
  route_t::
  add_route(std::string path)
  {
    children_.emplace_back(std::move(path));
    return children_.back();
  }

  route_t&
  route_t::
  add_route(std::string path, server::request_handler_t handler)
  {
    children_.emplace_back(std::move(path), std::move(handler));
    return children_.back();
  }

  std::ostream&
  to_stream(std::ostream& o, route_t const& r, std::size_t indent)
  {
    if (indent > 0) {
      o << std::string(indent, ' ');
      o << "-> ";
    }

    o << "route: '" << r.path() << '\'';

    if (!r.middleware().empty()) {
      o << " (with middleware)";
    }

    if (!r.handler()) {
      o << " (null handler)";
    }

    o << '\n';

    for (auto const& child : r.children()) {
      to_stream(o, child, indent + 2);
    }

    return o;
  }

  std::ostream&
  operator<<(std::ostream& o, route_t const& route)
  {
    return to_stream(o, route, 0);
  }

} // namespace art::seafire::routing
