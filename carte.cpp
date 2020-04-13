#include "carte.h"
carte::carte()
{

}
carte::carte(string coul,int val)
{
    couleur=coul;
    valeur=val;
}
int carte::donner_valeur()
{
    return(valeur);
}
string carte::donner_couleur()
{
    return(couleur);
}
carte::~carte()
{
    //dtor
}
