#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <deque>

int main() {
    std::ifstream inputFile("../../input/input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Could not open file!" << std::endl;
        return 1;
    }

    int stages, days, numberInStream;
    std::vector<int> stagesLengths;

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



    // Binäre Suche zur Bestimmung der minimalen maximalen Tagesstrecke
    int low = *std::max_element(stagesLengths.begin(), stagesLengths.end());
    int high = std::accumulate(stagesLengths.begin(), stagesLengths.end(), 0);
    int minimalMax;

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

    // Gruppenbildung für die Ausgabe
    std::deque<int> stageGroups;
    int currentSum = 0;
    int remainingDays = days;

    // Rückwärts durch die Etappen gehen
    for (auto it = stagesLengths.rbegin(); it != stagesLengths.rend(); ++it) {
        if (currentSum + *it > minimalMax || (remainingDays - 1) > std::distance(it, stagesLengths.rend()) - 1) {
            stageGroups.push_front(currentSum);
            currentSum = 0;
            remainingDays--;
        }
        currentSum += *it;
    }
    stageGroups.push_front(currentSum); // Letzte Gruppe hinzufügen

    // Ausgabe der Tagesstrecken
    for (size_t i = 0; i < stageGroups.size(); ++i) {
        std::cout << (i + 1) << ". Day: " << stageGroups[i] << " km\n";
    }
    std::cout << "Max: " << minimalMax << " km" << std::endl;

    inputFile.close();
    return 0;
}
