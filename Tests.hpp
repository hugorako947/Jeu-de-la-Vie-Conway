#pragma once
#include <string>

namespace JeuDeLaVie{
    class TestsUnitaires{
    private:
        std::string fichier_depart;
        std::string fichier_attendu;
        int iterations;
    public:
        TestsUnitaires(std::string fd, std::string fa, int i);

        bool estValide();
    };
    
}
