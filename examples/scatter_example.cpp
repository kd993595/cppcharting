#include <stdio.h>
#include <stdlib.h>

#include <cassert>
#include <chartastic/2d/scatter.hpp>

int main(void)
{

    //Scatter(std::string t, int minX, int maxX, int minY, int maxY) 
    chartastic::Scatter scatter_plot("My Scatter Plot", 0, 15, -250, -100, "My x axis(cm)", "Y axis name(4)",true);

    std::vector<int> x = {1,5,6,8,9,11,5,6};
    std::vector<int> y = {-100,-200,-150,-140,-150,-160,-170,-240};
    std::vector<int> sizes = {1,2,0,0,9,8,4,0};

    assert(x.size() == y.size());

    scatter_plot.addScatter(x.begin(), x.end(), y.begin(), y.end(), sizes.begin(), sizes.end());

    x = {2,3,4,7,8,9,10,11};
    y = {-115,-130,-125,-147,-191,-172,-165,-175};

    scatter_plot.addScatter(x.begin(), x.end(), y.begin(), y.end());

    x = {3,4,5,6,7,8};
    y = {-165,-170,-113,-156,-134,-179};
    scatter_plot.addScatter(x.begin(), x.end(), y.begin(), y.end());

    x = {3,4,5,6,7,8};
    y = {-225,-205,-111,-116,-132,-169};
    scatter_plot.addScatter(x.begin(), x.end(), y.begin(), y.end());


    x = {3,4,5,6,7,8};
    y = {-245,-179,-143,-146,-187,-198};
    scatter_plot.addScatter(x.begin(), x.end(), y.begin(), y.end());


    x = {2,4,5,6,10,12};
    y = {-157,-245,-156,-176,-166,-177};
    scatter_plot.addScatter(x.begin(), x.end(), y.begin(), y.end());


    x = {3,4,5,6,9,15};
    y = {-169,-188,-123,-146,-194,-129};
    scatter_plot.addScatter(x.begin(), x.end(), y.begin(), y.end());


    x = {3,4,5,6,7,14};
    y = {-199,-154,-198,-121,-187,-205};
    scatter_plot.addScatter(x.begin(), x.end(), y.begin(), y.end());


    x = {1,4,5,6,9,8};
    y = {-160,-160,-134,-234,-240,-102};
    scatter_plot.addScatter(x.begin(), x.end(), y.begin(), y.end());


    scatter_plot.show();

    return 0;
}

