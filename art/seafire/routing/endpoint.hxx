#ifndef art__seafire__routing__endpoint_hxx_
#define art__seafire__routing__endpoint_hxx_

#include <art/seafire/server/request-handler.hxx>

#include <ostream>
#include <string>

namespace art::seafire::routing
{

  class endpoint_t
  {
  public:
    endpoint_t(std::string, std::string, server::request_handler_t);

    std::string const&
    host() const;

    std::string const&
    path() const;

    server::request_handler_t const&
    handler() const;

  private:
    std::string host_;
    std::string path_;
    server::request_handler_t handler_;

  };

  std::ostream&
  to_stream(std::ostream&, endpoint_t const&);

  std::ostream&
  operator<<(std::ostream&, endpoint_t const&);

} // namespace art::seafire::routing

#endif
