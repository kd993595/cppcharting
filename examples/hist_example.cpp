#include <graphlib/2d/hist.hpp>
#include <vector>

int main(){
    std::vector<int> values = {1,2,3,4};
    auto plot = hist(values.begin(), values.end(), 1);
    plot.show();
}
