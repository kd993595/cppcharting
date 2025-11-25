#ifndef GRAPHLIB_CORE_CONCEPTS_HPP
#define GRAPHLIB_CORE_CONCEPTS_HPP

#pragma once
#include <iterator>

namespace graphlib {

// Numeric iterator
template <typename It>
concept NumericIterator =
    std::forward_iterator<It> &&
    std::is_arithmetic_v<std::iter_value_t<It>>;

// String-like iterator for categorical labels
template <typename It>
concept StringIterator =
    std::forward_iterator<It> &&
    (std::same_as<std::iter_value_t<It>, std::string> ||
     std::same_as<std::iter_value_t<It>, const char*>);


}
#endif // GRAPHLIB_CORE_CONCEPTS_HPP
