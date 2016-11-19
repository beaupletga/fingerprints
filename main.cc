#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <fstream>
#include "image_png.h"


using namespace std;


unsigned compteur_black(const ImagePNG &originale,unsigned i, unsigned j)//compte le nombre de pixels noirs sur les huits cases voisines
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

  unsigned compteur_proche(ImagePNG &originale,unsigned i,unsigned j)//compte le nb de pixels noir sur les casee : du bas, gauche,droite,haut
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



unsigned min_largeur( ImagePNG &originale)//xmin (cf rapport)
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


unsigned min_hauteur( ImagePNG &originale)//ymin (cf rapport)
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


unsigned max_largeur( ImagePNG &originale)//xmax (cf rapport)
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



unsigned max_hauteur(ImagePNG &originale)//ymax (cf rapport)
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
         if (gris>230)//arbitraire mais baser sur bcp d'essais
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
  ImagePNG originale=gg;
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
  gg.save("filtre.png");
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


bool premiere_conditions(const ImagePNG &originale, unsigned i, unsigned j)//premiere condition de squelettisation
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

bool deuxieme_condition(const ImagePNG &copie, unsigned i, unsigned j)//seconde condition de squelettisation
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

bool troisieme_condition(const ImagePNG &copie,unsigned i,unsigned j)//troisieme condition de squelettisation
{
  if (((copie[i-1][j]==PIXEL_WHITE)||(copie[i][j+1]==PIXEL_WHITE))||((copie[i+1][j]==PIXEL_WHITE)))
  {
    return true;
  }
  else
    return false;
}


bool quatrieme_condition(const ImagePNG &copie,unsigned i,unsigned j)//quatrieme condition de squelettisation
{
  if (((copie[i-1][j]==PIXEL_WHITE)||(copie[i][j+1]==PIXEL_WHITE))||((copie[i][j-1]==PIXEL_WHITE)))
  {
    return true;
  }
  else
    return false;
}

bool cinquieme_condition(const ImagePNG &copie,unsigned i,unsigned j)//cinquieme condition de squelettisation
{
  if (((copie[i][j+1]==PIXEL_WHITE)||(copie[i+1][j]==PIXEL_WHITE))||((copie[i][j-1]==PIXEL_WHITE)))
  {
    return true;
  }
  else
    return false;
}

bool sixieme_condition(const ImagePNG &copie,unsigned i,unsigned j)//sixieme condition de squelettisation
{
  if (((copie[i-1][j]==PIXEL_WHITE)||(copie[i+1][j]==PIXEL_WHITE))||((copie[i][j-1]==PIXEL_WHITE)))
  {
    return true;
  }
  else
    return false;
}



void squelette( ImagePNG &copie, string numero)//squelettise l'empreinte avec les conditions ci-dessus
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


void bifurcation(ImagePNG &originale)//trouve les bifurcations sur l'image
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
         if (compteur_proche(originale,i,j)==3)//je sais pas pourquoi 5
         {
           originale[i][j]=PIXEL_BLUE;
           somme++;
         }
       }
     }
  }
  originale.save("bifurcation.png");
}


void verif_minutie(ImagePNG &originale,string numero)//enleve les mauvaises minuties
{
  const unsigned height=originale.height();
  const unsigned width=originale.width();
  for (unsigned i=9;i<height-9;i++)
  {
     for (unsigned j=9;j<width-9;j++)
     {
       if (originale[i][j]==PIXEL_BLUE)
       {
         {
           for (unsigned k=i-9;k<i+9;k++)
           {
              for (unsigned f=j-9;f<j+9;f++)
              {
                if (originale[k][f]==PIXEL_BLUE)
                {
                  if ((k!=i)+(f!=j)!=0)
                  {
                    originale[k][f]=PIXEL_BLACK;
                  }
                }
              }
            }
         }
       }
     }
   }
   originale.save("bifurcation"+numero+".png");
}


void affichage(ImagePNG &tmp,string numero)//affiche les bifurcations en bleu
{
  ImagePNG originale;
    originale=tmp;
  const unsigned height=originale.height();
  const unsigned width=originale.width();

  for (unsigned i=3;i<height-3;i++)
  {
     for (unsigned j=3;j<width-3;j++)
     {
       if (tmp[i][j]==PIXEL_BLUE)
       {
         for (unsigned k=i-3;k<i+3;k++)
         {
            for (unsigned f=j-3;f<j+3;f++)
            {
              originale[k][f]=PIXEL_BLUE;
            }
          }
       }
     }
   }
   originale.save("disp_bifurcation"+numero+".png");
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


int main(int argc,char** argv)
{
  (void) argc;

   string nom_image;
   nom_image=argv[1];
   string numero;
   numero=argv[2];
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

  binarise(img);
  img.load("binarise.png");

  filtre_median(img,numero);
  img.save("filtre_median"+numero+".png");

  squelette(img,numero);
  img.load("squelette"+numero+".png");

  bifurcation(img);
  img.load("bifurcation.png");

  verif_minutie(img,numero);
  img.load("bifurcation"+numero+".png");

  ecriture(img,largeur,hauteur,minh,minl,maxl,maxh,numero);//2=bb

  affichage(img,numero);
  img.load("disp_bifurcation"+numero+".png");

  return 0;
}
