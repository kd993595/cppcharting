#include <stdio.h>
#include <stdlib.h>

#include <cassert>
#include <graphlib/2d/scatter.hpp>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{

    //Scatter(std::string t, int minX, int maxX, int minY, int maxY) : 
    graphlib::Scatter scatter_plot("My Scatter Plot", 0, 15, 0, 100);

    std::vector<int> x = {1,5,6,8,9,11,5,6};
    std::vector<int> y = {10,20,30,40,50,60,70,80};

    assert(x.size() == y.size());

    scatter_plot.addScatter(x.begin(), x.end(), y.begin(), y.end());

    scatter_plot.show();

    return 0;
}

