#ifndef CHARTASTIC_CORE_ERROR_HPP
#define CHARTASTIC_CORE_ERROR_HPP

#include <stdexcept>
#include <string>

namespace chartastic {

class ChartasticError : public std::runtime_error {
public:
    explicit ChartasticError(const std::string& message)
        : std::runtime_error("Chartastic error: " + message) {}
};

} // namespace chartastic

#endif // CHARTASTIC_CORE_ERROR_HPP
