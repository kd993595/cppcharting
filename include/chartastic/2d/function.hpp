#ifndef CHARTASTIC_2D_FUNCTION_HPP
#define CHARTASTIC_2D_FUNCTION_HPP

#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include <chartastic/core/error.hpp>
#include <chartastic/2d/plot.hpp>
#include <raylib.h>

namespace chartastic {

// Base class for mathematical functions
class Function {
public:
    virtual ~Function() = default;
    virtual double evaluate(double x) const = 0;
    virtual std::string getLabel() const = 0;
};

// Polynomial class: a₀ + a₁x + a₂x² + ... + aₙxⁿ
class Polynomial : public Function {
private:
    std::vector<double> coefficients_;  // [a₀, a₁, a₂, ..., aₙ]
    std::string label_;

    std::string generateLabel() const {
        // Generate label like "2x² + 3x - 1"
        std::string result;
        bool first_term = true;

        for (int i = coefficients_.size() - 1; i >= 0; --i) {
            double coef = coefficients_[i];
            if (std::abs(coef) < 1e-10) continue;  // Skip zero coefficients

            // Add sign
            if (!first_term) {
                result += (coef > 0) ? " + " : " - ";
            } else if (coef < 0) {
                result += "-";
            }

            double abs_coef = std::abs(coef);

            // Add coefficient (skip 1 unless it's the constant term)
            if (abs_coef != 1.0 || i == 0) {
                // Format nicely - show decimals only if needed
                if (abs_coef == static_cast<int>(abs_coef)) {
                    result += std::to_string(static_cast<int>(abs_coef));
                } else {
                    char buf[32];
                    snprintf(buf, sizeof(buf), "%.2f", abs_coef);
                    result += buf;
                }
            }

            // Add variable and exponent
            if (i > 0) {
                result += "x";
                if (i > 1) {
                    result += "^" + std::to_string(i);
                }
            }

            first_term = false;
        }

        return result.empty() ? "0" : result;
    }

public:
    // Coefficients from lowest to highest degree: {a₀, a₁, a₂, ...}
    Polynomial(const std::vector<double>& coefficients, const std::string& label = "")
        : coefficients_(coefficients) {
        if (coefficients_.empty()) {
            throw ChartasticError("Polynomial coefficients cannot be empty");
        }

        // Generate label if not provided
        label_ = label.empty() ? generateLabel() : label;
    }

    double evaluate(double x) const override {
        double result = 0.0;
        double x_power = 1.0;
        for (double coef : coefficients_) {
            result += coef * x_power;
            x_power *= x;
        }
        return result;
    }

    std::string getLabel() const override {
        return label_;
    }
};

// Custom function using lambda/function pointer
class CustomFunction : public Function {
private:
    std::function<double(double)> func_;
    std::string label_;

public:
    CustomFunction(std::function<double(double)> func, const std::string& label)
        : func_(func), label_(label) {
        if (!func_) {
            throw ChartasticError("Custom function cannot be null");
        }
    }

    double evaluate(double x) const override {
        return func_(x);
    }

    std::string getLabel() const override {
        return label_;
    }
};

// Function plot class
class FunctionPlot : public Plot {
private:
    struct FunctionData {
        std::shared_ptr<Function> function;
        Color color;
    };

    std::vector<FunctionData> functions_;
    double x_min_ = -10.0;
    double x_max_ = 10.0;
    double y_min_ = -10.0;
    double y_max_ = 10.0;
    bool auto_scale_y_ = true;
    int num_points_ = 500;

    void renderChart() const;

public:
    FunctionPlot() {
        title_ = "Function Plot";
    }

    void show() const override;
    void exportAs(const std::string& filename) const;

    // Add functions
    void add(const Polynomial& poly, Color color = BLUE) {
        functions_.push_back({std::make_shared<Polynomial>(poly), color});
    }

    void add(std::function<double(double)> func, const std::string& label, Color color = BLUE) {
        functions_.push_back({std::make_shared<CustomFunction>(func, label), color});
    }

    void clear() {
        functions_.clear();
    }

    // Getters
    double getXMin() const { return x_min_; }
    double getXMax() const { return x_max_; }
    double getYMin() const { return y_min_; }
    double getYMax() const { return y_max_; }
    bool getAutoScaleY() const { return auto_scale_y_; }
    int getNumPoints() const { return num_points_; }

    // Setters
    void setXRange(double x_min, double x_max) {
        if (x_min >= x_max) {
            throw ChartasticError("X minimum must be less than X maximum");
        }
        x_min_ = x_min;
        x_max_ = x_max;
    }

    void setYRange(double y_min, double y_max) {
        if (y_min >= y_max) {
            throw ChartasticError("Y minimum must be less than Y maximum");
        }
        y_min_ = y_min;
        y_max_ = y_max;
        auto_scale_y_ = false;
    }

    void setAutoScaleY(bool auto_scale) {
        auto_scale_y_ = auto_scale;
    }

    void setNumPoints(int num_points) {
        if (num_points < 10) {
            throw ChartasticError("Number of points must be at least 10, got " +
                                std::to_string(num_points));
        }
        num_points_ = num_points;
    }
};

} // namespace chartastic

#endif // CHARTASTIC_2D_FUNCTION_HPP
