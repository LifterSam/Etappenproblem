#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::ifstream inputDatei("../../input/input.txt");
     // Datei öffnen

    if (!inputDatei.is_open()) {
        std::cerr << "Konnte die Datei nicht oeffnen!" << std::endl;
        return 1;
    }

    int etappen;
    int tage;
    int zahlImStream;
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

    inputDatei.close(); // Datei schließen
    return 0;
}
