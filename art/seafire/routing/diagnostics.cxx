#include <art/seafire/routing/diagnostics.hxx>

namespace art::seafire::routing
{

  /// Returns a reference to the routing diagnostic category.
  ///
  common::diagnostics_t::category_t const&
  routing_category()
  {
    static common::diagnostics_t::category_t category{"router"};
    return category;
  }

} // namespace art::seafire::routing
