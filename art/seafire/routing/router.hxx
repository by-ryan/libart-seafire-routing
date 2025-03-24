#ifndef art__seafire__routing__router_hxx_
#define art__seafire__routing__router_hxx_

#include <art/seafire/routing/diagnostics.hxx>
#include <art/seafire/routing/routing-table.hxx>

#include <art/seafire/common/diagnostics.hxx>

#include <art/seafire/server/request.hxx>
#include <art/seafire/server/response.hxx>

namespace art::seafire::routing
{

  class router_t
  {
  public:
    router_t(common::diagnostics_t&, routing_table_t);

    routing_table_t const&
    routing_table() const;

    void
    on_request(server::request_t&, server::response_t&) const;

    void
    operator()(server::request_t&, server::response_t&) const;

  private:
    common::diagnostics_t::proxy_t
    trace() const;

    common::diagnostics_t& diagnostics_;
    routing_table_t rt_;

  };

} // namespace art::seafire::routing

#endif
