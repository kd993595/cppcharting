#include <chartastic/3d/scatter.hpp>
#include <raylib.h>
#include <vector>
#include <string>
#include <cmath>
#include <numbers>

int main() {
  std::vector<float> xvals;
  std::vector<float> yvals;
  std::vector<float> zvals;

  const float a = 5;
  const float c = 1;

  for(int t=0;t<100;++t){
    xvals.push_back(std::sin(std::numbers::pi_v<float>/8 * t * a));
    zvals.push_back(std::cos(std::numbers::pi_v<float>/8 * t * a));
    yvals.push_back(t * c);
  }

  chartastic::ScatterPlot3D plot("My 3D scatter plot");
  plot.addSeries(xvals.begin(),xvals.end(),yvals.begin(),yvals.end(),zvals.begin(),zvals.end());
  

  plot.show();
  return 0;
}
