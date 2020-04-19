#include "joueur.h"
#include "UNO.h"
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <chrono>
joueur::joueur()
{
    score=0;
}
void joueur::jouer_contre_la_machine(UNO& u,joueur& j,int nbr)
{
    bool debut=true;
    int n;
    carte c;
    u.nouvelle_partie();
    c=distribuer(u,j);
    system("cls");
    while((nbr_de_cartes()!=0)&&(j.nbr_de_cartes()!=0))
    {
        string ch;
        bool t,t1,t2;
        vector<carte> v,v1;
        if(((c.donner_symbole()!="+4")&&(c.donner_symbole()!="+2")&&(c.donner_symbole()!="inverse")&&(c.donner_symbole()!="block"))||(debut==false))
            do
            {
                t2=j.joueur_automatique(u,*this);
                if(t2==true)
                    v1.push_back(u.derniere_carte());
                if(u.vuno.size()==0)
                    u.nouvelle_tour();
            }
            while((bloque(u)==true)&&(t2==true)&&(j.nbr_de_cartes()!=0));
        if(j.nbr_de_cartes()!=0)
        {
            do
            {
                t1=false;
                affiche(u,j);
                if(debut==true)
                    cout<<"La premiere carte joue est : ("<<c.donner_couleur()<<","<<c.donner_symbole()<<")"<<endl;
                if(v1.size()!=0)
                {
                    cout<<"Le joueur 2 a joue : ";
                    for(int i=0;i<v1.size();i++)
                        cout<<"("<<v1[i].donner_couleur()<<","<<v1[i].donner_symbole()<<")   ";
                    cout<<endl;
                    v1.clear();
                }
                else
                    cout<<"Le joueur 2 n'a joue aucune carte"<<endl;
                if((chercher_couleur(u.derniere_carte().donner_couleur()).size()==0)&&(chercher_symbole(u.derniere_carte().donner_symbole()).size()==0)&&(chercher_couleur("noir").size()==0))
                {
                    v=piocher(u,1);
                    cout<<"Vous avez piocher cette carte : ("<<v[v.size()-1].donner_couleur()<<","<<v[v.size()-1].donner_symbole()<<")"<<endl;
                    t=jeter(u,nbr_de_cartes(),j);
                    verif_uno(u);
                    t1=true;
                    do
                    {
                        cout<<"Ecrivez fin pour continuer a jouer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="fin")&&(ch!="FIN"));
                }
                else
                {
                    do
                    {
                        do
                        {
                            do
                            {
                                cout<<"Voulez-vous jeter ou piocher une carte :";
                                cin>>ch;
                            }
                            while((ch!="jeter")&&(ch!="piocher"));
                            if(ch=="jeter")
                            {
                                do
                                {
                                    cout<<"Donner un indice :";
                                    cin>>n;
                                }
                                while((n<1)||(n>nbr_de_cartes()));
                                t=jeter(u,n,j);
                                verif_uno(u);
                            }
                            else if(ch=="piocher")
                            {
                                v=piocher(u,1);
                                cout<<"Vous avez piocher cette carte : ("<<v[v.size()-1].donner_couleur()<<","<<v[v.size()-1].donner_symbole()<<")"<<endl;
                                t=jeter(u,nbr_de_cartes(),j);
                                verif_uno(u);
                                t1=true;
                                do
                                {
                                    cout<<"Ecrivez fin pour continuer a jouer"<<endl;
                                    cin>>ch;
                                }
                                while((ch!="fin")&&(ch!="FIN"));
                            }
                        }
                        while((t==false)&&(t1==false));
                    }
                    while((t==false)&&(t1==false));
                }
                if(u.vuno.size()==0)
                    u.nouvelle_tour();
                system("cls");
                debut=false;
            }
            while((j.bloque(u)==true)&&(t==true)&&(nbr_de_cartes()!=0));
        }
    }
    if(nbr_de_cartes()==0)
        cout<<"Vous etes gagnant"<<endl;
    if(j.nbr_de_cartes()==0)
        cout<<"Vous etes perdant"<<endl;
    cout<<"Votre score est : "<<calcule_score()<<endl;
    cout<<"Le score du joueur 2 est : "<<j.calcule_score()<<endl;
   if(nbr==1)
    {
        string ch;
        do
        {
            cout<<"Pour continuer le jeu ecrivez continuer"<<endl;
            cin>>ch;
        }
        while((ch!="continuer")&&(ch!="CONTINUER"));
    }
}
void joueur::jouer_a_deux(UNO& u,joueur& j,int nbr)
{
    bool debut=true;
    int n;
    carte c;
    bool t,t1=false,t2,t3;
    vector<carte> v1,v2;
    u.nouvelle_partie();
    c=distribuer(u,j);
    system("cls");
    while((nbr_de_cartes()!=0)&&(j.nbr_de_cartes()!=0))
    {
        string ch;
        vector<carte> v;
        cout<<"\t\t\t\t\tLe joueur 2 est en train de jouer"<<endl<<endl<<endl;
        t3=false;
        if(((c.donner_symbole()!="+4")&&(c.donner_symbole()!="+2")&&(c.donner_symbole()!="inverse")&&(c.donner_symbole()!="block"))||(debut==false))
        {
            do
            {
                j.affiche(u,*this);
                if(t1==true)
                    cout<<"Le joueur 1 a pioche une carte"<<endl;
                if(v1.size()!=0)
                {
                    cout<<"Le joueur 1 a joue : ";
                    for(int i=0;i<v1.size();i++)
                        cout<<"("<<v1[i].donner_couleur()<<","<<v1[i].donner_symbole()<<")   ";
                    cout<<endl;
                    v1.clear();
                }
                else if(debut==false)
                    cout<<"Le joueur 1 n'a joue aucune carte"<<endl;
                if((j.chercher_couleur(u.derniere_carte().donner_couleur()).size()==0)&&(j.chercher_symbole(u.derniere_carte().donner_symbole()).size()==0)&&(j.chercher_couleur("noir").size()==0))
                {
                    v=j.piocher(u,1);
                    cout<<"Vous avez piocher cette carte : ("<<v[v.size()-1].donner_couleur()<<","<<v[v.size()-1].donner_symbole()<<")"<<endl;
                    t2=j.jeter(u,j.nbr_de_cartes(),*this);
                    if(t2==true)
                        v2.push_back(u.derniere_carte());
                    j.verif_uno(u);
                    t3=true;
                    do
                    {
                        cout<<"Ecrivez fin pour continuer a jouer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="fin")&&(ch!="FIN"));
                }
                else
                {
                    do
                    {
                        do
                        {
                            do
                            {
                                cout<<"Voulez-vous jeter ou piocher une carte :";
                                cin>>ch;
                            }
                            while((ch!="jeter")&&(ch!="piocher")&&(ch!="JETER")&&(ch!="PIOCHER"));
                            if((ch=="jeter")||(ch=="JETER"))
                            {
                                do
                                {
                                    cout<<"Donner un indice :";
                                    cin>>n;
                                }
                                while((n<1)||(n>j.nbr_de_cartes()));
                                t2=j.jeter(u,n,*this);
                                if(t2==true)
                                    v2.push_back(u.derniere_carte());
                                j.verif_uno(u);
                            }
                            else if((ch=="piocher")||(ch=="PIOCHER"))
                            {
                                v=j.piocher(u,1);
                                cout<<"Vous avez piocher cette carte : ("<<v[v.size()-1].donner_couleur()<<","<<v[v.size()-1].donner_symbole()<<")"<<endl;
                                t2=j.jeter(u,j.nbr_de_cartes(),*this);
                                if(t2==true)
                                    v2.push_back(u.derniere_carte());
                                j.verif_uno(u);
                                t3=true;
                                do
                                {
                                    cout<<"Ecrivez fin pour continuer a jouer"<<endl;
                                    cin>>ch;
                                }
                                while((ch!="fin")&&(ch!="FIN"));
                            }
                        }
                        while((t2==false)&&(t3==false));
                    }
                    while((t2==false)&&(t3==false));
                }
                if(u.vuno.size()==0)
                    u.nouvelle_tour();
                system("cls");
            }
            while((bloque(u)==true)&&(t2==true)&&(j.nbr_de_cartes()!=0));
        }
        else
        {
            do
            {
                cout<<"Vous etes bloque"<<endl<<"Ecrire daccord pour continuer a jouer"<<endl;
                cin>>ch;
            }
            while((ch!="daccord")&&(ch!="DACCORD"));
            system("cls");
        }
        if(j.nbr_de_cartes()!=0)
        {
            do
            {
                cout<<"Vous etes pret ? "<<endl;
                cin>>ch;
            }
            while((ch!="oui")&&(ch!="OUI"));
            system("cls");
            cout<<"\t\t\t\t\tLe joueur 1 est en train de jouer"<<endl<<endl<<endl;
            do
            {
                t=false;
                t1=false;
                affiche(u,j);
                if(debut==true)
                    cout<<"La premiere carte joue est : ("<<c.donner_couleur()<<","<<c.donner_symbole()<<")"<<endl;
                if(t3==true)
                    cout<<"Le joueur 2 a pioche une carte"<<endl;
                if(v2.size()!=0)
                {
                    cout<<"Le joueur 2 a joue : ";
                    for(int i=0;i<v2.size();i++)
                        cout<<"("<<v2[i].donner_couleur()<<","<<v2[i].donner_symbole()<<")   ";
                    cout<<endl;
                    v2.clear();
                }
                else
                    cout<<"Le joueur 2 n'a joue aucune carte"<<endl;
                if((chercher_couleur(u.derniere_carte().donner_couleur()).size()==0)&&(chercher_symbole(u.derniere_carte().donner_symbole()).size()==0)&&(chercher_couleur("noir").size()==0))
                {
                    v=piocher(u,1);
                    cout<<"Vous avez piocher cette carte : ("<<v[v.size()-1].donner_couleur()<<","<<v[v.size()-1].donner_symbole()<<")"<<endl;
                    t=jeter(u,nbr_de_cartes(),j);
                    if(t==true)
                        v1.push_back(u.derniere_carte());
                    verif_uno(u);
                    t1=true;
                    do
                    {
                        cout<<"Ecrivez fin pour continuer a jouer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="fin")&&(ch!="FIN"));
                }
                else
                {
                    do
                    {
                        do
                        {
                            do
                            {
                                cout<<"Voulez-vous jeter ou piocher une carte :";
                                cin>>ch;
                            }
                            while((ch!="jeter")&&(ch!="piocher")&&(ch!="JETER")&&(ch!="PIOCHER"));
                            if((ch=="jeter")||(ch=="JETER"))
                            {
                                do
                                {
                                    cout<<"Donner un indice :";
                                    cin>>n;
                                }
                                while((n<1)||(n>nbr_de_cartes()));
                                t=jeter(u,n,j);
                                if(t==true)
                                    v1.push_back(u.derniere_carte());
                                verif_uno(u);
                            }
                            else if((ch=="piocher")||(ch=="PIOCHER"))
                            {
                                v=piocher(u,1);
                                cout<<"Vous avez piocher cette carte : ("<<v[v.size()-1].donner_couleur()<<","<<v[v.size()-1].donner_symbole()<<")"<<endl;
                                t=jeter(u,nbr_de_cartes(),j);
                                if(t==true)
                                    v1.push_back(u.derniere_carte());
                                verif_uno(u);
                                t1=true;
                                do
                                {
                                    cout<<"Ecrivez fin pour continuer a jouer"<<endl;
                                    cin>>ch;
                                }
                                while((ch!="fin")&&(ch!="FIN"));
                            }
                        }
                        while((t==false)&&(t1==false));
                    }
                    while((t==false)&&(t1==false));
                }
                if(u.vuno.size()==0)
                    u.nouvelle_tour();
                system("cls");
                debut=false;
            }
            while((j.bloque(u)==true)&&(t==true)&&(nbr_de_cartes()!=0));
            do
            {
                cout<<"Vous etes pret ? "<<endl;
                cin>>ch;
            }
            while((ch!="oui")&&(ch!="OUI"));
            system("cls");
        }
    }
    if(nbr_de_cartes()==0)
        cout<<"Le joueur 1 a gagne"<<endl;
    if(j.nbr_de_cartes()==0)
        cout<<"Le joueur 2 a gagne"<<endl;
    cout<<"Votre score est : "<<calcule_score()<<endl;
    cout<<"Le score du joueur 2 est : "<<j.calcule_score()<<endl;
    if(nbr==1)
    {
        string ch;
        do
        {
            cout<<"Pour continuer le jeu ecrivez continuer"<<endl;
            cin>>ch;
        }
        while((ch!="continuer")&&(ch!="CONTINUER"));
    }
}
void joueur::verif_uno(UNO u)
{
    char c;
    if(nbr_de_cartes()==1)
    {
        auto start=chrono::steady_clock::now();
        chrono::duration<double> d;
        do
        {
            cout<<"Crier uno"<<endl;
            cin>>c;
            auto end=chrono::steady_clock::now();
            d=end-start;
        }
        while((c!=toupper('u'))&&(c!='u')&&(d.count()<3));
        if(d.count()>3)
            piocher(u,2);
    }
}
bool joueur::bloque(UNO u)
{
    if((u.derniere_carte().donner_symbole()=="+4")||(u.derniere_carte().donner_symbole()=="+2")||(u.derniere_carte().donner_symbole()=="inverse")||(u.derniere_carte().donner_symbole()=="block"))
        return(true);
    else
        return(false);
}
int joueur::nbr_de_cartes()
{
    return(v.size());
}
void joueur::affiche(UNO u,joueur j)
{
    for(int i=0;i<j.v.size();i++)
        cout<<"(*,*)   ";
    cout<<endl<<endl<<endl<<endl;
    cout<<"\t\t\t\t\t("<<u.vjeter[u.vjeter.size()-1].donner_couleur()<<","<<u.vjeter[u.vjeter.size()-1].donner_symbole()<<")"<<endl<<endl<<endl<<endl;
    for(int i=0;i<v.size();i++)
        cout<<i+1<<": ("<<v[i].donner_couleur()<<","<<v[i].donner_symbole()<<")   ";
    cout<<endl<<endl<<endl<<endl;
}
carte joueur::distribuer(UNO& u,joueur& j)
{
    int r;
    carte c;
    if(v.size()!=0)
        v.clear();
    if(j.v.size()!=0)
        j.v.clear();
    j.piocher(u,7);
    piocher(u,7);
    srand(time(0));
    r=rand()%(u.vuno.size());
    u.vjeter.push_back(u.vuno[r]);
    c=u.vuno[r];
    u.vuno.erase(u.vuno.begin()+r-1);
    affiche(u,j);
    if(u.vjeter[u.vjeter.size()-1].donner_symbole()=="joker")
    {
        string coul;
        while((coul!="jaune")&&(coul!="JAUNE")&&(coul!="rouge")&&(coul!="ROUGE")&&(coul!="vert")&&(coul!="VERT")&&(coul!="bleu")&&(coul!="BLEU"))
        {
            cout<<"Donner le couleur a modifier : ";
            cin>>coul;
        }
        u.vjeter[u.vjeter.size()-1].modifier_couleur(coul);
    }
    else if(u.vjeter[u.vjeter.size()-1].donner_symbole()=="+4")
    {
        string coul;
        while((coul!="jaune")&&(coul!="JAUNE")&&(coul!="rouge")&&(coul!="ROUGE")&&(coul!="vert")&&(coul!="VERT")&&(coul!="bleu")&&(coul!="BLEU"))
        {
            cout<<"Donner le couleur a modifier : ";
            cin>>coul;
        }
        u.vjeter[u.vjeter.size()-1].modifier_couleur(coul);
        j.piocher(u,4);
    }
    else if(u.vjeter[u.vjeter.size()-1].donner_symbole()=="+2")
        j.piocher(u,2);
    return c;
}
vector<carte> joueur::piocher(UNO& u,int nbr)
{
    int r;
    vector<carte> vect;
    for(int i=0;i<nbr;i++)
    {
        srand(time(0));
        r=rand()%(u.vuno.size());
        v.push_back(u.vuno[r]);
        vect.push_back(u.vuno[r]);
        u.vuno.erase(u.vuno.begin()+r-1);
    }
    return vect;
}
vector<int> joueur::chercher_couleur(string coul)
{
    vector<int> vect;
    for(int i=0;i<v.size();i++)
        if(v[i].donner_couleur()==coul)
            vect.push_back(i+1);
    return vect;
}
vector<int> joueur::chercher_symbole(string sym)
{
    vector<int> vect;
    for(int i=0;i<v.size();i++)
        if(v[i].donner_symbole()==sym)
            vect.push_back(i+1);
    return vect;
}
bool joueur::jeter(UNO& u,int indice,joueur& j)
{
    bool test=false;
    int n=u.vjeter.size();
    if(v[indice-1].donner_symbole()=="joker")
    {
        string coul;
        while((coul!="jaune")&&(coul!="JAUNE")&&(coul!="rouge")&&(coul!="ROUGE")&&(coul!="vert")&&(coul!="VERT")&&(coul!="bleu")&&(coul!="BLEU"))
        {
            cout<<"Donner le couleur a modifier : ";
            cin>>coul;
        }
        u.vjeter.push_back(v[indice-1]);
        v.erase(v.begin()+indice-1);
        u.vjeter[n].modifier_couleur(coul);
        test=true;
    }
    else if(v[indice-1].donner_symbole()=="+4")
    {
        if((chercher_couleur(u.vjeter[n-1].donner_couleur()).size()==0)&&(chercher_symbole(u.vjeter[n-1].donner_symbole()).size()==0)&&(chercher_symbole("joker").size()==0))
        {
            string coul;
            while((coul!="jaune")&&(coul!="JAUNE")&&(coul!="rouge")&&(coul!="ROUGE")&&(coul!="vert")&&(coul!="VERT")&&(coul!="bleu")&&(coul!="BLEU"))
            {
                cout<<"Donner le couleur a modifier : ";
                cin>>coul;
            }
            u.vjeter.push_back(v[indice-1]);
            v.erase(v.begin()+indice-1);
            u.vjeter[n].modifier_couleur(coul);
            j.piocher(u,4);
            test=true;
        }
    }
    else if ((u.vjeter[n-1].donner_couleur()==v[indice-1].donner_couleur())||(u.vjeter[n-1].donner_symbole()==v[indice-1].donner_symbole()))
    {
        u.vjeter.push_back(v[indice-1]);
        v.erase(v.begin()+indice-1);
        test=true;
    }
    if((u.vjeter[u.vjeter.size()-1].donner_symbole()=="+2")&&(test==true))
        j.piocher(u,2);
    return test;
}
int joueur::calcule_score()
{
    for (int i=0;i<v.size();i++)
        score=score+v[i].donner_valeur();
    return score;
}
bool joueur::joueur_automatique(UNO& u,joueur& j)
{
    vector<int> vcoul=chercher_couleur(u.vjeter[u.vjeter.size()-1].donner_couleur());
    vector<int> vsym=chercher_symbole(u.vjeter[u.vjeter.size()-1].donner_symbole());
    bool test=false;
    int n=u.vjeter.size();
    if(vcoul.size()!=0)
        jeter(u,vcoul[rand()%(vcoul.size())],j);
    else if(vsym.size()!=0)
        jeter(u,vsym[rand()%(vsym.size())],j);
    else if(chercher_symbole("joker").size()!=0)
    {
        int indice=chercher_symbole("joker")[0];
        u.vjeter.push_back(v[indice-1]);
        v.erase(v.begin()+indice-1);
    }
    else if(chercher_symbole("+4").size()!=0)
    {
        int indice=chercher_symbole("+4")[0];
        u.vjeter.push_back(v[indice-1]);
        v.erase(v.begin()+indice-1);
    }
    else
    {
        piocher(u,1);
        cout<<"Le joueur 2 a pioche une carte"<<endl<<endl<<endl<<endl;
        if((v[v.size()-1].donner_couleur()==u.vjeter[u.vjeter.size()-1].donner_couleur())||(v[v.size()-1].donner_symbole()==u.vjeter[u.vjeter.size()-1].donner_symbole())||(v[v.size()-1].donner_couleur()=="noir"))
        {
            u.vjeter.push_back(v[v.size()-1]);
            v.erase(v.begin()+v.size()-1);
        }
    }
    if(u.vjeter.size()==n+1)
    {
        test=true;
        if((u.vjeter[u.vjeter.size()-1].donner_symbole()=="joker")||(u.vjeter[u.vjeter.size()-1].donner_symbole()=="+4"))
        {
            int a=chercher_couleur("rouge").size();
            int b=chercher_couleur("bleu").size();
            int c=chercher_couleur("jaune").size();
            int d=chercher_couleur("vert").size();
            int liste[]={a,b,c,d};
            if(*(max_element(liste,liste+4))==a)
                u.vjeter[u.vjeter.size()-1].modifier_couleur("rouge");
            if(*(max_element(liste,liste+4))==b)
                u.vjeter[u.vjeter.size()-1].modifier_couleur("bleu");
            if(*(max_element(liste,liste+4))==c)
                u.vjeter[u.vjeter.size()-1].modifier_couleur("jaune");
            if(*(max_element(liste,liste+4))==d)
                u.vjeter[u.vjeter.size()-1].modifier_couleur("vert");
        }
        if(u.vjeter[u.vjeter.size()-1].donner_symbole()=="+4")
            j.piocher(u,4);
    }
    return(test);
}
joueur::~joueur()
{
    //dtor
}
