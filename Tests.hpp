#pragma once
#include <string>

namespace JeuDeLaVie{
    class TestsUnitaires{
    private:
        std::string fichier_depart;
        std::string fichier_attendu;
        int iterations;
        static double total_tests;
        static double tests_valides;
    public:
        TestsUnitaires(std::string fd, std::string fa, int i);

        bool estValide();

        void resultat();

        double getTotalTests();

        double getTestsValides();
    };
    
}
