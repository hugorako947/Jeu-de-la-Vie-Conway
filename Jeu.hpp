#pragma once
#include <iostream>
#include <vector>
#include <string>

class Jeu {
private:
    std::string chemin_input;
    bool mode_console;
    int iterations_max;
    double pause;
    std::vector<std::string> historique;
    std::string chemin_output;
    
public:
    Jeu(std::string ci, bool mc, int im, double p, std::string co);

    void simulation();

    bool stabilite(const std::string& etat_actuel);

    void tests_unitaires();
};
