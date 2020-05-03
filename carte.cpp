#include "carte.h"
carte::carte()
{

}
carte::carte(string coul,int val,string sym)
{
    couleur=coul;
    valeur=val;
    symbole=sym;
}
int carte::donner_valeur()//retourne la valeur du carte
{
    return(valeur);
}
string carte::donner_couleur()//retourne la couleur du carte
{
    return(couleur);
}
string carte::donner_symbole()//retourne le symbole du carte
{
    return(symbole);
}
void carte::modifier_couleur(string coul)//modifier la couleur du carte
{
    couleur=coul;
}
carte::~carte()
{
    //dtor
}
