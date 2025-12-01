#include <iostream>
#include "Jeu.hpp"
#include "Fichiers.hpp"

namespace JeuDeLaVie {

JeuDeLaVie::JeuDeLaVie(std::string c, bool mc, int im) : chemin(c), mode_console(mc), iterations_max(im) {}

void JeuDeLaVie::simulation(){
    Fichiers fichier(chemin);

}

bool JeuDeLaVie::stabilite(){
    return true;
}
















}
