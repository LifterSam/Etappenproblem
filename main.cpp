#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <deque>

int main() {
    std::ifstream inputDatei("../../input/input.txt");
     // Datei öffnen

    if (!inputDatei.is_open()) {
        std::cerr << "Konnte die Datei nicht oeffnen!" << std::endl;
        return 1;
    }

    int etappen, tage, zahlImStream;
    std::vector<int> etappenLaengen;

    inputDatei >> etappen;
    inputDatei >> tage;
    while (inputDatei >> zahlImStream) {
        etappenLaengen.push_back(zahlImStream);
    }

    std::cout << "Eingelesene Etappen: " << etappen << std::endl;
    std::cout << "Eingelesene Tage: " << tage << std::endl;

    std::cout << "Eingelesene EtappenLaengen: [";
    if (!etappenLaengen.empty()) {
        for (size_t i = 0; i < etappenLaengen.size() - 1; ++i) {
            std::cout << etappenLaengen[i] << ", ";
        }
        std::cout << etappenLaengen.back();
    }
    std::cout << "]" << std::endl;



    // Binäre Suche zur Bestimmung der minimalen maximalen Tagesstrecke
    int low = *std::max_element(etappenLaengen.begin(), etappenLaengen.end());
    int high = std::accumulate(etappenLaengen.begin(), etappenLaengen.end(), 0);
    int minimalMax;

    while (low < high) {
        int mid = low + (high - low) / 2;
        int tageBenoetigt = 1;
        int summe = 0;

        for (int distanz : etappenLaengen) {
            if (summe + distanz > mid) {
                tageBenoetigt++;
                summe = 0;
            }
            summe += distanz;
        }

        if (tageBenoetigt <= tage) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    minimalMax = low;

    // Gruppenbildung für die Ausgabe
    std::deque<int> gruppen;
    int currentSum = 0;
    int remainingDays = tage;

    // Rückwärts durch die Etappen gehen
    for (auto it = etappenLaengen.rbegin(); it != etappenLaengen.rend(); ++it) {
        if (currentSum + *it > minimalMax || (remainingDays - 1) > std::distance(it, etappenLaengen.rend()) - 1) {
            gruppen.push_front(currentSum);
            currentSum = 0;
            remainingDays--;
        }
        currentSum += *it;
    }
    gruppen.push_front(currentSum); // Letzte Gruppe hinzufügen

    // Ausgabe der Tagesstrecken
    for (size_t i = 0; i < gruppen.size(); ++i) {
        std::cout << (i + 1) << " . Tag : " << gruppen[i] << " km\n";
    }
    std::cout << "Maximum : " << minimalMax << " km" << std::endl;

    inputDatei.close();
    return 0;
}
