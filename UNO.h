#ifndef UNO_H
#define UNO_H
#include <vector>
#include "carte.h"
class UNO
{
    public:
        UNO();
        virtual ~UNO();
        void nouvelle_tour();
        void nouvelle_partie();
        carte derniere_carte();
        bool fin_de_cartes();
        friend class joueur;
        friend ostream& operator<<(ostream& s,UNO& u);
    protected:
        vector<carte> vjeter;
        vector<carte> vuno;
        
};
#endif // UNO_H
