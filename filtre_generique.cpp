#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <fstream>
#include "image_png.h"


using namespace std;



void niveau_de_gris(const ImagePNG &original) { // remplace tous les pixels par des pixels bleus

   ImagePNG copie(original);

   for (auto &ligne : copie) {
      for (auto &pixel : ligne) {
         pixel=(pixel.red()+pixel.blue()+pixel.green())/3;
      }
   }

   copie.save("bb_gris.png");
}


unsigned compteur_black(const ImagePNG &originale,unsigned i, unsigned j)//Compte le nombre de noirs dans les 8 cases autour
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

  unsigned compteur_proche(ImagePNG &originale,unsigned i,unsigned j)//compte le nombre de pixels noirs dans les 4 cases autour (haut,bas,droite,gauche)
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



unsigned min_largeur( ImagePNG &originale)//calcule le xmin (cf rapport)
{ // remplace tous les pixels par des pixels blancs

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


unsigned min_hauteur( ImagePNG &originale)//calcule le ymin (cf rapport)
{ // remplace tous les pixels par des pixels blancs

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


unsigned max_largeur( ImagePNG &originale)//calcule le xmax (cf rapport)
{ // remplace tous les pixels par des pixels blancs

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



unsigned max_hauteur(ImagePNG &originale)//calcule le ymax (cf rapport)
{ // remplace tous les pixels par des pixels blancs

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







void binarise(ImagePNG &original, string numero)//binarise l'empreinte
{ // convertit l'image en niveaux de gris

   ImagePNG copie=original;
   for (auto &ligne : copie)
   {
      for (auto &colonne : ligne)
      {
         unsigned short gris=(colonne.red()+colonne.blue()+colonne.green())/3;
         if (gris>230)//nombre basé sur l'expérience et valeur la plus courante
         {
           colonne=PIXEL_WHITE;
         }
         else
         {
           colonne=PIXEL_BLACK;
         }
      }
    }
    copie.save("binarise"+numero+".png");
}



void filtre (ImagePNG &gg, string numero)//filtre moyenneur
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
  gg.save("filtre"+numero+".png");
}

void tri_a_bulle(int *t, int const size)//tri un vector
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

void filtre_median(ImagePNG &originale,string numero)//filtre median
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
  originale.save("filtre_median"+numero+".png");
}


bool premiere_conditions(const ImagePNG &originale, unsigned i, unsigned j)//premiere condition squelettisation
{
  int compteur(0);
  //ImagePNG copie=original;
  compteur=compteur_black(originale,i,j);
  if((compteur>=2)&&(compteur<=6))
  {
    return true;
  }
  else
    return false;
}

bool deuxieme_condition(const ImagePNG &copie, unsigned i, unsigned j)//deuxieme condition squelettisation
{
  int somme(0);
  //if ((i>1) && ((j>1) && ((i<copie.height()) && (j<copie.width()))))
  {

    if ((copie[i-1][j-1]==PIXEL_WHITE)&&(copie[i-1][j]==PIXEL_BLACK))
    {
      somme++;
    }

    if ((copie[i-1][j]==PIXEL_WHITE)&&(copie[i-1][j+1]==PIXEL_BLACK))
    {
      somme++;
    }
    if ((copie[i-1][j+1]==PIXEL_WHITE)&&(copie[i][j+1]==PIXEL_BLACK))
    {
      somme++;
    }
    if ((copie[i][j+1]==PIXEL_WHITE)&&(copie[i+1][j+1]==PIXEL_BLACK))
    {
      somme++;
    }
    if ((copie[i+1][j+1]==PIXEL_WHITE)&&(copie[i+1][j]==PIXEL_BLACK))
    {
      somme++;
    }
    if ((copie[i+1][j]==PIXEL_WHITE)&&(copie[i+1][j-1]==PIXEL_BLACK))
    {
      somme++;
    }
    if ((copie[i+1][j-1]==PIXEL_WHITE)&&(copie[i][j-1]==PIXEL_BLACK))
    {
      somme++;
    }

    if ((copie[i][j-1]==PIXEL_WHITE)&&(copie[i-1][j-1]==PIXEL_BLACK))
    {
      somme++;
    }

  }
  if (somme==1)
  {
    return true;
  }
  else
    return false;
}

bool troisieme_condition(const ImagePNG &copie,unsigned i,unsigned j)//troisieme condition squelettisation
{
  if (((copie[i-1][j]==PIXEL_WHITE)||(copie[i][j+1]==PIXEL_WHITE))||((copie[i+1][j]==PIXEL_WHITE)))
  {
    return true;
  }
  else
    return false;
}


bool quatrieme_condition(const ImagePNG &copie,unsigned i,unsigned j)//quatrieme condition squelettisation
{
  if (((copie[i-1][j]==PIXEL_WHITE)||(copie[i][j+1]==PIXEL_WHITE))||((copie[i][j-1]==PIXEL_WHITE)))
  {
    return true;
  }
  else
    return false;
}

bool cinquieme_condition(const ImagePNG &copie,unsigned i,unsigned j)//cinquieme condition squelettisation
{
  if (((copie[i][j+1]==PIXEL_WHITE)||(copie[i+1][j]==PIXEL_WHITE))||((copie[i][j-1]==PIXEL_WHITE)))
  {
    return true;
  }
  else
    return false;
}

bool sixieme_condition(const ImagePNG &copie,unsigned i,unsigned j)//sixieme condition squelettisation
{
  if (((copie[i-1][j]==PIXEL_WHITE)||(copie[i+1][j]==PIXEL_WHITE))||((copie[i][j-1]==PIXEL_WHITE)))
  {
    return true;
  }
  else
    return false;
}



void squelette( ImagePNG &copie, string numero)//applique toutes les conditions precedentes pour squelettiser
{

     const unsigned height=copie.height();
     const unsigned width=copie.width();

     for (unsigned i=1;i<height-1;i++)
     {
        for (unsigned j=1;j<width-1;j++)
        {
          if (copie[i][j]!=PIXEL_WHITE)
          {
            if ( (premiere_conditions(copie,i,j))&&(deuxieme_condition(copie,i,j)) && ((troisieme_condition(copie,i,j))||(quatrieme_condition(copie,i,j)))  && ((cinquieme_condition(copie,i,j))||(sixieme_condition(copie,i,j))))
            {
              copie[i][j]=PIXEL_WHITE;
            }
          }
        }
     }
     copie.save("squelette"+numero+".png");
}

//((premiere_conditions(copie,i,j))&&(deuxieme_condition(copie,i,j))&&((troisieme_condition(copie,i,j))&&(quatrieme_condition(copie,i,j))))



bool verif_not_bifurc(ImagePNG &originale,unsigned i, unsigned j)//verification pou la detection de terminaisons
{
  for (unsigned k=i-8;k<i+8;k++)
  {
    for (unsigned h=j-8;h<j+8;h++)
    {
      if (compteur_proche(originale,k,h)>=3)
      {
        return false;
      }
    }
  }
  return true;
}



void terminaison(ImagePNG &originale)//pas sur les bords (qu'au milieu)
{
  int somme(0);
  const unsigned height=originale.height();
  const unsigned width=originale.width();

  for (unsigned i=8;i<height-8;i++)
  {
     for (unsigned j=8;j<width-8;j++)
     {
       if (originale[i][j]==PIXEL_BLACK)
       {
         if ((compteur_proche(originale,i,j)==1)&&verif_not_bifurc(originale,i,j))
         {
           somme++;
           originale[i][j]=PIXEL_RED;
           (originale[i+1][j]=PIXEL_RED);
           (originale[i][j+1]=PIXEL_RED);
           (originale[i-1][j]=PIXEL_RED);
           (originale[i][j-1]=PIXEL_RED);
           (originale[i-1][j-1]=PIXEL_RED);
           (originale[i+1][j-1]=PIXEL_RED);
           (originale[i+1][j+1]=PIXEL_RED);
           (originale[i-1][j+1]=PIXEL_RED);
         }
       }
     }
  }
  originale.save("terminaison.png");
}





void bifurcation(ImagePNG &originale, string numero)//calcul des bifurcations
{
  const unsigned height=originale.height();
  const unsigned width=originale.width();
  int somme(0);

  for (unsigned i=1;i<height-1;i++)
  {
     for (unsigned j=1;j<width-1;j++)
     {
       if (originale[i][j]==PIXEL_BLACK)
       {
         if (compteur_proche(originale,i,j)==3)
         {
           originale[i][j]=PIXEL_BLUE;
           somme++;
           /*
           (originale[i+1][j]=PIXEL_BLUE);
           (originale[i][j+1]=PIXEL_BLUE);
           (originale[i-1][j]=PIXEL_BLUE);
           (originale[i][j-1]=PIXEL_BLUE);
           (originale[i-1][j-1]=PIXEL_BLUE);
           (originale[i+1][j-1]=PIXEL_BLUE);
           (originale[i+1][j+1]=PIXEL_BLUE);
           (originale[i-1][j+1]=PIXEL_BLUE);
           */
         }
       }
     }
  }
  originale.save("bifurcation"+numero+".png");
}


bool compteur_loin(ImagePNG &originale, unsigned i, unsigned j)//verfi pour l'élémination de bifurcations du au bruit
{
  for (unsigned k=i-5;k<i+5;k++)
  {
     for (unsigned f=j-5;f<j+5;f++)
     {
       if ((k!=i)&&(f!=j))
       {
         if (originale[k][f]==PIXEL_BLUE)
         {
           return false;
         }
       }
    }
  }
  return true;
}


void verif_minutie(ImagePNG &originale,string numero)//enleve le surplus de bifurc
{
  const unsigned height=originale.height();
  const unsigned width=originale.width();
  for (unsigned i=9;i<height-9;i++)
  {
     for (unsigned j=9;j<width-9;j++)
     {
       if (originale[i][j]==PIXEL_BLUE)
       {
         if (!compteur_loin(originale,i,j))
         {
           for (unsigned k=i-9;k<i+9;k++)
           {
              for (unsigned f=j-9;f<j+9;f++)
              {
                if (originale[k][f]==PIXEL_BLUE)
                {
                  originale[k][f]=PIXEL_BLACK;
                }
              }
            }
         }
       }
     }
   }
   originale.save("bifurcation2"+numero+".png");
}


void ecriture(ImagePNG &originale,float largeur, float hauteur, unsigned min_hauteur, unsigned min_largeur,unsigned max_largeur,unsigned max_hauteur,string numero)//ecris dans un fichier texte la signature de l'empreinte
{
  string nom,nom_complet;
  int compteur(0);
  nom="ratio"+numero;
  nom_complet="touch "+nom+".txt";
  system(nom_complet.c_str());
  ofstream fichier(nom+".txt");
  const unsigned height=originale.height();
  const unsigned width=originale.width();

  for (unsigned i=0;i<height;i++)
  {
     for (unsigned j=0;j<width;j++)
     {
       if ((originale[i][j]==PIXEL_BLUE))//+(originale[i][j]==PIXEL_RED))
       {
          compteur++;
          fichier<<round(((i-min_hauteur)/hauteur)*1000)/1000<<" "<<round(((j-min_largeur)/largeur)*1000)/1000<<" "<<round(((max_hauteur-i)/hauteur)*1000)/1000<<" "<<round(((max_largeur-j)/largeur)*1000)/1000<<endl;
       }
     }
   }
}


int main(int argc,char** argv) {

  (void) argc;
   string nom_image;
   nom_image=argv[1];//nom de l'image (adresse)
   string numero,numero2;
   numero=argv[2];//premiere ou seconde image a comparer (pour sauvegarder le ratio)
   numero2=argv[3];//le type de filtre voulu
   ImagePNG img;
   img.load(nom_image);

  float largeur;
  float hauteur;

  largeur=max_largeur(img)-min_largeur(img);
  hauteur=max_hauteur(img)-min_hauteur(img);
  unsigned minl,minh,maxl,maxh;
  minl=min_largeur(img);
  minh=min_hauteur(img);
  maxl=max_largeur(img);
  maxh=max_hauteur(img);


  //niveau_de_gris(img);
  binarise(img,numero);
  img.load("binarise"+numero+".png");


  if (numero2=="1")
  {
    filtre_median(img,numero);
    img.load("filtre_median"+numero+".png");
  }
  if (numero2=="2")
  {
    filtre(img,numero);
    img.load("filtre"+numero+".png");
  }


  squelette(img,numero);
  img.load("squelette"+numero+".png");

  bifurcation(img,numero);
  img.load("bifurcation"+numero+".png");

  verif_minutie(img,numero);
  img.load("bifurcation2"+numero+".png");

  ecriture(img,largeur,hauteur,minh,minl,maxl,maxh,numero);//2=bb
  return 0;
}
