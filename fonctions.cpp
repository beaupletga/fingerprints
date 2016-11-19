#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <cmath>
#include <fstream>
//#include <Python.h>

using namespace std;

typedef struct couple couple;

struct couple
{
  float a;
  float b;
  float c;
  float d;
};


void intro_dans_vector(vector<couple> &tab1,vector<couple> &tab2)//lis valeurs depuis un fichier texte et les injecte dans un vector grace au type 'couple'
{
  string tmp1,tmp2;
  ifstream fichier1("ratio1.txt", ios::in);  // on ouvre le fichier en lecture
  if(fichier1)  // si l'ouverture a réussi
  {
    while(!fichier1.eof())
    {
      couple tmp;
      fichier1>>tmp.a;
      fichier1>>tmp.b;
      fichier1>>tmp.c;
      fichier1>>tmp.d;

      tab1.push_back(tmp);
    }
  }
  else
  {
    cerr<<"Erreur : imposible d'ouvrir le fichier";
  }
  fichier1.close();

  ifstream fichier2("ratio2.txt", ios::in);  // on ouvre le fichier en lecture
  if(fichier2)  // si l'ouverture a réussi
  {
    while(!fichier2.eof())
    {
      couple tmp;
      fichier2>>tmp.a;
      fichier2>>tmp.b;
      fichier2>>tmp.c;
      fichier2>>tmp.d;
      tab2.push_back(tmp);
    }
  }
  else
  {
    cerr<<"Erreur : imposible d'ouvrir le fichier";
  }
  fichier2.close();
}

int comparaison(vector<couple> &tab1,vector<couple> &tab2)//premier modèle
{
  int somme(0);
  for (unsigned i=0;i<tab1.size();i++)
  {
    for(unsigned j=0;j<tab2.size();j++)
    {
      if (abs(tab1[i].a-tab2[j].a)<=0.008)
      {
        if (abs(tab1[i].b-tab2[j].b)<=0.008)
        {
          if (abs(tab1[i].c-tab2[j].c)<=0.008)
          {
            if (abs(tab1[i].d-tab2[j].d)<=0.008)
            {
              somme++;
            }
          }
        }
      }
    }
  }
  return somme;
}


int comparaison2(vector<couple> &tab1,vector<couple> &tab2)//deuxieme modèle
{
  int somme(0);
  for (unsigned i=0;i<tab1.size();i++)
  {
    for(unsigned j=0;j<tab2.size();j++)
    {
      if (((abs(tab1[i].a-tab2[j].a))+(abs(tab1[i].b-tab2[j].b))+(abs(tab1[i].c-tab2[j].c))+(abs(tab1[i].d-tab2[j].d)))<=0.025)
      {
        somme++;
      }
    }
  }
  return somme;
}

int main()
{
  vector<couple> tab1,tab2;
  intro_dans_vector(tab1,tab2);


  string command;
  command="touch resultat.txt";
  system(command.c_str());

  ofstream fichier("resultat.txt");

  fichier<<(comparaison(tab1,tab2)+comparaison2(tab1,tab2))/2<<endl;//moyenne des deux modeles

  fichier.close();

  return 0;
}
