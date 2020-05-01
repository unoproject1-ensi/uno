#include <iostream>
#include <algorithm>
#include <fstream>
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
    cout<<"     3) Jouer a deux contre la machine"<<endl<<endl<<endl;
    cout<<"     4) Jouer a trois"<<endl<<endl<<endl;
    cout<<"     5) Jouer a quatre"<<endl<<endl<<endl;
    do
    {
        cout<<"Choisissez une option : ";
        cin>>n;
    }
    while((n!=1)&&(n!=2)&&(n!=3)&&(n!=4)&&(n!=5));
    system("cls");
    UNO u;
    joueur j1,j2,j3,j4;
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
        else if(n==3)
        {
            nbr_de_parties++;
            j1.jouer_a_deux_contre_la_machine(u,j2,j3,j4,nbr_de_parties);
        }
        else if(n==4)
        {
            nbr_de_parties++;
            j1.jouer_a_trois(u,j2,j3,j4,nbr_de_parties);
        }
        else if(n==5)
        {
            nbr_de_parties++;
            j1.jouer_a_quatre(u,j2,j3,j4,nbr_de_parties);
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
    else if(n==2)
    {
        if(j1.calcule_score()<j2.calcule_score())
            cout<<"Le joueur 1 a gagne la partie"<<endl;
        else if(j1.calcule_score()>j2.calcule_score())
            cout<<"Le joueur 2 a gagne la partie"<<endl;
        else
            cout<<"La partie est nulle"<<endl;
    }
    else if(n==3)
    {
        int s1=j1.calcule_score();
        int s2=j2.calcule_score();
        int s3=j3.calcule_score();
        int s4=j4.calcule_score();
        int liste[]={s1,s2,s3,s4};
        if((*(max_element(liste,liste+4))==s1)||(*(max_element(liste,liste+4))==s3))
            cout<<"Votre equipe a gagne la partie"<<endl;
        if((*(max_element(liste,liste+4))==s2)||(*(max_element(liste,liste+4))==s4))
            cout<<"Votre equipe a perdue la partie"<<endl;
    }
    else if(n==4)
    {
        int s1=j1.calcule_score();
        int s2=j2.calcule_score();
        int s3=j3.calcule_score();
        int s4=j4.calcule_score();
        int liste[]={s1,s2,s3,s4};
        if((*(max_element(liste,liste+4))==s1)||(*(max_element(liste,liste+4))==s3))
            cout<<"L'equipe 1 a gagne la partie"<<endl;
        if((*(max_element(liste,liste+4))==s2)||(*(max_element(liste,liste+4))==s4))
            cout<<"L'equipe 2 a gagne la partie"<<endl;
    }
    else if(n==5)
    {
        int s1=j1.calcule_score();
        int s2=j2.calcule_score();
        int s3=j3.calcule_score();
        int s4=j4.calcule_score();
        int liste[]={s1,s2,s3,s4};
        if((*(max_element(liste,liste+4))==s1)||(*(max_element(liste,liste+4))==s3))
            cout<<"L'equipe 1 a gagne la partie"<<endl;
        if((*(max_element(liste,liste+4))==s2)||(*(max_element(liste,liste+4))==s4))
            cout<<"L'equipe 2 a gagne la partie"<<endl;
    }
    if ((n==1) || (n==2))
      remove("f2.text");
    else
      remove("f4.text");
    do
    {
        cout<<"Ecrivez quitter pour fermer le jeu"<<endl;
        cin>>ch;
    }
    while((ch!="quitter")&&(ch!="QUITTER"));
}
