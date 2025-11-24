#include <graphlib/2d/area.hpp>
#include <raylib.h>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> products = {"Apple", "Banana", "Pear", "Orange"};
    std::vector<double> sales = {10, 20, 15, 25};

    auto plot = graphlib::area(products.begin(), products.end(),
                               sales.begin(), sales.end());

    plot.title = "Fruit Sales Area";
    plot.fill_color = SKYBLUE;

    plot.show();
}
