#include <stdio.h>
#include <stdlib.h>

#include <chartastic/2d/facetgrid.hpp>

int main(void)
{
    //Facetgrid(std::string t, int minX, int maxX, int minY, int maxY, int maxGrids)
    chartastic::Facetgrid facetgrid_plot("My Facetgrid Plot", 0, 15, 0, 100, 2, "x axis name", "y axis name");

    std::vector<int> x = {1,5,6,8,9,11,5,6};
    std::vector<int> y = {10,20,30,40,50,60,70,80};

    facetgrid_plot.addGrid(x.begin(), x.end(), y.begin(), y.end(), "Female");

    x = {2,3,4,7,8,9,10,11};
    y = {15,30,25,47,91,72,65,75};

    facetgrid_plot.addGrid(x.begin(), x.end(), y.begin(), y.end(), "Male");

    facetgrid_plot.show();

    return 0;
}

