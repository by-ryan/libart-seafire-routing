#include <art/seafire/routing/endpoint.hxx>

namespace art::seafire::routing
{

  endpoint_t::
  endpoint_t(std::string host,
             std::string path,
             server::request_handler_t handler)
    : host_{std::move(host)},
      path_{std::move(path)},
      handler_{std::move(handler)}
  {}

  std::string const&
  endpoint_t::
  host() const
  {
    return host_;
  }

  std::string const&
  endpoint_t::
  path() const
  {
    return path_;
  }

  server::request_handler_t const&
  endpoint_t::
  handler() const
  {
    return handler_;
  }

  std::ostream&
  to_stream(std::ostream& o, endpoint_t const& ep)
  {
    return o << ep.host() << ": " << ep.path();
  }

  std::ostream&
  operator<<(std::ostream& o, endpoint_t const& ep)
  {
    return to_stream(o, ep);
  }

} // namespace art::seafire::routing
