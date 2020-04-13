#include <iostream>
#include <vector>
using namespace std;
#include "carte.h"
class joueur
{
    public:
        joueur();
        virtual ~joueur();
        void piocher(int nbr);
        bool jeter(int indice);
        bool crier_uno(char c);
        int calcule_score();
        bool fin();
        vector<int> chercher_couleur();
        vector<int> chercher_valeur();
        vector<int> chercher_symbole();
    protected:
        int score;
        vector<carte> v;
};
