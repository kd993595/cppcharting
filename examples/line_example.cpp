#include <stdio.h>
#include <stdlib.h>

#include <cassert>
#include <graphlib/2d/line.hpp>

int main(void)
{

    //Scatter(std::string t, int minX, int maxX, int minY, int maxY) : 
    graphlib::Line line_plot("My Line Plot", 0, 15, 0, 100);

    std::vector<int> x = {1,5,6,8,9,12,13,15};
    std::vector<int> y = {10,20,30,40,10,80,70,80};

    assert(x.size() == y.size());

    line_plot.addLine(x.begin(), x.end(), y.begin(), y.end());

    line_plot.show();

    return 0;
}
