#ifndef GRAPHLIB_2D_PLOT_HPP
#define GRAPHLIB_2D_PLOT_HPP
#pragma once
#include <string>

namespace chartastic {

class Plot {
public:
    std::string title = "Plot";

    virtual ~Plot() = default;

    virtual void show() const = 0;
};

} // namespace graphlib
#endif // GRAPHLIB_2D_PLOT_HPP
