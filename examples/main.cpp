#include <graphlib/2d/bar.hpp>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> products = {"apple", "banana", "pear"};
    std::vector<double> sales = {10, 20, 15};

    auto plot = graphlib::bar(products.begin(), products.end(),
                              sales.begin(), sales.end());

	plot.show(); 
}
