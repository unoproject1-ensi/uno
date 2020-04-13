#include <iostream>
using namespace std;
#include <string>
class carte
{
    public:
        carte();
        carte(string coul,int val);
        virtual ~carte();
        int donner_valeur();
        string donner_couleur();
    protected:
        string couleur;
        int valeur;
};
