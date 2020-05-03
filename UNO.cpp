#include "UNO.h"
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
UNO::UNO()
{
    
}
bool UNO::fin_de_cartes()
{
    if(vuno.size()==0)
        return(true);
    else
        return(false);
}
carte UNO::derniere_carte()//retourne la derniere carte jetée
{
    return(vjeter[vjeter.size()-1]);
}
void UNO::nouvelle_partie()//commencer une partie
{
    if(vuno.size()!=0)
        vuno.clear();
    if(vjeter.size()!=0)
        vjeter.clear();
    string tcoul[4]={"rouge","bleu","jaune","vert"};
    string tsym[4]={"+2","block","inverse"};
    for(int i=0;i<4;i++)
    {
        vuno.push_back(carte(tcoul[i],0,"0"));
        for(int j=1;j<10;j++)//création des cartes numérotées
        {
            vuno.push_back(carte(tcoul[i],j,to_string(j)));
            vuno.push_back(carte(tcoul[i],j,to_string(j)));
        }
        for(int k=0;k<3;k++)//création des cartes +2 , block et inverse
        {
            vuno.push_back(carte(tcoul[i],20,tsym[k]));
            vuno.push_back(carte(tcoul[i],20,tsym[k]));
        }
    }
    for(int i=0;i<4;i++)//création des cartes spéciales +4 et joker
    {
        vuno.push_back(carte("noir",50,"+4"));
        vuno.push_back(carte("noir",50,"joker"));
    }
}
void UNO::nouvelle_tour()
{
    carte c;
    c=vjeter[vjeter.size()-1];
    vjeter.erase(vjeter.begin()+vjeter.size()-1);//supprimer la dernière carte avant de transférer les cartes dans vuno
    vuno.swap(vjeter);//transférer les cartes de vjeter dans vuno
    for(int i=0;i<vuno.size();i++)//ramener les cartes à l'etat initial(avant la modification du couleur)
    {
        if((vuno[i].donner_symbole()=="joker")||(vuno[i].donner_symbole()=="+4"))
            vuno[i].modifier_couleur("noir");
    }
    vjeter.push_back(c);//remettre la dernière carte dans vjeter
}
ostream& operator<<(ostream& s,UNO& u)//surcharge de l'opérateur << va être utiliser dans l'enregistrement
{
    s<<u.vuno.size()<<" ";
    for(int i=0;i<u.vuno.size();i++)
    {
        s<<u.vuno[i].donner_couleur()<<" "<<u.vuno[i].donner_valeur()<<" "<<u.vuno[i].donner_symbole()<<" ";
    }
    s<<'\n';
    s<<u.vjeter.size()<<" ";
    for(int j=0;j<u.vjeter.size();j++)
    {
        s<<u.vjeter[j].donner_couleur()<<" "<<u.vjeter[j].donner_valeur()<<" "<<u.vjeter[j].donner_symbole()<<" ";
    }
    s<<'\n';
    return s;
}
UNO::~UNO()
{
    //dtor
}
