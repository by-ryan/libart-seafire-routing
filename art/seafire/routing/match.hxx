#ifndef art__seafire__routing__match_hxx_
#define art__seafire__routing__match_hxx_

#include <art/seafire/routing/parameters.hxx>

#include <string>

namespace art::seafire::routing
{

  bool
  match(std::string const&,
        std::string const&,
        char,
        parameters_t&);

  std::string
  render(std::string const&, parameters_t&);

} // namespace art::seafire::routing

#endif
