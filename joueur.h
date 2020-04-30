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
        void verif_uno(UNO& u);
        int calcule_score();
        int nbr_de_cartes();
        vector<bool> joueur_automatique(UNO& u,joueur& j);
        carte distribuer_a_deux(UNO& u,joueur& j);
        carte distribuer_a_quatre(UNO& u,joueur& j1,joueur& j2,joueur& j3);
        bool bloque(UNO u);
        bool inverse(UNO u);
        void affiche(UNO u,joueur j);
        void affiche(UNO u,joueur j1,joueur j2,joueur j3);
        vector<carte> jouer(UNO& u,joueur& j1,joueur& j2,joueur& j3,int i,int nbr,int nm);
        void jouer_contre_la_machine(UNO& u,joueur& j,int n);
        void jouer_a_deux(UNO& u,joueur& j,int& nbr);
        void jouer_a_deux_contre_la_machine(UNO& u,joueur& j1,joueur& j2,joueur& j3,int& nbr);
        void jouer_a_trois(UNO& u,joueur& j1,joueur& j2,joueur& j3,int& nbr);
        void jouer_a_quatre(UNO& u,joueur& j1,joueur& j2,joueur& j3,int& nbr);
        vector<int> chercher_couleur(string coul);
        vector<int> chercher_symbole(string sym);
        vector<int> reprendre_partie_a_deux(UNO& u,joueur& j,vector<carte>& v1,vector<carte>& v2);
        vector<int> reprendre_partie_a_quatre(UNO& u,joueur& j1,joueur& j2,joueur& j3);
        void enregistrer_partie_a_deux(UNO u,joueur j,int i,int nbr,int n,vector<carte> v1,vector<carte> v2);
        void enregistrer_partie_a_quatre(UNO u,joueur j1,joueur j2,joueur j3,int i,bool bloquee,bool inversee,bool test,int nbr,int n);
        friend ostream& operator<<(ostream& s,joueur& j);
    protected:
        int score;
        vector<carte> v;
};
#endif // JOUEUR_H
