#include <chartastic/2d/bar.hpp>
#include <raylib.h>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> products = {"Apple", "Banana", "Pear", "Orange"};
    std::vector<double> sales = {10, 20, 15, 25};

    chartastic::BarPlot plot(products.begin(), products.end(),
                             sales.begin(), sales.end());

    plot.setTitle("Fruit Sales");
    plot.setColors({RED, YELLOW, GREEN, ORANGE});
    plot.setOrientation(chartastic::Orientation::Horizontal);

    plot.show();
}
