#include <art/seafire/routing/builder.hxx>
#include <art/seafire/routing/flatten.hxx>

#include <vector>

namespace art::seafire::routing
{

  builder_t::
  builder_t()
  {}

  std::list<virtual_host_t> const&
  builder_t::
  virtual_hosts() const
  {
    return _vhosts;
  }

  virtual_host_t&
  builder_t::
  add_virtual_host(std::string vhost)
  {
    _vhosts.emplace_back(std::move(vhost));
    return _vhosts.back();
  }

  routing_table_t
  builder_t::
  build() const
  {
    std::vector<endpoint_t> endpoints;

    for (auto const& vhost : _vhosts) {
      for (auto const& r : vhost.routes()) {
        flatten(endpoints, vhost.host(), vhost.middleware(), r);
      }
    }

    return routing_table_t{std::move(endpoints)};
  }

} // namespace art::seafire::routing
