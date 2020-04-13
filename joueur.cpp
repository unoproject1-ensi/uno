#include "joueur.h"

joueur::joueur()
{
    score=0;
}
void joueur::piocher(int nbr)
{

}
vector<int> joueur::chercher_couleur()
{
    vector<int> vect;
    for(int i=0;i<v.size();i++)
        if(v[i].donner_couleur()==vjeter[vjeter.size()-1].donner_couleur())
            vect.push_back(i);
    return vect;
}
vector<int> joueur::chercher_valeur()
{
    vector<int> vect;
    for(int i=0;i<v.size();i++)
        if(v[i].donner_valeur()==vjeter[vjeter.size()-1].donner_valeur())
            vect.push_back(i);
    return vect;
}
vector<int> joueur::chercher_symbole()
{
    vector<int> vect;
    for(int i=0;i<v.size();i++)
        if(v[i].donner_valeur()==vjeter[vjeter.size()-1].donner_valeur())
            vect.push_back(i);
    return vect;
}
bool joueur::jeter(int indice)
{
    bool test=false;
    if (((vjeter[vjeter.size()-1].donner_couleur()==v[indice-1].donner_couleur())||(vjeter[vjeter.size()-1].donner_valeur()==v[indice-1].donner_valeur()))||(vjeter[vjeter.size()-1].donner_symbole()==v[indice-1].donner_symbole()))
    {
        vjeter.push_back(v[indice-1]);
        v.erase(v.begin()+indice-1);
        test=true;
    }
    if(v[indice-1].donner_symbole()=="+4")
        if((chercher_couleur().size()==0)&&(chercher_valeur().size()==0)&&(chercher_symbole().size()==0))
        {
            vjeter.push_back(v[indice-1]);
            v.erase(v.begin()+indice-1);
            test=true;
        }
}
bool joueur::crier_uno(char c)
{
    if((v.size()==1)&&(c==toupper('u')))
        return true;
}
int joueur::calcule_score()
{
    for (int i=0;i<v.size();i++)
        score=score+v[i].donner_valeur();
}
bool joueur::fin()
{
    if (v.size()==0)
        return true;
}
joueur::~joueur()
{
    //dtor
}
