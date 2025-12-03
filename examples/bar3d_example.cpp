#include <chartastic/3d/bar.hpp>
#include <raylib.h>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> products = {"Apple", "Banana", "Pear", "Orange", "Grape"};
    std::vector<double> sales = {45, 78, 62, 91, 53};

    chartastic::BarPlot3D plot(products.begin(), products.end(),
                               sales.begin(), sales.end());

    plot.setTitle("3D Fruit Sales");
    plot.setColors({RED, YELLOW, GREEN, ORANGE, PURPLE});

    plot.show();

    return 0;
}
