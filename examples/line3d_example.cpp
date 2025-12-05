#include <chartastic/3d/line.hpp>
#include <raylib.h>
#include <vector>
#include <string>
#include <cmath>
#include <numbers>

int main() {
  std::vector<float> xvals;
  std::vector<float> yvals;
  std::vector<float> zvals;

  float a = 1;
  const float c = .1;

  for(int t=0;t<200;++t){
    xvals.push_back(std::sin(std::numbers::pi_v<float>/16 * t) * a);
    zvals.push_back(std::cos(std::numbers::pi_v<float>/16 * t) * a);
    yvals.push_back(t * c);
  }

  chartastic::LinePlot3D plot("My 3D line plot");
  plot.addSeries(xvals.begin(),xvals.end(),yvals.begin(),yvals.end(),zvals.begin(),zvals.end(), BLUE, "Helix");

  xvals.clear();
  yvals.clear();
  zvals.clear();
  a = 4;
  for(int t=0;t<200;++t){
    xvals.push_back(std::sin(std::numbers::pi_v<float>/16 * t) * a);
    zvals.push_back(std::cos(std::numbers::pi_v<float>/16 * t) * a);
    yvals.push_back(t * c);
  }
  plot.addSeries(xvals.begin(),xvals.end(),yvals.begin(),yvals.end(),zvals.begin(),zvals.end(), RED, "Bigger Helix");

  plot.show();
  return 0;
}
