#include <stdio.h>
#include <stdlib.h>

#include <chartastic/2d/line.hpp>

int main(void)
{

    //Line(std::string t, int minX, int maxX, int minY, int maxY) : 
    chartastic::Line line_plot("My Line Plot", 0, 15, 0, 100, "x axis name", "y axis name", true);
    line_plot.setColors(chartastic::ColorPalette::palette2);

    std::vector<int> x = {1,5,6,8,9,12,13,15};
    std::vector<int> y = {10,20,30,40,10,80,70,80};
    line_plot.addLine(x.begin(), x.end(), y.begin(), y.end());

    x = {1,3,5,7,9,11,13};
    y = {90,80,65,70,50,40,30};
    line_plot.addLine(x.begin(),x.end(),y.begin(),y.end());

    line_plot.show();

    return 0;
}
