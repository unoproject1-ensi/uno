#include "carte_special.h"
#include <iostream>
#include <string>
using namespace std;
carte_special::carte_special(string coul,int val,string sym)
{
    couleur=coul;
    valeur=val;
    symbole=sym;
}
string carte_special::donner_symbole()
{
    return(symbole);
}
carte_special::~carte_special()
{
    //dtor
}
void carte_special::modifier_couleur(string coul)
{
    couleur=coul;
}
