#include <graphlib/2d/bar.hpp>
#include <raylib.h>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> products = {"Apple", "Banana", "Pear", "Orange"};
    std::vector<double> sales = {10, 20, 15, 25};

    auto plot = graphlib::bar(products.begin(), products.end(),
                              sales.begin(), sales.end());

    plot.title = "Fruit Sales";
    plot.colors = {RED, YELLOW, GREEN, ORANGE};
    plot.orientation = graphlib::Orientation::Horizontal;

    plot.show();
}
