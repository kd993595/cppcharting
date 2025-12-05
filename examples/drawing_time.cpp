#include <chartastic/2d/hist.hpp>
#include <iostream>
#include <random>
#include <vector>

int main(){
    std::vector<int> counts {10, 100, 1'000};
    std::vector<int> seeds {30, 60, 90};

    for (auto& count : counts){
        for (auto& seed : seeds){
            std::default_random_engine random_engine {};
            random_engine.seed(seed);
            std::uniform_int_distribution number_dist {1, 100}; // inclusive range

            std::vector<int> numbers;
            for (int i = 0; i < count; ++i){
                numbers.push_back(number_dist(random_engine));
            }

            chartastic::HistPlot plot(numbers.begin(), numbers.end(), 5);
            plot.setTitle("Exam Grade Histogram");
            plot.setColor(RED);
            plot.show();
        }
    }
}
