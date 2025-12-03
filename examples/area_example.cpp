#include <chartastic/2d/area.hpp>
#include <raylib.h>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> products = {"Apple", "Banana", "Pear", "Orange"};
    std::vector<double> sales = {10, 20, 15, 25};

    chartastic::AreaPlot plot(products.begin(), products.end(),
                              sales.begin(), sales.end());

    plot.setTitle("Fruit Sales Area");
    plot.setFillColor(SKYBLUE);

    plot.show();
}
