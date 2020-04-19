#include "UNO.h"
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
UNO::UNO()
{
    //ctor
}
carte UNO::derniere_carte()
{
    return(vjeter[vjeter.size()-1]);
}
void UNO::nouvelle_partie()
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
        for(int j=1;j<10;j++)
        {
            vuno.push_back(carte(tcoul[i],j,to_string(j)));
            vuno.push_back(carte(tcoul[i],j,to_string(j)));
        }
        for(int k=0;k<3;k++)
        {
            vuno.push_back(carte(tcoul[i],20,tsym[k]));
            vuno.push_back(carte(tcoul[i],20,tsym[k]));
        }
    }
    for(int i=0;i<4;i++)
    {
        vuno.push_back(carte("noir",50,"+4"));
        vuno.push_back(carte("noir",50,"joker"));
    }
}
void UNO::nouvelle_tour()
{
    carte c;
    c=vjeter[vjeter.size()-1];
    vjeter.erase(vjeter.begin()+vjeter.size()-1);
    vuno.swap(vjeter);
    for(int i=0;i<vuno.size();i++)
    {
        if((vuno[i].donner_symbole()=="joker")||(vuno[i].donner_symbole()=="+4"))
            vuno[i].modifier_couleur("noir");
    }
    vjeter.push_back(c);
}
UNO::~UNO()
{
    //dtor
}
