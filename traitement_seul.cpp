#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <fstream>
#include "image_png.h"


using namespace std;



unsigned compteur_black(const ImagePNG &originale,unsigned i, unsigned j)//compte le nombre de pixels noires parmi les 8 voisins
{
  unsigned compteur_black=0;
        if (originale[i+1][j]!=PIXEL_WHITE)
        {
          compteur_black++;
        }
        if (originale[i][j+1]!=PIXEL_WHITE)
        {
          compteur_black++;
        }
        if (originale[i-1][j]!=PIXEL_WHITE)
        {
          compteur_black++;
        }
        if (originale[i][j-1]!=PIXEL_WHITE)
        {
          compteur_black++;
        }
        if (originale[i-1][j-1]!=PIXEL_WHITE)
        {
          compteur_black++;
        }
        if (originale[i+1][j-1]!=PIXEL_WHITE)
        {
          compteur_black++;
        }
        if (originale[i+1][j+1]!=PIXEL_WHITE)
        {
          compteur_black++;
        }
        if (originale[i-1][j+1]!=PIXEL_WHITE)
        {
          compteur_black++;
        }
        return compteur_black;
  }

  unsigned compteur_proche(ImagePNG &originale,unsigned i,unsigned j)//compte le nombre de pixels noire parmi les 4 voisins
  {
    unsigned compteur_black=0;
    if (originale[i+1][j]!=PIXEL_WHITE)
    {
      compteur_black++;
    }
    if (originale[i][j+1]!=PIXEL_WHITE)
    {
      compteur_black++;
    }
    if (originale[i-1][j]!=PIXEL_WHITE)
      {
    compteur_black++;
    }
    if (originale[i][j-1]!=PIXEL_WHITE)
    {
      compteur_black++;
    }
    return compteur_black;
  }

  void enlever(vector<unsigned> &last)
  {
    while(last[last.size()-1]!=0)
    {
      last.pop_back();
    }
  }


unsigned min_largeur( ImagePNG &originale)//xmin
{

   const unsigned height=originale.height();
   const unsigned width=originale.width();
   unsigned min(width);
   for (unsigned i=1;i<height-1;i++)
   {
      for (unsigned j=1;j<width-1;j++)
      {
         if (compteur_black(originale,i,j)>6)
         {
           if (min>j)
           {
             min=j;
           }
         }
      }
   }
   return min;
}


unsigned min_hauteur( ImagePNG &originale)//ymin
{

   const unsigned height=originale.height();
   const unsigned width=originale.width();
   unsigned min(height);
   for (unsigned i=1;i<height-1;i++)
   {
      for (unsigned j=1;j<width-1;j++)
      {
         if (compteur_black(originale,i,j)>6)
         {
           if (min>i)
           {
             min=i;
           }
         }
      }
   }
   return min;
}


unsigned max_largeur( ImagePNG &originale)//xmax
{

   const unsigned height=originale.height();
   const unsigned width=originale.width();
   unsigned max(0);

   for (unsigned i=height-2;i>1;i--)
   {
      for (unsigned j=width-2;j>1;j--)
      {
         if (compteur_black(originale,i,j)>6)
         {
           if(max<j)
           {
             max=j;
           }
         }
      }
   }
   return max;
}



unsigned max_hauteur(ImagePNG &originale)//ymax
{

   const unsigned height=originale.height();
   const unsigned width=originale.width();
   unsigned max(0);
   for (unsigned i=height-2;i>1;i--)
   {
      for (unsigned j=width-2;j>1;j--)
      {
         if (compteur_black(originale,i,j)>6)
         {
           if(max<i)
           {
             max=i;
           }
         }
      }
   }
   return max;
}



void binarise(ImagePNG &original)//binarise l'image
{

   ImagePNG copie=original;
   for (auto &ligne : copie)
   {
      for (auto &colonne : ligne)
      {
         unsigned short gris=(colonne.red()+colonne.blue()+colonne.green())/3;
         if (gris>230)
         {
           colonne=PIXEL_WHITE;
         }
         else
         {
           colonne=PIXEL_BLACK;
         }
      }
    }
    copie.save("binarise.png");
}



void filtre (ImagePNG &gg)//filtre moyenneur
{
  ImagePNG originale;
  originale=gg;
  int gris1,gris2,gris3,gris4,gris5,gris6,gris7,gris8,gris9,total;
  for (unsigned i=1;i<originale.height()-1;i++)
  {
    for (unsigned j=1;j<originale.width()-1;j++)
    {
      gris1=(originale[i+1][j].red()+originale[i+1][j].blue()+originale[i+1][j].green())/3;
      gris2=(originale[i-1][j].red()+originale[i-1][j].blue()+originale[i-1][j].green())/3;
      gris3=(originale[i][j-1].red()+originale[i][j-1].blue()+originale[i][j-1].green())/3;
      gris4=(originale[i][j+1].red()+originale[i][j+1].blue()+originale[i][j+1].green())/3;
      gris5=(originale[i-1][j-1].red()+originale[i-1][j-1].blue()+originale[i-1][j-1].green())/3;
      gris6=(originale[i+1][j-1].red()+originale[i+1][j-1].blue()+originale[i+1][j-1].green())/3;
      gris7=(originale[i+1][j+1].red()+originale[i+1][j+1].blue()+originale[i+1][j+1].green())/3;
      gris8=(originale[i-1][j+1].red()+originale[i-1][j+1].blue()+originale[i-1][j+1].green())/3;
      gris9=(originale[i][j].red()+originale[i][j].blue()+originale[i][j].green())/3;

      total=(gris1+gris2+gris3+gris4+gris5+gris6+gris7+gris8+gris9)/9;
      if (total<180)
      {
        gg[i][j]=PIXEL_BLACK;
      }
      else
      {
        gg[i][j]=PIXEL_WHITE;
      }
    }
  }
  gg.save("traitement.png");
}



void histo (ImagePNG &originale,vector<unsigned> &tab)//egalisation d'histogramme
{
  unsigned gris;
  for (unsigned i=0;i<originale.height();i++)
  {
    for (unsigned j=0;j<originale.width();j++)
    {
      gris=(originale[i][j].red()+originale[i][j].blue()+originale[i][j].green())/3;
      tab.push_back(gris);
    }
  }
}

void combien(const vector<unsigned> &tab, vector<unsigned> &last)//egalisation d'histogramme
{
  unsigned result;
  for (unsigned i=0;i<255;i++)
  {
    result=0;
    for(unsigned j=0;j<tab.size();j++)
    {
      if (tab[j]==i)
      {
        result++;
      }
    }
    last.push_back(result);
  }
}


int somme_en_cours (const vector<unsigned> &last, unsigned j)//egalisation d'histogramme
{
  int tmp(0);
  for (unsigned i=0;i<j;i++)
  {
    tmp+=last[i];
  }
  return tmp;
}


void appliquer2(ImagePNG &originale,const vector<unsigned> &last )//egalisation d'histogramme
{
  unsigned gris;
  double x(0);
  for(unsigned i=0;i<originale.height();i++)
  {
    for (unsigned j=0;j<originale.width();j++)
    {
      gris=(originale[i][j].red()+originale[i][j].blue()+originale[i][j].green())/3;
      x=254;//last.size()
      x=x/(originale.height()*originale.width());
      x=x*somme_en_cours(last,gris);
      originale[i][j]=x;
    }
  }
  originale.save("traitement.png");
}


void inverse(ImagePNG &originale)//inverse les couleurs
{
  unsigned gris(0);
  for (unsigned i=0;i<originale.height();i++)
  {
    for (unsigned j=0;j<originale.width();j++)
    {
      gris=(originale[i][j].red()+originale[i][j].blue()+originale[i][j].green())/3;
      originale[i][j]=abs(255-gris);
    }
  }
  originale.save("traitement.png");
}

void tri_a_bulle(int *t, int const size)//tri tableau
{
	bool en_desordre = true;
	for (int i = 0; i < size && en_desordre; ++i)
	{
		en_desordre = false;
		for (int j = 1; j < size - i; ++j)
			if (t[j-1] > t[j])
			{
				swap(t[j], t[j-1]);
				en_desordre = true;
 			}
	}
}

void filtre_median(ImagePNG &originale)//filtre median
{
  int tab[8];
  ImagePNG copie=originale;
  int gris1,gris2,gris3,gris4,gris5,gris6,gris7,gris8;
  for (unsigned i=1;i<originale.height()-1;i++)
  {
    for (unsigned j=1;j<originale.width()-1;j++)
    {

      gris1=(copie[i+1][j].red()+copie[i+1][j].blue()+copie[i+1][j].green())/3;
      gris2=(copie[i-1][j].red()+copie[i-1][j].blue()+copie[i-1][j].green())/3;
      gris3=(copie[i][j-1].red()+copie[i][j-1].blue()+copie[i][j-1].green())/3;
      gris4=(copie[i][j+1].red()+copie[i][j+1].blue()+copie[i][j+1].green())/3;
      gris5=(copie[i-1][j-1].red()+copie[i-1][j-1].blue()+copie[i-1][j-1].green())/3;
      gris6=(copie[i+1][j-1].red()+copie[i+1][j-1].blue()+copie[i+1][j-1].green())/3;
      gris7=(copie[i+1][j+1].red()+copie[i+1][j+1].blue()+copie[i+1][j+1].green())/3;
      gris8=(copie[i-1][j+1].red()+copie[i-1][j+1].blue()+copie[i-1][j+1].green())/3;

      tab[0]=gris1;
      tab[1]=gris2;
      tab[2]=gris3;
      tab[3]=gris4;
      tab[4]=gris5;
      tab[5]=gris6;
      tab[6]=gris7;
      tab[7]=gris8;
      tab[8]=(copie[i][j].red()+copie[i][j].blue()+copie[i][j].green())/3;
      tri_a_bulle(tab,8);

      if(tab[5]<120)
      {
        originale[i][j]=PIXEL_BLACK;
      }
      else
        originale[i][j]=PIXEL_WHITE;
    }
  }
  originale.save("traitement.png");
}


void high_pass(ImagePNG &originale)//calcul le filtre passe haut de l'image
{
  unsigned total(0);
  ImagePNG copie=originale;
  unsigned gris1,gris2,gris3,gris4,gris5,gris6,gris7,gris8,gris9;
  for (unsigned i=1;i<originale.height()-1;i++)
  {
    for (unsigned j=1;j<originale.width()-1;j++)
    {

      gris1=(originale[i-1][j-1].red()+originale[i-1][j-1].blue()+originale[i-1][j-1].green())/3;
      gris2=(originale[i][j-1].red()+originale[i][j-1].blue()+originale[i][j-1].green())/3;
      gris3=(originale[i+1][j-1].red()+originale[i+1][j-1].blue()+originale[i+1][j-1].green())/3;
      gris4=(originale[i-1][j+1].red()+originale[i-1][j+1].blue()+originale[i-1][j+1].green())/3;
      gris5=(originale[i][j+1].red()+originale[i][j+1].blue()+originale[i][j].green())/3;
      gris6=(originale[i+1][j+1].red()+originale[i+1][j+1].blue()+originale[i+1][j+1].green())/3;
      gris7=(originale[i-1][j].red()+originale[i-1][j].blue()+originale[i-1][j].green())/3;
      gris8=(originale[i+1][j].red()+originale[i+1][j].blue()+originale[i+1][j].green())/3;
      gris9=(originale[i][j].red()+originale[i][j].blue()+originale[i][j].green())/3;

      total=gris1*(0)+gris2*(-1/4)+gris3*(-1)+gris4*(0)+gris5*(-1/4)+gris6*(1)+gris7*(-1/4)+gris8*(-1/4)+gris9*(2);
      copie[i][j]=abs(total);
    }
  }
  copie.save("traitement.png");
}



void inverser(ImagePNG &originale)//inverse le sens de l'image
{
  ImagePNG copie=originale;
  for (unsigned i=1;i<originale.height()-1;i++)
  {
    for (unsigned j=1;j<originale.width()-1;j++)
    {
      originale[i][j]=copie[originale.height()-i][originale.width()-j];
    }
  }
  originale.save("traitement.png");
}



int main(int argc,char** argv) {
  (void) argc;
   string nom_image;
   nom_image=argv[1];
   string numero,numero2;
   numero=argv[2];
   ImagePNG img;
   img.load(nom_image);
   if (numero=="1")
   {
     vector<unsigned>tab;
     vector<unsigned> last;
     histo(img,tab);
     combien(tab,last);
     enlever(last);
     appliquer2(img,last);
   }
  if (numero=="2")
  {
    inverse(img);
  }
  if (numero=="3")
  {
    high_pass(img);
  }
  if (numero=="4")
  {
    inverser(img);
  }
  if (numero=="6")
  {
    binarise(img);
    img.load("binarise.png");
    filtre_median(img);
  }
  if (numero=="7")
  {
    binarise(img);
    img.load("binarise.png");
    filtre(img);
  }
  return 0;
}
