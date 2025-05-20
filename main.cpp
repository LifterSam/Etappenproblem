#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <deque>


int readInputFile(int& stages, int& days, std::vector<int>& stagesLengths){
    std::ifstream inputFile("../../input/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Could not open file!" << std::endl;
        return -1;
    }

    int numberInStream;
    inputFile >> stages;
    inputFile >> days;
    while (inputFile >> numberInStream) {
        stagesLengths.push_back(numberInStream);
    }

    std::cout << "Read stages: " << stages << std::endl;
    std::cout << "Read days: " << days << std::endl;

    // a bit of formatting to make it look like an array
    std::cout << "Read stagesLengths: [";
    if (!stagesLengths.empty()) {
        for (size_t i = 0; i < stagesLengths.size() - 1; ++i) {
            std::cout << stagesLengths[i] << ", ";
        }
        std::cout << stagesLengths.back();
    }
    std::cout << "]" << std::endl;

    inputFile.close();

    return 0;
}


int maxLengthPerDay(int days, const std::vector<int>& stagesLengths){
    int low = *std::max_element(stagesLengths.begin(), stagesLengths.end());
    int high = std::accumulate(stagesLengths.begin(), stagesLengths.end(), 0);

    while (low < high) {
        int mid = low + (high - low) / 2;
        int daysNeeded = 1;
        int sumOfStages = 0;

        for (int distance : stagesLengths) {
            if (sumOfStages + distance > mid) {
                daysNeeded++;
                sumOfStages = 0;
            }
            sumOfStages += distance;
        }

        if (daysNeeded <= days) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}


std::deque<int> groupStagesPerDay(int days, int minimalMax, const std::vector<int>& stagesLengths) {
    std::deque<int> stageGroups;
    int currentSum = 0;
    int remainingDays = days;

    for (auto it = stagesLengths.rbegin(); it != stagesLengths.rend(); ++it) {
        if (currentSum + *it > minimalMax || (remainingDays - 1) > std::distance(it, stagesLengths.rend()) - 1) {
            stageGroups.push_front(currentSum);
            currentSum = 0;
            remainingDays--;
        }
        currentSum += *it;
    }
    stageGroups.push_front(currentSum);
    return stageGroups;
}


int main() {

    int stages, days, minimalMax;
    std::vector<int> stagesLengths;
    std::deque<int> stageGroups;

    readInputFile(stages, days, stagesLengths);
    minimalMax = maxLengthPerDay(days, stagesLengths);
    stageGroups = groupStagesPerDay(days, minimalMax, stagesLengths);

    // output
    std::cout << std::endl;
    for (size_t i = 0; i < stageGroups.size(); ++i) {
        std::cout << (i + 1) << ". Day: " << stageGroups[i] << " km\n";
    }
    std::cout << "Max: " << minimalMax << " km" << std::endl;
    std::cout << std::endl;

    return 0;
}
