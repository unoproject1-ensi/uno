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
        friend class joueur;
    private:
        vector<carte> vjeter;
        vector<carte> vuno;
};
#endif // UNO_H
