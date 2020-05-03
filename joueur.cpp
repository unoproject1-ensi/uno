#include "joueur.h"
#include "UNO.h"
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <fstream>
joueur::joueur()
{
    score=0;
}
void joueur::jouer_contre_la_machine(UNO& u,joueur& j,int nbr)
{
    bool debut=true,t,t1=false,t3,reprendre=false;
    vector<bool> vb;
    int n,i;
    carte c;
    string ch;
    vector<carte> v1,v2;
    ifstream fich("f2.txt");
    if(fich.fail())// il n'y a pas une ancienne partie
    {
        u.nouvelle_partie();//on lance une nouvelle partie
        c=distribuer_a_deux(u,j);//Distribution
        i=1;
        enregistrer_partie_a_deux(u,j,1,1,nbr,v1,v2);//commencer l'enregistrement
    }
    else//en cas ou il y a une partie non terminée
    {
        vector<int> v3;
        v3=reprendre_partie_a_deux(u,j,v1,v2);
        if(v3[2]==1)//voir si la partie correspond à son choix d'option(option 1)

        {
            do//il a le choix de commencer une nouvelle partie ou reprendre la dernière
            {
                cout<<"voulez vous reprendre la partie oui/non"<<endl;
                cin>>ch;
            }
            while((ch!="oui")&&(ch!="non")&&(ch!="OUI")&&(ch!="NON"));
            system("cls");
            if((ch=="oui")||(ch=="OUI"))//reprendre la partie
            {
                i=v3[0];//le tour va commencer par le joueur ayant cet indice
                nbr=v3[1];//nombre de partie
                c=u.derniere_carte();
                reprendre=true;//indication de reprise
                enregistrer_partie_a_deux(u,j,i,1,nbr,v1,v2);//commencer l'enregistrement
            }
            else//commencer une nouvelle partie
            {
                remove("f2.txt");//effacer les anciennes données
                v1.clear();
                v2.clear();
                u.nouvelle_partie();//lancer une nouvelle partie
                c=distribuer_a_deux(u,j);
                i=1;
                enregistrer_partie_a_deux(u,j,1,1,nbr,v1,v2);//commencer l'enregistrement
            }
        }
        else//la partie enregistrée ne correspond pas à son choix d'option(option 1)
        {
            remove("f2.txt");//effacer les anciennes données
            v1.clear();
            v2.clear();
            u.nouvelle_partie();//lancer une nouvelle partie
            c=distribuer_a_deux(u,j);
            i=1;
            enregistrer_partie_a_deux(u,j,1,1,nbr,v1,v2);//commencer l'enregistrement
        }
    }
    if(reprendre==true)//cas de reprise debut prend false
       debut=false;
    system("cls");
    while((nbr_de_cartes()!=0)&&(j.nbr_de_cartes()!=0))//tant qu'aucun joueur n'a terminé ses cartes
    {
        vector<carte> v3;
        t3=false;
        int nb=0;
        if(((c.donner_symbole()!="+4")&&(c.donner_symbole()!="+2")&&(c.donner_symbole()!="inverse")&&(c.donner_symbole()!="block")&&(i==1))||((debut==false)&&(i==1)))
            do
            {
                vb=j.joueur_automatique(u,*this);
                if(vb[1]==true)//joueur automatique a pioché une
                    nb++;//nombre de cartes piochées
                if(vb[0]==true)//il a jeté une carte
                {
                    v2.push_back(u.derniere_carte());//on a utilisé vector car il peut jouer plusieurs fois à la file(cas du block inverse ou +4)ses cartes vont d'être afficher par la suite au joueur suivant.
                    if((bloque(u)==true)||(inverse(u)==true))//enregistrer le nouveau etat du jeu
                        enregistrer_partie_a_deux(u,j,1,1,nbr,v1,v2);
                    else
                        enregistrer_partie_a_deux(u,j,0,1,nbr,v1,v2);
                }
                else
                    enregistrer_partie_a_deux(u,j,0,1,nbr,v1,v2);
                if(u.fin_de_cartes()==true)//si les cartes à piochées sont terminées, on va remplir à nouveau vuno
                    u.nouvelle_tour();
            }
            while(((bloque(u)==true)||(inverse(u)==true))&&(vb[0]==true)&&(j.nbr_de_cartes()!=0));
        if(j.nbr_de_cartes()!=0)//ce n'est pas la peine de jouer si l'autre joueur a déjà fini ses cartes
        {
            do
            {
                t1=false;
                affiche(u,j);
                if(debut==true)//debut du  partie on affiche la 1ere carte
                    cout<<"La premiere carte joue est : ("<<c.donner_couleur()<<","<<c.donner_symbole()<<")"<<endl;
                if(nb==1)//nombre de cartes piochées par l'autre joueur vaut 1
                    cout<<"Le joueur 2 a pioche une carte"<<endl;
                else if(nb!=0)
                    cout<<"Le joueur 2 a pioche "<<nb<<" cartes"<<endl;
                nb=0;
                if(v2.size()!=0)//afficher les cartes jetées par le joueur concurrent
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
                {//il n'a aucune carte à jouer
                    v3=piocher(u,1);//il va pioché puisqu'il n'a aucune carte à jouer
                    cout<<"Vous avez piocher cette carte : ("<<v3[v3.size()-1].donner_couleur()<<","<<v3[v3.size()-1].donner_symbole()<<")"<<endl;
                    t=jeter(u,nbr_de_cartes(),j);
                    if(t==true)// il a jeté la carte piochée
                        if((bloque(u)==true)||(inverse(u)==true))//enregistrer le nouveau etat du jeu
                            enregistrer_partie_a_deux(u,j,0,1,nbr,v1,v2);
                        else
                            enregistrer_partie_a_deux(u,j,1,1,nbr,v1,v2);
                    else
                        enregistrer_partie_a_deux(u,j,1,1,nbr,v1,v2);
                    verif_uno(u);
                    t1=true;//il a pioché
                    do
                    {
                        cout<<"Ecrivez fin pour continuer a jouer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="fin")&&(ch!="FIN"));//ecrire fin pour terminer son tour et passer au joueur suivant
                }
                else//s'il a la possibilité de jouer
                {
                        do
                        {
                            do//il a toujours le choix de jeter ou de piocher une carte
                            {
                                cout<<"Voulez-vous jeter ou piocher une carte :";
                                cin>>ch;
                            }
                            while((ch!="jeter")&&(ch!="piocher"));
                            if(ch=="jeter")//s'il a choisi de jeter
                            {
                                do
                                {
                                    cout<<"Donner un indice :";
                                    cin>>n;
                                }
                                while((n<1)||(n>nbr_de_cartes()));//controle sur l'indice
                                t=jeter(u,n,j);//jeter la carte choisie
                                verif_uno(u);//verifier qu'il a tapper u ou U 
                            }
                            else if(ch=="piocher")//s'il a choisi de piocher
                            {
                                v3=piocher(u,1);//piocher une carte puis afficher celle-ci
                                cout<<"Vous avez piocher cette carte : ("<<v3[v3.size()-1].donner_couleur()<<","<<v3[v3.size()-1].donner_symbole()<<")"<<endl;
                                t=jeter(u,nbr_de_cartes(),j);
                                if(t==true)//il a jeté la carte piochée
                                    if((bloque(u)==true)||(inverse(u)==true))//enregistrer le nouveau etat du jeu
                                        enregistrer_partie_a_deux(u,j,0,1,nbr,v1,v2);
                                    else
                                        enregistrer_partie_a_deux(u,j,1,1,nbr,v1,v2);
                                else
                                    enregistrer_partie_a_deux(u,j,1,1,nbr,v1,v2);
                                verif_uno(u);
                                t1=true;//il a pioché
                                do
                                {
                                    cout<<"Ecrivez fin pour continuer a jouer"<<endl;
                                    cin>>ch;
                                }
                                while((ch!="fin")&&(ch!="FIN"));//ecrire fin pour terminer son tour et passer au joueur suivant
                            }
                        }
                        while((t==false)&&(t1==false));//répéter jusqu'à il jette ou pioche une carte 
                }
                if(t==true)
                    if((bloque(u)==true)||(inverse(u)==true))
                        enregistrer_partie_a_deux(u,j,0,1,nbr,v1,v2);
                    else
                        enregistrer_partie_a_deux(u,j,1,1,nbr,v1,v2);
                else
                    enregistrer_partie_a_deux(u,j,1,1,nbr,v1,v2);
                if(u.fin_de_cartes()==true)
                    u.nouvelle_tour();
                system("cls");
                debut=false;
            }
            while(((j.bloque(u)==true)||(j.inverse(u)==true))&&(t==true)&&(nbr_de_cartes()!=0));
        }
        i=1;
    }
    //afficher la resultat à la fin du partie
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
    system("cls");
}
void joueur::jouer_a_deux(UNO& u,joueur& j,int& nbr)
{
    bool debut=true,t,t1=false,t2,t3,reprendre=false;;
    int n,i;
    carte c;
    string ch;
    vector<carte> v1,v2;
    ifstream fich("f2.txt");
    if(fich.fail())// il n'y a pas une ancienne partie
    {
        u.nouvelle_partie();
        c=distribuer_a_deux(u,j);
        i=1;
        enregistrer_partie_a_deux(u,j,1,2,nbr,v1,v2);//commencer l'enregistrement
    }
    else//en cas ou il y a une partie non terminée
    {
        vector<int> v3;
        v3=reprendre_partie_a_deux(u,j,v1,v2);
        if(v3[2]==2)//voir si la partie correspond à son choix d'option(option 2)
        {
            do//il a le choix de commencer une nouvelle partie ou reprendre la dernière
            {
                cout<<"voulez vous reprendre la partie oui/non"<<endl;
                cin>>ch;
            }
            while((ch!="oui")&&(ch!="non")&&(ch!="OUI")&&(ch!="NON"));
            system("cls");
            if((ch=="oui")||(ch=="OUI"))//reprendre la partie
            {
                i=v3[0];//le joueur qui va jouer
                nbr=v3[1];//nombre de partie
                c=u.derniere_carte();
                reprendre=true;//indication de reprise
                enregistrer_partie_a_deux(u,j,i,2,nbr,v1,v2);//commencer l'enregistrement
            }
            else//commencer une nouvelle partie
            {
                remove("f2.txt");//effacer les anciennes données
                v1.clear();
                v2.clear();
                u.nouvelle_partie();//lancer une nouvelle partie
                c=distribuer_a_deux(u,j);
                i=1;
                enregistrer_partie_a_deux(u,j,1,2,nbr,v1,v2);//commencer l'enregistrement
            }
        }
        else//la partie enregistrée ne correspond pas à son choix d'option(option 1)
        {
            remove("f2.txt");//effacer les anciennes données
            v1.clear();
            v2.clear();
            u.nouvelle_partie();//lancer nouvelle partie
            c=distribuer_a_deux(u,j);
            i=1;
            enregistrer_partie_a_deux(u,j,1,2,nbr,v1,v2);//commencer l'enregistrement
        }
    }
    if(reprendre==true)
       debut=false;
    system("cls");
    while((nbr_de_cartes()!=0)&&(j.nbr_de_cartes()!=0))//aucun joueur n'a terminé ses cartes
    {
        vector<carte> v3;
        t3=false;
        if(((c.donner_symbole()!="+4")&&(c.donner_symbole()!="+2")&&(c.donner_symbole()!="inverse")&&(c.donner_symbole()!="block")&&(i==1))||((debut==false)&&(i==1)))
        {//si la 1ere carte n'est pas +4,+2,block ou inverse le 2eme joueur 
            cout<<"\t\t\t\t\tLe joueur 2 est en train de jouer"<<endl<<endl<<endl;
            do
            {
                cout<<"Vous etes pret ? "<<endl;
                cin>>ch;
            }
            while((ch!="oui")&&(ch!="OUI"));
            system("cls");
            do
            {
                cout<<"\t\t\t\t\tLe joueur 2 est en train de jouer"<<endl<<endl<<endl;
                j.affiche(u,*this);
                if(t1==true)
                    cout<<"Le joueur 1 a pioche une carte"<<endl;
                if(v1.size()!=0)
                {
                    cout<<"Le joueur 1 a joue : ";
                    for(int i=0;i<v1.size();i++)//afficher les cartes jetées par le joueur 1
                        cout<<"("<<v1[i].donner_couleur()<<","<<v1[i].donner_symbole()<<")   ";
                    cout<<endl;
                    v1.clear();
                }
                else if(debut==false)
                    cout<<"Le joueur 1 n'a joue aucune carte"<<endl;
                if((j.chercher_couleur(u.derniere_carte().donner_couleur()).size()==0)&&(j.chercher_symbole(u.derniere_carte().donner_symbole()).size()==0)&&(j.chercher_couleur("noir").size()==0))
                {//il n'a aucune carte jouable
                    v3=j.piocher(u,1);//il va pioché puisqu'il n'a aucune carte à jouer
                    cout<<"Vous avez piocher cette carte : ("<<v3[v3.size()-1].donner_couleur()<<","<<v3[v3.size()-1].donner_symbole()<<")"<<endl;
                    t2=j.jeter(u,j.nbr_de_cartes(),*this);
                    if(t2==true)// il a jeté la carte piochée
                    {
                        v2.push_back(u.derniere_carte());//ajouter la carte jetée dans v2
                        if((bloque(u)==true)||(inverse(u)==true))//enregistrer le nouveau etat du jeu
                            enregistrer_partie_a_deux(u,j,1,2,nbr,v1,v2);
                        else
                            enregistrer_partie_a_deux(u,j,0,2,nbr,v1,v2);
                    }
                    else
                        enregistrer_partie_a_deux(u,j,0,2,nbr,v1,v2);
                    j.verif_uno(u);//verifier qu'il a tapé u ou U
                    t3=true;//il a pioché une carte
                    do
                    {
                        cout<<"Ecrivez fin pour continuer a jouer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="fin")&&(ch!="FIN"));//ecrire fin pour terminer son tour et passer au joueur suivant
                }
                else//s'il a la possibilité de jouer
                {
                        do
                        {
                            do//il a toujours le choix de jeter ou de piocher une carte
                            {
                                cout<<"Voulez-vous jeter ou piocher une carte :";
                                cin>>ch;
                            }
                            while((ch!="jeter")&&(ch!="piocher")&&(ch!="JETER")&&(ch!="PIOCHER"));
                            if((ch=="jeter")||(ch=="JETER"))//il a choisi de jeter
                            {
                                do
                                {
                                    cout<<"Donner un indice :";
                                    cin>>n;
                                }
                                while((n<1)||(n>j.nbr_de_cartes()));//controle sur l'indice
                                t2=j.jeter(u,n,*this);
                                if(t2==true)//s'il a jeté
                                    v2.push_back(u.derniere_carte());//ajouter la carte jetée dans v2 
                                j.verif_uno(u);//verifier qu'il a tapé u
                            }
                            else if((ch=="piocher")||(ch=="PIOCHER"))//il a choisi de piocher
                            {
                                v3=j.piocher(u,1);//piocher une carte 
                                cout<<"Vous avez piocher cette carte : ("<<v3[v3.size()-1].donner_couleur()<<","<<v3[v3.size()-1].donner_symbole()<<")"<<endl;
                                t2=j.jeter(u,j.nbr_de_cartes(),*this);
                                if(t2==true)//s'il a jeté la carte
                                {
                                    v2.push_back(u.derniere_carte());//ajouter la carte jeté dans v2 
                                    if((bloque(u)==true)||(inverse(u)==true))//enregistrer l'etat du jeu
                                        enregistrer_partie_a_deux(u,j,1,2,nbr,v1,v2);
                                    else
                                        enregistrer_partie_a_deux(u,j,0,2,nbr,v1,v2);
                                }
                                else//il n'a pas jeté
                                    enregistrer_partie_a_deux(u,j,0,2,nbr,v1,v2);
                                j.verif_uno(u);
                                t3=true;//il a pioché
                                do
                                {
                                    cout<<"Ecrivez fin pour continuer a jouer"<<endl;
                                    cin>>ch;
                                }
                                while((ch!="fin")&&(ch!="FIN"));//ecrire fin pour terminer son tour et passer au joueur suivant
                            }
                        }
                        while((t2==false)&&(t3==false));//répéter jusqu'à il jette ou pioche une carte
                }
                if(t2==true)
                    if((bloque(u)==true)||(inverse(u)==true))
                        enregistrer_partie_a_deux(u,j,1,2,nbr,v1,v2);
                    else
                        enregistrer_partie_a_deux(u,j,0,2,nbr,v1,v2);
                else
                    enregistrer_partie_a_deux(u,j,0,2,nbr,v1,v2);
                if(u.fin_de_cartes()==true)
                    u.nouvelle_tour();
                system("cls");
            }
            while(((bloque(u)==true)||(inverse(u)==true))&&(t2==true)&&(j.nbr_de_cartes()!=0)); 
        }
        else if(((c.donner_symbole()=="+4")||(c.donner_symbole()=="+2")||(c.donner_symbole()=="inverse")||(c.donner_symbole()=="block"))&&(debut==true))
        {//si la 1ere carte est +4 ,+2 inverse ou block le joueur 2 est bloqué
            cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
            do
            {
                cout<<"Vous etes bloque"<<endl<<"Ecrire daccord pour continuer a jouer"<<endl;
                cin>>ch;
            }
            while((ch!="daccord")&&(ch!="DACCORD"));
            system("cls");
        }
        if(j.nbr_de_cartes()!=0)//ce n'est pas la peine de jouer si l'autre joueur a deja fini ses cartes
        {
            cout<<"\t\t\t\t\tLe joueur 1 est en train de jouer"<<endl<<endl<<endl;
            do
            {
                cout<<"Vous etes pret ? "<<endl;
                cin>>ch;
            }
            while((ch!="oui")&&(ch!="OUI"));
            system("cls");
            do
            {
                cout<<"\t\t\t\t\tLe joueur 1 est en train de jouer"<<endl<<endl<<endl;
                t=false;
                t1=false;
                affiche(u,j);
                if(debut==true)//afficher la 1ere carte
                    cout<<"La premiere carte joue est : ("<<c.donner_couleur()<<","<<c.donner_symbole()<<")"<<endl;
                if(t3==true)
                    cout<<"Le joueur 2 a pioche une carte"<<endl;
                if(v2.size()!=0)
                {
                    cout<<"Le joueur 2 a joue : ";
                    for(int i=0;i<v2.size();i++)//afficher les cartes jouées par le joueur 2
                        cout<<"("<<v2[i].donner_couleur()<<","<<v2[i].donner_symbole()<<")   ";
                    cout<<endl;
                    v2.clear();
                }
                else
                    cout<<"Le joueur 2 n'a joue aucune carte"<<endl;
                if((chercher_couleur(u.derniere_carte().donner_couleur()).size()==0)&&(chercher_symbole(u.derniere_carte().donner_symbole()).size()==0)&&(chercher_couleur("noir").size()==0))
                {
                    v3=piocher(u,1);//il va pioché puisque il n'a aucune carte à jouée
                    cout<<"Vous avez piocher cette carte : ("<<v3[v3.size()-1].donner_couleur()<<","<<v3[v3.size()-1].donner_symbole()<<")"<<endl;
                    t=jeter(u,nbr_de_cartes(),j);
                    if(t==true)//il a jetté une carte
                    {
                        //on a utilisé vector car il peut jouer plusieurs fois à la file(cas du bloc inverse ou +4  ces cartes vont d'être afficher par la suite au joueur suivant
                        v1.push_back(u.derniere_carte());
                        if((bloque(u)==true)||(inverse(u)==true))
                            enregistrer_partie_a_deux(u,j,0,2,nbr,v1,v2);
                        else
                            enregistrer_partie_a_deux(u,j,1,2,nbr,v1,v2);
                    }
                    else
                        enregistrer_partie_a_deux(u,j,1,2,nbr,v1,v2);
                    verif_uno(u);
                    t1=true;//il a pioché
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
                                v3=piocher(u,1);
                                cout<<"Vous avez piocher cette carte : ("<<v3[v3.size()-1].donner_couleur()<<","<<v3[v3.size()-1].donner_symbole()<<")"<<endl;
                                t=jeter(u,nbr_de_cartes(),j);
                                if(t==true)
                                {
                                    v1.push_back(u.derniere_carte());
                                    if((bloque(u)==true)||(inverse(u)==true))
                                        enregistrer_partie_a_deux(u,j,0,2,nbr,v1,v2);
                                    else
                                        enregistrer_partie_a_deux(u,j,1,2,nbr,v1,v2);
                                }
                                else
                                    enregistrer_partie_a_deux(u,j,1,2,nbr,v1,v2);
                                verif_uno(u);
                                t1=true;//il a pioché
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
                if(t==true)
                    if((bloque(u)==true)||(inverse(u)==true))
                        enregistrer_partie_a_deux(u,j,0,2,nbr,v1,v2);
                    else
                        enregistrer_partie_a_deux(u,j,1,2,nbr,v1,v2);
                else
                    enregistrer_partie_a_deux(u,j,1,2,nbr,v1,v2);
                if(u.fin_de_cartes()==true)
                    u.nouvelle_tour();
                system("cls");
                debut=false;
            }
            while(((j.bloque(u)==true)||(j.inverse(u)==true))&&(t==true)&&(nbr_de_cartes()!=0));
        }
        i=1;
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
    system("cls");
}
void joueur::jouer_a_deux_contre_la_machine(UNO& u,joueur& j1,joueur& j2,joueur& j3,int& nbr)
{
    bool debut=true,bloquee=false,inversee=false,reprendre=false,testb=false,testi=false,test=true,t=false;
    carte c;
    string ch;
    int i;
    vector<carte> v1;
    vector<bool> vb;
    ifstream fich("f4.txt");
    if(fich.fail())// il n'y a pas une ancienne partie
    {
        u.nouvelle_partie();
        c=distribuer_a_quatre(u,j1,j2,j3);
        i=1;
        enregistrer_partie_a_quatre(u,j1,j2,j3,0,bloque(u),inverse(u),inverse(u),nbr,3);
    }
    else//en cas ou il y a une partie non terminée
    {
        vector<int> v2;
        v2=reprendre_partie_a_quatre(u,j1,j2,j3);
        if(v2[5]==3)//voir si la partie correspond à son choix d'option(option 3)
        {
            do//il a le choix de commencer une nouvelle partie ou reprendre la dernière
            {
                cout<<"Vous voulez reprendre la partie oui/non"<<endl;
                cin>>ch;
            }
            while((ch!="oui")&&(ch!="non")&&(ch!="OUI")&&(ch!="NON"));
            system("cls");
            if((ch=="non")||(ch=="NON"))
            {
                remove("f4.txt");
                u.nouvelle_partie();
                c=distribuer_a_quatre(u,j1,j2,j3);
                i=1;
                enregistrer_partie_a_quatre(u,j1,j2,j3,0,bloque(u),inverse(u),inverse(u),nbr,3);
            }
            else
            {
                i=v2[0];
                testb=v2[1];
                testi=v2[2];
                test=v2[3];
                nbr=v2[4];
                c=u.derniere_carte();
                reprendre=true;
            }
        }
        else
        {
            remove("f4.txt");
            u.nouvelle_partie();
            c=distribuer_a_quatre(u,j1,j2,j3);
            i=1;
            enregistrer_partie_a_quatre(u,j1,j2,j3,0,bloque(u),inverse(u),inverse(u),nbr,3);
        }
    }
    system("cls");
    joueur* vj[4];
    vj[0]=this;
    vj[1]=&j1;
    vj[2]=&j2;
    vj[3]=&j3;
    inversee=inverse(u);
    bloquee=bloque(u);
    if(reprendre==true)
    {
        bloquee=testb;
        inversee=testi;
    }
    while((nbr_de_cartes()!=0)&&(j1.nbr_de_cartes()!=0)&&(j2.nbr_de_cartes()!=0)&&(j3.nbr_de_cartes()!=0))
    {
        string ch;
        if((debut==true)&&(!fich.fail())&&((ch=="oui")||(ch=="OUI")))
        {
            cout<<"La derniere carte joue est : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
            do
            {
                cout<<"Ecrivez daccord pour continuer"<<endl;
                cin>>ch;
            }
            while((ch!="daccord")&&(ch!="DACCORD"));
            system("cls");
        }
        else if(((debut==true)&&(!fich.fail())&&((ch=="non")||(ch=="NON")))||(debut==true))
        {
            cout<<"La premiere carte joue est : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
            do
            {
                cout<<"Ecrivez daccord pour continuer"<<endl;
                cin>>ch;
            }
            while((ch!="daccord")&&(ch!="DACCORD"));
            system("cls");
        }
        debut=false;
        while((inversee==false)&&(i<4)&&(nbr_de_cartes()!=0)&&(j1.nbr_de_cartes()!=0)&&(j2.nbr_de_cartes()!=0)&&(j3.nbr_de_cartes()!=0))
        {
            if(reprendre==true)
                i=(i+1)%4;
            if((bloquee==false))
            {
                if((i==0)||(i==2))
                {
                    cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                    int n=vj[i]->v.size();
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i-1,false,inversee,false,nbr,3);
                    v1=vj[i]->jouer(u,*vj[(i+1)%4],*vj[(i+2)%4],*vj[(i+3)%4],i,nbr,3);
                    if((bloque(u)==true)&&(v1.size()!=0))
                        bloquee=true;
                    if((v1.size()!=0)&&(inverse(u)==true))
                        inversee=true;
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i,bloquee,inversee,true,nbr,3);
                    if((vj[i]->v.size()==n)||(vj[i]->v.size()==n+1))
                        cout<<"Le joueur "<<i+1<<" a pioche une carte"<<endl;
                    if(v1.size()!=0)
                        cout<<"Le joueur "<<i+1<<" a joue cette carte : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
                    do
                    {
                        cout<<"Ecrivez daccord pour continuer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="daccord")&&(ch!="DACCORD"));
                    system("cls");
                    i++;
                }
                else
                {
                    cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i-1,false,inversee,false,nbr,3);
                    vb=vj[i]->joueur_automatique(u,*vj[(i+1)%4]);
                    if((bloque(u)==true)&&(vb[0]==true))
                        bloquee=true;
                    if((vb[0]==true)&&(inverse(u)==true))
                        inversee=true;
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i,bloquee,inversee,true,nbr,3);
                    if(vb[1]==true)
                        cout<<"Le joueur "<<i+1<<" a pioche une carte"<<endl;
                    if(vb[0]==true)
                        cout<<"Le joueur "<<i+1<<" a joue cette carte : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
                    do
                    {
                        cout<<"Ecrivez daccord pour continuer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="daccord")&&(ch!="DACCORD"));
                    system("cls");
                    i++;
                }
            }
            else
            {
                  if((i==0)||(i==2))
                  {
                      enregistrer_partie_a_quatre(u,j1,j2,j3,i,false,inversee,false,nbr,3);
                      cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                      do
                      {
                          cout<<"Vous etes bloque"<<endl<<"Ecrire daccord pour continuer a jouer"<<endl;
                          cin>>ch;
                      }
                      while((ch!="daccord")&&(ch!="DACCORD"));
                      bloquee=false;
                      system("cls");
                      cout<<"Le joueur "<<i+1<<" a etait bloque"<<endl;
                      do
                      {
                          cout<<"Ecrivez daccord pour continuer"<<endl;
                          cin>>ch;
                      }
                      while((ch!="daccord")&&(ch!="DACCORD"));
                      system("cls");
                      i++;
                  }
                  else
                  {
                       enregistrer_partie_a_quatre(u,j1,j2,j3,i,false,inversee,false,nbr,3);
                       cout<<"Le joueur "<<i+1<<" est bloquee"<<endl;
                       do
                       {
                           cout<<"Ecrivez daccord pour continuer"<<endl;
                           cin>>ch;
                       }
                       while((ch!="daccord")&&(ch!="DACCORD"));
                       bloquee=false;
                       system("cls");
                       i++;
                  }

            }
            if(i==4)
                i=0;
            reprendre=false;
            test=true;
        }
        if(reprendre==true)
            i=(i+1)%4;
        if(test==true)
            if(i<2)
                i=i+2;
            else
                i=i-2;
        reprendre=false;
        while((inversee==true)&&(i>=0)&&(nbr_de_cartes()!=0)&&(j1.nbr_de_cartes()!=0)&&(j2.nbr_de_cartes()!=0)&&(j3.nbr_de_cartes()!=0))
        {
            if((bloquee==false))
            {
                if((i==0)||(i==2))
                {
                    cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                    int n=vj[i]->v.size();
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i-1,false,inversee,false,nbr,3);
                    v1=vj[i]->jouer(u,*vj[(i+3)%4],*vj[(i+2)%4],*vj[(i+1)%4],i,nbr,3);
                    if((bloque(u)==true)&&(v1.size()!=0))
                        bloquee=true;
                    if((inverse(u)==true)&&(v1.size()!=0))
                        inversee=false;
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i,bloquee,inversee,true,nbr,3);
                    if((vj[i]->v.size()==n)||(vj[i]->v.size()==n+1))
                        cout<<"Le joueur "<<i+1<<" a pioche une carte"<<endl;
                    if(v1.size()!=0)
                        cout<<"Le joueur "<<i+1<<" a joue cette carte : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
                    do
                    {
                        cout<<"Ecrivez daccord pour continuer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="daccord")&&(ch!="DACCORD"));
                    system("cls");
                    i--;
                }

                else
                {
                    cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i-1,false,inversee,false,nbr,3);
                    vb=vj[i]->joueur_automatique(u,*vj[(i+3)%4]);
                    if((bloque(u)==true)&&(vb[0]==true))
                        bloquee=true;
                    if((inverse(u)==true)&&(vb[0]==true))
                        inversee=false;
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i,bloquee,inversee,true,nbr,3);
                    if(vb[1]==true)
                        cout<<"Le joueur "<<i+1<<" a pioche une carte"<<endl;
                    if(vb[0]==true)
                        cout<<"Le joueur "<<i+1<<" a joue cette carte : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
                    do
                    {
                        cout<<"Ecrivez daccord pour continuer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="daccord")&&(ch!="DACCORD"));
                    system("cls");
                    i--;
                }
            }
            else
            {
                if((i==0)||(i==2))
                {
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i,false,inversee,true,nbr,3);
                    do
                    {
                        cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                        cout<<"Vous etes bloque"<<endl<<"Ecrire daccord pour continuer a jouer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="daccord")&&(ch!="DACCORD"));
                    bloquee=false;
                    system("cls");
                    cout<<"Le joueur "<<i+1<<" a etait bloque"<<endl;
                    do
                    {
                        cout<<"Ecrivez daccord pour continuer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="daccord")&&(ch!="DACCORD"));
                    system("cls");
                    i--;
                }
                else
                {
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i,false,inversee,true,nbr,3);
                    cout<<"Le joueur "<<i+1<<" est bloquee"<<endl;
                    do
                    {
                        cout<<"Ecrivez daccord pour continuer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="daccord")&&(ch!="DACCORD"));
                    bloquee=false;
                    system("cls");
                    i--;
                }
            }
            if(i==-1)
                i=3;
            reprendre=false;
        }
        if(inversee==false)
            if(i>1)
                i=i-2;
            else
                i=i+2;
    }
    if((nbr_de_cartes()==0)||(j2.nbr_de_cartes()==0))
        cout<<"Votre equipe a gagne"<<endl;
    if((j1.nbr_de_cartes()==0)||(j3.nbr_de_cartes()==0))
        cout<<"Votre equipe a perdue"<<endl;
    cout<<"Le score du joueur 1 est : "<<calcule_score()<<endl;
    cout<<"Le score du joueur 2 est : "<<j1.calcule_score()<<endl;
    cout<<"Le score du joueur 3 est : "<<j2.calcule_score()<<endl;
    cout<<"Le score du joueur 4 est : "<<j3.calcule_score()<<endl;
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
void joueur::jouer_a_trois(UNO& u,joueur& j1,joueur& j2,joueur& j3,int& nbr)
{
    bool debut=true,bloquee=false,inversee=false,reprendre=false,testb=false,testi=false,test=true,t=false;
    carte c;
    string ch;
    int i;
    vector<carte> v1;
    vector<bool> vb;
    ifstream fich("f4.txt");
    if(fich.fail())// il n'y a pas une ancienne partie
    {
        u.nouvelle_partie();
        c=distribuer_a_quatre(u,j1,j2,j3);
        i=1;
        enregistrer_partie_a_quatre(u,j1,j2,j3,0,bloque(u),inverse(u),inverse(u),nbr,4);
    }
    else//en cas ou il y a une partie non terminée
    {
        vector<int> v2;
        v2=reprendre_partie_a_quatre(u,j1,j2,j3);
        if(v2[5]==4)//voir si la partie correspond à son choix d'option(option 4)
        {
            do//il a le choix de commencer une nouvelle partie ou reprendre la dernière
            {
                cout<<"Vous voulez reprendre la partie oui/non"<<endl;
                cin>>ch;
            }
            while((ch!="oui")&&(ch!="non")&&(ch!="OUI")&&(ch!="NON"));
            system("cls");
            if((ch=="non")||(ch=="NON"))
            {
                remove("f4.txt");
                u.nouvelle_partie();
                c=distribuer_a_quatre(u,j1,j2,j3);
                i=1;
                enregistrer_partie_a_quatre(u,j1,j2,j3,0,bloque(u),inverse(u),inverse(u),nbr,4);
            }
            else
            {
                i=v2[0];
                testb=v2[1];
                testi=v2[2];
                test=v2[3];
                nbr=v2[4];
                c=u.derniere_carte();
                reprendre=true;
            }
        }
        else
        {
            remove("f4.txt");
            u.nouvelle_partie();
            c=distribuer_a_quatre(u,j1,j2,j3);
            i=1;
            enregistrer_partie_a_quatre(u,j1,j2,j3,0,bloque(u),inverse(u),inverse(u),nbr,4);
        }
    }
    system("cls");
    joueur* vj[4];
    vj[0]=this;
    vj[1]=&j1;
    vj[2]=&j2;
    vj[3]=&j3;
    inversee=inverse(u);
    bloquee=bloque(u);
    if(reprendre==true)
    {
        bloquee=testb;
        inversee=testi;
    }
    while((nbr_de_cartes()!=0)&&(j1.nbr_de_cartes()!=0)&&(j2.nbr_de_cartes()!=0)&&(j3.nbr_de_cartes()!=0))
    {
        string ch;
        if((debut==true)&&(!fich.fail())&&((ch=="oui")||(ch=="OUI")))
        {
            cout<<"La derniere carte joue est : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
            do
            {
                cout<<"Ecrivez daccord pour continuer"<<endl;
                cin>>ch;
            }
            while((ch!="daccord")&&(ch!="DACCORD"));
            system("cls");
        }
        else if(((debut==true)&&(!fich.fail())&&((ch=="non")||(ch=="NON")))||(debut==true))
        {
            cout<<"La premiere carte joue est : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
            do
            {
                cout<<"Ecrivez daccord pour continuer"<<endl;
                cin>>ch;
            }
            while((ch!="daccord")&&(ch!="DACCORD"));
            system("cls");
        }
        debut=false;
        while((inversee==false)&&(i<4)&&(nbr_de_cartes()!=0)&&(j1.nbr_de_cartes()!=0)&&(j2.nbr_de_cartes()!=0)&&(j3.nbr_de_cartes()!=0))
        {
            if(reprendre==true)
                i=(i+1)%4;
            if((bloquee==false))
            {
                if((i==0)||(i==2)||(i==1))
                {
                    cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                    int n=vj[i]->v.size();
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i-1,false,inversee,false,nbr,4);
                    v1=vj[i]->jouer(u,*vj[(i+1)%4],*vj[(i+2)%4],*vj[(i+3)%4],i,nbr,3);
                    if((bloque(u)==true)&&(v1.size()!=0))
                        bloquee=true;
                    if((v1.size()!=0)&&(inverse(u)==true))
                        inversee=true;
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i,bloquee,inversee,true,nbr,4);
                    if((vj[i]->v.size()==n)||(vj[i]->v.size()==n+1))
                        cout<<"Le joueur "<<i+1<<" a pioche une carte"<<endl;
                    if(v1.size()!=0)
                        cout<<"Le joueur "<<i+1<<" a joue cette carte : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
                    do
                    {
                        cout<<"Ecrivez daccord pour continuer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="daccord")&&(ch!="DACCORD"));
                    system("cls");
                    i++;
                }
                else
                {
                    cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i-1,false,inversee,false,nbr,4);
                    vb=vj[i]->joueur_automatique(u,*vj[(i+1)%4]);
                    if((bloque(u)==true)&&(vb[0]==true))
                        bloquee=true;
                    if((vb[0]==true)&&(inverse(u)==true))
                        inversee=true;
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i,bloquee,inversee,true,nbr,4);
                    if(vb[1]==true)
                        cout<<"Le joueur "<<i+1<<" a pioche une carte"<<endl;
                    if(vb[0]==true)
                        cout<<"Le joueur "<<i+1<<" a joue cette carte : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
                    do
                    {
                        cout<<"Ecrivez daccord pour continuer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="daccord")&&(ch!="DACCORD"));
                    system("cls");
                    i++;
                }
            }
            else
            {
                  if((i==0)||(i==2)||(i==1))
                  {
                      enregistrer_partie_a_quatre(u,j1,j2,j3,i,false,inversee,false,nbr,4);
                      cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                      do
                      {
                          cout<<"Vous etes bloque"<<endl<<"Ecrire daccord pour continuer a jouer"<<endl;
                          cin>>ch;
                      }
                      while((ch!="daccord")&&(ch!="DACCORD"));
                      bloquee=false;
                      system("cls");
                      cout<<"Le joueur "<<i+1<<" a etait bloque"<<endl;
                      do
                      {
                          cout<<"Ecrivez daccord pour continuer"<<endl;
                          cin>>ch;
                      }
                      while((ch!="daccord")&&(ch!="DACCORD"));
                      system("cls");
                      i++;
                  }
                  else
                  {
                       enregistrer_partie_a_quatre(u,j1,j2,j3,i,false,inversee,false,nbr,4);
                       cout<<"Le joueur "<<i+1<<" est bloquee"<<endl;
                       do
                       {
                           cout<<"Ecrivez daccord pour continuer"<<endl;
                           cin>>ch;
                       }
                       while((ch!="daccord")&&(ch!="DACCORD"));
                       bloquee=false;
                       system("cls");
                       i++;
                  }

            }
            if(i==4)
                i=0;
            reprendre=false;
            test=true;
        }
        if(reprendre==true)
            i=(i+1)%4;
        if(test==true)
            if(i<2)
                i=i+2;
            else
                i=i-2;
        reprendre=false;
        while((inversee==true)&&(i>=0)&&(nbr_de_cartes()!=0)&&(j1.nbr_de_cartes()!=0)&&(j2.nbr_de_cartes()!=0)&&(j3.nbr_de_cartes()!=0))
        {
            if((bloquee==false))
            {
                if((i==0)||(i==2)||(i==1))
                {
                    cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                    int n=vj[i]->v.size();
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i-1,false,inversee,false,nbr,4);
                    v1=vj[i]->jouer(u,*vj[(i+3)%4],*vj[(i+2)%4],*vj[(i+1)%4],i,nbr,4);
                    if((bloque(u)==true)&&(v1.size()!=0))
                        bloquee=true;
                    if((inverse(u)==true)&&(v1.size()!=0))
                        inversee=false;
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i,bloquee,inversee,true,nbr,4);
                    if((vj[i]->v.size()==n)||(vj[i]->v.size()==n+1))
                        cout<<"Le joueur "<<i+1<<" a pioche une carte"<<endl;
                    if(v1.size()!=0)
                        cout<<"Le joueur "<<i+1<<" a joue cette carte : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
                    do
                    {
                        cout<<"Ecrivez daccord pour continuer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="daccord")&&(ch!="DACCORD"));
                    system("cls");
                    i--;
                }
                else
                {
                    cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i-1,false,inversee,false,nbr,4);
                    vb=vj[i]->joueur_automatique(u,*vj[(i+3)%4]);
                    if((bloque(u)==true)&&(vb[0]==true))
                        bloquee=true;
                    if((inverse(u)==true)&&(vb[0]==true))
                        inversee=false;
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i,bloquee,inversee,true,nbr,4);
                    if(vb[1]==true)
                        cout<<"Le joueur "<<i+1<<" a pioche une carte"<<endl;
                    if(vb[0]==true)
                        cout<<"Le joueur "<<i+1<<" a joue cette carte : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
                    do
                    {
                        cout<<"Ecrivez daccord pour continuer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="daccord")&&(ch!="DACCORD"));
                    system("cls");
                    i--;
                }
            }
            else
            {
                if((i==0)||(i==2)||(i==1))
                {
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i,false,inversee,true,nbr,4);
                    do
                    {
                        cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                        cout<<"Vous etes bloque"<<endl<<"Ecrire daccord pour continuer a jouer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="daccord")&&(ch!="DACCORD"));
                    bloquee=false;
                    system("cls");
                    cout<<"Le joueur "<<i+1<<" a etait bloque"<<endl;
                    do
                    {
                        cout<<"Ecrivez daccord pour continuer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="daccord")&&(ch!="DACCORD"));
                    system("cls");
                    i--;
                }
                else
                {
                    enregistrer_partie_a_quatre(u,j1,j2,j3,i,false,inversee,true,nbr,4);
                    cout<<"Le joueur "<<i+1<<" est bloquee"<<endl;
                    do
                    {
                        cout<<"Ecrivez daccord pour continuer"<<endl;
                        cin>>ch;
                    }
                    while((ch!="daccord")&&(ch!="DACCORD"));
                    bloquee=false;
                    system("cls");
                    i--;
                }
            }
            if(i==-1)
                i=3;
            reprendre=false;
        }
        if(inversee==false)
            if(i>1)
                i=i-2;
            else
                i=i+2;
    }
    if((nbr_de_cartes()==0)||(j2.nbr_de_cartes()==0))
        cout<<"L'equipe 1 a gagne"<<endl;
    if((j1.nbr_de_cartes()==0)||(j3.nbr_de_cartes()==0))
        cout<<"L'equipe 2 a gagne"<<endl;
    cout<<"le score du joueur 1 est : "<<calcule_score()<<endl;
    cout<<"Le score du joueur 2 est : "<<j1.calcule_score()<<endl;
    cout<<"Le score du joueur 3 est : "<<j2.calcule_score()<<endl;
    cout<<"Le score du joueur 4 est : "<<j3.calcule_score()<<endl;
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
void joueur::jouer_a_quatre(UNO& u,joueur& j1,joueur& j2,joueur& j3,int& nbr)
{
    bool debut=true,bloquee=false,inversee=false,reprendre=false,testb=false,testi=false,test=true;
    carte c;
    string ch;
    int i;
    vector<carte> v1;
    ifstream fich("f4.txt");
    if(fich.fail())// il n'y a pas une ancienne partie
    {
        u.nouvelle_partie();//lancer une nouvelle partie
        c=distribuer_a_quatre(u,j1,j2,j3);
        i=1;
        enregistrer_partie_a_quatre(u,j1,j2,j3,0,bloque(u),inverse(u),inverse(u),nbr,5);
    }
    else//en cas ou il y a une partie non terminée
    {
        vector<int> v2;
        v2=reprendre_partie_a_quatre(u,j1,j2,j3);
        if(v2[5]==5)//voir si la partie correspond à son choix d'option(option 5)
        {
            do//il a le choix de commencer une nouvelle partie ou reprendre la dernière
            {
                cout<<"Vous voulez reprendre la partie oui/non"<<endl;
                cin>>ch;
            }
            while((ch!="oui")&&(ch!="non")&&(ch!="OUI")&&(ch!="NON"));
            system("cls");
            if((ch=="non")||(ch=="NON"))//commencer une nouvelle partie
            {
                remove("f4.txt");//supprimer les données de l'ancienne partie
                u.nouvelle_partie();//lancer une nouvelle partie//lancer une nouvelle partie
                c=distribuer_a_quatre(u,j1,j2,j3);
                i=1;
                enregistrer_partie_a_quatre(u,j1,j2,j3,0,bloque(u),inverse(u),inverse(u),nbr,5);
            }
            else
            {
                i=v2[0];//la position du joueur
                testb=v2[1];//s'il etait boqué ou pas avant la pause(true or false)
                testi=v2[2];//si le tour etait dans le sens inverse (true or false)
                test=v2[3];//voir dans qu'elle boucle il a quitté
                nbr=v2[4];//nombre de partie pour non pas confondre la reprise du jeu par une nouvelle partie
                c=u.derniere_carte();
                reprendre=true;//indication de la reprise
            }
        }
        else// la partie enregistrée ne correspond pas à son choix d'option(option 5)
        {
            remove("f4.txt");//supprimer les données de l'ancienne partie
            u.nouvelle_partie();//lancer une nouvelle partie
            c=distribuer_a_quatre(u,j1,j2,j3);
            i=1;
            enregistrer_partie_a_quatre(u,j1,j2,j3,0,bloque(u),inverse(u),inverse(u),nbr,5);
        }
    }
    system("cls");
    joueur* vj[4];
    vj[0]=this;
    vj[1]=&j1;
    vj[2]=&j2;
    vj[3]=&j3;
    inversee=inverse(u);
    bloquee=bloque(u);
    if(reprendre==true)
    {//reprendre l'état du jeu avant de quitter
        bloquee=testb;
        inversee=testi;
    }
    while((nbr_de_cartes()!=0)&&(j1.nbr_de_cartes()!=0)&&(j2.nbr_de_cartes()!=0)&&(j3.nbr_de_cartes()!=0))
    {//si aucun de joueur n'a terminé ses cartes
        string ch;
        if((debut==true)&&(!fich.fail())&&((ch=="oui")||(ch=="OUI")))//affichage en cas de reprise
        {
            cout<<"La derniere carte joue est : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
            do
            {
                cout<<"Ecrivez daccord pour continuer"<<endl;
                cin>>ch;
            }
            while((ch!="daccord")&&(ch!="DACCORD"));
            system("cls");
        }
        else if(((debut==true)&&(!fich.fail())&&((ch=="non")||(ch=="NON")))||(debut==true))//affichage en cas d'une nouvelle partie
        {
            cout<<"La premiere carte joue est : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
            do
            {
                cout<<"Ecrivez daccord pour continuer"<<endl;
                cin>>ch;
            }
            while((ch!="daccord")&&(ch!="DACCORD"));
            system("cls");
        }
        debut=false;
        while((inversee==false)&&(i<4)&&(nbr_de_cartes()!=0)&&(j1.nbr_de_cartes()!=0)&&(j2.nbr_de_cartes()!=0)&&(j3.nbr_de_cartes()!=0))
        {//1ere cas le tour est dans le sens direct
            if(reprendre==true)
                i=(i+1)%4;//pour passer au joueur suivant aprés la reprise
            if((bloquee==false))//le joueur n'etait pas bloqué
            {
                cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                int n=vj[i]->v.size();//nombre des carte du joueur
                //on commence à enregistrer avant qu'il joue on cas ou il va quitter
                enregistrer_partie_a_quatre(u,j1,j2,j3,i-1,false,inversee,false,nbr,5);
                v1=vj[i]->jouer(u,*vj[(i+1)%4],*vj[(i+2)%4],*vj[(i+3)%4],i,nbr,4);
                if((bloque(u)==true)&&(v1.size()!=0))//changer l'état après le tour du joueur
                    bloquee=true;
                if((v1.size()!=0)&&(inverse(u)==true))//changer l'état du jeu après le tour du joueur
                    inversee=true;
                //sauvegarder les données aprés son tour
                enregistrer_partie_a_quatre(u,j1,j2,j3,i,bloquee,inversee,true,nbr,5);
                if((vj[i]->v.size()==n)||(vj[i]->v.size()==n+1))
                    cout<<"Le joueur "<<i+1<<" a pioche une carte"<<endl;
                if(v1.size()!=0)//v1 contient la carte jouée(jeté)
                    cout<<"Le joueur "<<i+1<<" a joue cette carte : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
                do
                {
                    cout<<"Ecrivez daccord pour continuer"<<endl;
                    cin>>ch;
                }
                while((ch!="daccord")&&(ch!="DACCORD"));
                system("cls");
                i++;// passer au joueur suivant
            }
            else//cas ou le joueur est bloqué
            {
                enregistrer_partie_a_quatre(u,j1,j2,j3,i,false,inversee,false,nbr,5);
                cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                do
                {
                    cout<<"Vous etes bloque"<<endl<<"Ecrire daccord pour continuer a jouer"<<endl;
                    cin>>ch;
                }
                while((ch!="daccord")&&(ch!="DACCORD"));
                bloquee=false;
                system("cls");
                cout<<"Le joueur "<<i+1<<" a etait bloque"<<endl;
                do
                {
                    cout<<"Ecrivez daccord pour continuer"<<endl;
                    cin>>ch;
                }
                while((ch!="daccord")&&(ch!="DACCORD"));
                system("cls");
                i++;//passer le tour au joueur suivant
            }
            if(i==4)
                i=0;//revenir au premier joueur
            reprendre=false;
            test=true;//il a terminé son tour
        }
        if(reprendre==true)//cad on a pas entré dans la boucle while precedente
            i=(i+1)%4;//pour passer au joueur suivant aprés la reprise
        if(test==true)
            if(i<2)
                i=i+2;
            else
                i=i-2;
        reprendre=false;
        while((inversee==true)&&(i>=0)&&(nbr_de_cartes()!=0)&&(j1.nbr_de_cartes()!=0)&&(j2.nbr_de_cartes()!=0)&&(j3.nbr_de_cartes()!=0))
        {//2eme cas le tour est dans le sens inverse
            if((bloquee==false))//le joueur n'est pas bloqué
            {
                cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                int n=vj[i]->v.size();
                enregistrer_partie_a_quatre(u,j1,j2,j3,i-1,false,inversee,false,nbr,5);
                v1=vj[i]->jouer(u,*vj[(i+3)%4],*vj[(i+2)%4],*vj[(i+1)%4],i,nbr,4);
                if((bloque(u)==true)&&(v1.size()!=0))//changer l'état après le tour du joueur
                    bloquee=true;
                if((inverse(u)==true)&&(v1.size()!=0))//changer l'état du jeu après le tour du joueur
                    inversee=false;
                enregistrer_partie_a_quatre(u,j1,j2,j3,i,bloquee,inversee,true,nbr,5);
                if((vj[i]->v.size()==n)||(vj[i]->v.size()==n+1))
                    cout<<"Le joueur "<<i+1<<" a pioche une carte"<<endl;
                if(v1.size()!=0)
                    cout<<"Le joueur "<<i+1<<" a joue cette carte : ("<<u.derniere_carte().donner_couleur()<<","<<u.derniere_carte().donner_symbole()<<")"<<endl;
                do
                {
                    cout<<"Ecrivez daccord pour continuer"<<endl;
                    cin>>ch;
                }
                while((ch!="daccord")&&(ch!="DACCORD"));
                system("cls");
                i--;
            }
            else//le joueur est bloqué
            {
                enregistrer_partie_a_quatre(u,j1,j2,j3,i,false,inversee,true,nbr,5);
                do
                {
                    cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
                    cout<<"Vous etes bloque"<<endl<<"Ecrire daccord pour continuer a jouer"<<endl;
                    cin>>ch;
                }
                while((ch!="daccord")&&(ch!="DACCORD"));
                bloquee=false;
                system("cls");
                cout<<"Le joueur "<<i+1<<" a etait bloque"<<endl;
                do
                {
                    cout<<"Ecrivez daccord pour continuer"<<endl;
                    cin>>ch;
                }
                while((ch!="daccord")&&(ch!="DACCORD"));
                system("cls");
                i--;
            }
            if(i==-1)
                i=3;
            reprendre=false;
        }
        if(inversee==false)
            if(i>1)
                i=i-2;
            else
                i=i+2;
    }
    //la resultat du partie
    if((nbr_de_cartes()==0)||(j2.nbr_de_cartes()==0))
        cout<<"L'equipe 1 a gagne"<<endl;
    if((j1.nbr_de_cartes()==0)||(j3.nbr_de_cartes()==0))
        cout<<"L'equipe 2 a gagne"<<endl;
    cout<<"le score du joueur 1 est : "<<calcule_score()<<endl;
    cout<<"Le score du joueur 2 est : "<<j1.calcule_score()<<endl;
    cout<<"Le score du joueur 3 est : "<<j2.calcule_score()<<endl;
    cout<<"Le score du joueur 4 est : "<<j3.calcule_score()<<endl;
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
void joueur::verif_uno(UNO& u)
{
    char c;
    if(nbr_de_cartes()==1)//si le nombre de carte de joueur égale 1
    {
        auto start=chrono::steady_clock::now();//déclencher le chronomètre
        chrono::duration<double> d;
        do
        {
            cout<<"Crier uno"<<endl;
            cin>>c;
            auto end=chrono::steady_clock::now();//arreter le chorno dés qu'il tape u ou U
            d=end-start;
        }
        while((c!=toupper('u'))&&(c!='u')&&(d.count()<3));
        if(d.count()>3)//s'il dépasse 3 secondes il va piocher deux cartes
            piocher(u,2);
    }
}
bool joueur::inverse(UNO u)//:indiquer si la dernière carte jetée est de type inverse ou non
{
    if(u.derniere_carte().donner_symbole()=="inverse")
        return(true);
    else
        return(false);
}
bool joueur::bloque(UNO u)//indique si la dernière carte jeté est de type block,+4 ou+2 puisque dans ces cas le joueur va passer son tour d'autre terme bloqué.
{
    if((u.derniere_carte().donner_symbole()=="+4")||(u.derniere_carte().donner_symbole()=="+2")||(u.derniere_carte().donner_symbole()=="block"))
        return(true);
    else
        return(false);
}
int joueur::nbr_de_cartes()//retourne le nombre de carte du joueur
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
void joueur::affiche(UNO u,joueur j1,joueur j2,joueur j3)
{
    int i=0,j=0,k=0;
    cout<<"      ";
    for(int i=0;i<j2.v.size();i++)
        cout<<"("<<j2.v[i].donner_couleur()<<","<<j2.v[i].donner_symbole()<<")   ";
    cout<<endl<<endl<<endl;
    while((i<j1.v.size())||(j<j3.v.size()))
    {
        if(j<j3.v.size())
            cout<<"(*,*)";
        j++;
        if((i+1==int((max(j1.v.size(),j3.v.size())/2)+1))||(j==int((max(j1.v.size(),j3.v.size())/2)+1))&&(k=0))
        {
            cout<<"\t\t\t\t\t\t\t("<<u.vjeter[u.vjeter.size()-1].donner_couleur()<<","<<u.vjeter[u.vjeter.size()-1].donner_symbole()<<")\t\t\t\t\t\t";
            k=1;
        }
        else
            cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
        if(i<j1.v.size())
        {
            if(j<=j3.v.size())
                if(j==j3.v.size())
                {
                    cout<<"   (*,*)";
                    j++;
                }
                else
                    cout<<"   (*,*)";
            else
                cout<<"           (*,*)";
        }
        i++;
        if(j3.v.size()>j1.v.size())
            cout<<endl;
    }
    cout<<endl<<endl<<endl;
    cout<<"      ";
    for(int i=0;i<v.size();i++)
        cout<<i+1<<": ("<<v[i].donner_couleur()<<","<<v[i].donner_symbole()<<")   ";
    cout<<endl<<endl<<endl<<endl;
}
carte joueur::distribuer_a_deux(UNO& u,joueur& j)
{
    int r;
    carte c;
    vector<carte> v1,v2;
    if(v.size()!=0)
        v.clear();
    if(j.v.size()!=0)
        j.v.clear();
    j.piocher(u,7);//distribuer 7 cartes à l'autre joueur
    piocher(u,7);//prend 7 cartes
    srand(time(0));
    r=rand()%(u.vuno.size());
    u.vjeter.push_back(u.vuno[r]);//jeter la 1ere carte
    c=u.vuno[r];
    u.vuno.erase(u.vuno.begin()+r);//supprimer cette carte du vuno (la pioche)
    cout<<"\t\t\t\t\tLe joueur 1 est en train de jouer"<<endl<<endl<<endl;
    affiche(u,j);
    if(u.vjeter[u.vjeter.size()-1].donner_symbole()=="joker")//si la premiere carte est joker, le 1ere joueur va choisir la couleur
    {
        string coul;
        while((coul!="jaune")&&(coul!="JAUNE")&&(coul!="rouge")&&(coul!="ROUGE")&&(coul!="vert")&&(coul!="VERT")&&(coul!="bleu")&&(coul!="BLEU"))
        {
            cout<<"Donner le couleur a modifier : ";
            cin>>coul;
        }
        u.vjeter[u.vjeter.size()-1].modifier_couleur(coul);//modifier la couleur du carte selon son choix
    }
    else if(u.vjeter[u.vjeter.size()-1].donner_symbole()=="+4")//si la premiere carte est +4 le, 1ere joueur va choisir la couleur
    {
        string coul;
        while((coul!="jaune")&&(coul!="JAUNE")&&(coul!="rouge")&&(coul!="ROUGE")&&(coul!="vert")&&(coul!="VERT")&&(coul!="bleu")&&(coul!="BLEU"))
        {
            cout<<"Donner le couleur a modifier : ";
            cin>>coul;
        }
        u.vjeter[u.vjeter.size()-1].modifier_couleur(coul);//modifier la couleur du carte
        j.piocher(u,4);//le joueur suivant pioche les quatre cartes
    }
    else if(u.vjeter[u.vjeter.size()-1].donner_symbole()=="+2")
        j.piocher(u,2);//le joueur suivant pioche deux cartes
    return c;
}
carte joueur::distribuer_a_quatre(UNO& u,joueur& j1,joueur& j2,joueur& j3)
{
    int r;
    carte c;
    if(v.size()!=0)
        v.clear();
    if(j1.v.size()!=0)
        j1.v.clear();
    if(j2.v.size()!=0)
        j2.v.clear();
    if(j3.v.size()!=0)
        j3.v.clear();
    j1.piocher(u,7);//distribuer à chaqune joueur 7 cartes
    j2.piocher(u,7);
    j3.piocher(u,7);
    piocher(u,7);//prend 7 cartes
    srand(time(0));
    r=rand()%(u.vuno.size());
    u.vjeter.push_back(u.vuno[r]);//jeter la 1ere carte
    c=u.vuno[r];
    u.vuno.erase(u.vuno.begin()+r);//supprimer la 1ere carte jetée
    cout<<"\t\t\t\t\tLe joueur 1 est en train de jouer"<<endl<<endl<<endl;
    affiche(u,j1,j2,j3);
    if(u.vjeter[u.vjeter.size()-1].donner_symbole()=="joker")//si la premiere carte est joker, le 1ere joueur va choisir la couleur
    {
        string coul;
        while((coul!="jaune")&&(coul!="JAUNE")&&(coul!="rouge")&&(coul!="ROUGE")&&(coul!="vert")&&(coul!="VERT")&&(coul!="bleu")&&(coul!="BLEU"))
        {
            cout<<"Donner le couleur a modifier : ";
            cin>>coul;
        }
        u.vjeter[u.vjeter.size()-1].modifier_couleur(coul);//modifier la carte selon la couleur choisie
    }
    else if(u.vjeter[u.vjeter.size()-1].donner_symbole()=="+4")//si la premiere carte est +4 ,le 1ere joueur va choisir la couleur
    {
        string coul;
        while((coul!="jaune")&&(coul!="JAUNE")&&(coul!="rouge")&&(coul!="ROUGE")&&(coul!="vert")&&(coul!="VERT")&&(coul!="bleu")&&(coul!="BLEU"))
        {
            cout<<"Donner le couleur a modifier : ";
            cin>>coul;
        }
        u.vjeter[u.vjeter.size()-1].modifier_couleur(coul);//modifier la carte selon la couleur choisie
        j1.piocher(u,4);//le joueur suivant pioche les quatre cartes
    }
    else if(u.vjeter[u.vjeter.size()-1].donner_symbole()=="+2")//si la 1ere carte +2 le joueur suivant pioche deux cartes
        j1.piocher(u,2);
    return c;//retourner la premiere carte jetée
}
vector<carte> joueur::piocher(UNO& u,int nbr)
{
    int r;
    vector<carte> vect;
    for(int i=0;i<nbr;i++)
    {
        srand(time(0));
        r=rand()%(u.vuno.size());
        v.push_back(u.vuno[r]);//piocher une carte d'une position aléatoire
        vect.push_back(u.vuno[r]);
        u.vuno.erase(u.vuno.begin()+r);//effacer cette cartes de l'ensemble des cartes à piochées(vuno)
    }
    return vect;//retourner un vecteur qui contient la carte piochée
}
vector<int> joueur::chercher_couleur(string coul)//retourne un vecteur qui contient les positions des cartes ayant le même couleur
{
    vector<int> vect;
    for(int i=0;i<v.size();i++)
        if(v[i].donner_couleur()==coul)
            vect.push_back(i+1);
    return vect;
}
vector<int> joueur::chercher_symbole(string sym)//retourne un vecteur qui contient les positions des cartes ayant le même symbole
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
    int n=u.vjeter.size();//taille de vjeteé (les cartes jetées)
    if(v[indice-1].donner_symbole()=="joker")//si la carte qu'il veut jeter, est joker le joueur choisit une couleur
    {
        string coul;
        while((coul!="jaune")&&(coul!="JAUNE")&&(coul!="rouge")&&(coul!="ROUGE")&&(coul!="vert")&&(coul!="VERT")&&(coul!="bleu")&&(coul!="BLEU"))
        {
            cout<<"Donner le couleur a modifier : ";
            cin>>coul;
        }
        u.vjeter.push_back(v[indice-1]);//ajouter cette carte avec les cartes jetées
        v.erase(v.begin()+indice-1);//supprimer cette carte de cartes de joueur(v)
        u.vjeter[n].modifier_couleur(coul);//modifier la couleur de carte
        test=true;//il a joué
    }
    else if(v[indice-1].donner_symbole()=="+4")//si la carte qu'il veut jeter, est +4
    {//il faut verifié qu'il n'a aucun choix(ni carte de meme couleur ni de méme symbole)
        if(((chercher_couleur(u.vjeter[n-1].donner_couleur()).size()==0)&&(chercher_symbole(u.vjeter[n-1].donner_symbole()).size()==0)&&(chercher_symbole("joker").size()==0))||((u.vjeter[n-1].donner_symbole()=="+4")&&(chercher_couleur(u.vjeter[n-1].donner_couleur()).size()==0)&&(chercher_symbole("joker").size()==0)))
        {
            string coul;
            while((coul!="jaune")&&(coul!="JAUNE")&&(coul!="rouge")&&(coul!="ROUGE")&&(coul!="vert")&&(coul!="VERT")&&(coul!="bleu")&&(coul!="BLEU"))
            {
                cout<<"Donner le couleur a modifier : ";//choisir une couleur
                cin>>coul;
            }
            u.vjeter.push_back(v[indice-1]);//ajouter cette carte avec les cartes jetées
            v.erase(v.begin()+indice-1);//supprimer cette carte de cartes de joueur(v)
            u.vjeter[n].modifier_couleur(coul);//modifier la couleur de carte
            j.piocher(u,4);//le joueur suivant pioche quatres cartes
            test=true;//il a joué
        }
    }
    else if ((u.vjeter[n-1].donner_couleur()==v[indice-1].donner_couleur())||(u.vjeter[n-1].donner_symbole()==v[indice-1].donner_symbole()))
    {//il a choisi une carte normale de meme couleur ou de meme symbole
        u.vjeter.push_back(v[indice-1]);//ajouter cette carte avec les cartes jetées
        v.erase(v.begin()+indice-1);//supprimer cette carte de cartes de joueur(v)
        test=true;//il a joué
    }
    if((u.vjeter[u.vjeter.size()-1].donner_symbole()=="+2")&&(test==true))
        j.piocher(u,2);//le joueur suivant pioche +2
    return test;
}
int joueur::calcule_score()
{
    for (int i=0;i<v.size();i++)
        score=score+v[i].donner_valeur();
    return score;
}
vector<bool> joueur::joueur_automatique(UNO& u,joueur& j)
{
    vector<int> vcoul=chercher_couleur(u.vjeter[u.vjeter.size()-1].donner_couleur());
    vector<int> vsym=chercher_symbole(u.vjeter[u.vjeter.size()-1].donner_symbole());
    vector<bool> v1;
    v1.push_back(false);//initialisation
    v1.push_back(false);//initialisation
    bool test=false;
    int n=u.vjeter.size();//nombre des cartes jetées
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
        v1[1]=true;//il a pioché
        if((v[v.size()-1].donner_couleur()==u.vjeter[u.vjeter.size()-1].donner_couleur())||(v[v.size()-1].donner_symbole()==u.vjeter[u.vjeter.size()-1].donner_symbole())||(v[v.size()-1].donner_couleur()=="noir"))
        {
            u.vjeter.push_back(v[v.size()-1]);
            v.erase(v.begin()+v.size()-1);
        }
    }
    if(u.vjeter.size()==n+1)//le nombre des cartes jetées a augmenté par 1 c-à-d il a joué
    {
        v1[0]=true;//il a jeté une carte
        if((u.vjeter[u.vjeter.size()-1].donner_symbole()=="joker")||(u.vjeter[u.vjeter.size()-1].donner_symbole()=="+4"))
        {   //si cette carte est joker ou +4 il va choisir la couleur
            //le choix de couleur va depondre du :
            int a=chercher_couleur("rouge").size();//nombres des cartes ayant la couleur rouge
            int b=chercher_couleur("bleu").size();//nombres des cartes ayant la couleur bleu
            int c=chercher_couleur("jaune").size();//nombres des cartes ayant la couleur jaune
            int d=chercher_couleur("vert").size();//nombres des cartes ayant la couleur vert
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
            j.piocher(u,4); //l'autre joueur pioche 4 cartes
    }
    return(v1);//retourne un vecteur qui contient deux paramètres indique s'il a pioché et s'il a jeté une carte
}
vector<carte> joueur::jouer(UNO& u,joueur& j1,joueur& j2,joueur& j3,int i,int nbr,int nm)//utiliser dans l'option 3 , 4 et 5
{
    string ch;
    int n;
    carte c=u.vjeter[0];
    bool t,t1=false,t2,t3;
    joueur* vj[4];
    vj[i]=this;
    vj[(i+1)%4]=&j1;
    vj[(i+2)%4]=&j2;
    vj[(i+3)%4]=&j3;
    vector<carte> v1,v2;
    do
    {
        cout<<"Vous etes pret ? "<<endl;
        cin>>ch;
    }
    while((ch!="oui")&&(ch!="OUI"));
    system("cls");
    cout<<"\t\t\t\t\tLe joueur "<<i+1<<" est en train de jouer"<<endl<<endl<<endl;
        t=false;
        t1=false;
        affiche(u,j1,j2,j3);
        if((chercher_couleur(u.derniere_carte().donner_couleur()).size()==0)&&(chercher_symbole(u.derniere_carte().donner_symbole()).size()==0)&&(chercher_couleur("noir").size()==0))
        {//il n'a aucune carte à jouer
            piocher(u,1);//il va pioché puisque il n'a aucune carte à jouer
            cout<<"Vous avez piocher cette carte : ("<<v[v.size()-1].donner_couleur()<<","<<v[v.size()-1].donner_symbole()<<")"<<endl;
            t=jeter(u,nbr_de_cartes(),j1);
            if(t==true)// il a jeté la carte piochée
            {
                v1.push_back(u.derniere_carte());
                vj[0]->enregistrer_partie_a_quatre(u,*vj[1],*vj[2],*vj[3],i,bloque(u),inverse(u),false,nbr,nm);
            }
            else//il n'a pas jeté la carte
                vj[0]->enregistrer_partie_a_quatre(u,*vj[1],*vj[2],*vj[3],i,false,false,false,nbr,nm);
            verif_uno(u);
            t1=true;//il a pioché
            do
            {
                cout<<"Ecrivez fin pour continuer a jouer"<<endl;
                cin>>ch;
            }
            while((ch!="fin")&&(ch!="FIN"));
        }
        else//s'il a la possibilité de jouer
        {
            do
            {
                do//il choisit de piocher ou jeter
                {
                    cout<<"Voulez-vous jeter ou piocher une carte :";
                    cin>>ch;
                }
                while((ch!="jeter")&&(ch!="piocher")&&(ch!="JETER")&&(ch!="PIOCHER"));
                if((ch=="jeter")||(ch=="JETER"))//s'il choisit de jeter
                {
                    do
                    {
                        cout<<"Donner un indice :";
                        cin>>n;
                    }
                    while((n<1)||(n>nbr_de_cartes()));
                    t=jeter(u,n,j1);
                    if(t==true)
                        v1.push_back(u.derniere_carte());
                    verif_uno(u);
                }
                else if((ch=="piocher")||(ch=="PIOCHER"))//s'il choisit de piocher
                {
                    piocher(u,1);
                    cout<<"Vous avez piocher cette carte : ("<<v[v.size()-1].donner_couleur()<<","<<v[v.size()-1].donner_symbole()<<")"<<endl;
                    t=jeter(u,nbr_de_cartes(),j1);
                    if(t==true)// il a jeté la carte piochée
                    {
                        v1.push_back(u.derniere_carte());
                        vj[0]->enregistrer_partie_a_quatre(u,*vj[1],*vj[2],*vj[3],i,bloque(u),inverse(u),false,nbr,nm);
                    }
                    else
                        vj[0]->enregistrer_partie_a_quatre(u,*vj[1],*vj[2],*vj[3],i,false,false,false,nbr,nm);
                    verif_uno(u);
                    t1=true;//il a pioché
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
        if(u.fin_de_cartes()==true)
            u.nouvelle_tour();
        system("cls");
    return(v1);//retourne les cartes jetées par le joueur
}
joueur::~joueur()
{
    //dtor
}
ostream& operator<<(ostream& s,joueur& j)//surcharge de l'operateur << pour l'enregistrement d'objet par la suite
{
    s<<j.score<<" "<<j.v.size()<<" ";
    for(int i=0;i<j.v.size();i++)
    {
        s<<j.v[i].donner_couleur()<<" "<<j.v[i].donner_valeur()<<" "<<j.v[i].donner_symbole()<<" ";
    }
    s<<'\n';
    return s;
}
vector<int> joueur::reprendre_partie_a_deux(UNO& u,joueur& j,vector<carte>& v1,vector<carte>& v2)
{
    ifstream fich("f2.txt",ios::in);
    int n,i,nbr,nm;
    string couleur;
    string symbole;
    int val;
    bool bloque,inverse;
    vector<int> v3;
    fich>>n;
    for(int i=0;i<n;i++)
    {
        fich>>couleur>>val>>symbole;
        carte c(couleur,val,symbole);
        v1.push_back(c);
    }
    fich>>n;
    for(int i=0;i<n;i++)
    {
        fich>>couleur>>val>>symbole;
        carte c(couleur,val,symbole);
        v2.push_back(c);
    }
    fich>>nbr;
    fich>>nm;
    fich>>i;
    fich>>n;
    for(int i=0;i<n;i++)
    {
        fich>>couleur>>val>>symbole;
        carte c(couleur,val,symbole);
        u.vuno.push_back(c);
    }
    fich>>n;
    for(int i=0;i<n;i++)
    {
        fich>>couleur>>val>>symbole;
        carte c(couleur,val,symbole);
        u.vjeter.push_back(c);
    }
    fich>>score;
    fich>>n;
    for(int i=0;i<n;i++)
    {
        fich>>couleur>>val>>symbole;
        carte c(couleur,val,symbole);
        v.push_back(c);
    }
    fich>>j.score;
    fich>>n;
    for(int i=0;i<n;i++)
    {
        fich>>couleur>>val>>symbole;
        carte c(couleur,val,symbole);
        j.v.push_back(c);
    }

    fich.close();
    v3.push_back(i);
    v3.push_back(nbr);
    v3.push_back(nm);
    return(v3);
}
vector<int> joueur::reprendre_partie_a_quatre(UNO& u,joueur& j1,joueur& j2,joueur& j3)
{
    ifstream fich("f4.txt",ios::in);
    int n,i,nbr,nm;
    vector<int> v1;
    bool bloque,inverse,test;
    string couleur;
    string symbole;
    int val;
    fich>>bloque;
    fich>>inverse;
    fich>>test;
    fich>>i;
    fich>>nbr;
    fich>>nm;
    fich>>n;
    for(int i=0;i<n;i++)
    {
        fich>>couleur>>val>>symbole;
        carte c(couleur,val,symbole);
        u.vuno.push_back(c);
    }
    fich>>n;
    for(int i=0;i<n;i++)
    {
        fich>>couleur>>val>>symbole;
        carte c(couleur,val,symbole);
        u.vjeter.push_back(c);
    }
    fich>>score;
    fich>>n;
    for(int i=0;i<n;i++)
    {
        fich>>couleur>>val>>symbole;
        carte c(couleur,val,symbole);
        v.push_back(c);
    }
    fich>>j1.score;
    fich>>n;
    for(int i=0;i<n;i++)
    {
        fich>>couleur>>val>>symbole;
        carte c(couleur,val,symbole);
        j1.v.push_back(c);
    }
    fich>>j2.score;
    fich>>n;
    for(int i=0;i<n;i++)
    {
        fich>>couleur>>val>>symbole;
        carte c(couleur,val,symbole);
        j2.v.push_back(c);
    }
    fich>>j3.score;
    fich>>n;
    for(int i=0;i<n;i++)
    {
        fich>>couleur>>val>>symbole;
        carte c(couleur,val,symbole);
        j3.v.push_back(c);
    }
    fich.close();
    v1.push_back(i);
    v1.push_back(bloque);
    v1.push_back(inverse);
    v1.push_back(test);
    v1.push_back(nbr);
    v1.push_back(nm);
    return(v1);
}
ostream& operator<<(ostream& s,vector<carte> v)
{
    s<<v.size()<<" ";
    for(int i=0;i<v.size();i++)
    {
        s<<v[i].donner_couleur()<<" "<<v[i].donner_valeur()<<" "<<v[i].donner_symbole()<<" ";
    }
    s<<'\n';
    return s;
}
void joueur::enregistrer_partie_a_deux(UNO u,joueur j,int i,int nbr,int n,vector<carte> v1,vector<carte> v2)
{
    ofstream fich("f2.txt",ios::binary);
    fich<<v1;
    fich<<v2;
    fich<<nbr;//nombre de partie
    fich<<" ";
    fich<<n;//numero de l'option
    fich<<" ";
    fich<<i;//indication sur le joueur qui va jouer
    fich<<" ";
    fich<<u;
    fich<<*this;
    fich<<j;
    fich.close();
}
void joueur::enregistrer_partie_a_quatre(UNO u,joueur j1,joueur j2,joueur j3,int i,bool bloquee,bool inversee,bool test,int nbr,int n)
{
    ofstream fich("f4.txt",ios::binary);
    fich<<bloquee;//dernier etat du jeu
    fich<<" ";
    fich<<inversee;//dernier etat du jeu
    fich<<" ";
    fich<<test;//dernier etat du jeu
    fich<<" ";
    fich<<i;//indication sur le joueur qui va jouer
    fich<<" ";
    fich<<nbr;//nombre de partie
    fich<<" ";
    fich<<n;//numero de l'option
    fich<<" ";
    fich<<u;
    fich<<*this;
    fich<<j1;
    fich<<j2;
    fich<<j3;
    fich.close();
}
