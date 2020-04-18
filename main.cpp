#include <iostream>
using namespace std;
#include "carte.h"
#include "joueur.h"
#include "UNO.h"
int main()
{
    int n;
    cout<<"   Options"<<endl<<endl<<endl;
    cout<<"     1) Jouer contre la machine"<<endl<<endl<<endl;
    cout<<"     2) Jouer a deux"<<endl<<endl<<endl;
    do
    {
        cout<<"Choisissez une option : ";
        cin>>n;
    }
    while((n!=1)&&(n!=2));
    system("cls");
    UNO u;
    joueur j1,j2;
    string ch;
    int nbr_de_parties=0;
    do
    {
        if(n==1)
        {
            nbr_de_parties++;
            j1.jouer_contre_la_machine(u,j2,nbr_de_parties);
        }
        else if(n==2)
        {
            nbr_de_parties++;
            j1.jouer_a_deux(u,j2,nbr_de_parties);
        }
        if(nbr_de_parties>=2)
        {
            do
            {
                cout<<"Voulez-vous continuer a jouer ?"<<endl;
                cin>>ch;
            }
            while((ch!="oui")&&(ch!="OUI")&&(ch!="non")&&(ch!="NON"));
        }
    }
    while((((ch=="oui")||(ch=="OUI")))||(nbr_de_parties<2));
    if(n==1)
    {
        if(j1.calcule_score()<j2.calcule_score())
            cout<<"Vous avez gagner la partie"<<endl;
        else if(j1.calcule_score()>j2.calcule_score())
            cout<<"Vous avez perdu la partie"<<endl;
        else
            cout<<"La partie est nulle"<<endl;
    }
    else
    {
        if(j1.calcule_score()<j2.calcule_score())
            cout<<"Le joueur 1 a gagne la partie"<<endl;
        else if(j1.calcule_score()>j2.calcule_score())
            cout<<"Le joueur 2 a gagne la partie"<<endl;
        else
            cout<<"La partie est nulle"<<endl;
    }
    do
    {
        cout<<"Ecrivez quitter pour fermer le jeu"<<endl;
        cin>>ch;
    }
    while((ch!="quitter")&&(ch!="QUITTER"));
}
