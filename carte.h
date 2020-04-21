#ifndef CARTE_H
#define CARTE_H
#include <iostream>
using namespace std;
#include <string>
class carte
{
    public:
        carte();
        carte(string coul,int val,string sym);
        virtual ~carte();
        int donner_valeur();
        string donner_couleur();
        string donner_symbole();
        void modifier_couleur(string coul);
    private:
        string couleur;
        string symbole;
        int valeur;
};
#endif // CARTE_H
