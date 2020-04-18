#ifndef JOUEUR_H
#define JOUEUR_H
#include <iostream>
#include <vector>
using namespace std;
#include "carte.h"
#include "UNO.h"
class joueur
{
    public:
        joueur();
        virtual ~joueur();
        vector<carte> piocher(UNO& u,int nbr);
        bool jeter(UNO& u,int indice,joueur& j);
        void verif_uno(UNO u);
        int calcule_score();
        bool fin();
        int nbr_de_cartes();
        bool joueur_automatique(UNO& u,joueur& j);
        carte distribuer(UNO& u,joueur& j);
        bool bloque(UNO u);
        void affiche(UNO u,joueur j);
        void jouer_contre_la_machine(UNO& u,joueur& j,int n);
        void jouer_a_deux(UNO& u,joueur& j,int n);
        vector<int> chercher_couleur(string coul);
        vector<int> chercher_symbole(string sym);
    protected:
        int score;
        vector<carte> v;
};
#endif // JOUEUR_H
