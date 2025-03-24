#ifndef art__seafire__routing__builder_hxx_
#define art__seafire__routing__builder_hxx_

#include <art/seafire/routing/routing-table.hxx>
#include <art/seafire/routing/virtual-host.hxx>

#include <art/seafire/server/request-handler.hxx>

#include <list>
#include <string>

namespace art::seafire::routing
{

  class builder_t
  {
  public:
    builder_t();

    builder_t(builder_t const&) = delete;
    builder_t(builder_t&&) = delete;

    std::list<virtual_host_t> const&
    virtual_hosts() const;

    virtual_host_t&
    add_virtual_host(std::string);

    routing_table_t
    build() const;

    builder_t& operator=(builder_t const&) = delete;
    builder_t& operator=(builder_t&&) = delete;

  private:
    std::list<virtual_host_t> _vhosts;

  };

} // namespace art::seafire::routing

#endif
