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
int carte::donner_valeur()
{
    return(valeur);
}
string carte::donner_couleur()
{
    return(couleur);
}
string carte::donner_symbole()
{
    return(symbole);
}
void carte::modifier_couleur(string coul)
{
    couleur=coul;
}
carte::~carte()
{
    //dtor
}
