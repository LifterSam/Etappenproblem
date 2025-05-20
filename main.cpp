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


void maxLengthPerDay(int& days, int& minimalMax, std::vector<int>& stagesLengths){
    int low = *std::max_element(stagesLengths.begin(), stagesLengths.end());
    int high = std::accumulate(stagesLengths.begin(), stagesLengths.end(), 0);

    while (low < high) {
        int mid = low + (high - low) / 2;
        int daysNeeded = 1;
        int sumOfStages = 0;

        for (int distanz : stagesLengths) {
            if (sumOfStages + distanz > mid) {
                daysNeeded++;
                sumOfStages = 0;
            }
            sumOfStages += distanz;
        }

        if (daysNeeded <= days) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    minimalMax = low;
}



int main() {

    int stages, days, minimalMax;
    std::vector<int> stagesLengths;

    readInputFile(stages, days, stagesLengths);
    maxLengthPerDay(days, minimalMax, stagesLengths);


    std::deque<int> stageGroups;
    int currentSum = 0;
    int remainingDays = days;

    // iterating backwards through the stages
    for (auto it = stagesLengths.rbegin(); it != stagesLengths.rend(); ++it) {
        if (currentSum + *it > minimalMax || (remainingDays - 1) > std::distance(it, stagesLengths.rend()) - 1) {
            stageGroups.push_front(currentSum);
            currentSum = 0;
            remainingDays--;
        }
        currentSum += *it;
    }
    stageGroups.push_front(currentSum); // add last group

    for (size_t i = 0; i < stageGroups.size(); ++i) {
        std::cout << (i + 1) << ". Day: " << stageGroups[i] << " km\n";
    }
    std::cout << "Max: " << minimalMax << " km" << std::endl;

    return 0;
}
