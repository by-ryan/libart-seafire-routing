#ifndef art__seafire__routing__route_parameter_hxx_
#define art__seafire__routing__route_parameter_hxx_

#include <art/seafire/server/parameters.hxx>
#include <art/seafire/server/request.hxx>

#include <art/seafire/routing/parameters.hxx>

#include <optional>

namespace art::seafire::routing
{

  template<
    server::parameter_name_t Name,
    typename ParameterType = server::string_parameter_t
  >
  class route_parameter_t
    : public server::named_parameter_t<Name>
  {
  public:
    using parameter_type = ParameterType;
    using value_type = typename parameter_type::value_type;

    route_parameter_t(std::optional<value_type> value)
      : _value{std::move(value)}
    {}

    using server::named_parameter_t<Name>::name;

    std::optional<value_type> const&
    value() const
    {
      return _value;
    }

    operator std::optional<value_type> const&() const
    {
      return value();
    }

    std::optional<value_type> const*
    operator->() const
    {
      return &value();
    }

    static
    route_parameter_t<Name, ParameterType>
    fetch(server::request_t& req)
    {
      auto v = req.extensions().use<route_parameters_t>().get(name());
      return parameter_type::try_parse(v);
    }

  private:
    std::optional<value_type> _value;

  };

} // namespace art::seafire::routing

#endif
