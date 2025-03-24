#include <art/seafire/routing/match.hxx>

#include <sstream>
#include <vector>

namespace art::seafire::routing
{

  bool
  match(std::string const& subject,
        std::string const& pattern,
        char delim,
        parameters_t& params)
  {
    parameters_t tmp_params;

    // p/pend = pattern iterators.
    //
    auto p = pattern.begin();
    auto const pend = pattern.end();

    // s/send = subject iterators.
    //
    auto s = subject.begin();
    auto const send = subject.end();

    auto match_param = [&]()
    {
      // k/kend = local pattern iterators.
      //
      auto const k = p;
      while (p != pend && '}' != *p) {
        ++p;
      }
      auto const kend = p;
      ++p;

      if (k == kend) {
        throw std::invalid_argument{"empty parameter name"};
      }

      // a greedy parameter will eat the rest of the subject.
      //
      bool const greedy{'*' == *k && 1 == std::distance(k, kend)};

      // v/vend = local subject iterators.
      //
      auto const v = s;
      while (s != send && (greedy || delim != *s)) {
        ++s;
      }
      auto const vend = s;

      tmp_params.map().emplace(std::string{k, kend}, std::string{v, vend});
    };

    while (p != pend) {
      if (*p == '{') {
        ++p;
        match_param();
        continue;
      }

      if (s == send) {
        break;
      }

      if (*p != *s) {
        return false;
      }

      ++p;
      ++s;
    }

    if (p != pend || s != send) {
      return false;
    }

    params = std::move(tmp_params);

    return true;
  }

  std::string
  render(std::string const& pattern, parameters_t& params)
  {
    std::stringstream str;

    auto p = pattern.begin();
    auto pend = pattern.end();

    while (p != pend) {
      if (*p == '{') {
        ++p;

        auto const k = p;
        while (p != pend && '}' != *p) {
          ++p;
        }
        auto const kend = p;

        str << params.get(std::string{k, kend}).value_or("<unknown>");
      }
      else {
        str << *p;
      }

      ++p;
    }

    return str.str();
  }

} // namespace art::seafire::routing
