#include <chartastic/2d/function.hpp>
#include <cmath>
#include <raylib.h>

int main() {
	chartastic::FunctionPlot plot;

	plot.setTitle("Mathematical Functions");
	plot.setXRange(-5, 5);
	plot.setWindowSize(1000, 700);

	// Add polynomials
	// y = x² - 2
	chartastic::Polynomial quadratic({-2, 0, 1});
	plot.add(quadratic, BLUE);

	// y = -x³ + 3x
	chartastic::Polynomial cubic({0, 3, 0, -1}, "-x³ + 3x");
	plot.add(cubic, RED);

	// y = 0.5x + 1
	chartastic::Polynomial linear({1, 0.5});
	plot.add(linear, GREEN);

	// Add custom functions using lambdas
	plot.add([](double x) { return std::sin(x) * 30; }, "30sin(x)", ORANGE);
	plot.add([](double x) { return std::cos(x) * 20; }, "20cos(x)", PURPLE);

	// Display the plot
	// plot.show();

	// Or export to file
	plot.exportAs("functions.png");

	return 0;
}
