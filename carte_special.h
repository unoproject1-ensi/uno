#include "carte.h"
#include <iostream>
#include <string>
using namespace std;
class carte_special:public carte
{
    public:
        carte_special(string coul,int val,string sym);
        virtual ~carte_special();
        void modifier_couleur(string coul);
        string donner_symbole();
    protected:
        string symbole;
};
