#ifndef _IMAGE_PNG_H_
#define _IMAGE_PNG_H_

/* *
 * Rémi Vernay
 * 21 octobre 2012
 * 27 janvier 2016
 */

#include <vector>
#include <string>
#include <memory>

class ImagePNG;

class Pixel {
private:   
   unsigned short _red;
   unsigned short _blue;
   unsigned short _green;
   unsigned short _alpha;
   
public:
   Pixel(); // Nouveau pixel blanc
   Pixel(const unsigned short red, const unsigned short blue, const unsigned short green, const unsigned short alpha=255); // Nouveau pixel de couleur (opaque par defaut)
   Pixel(const unsigned short couleur, const unsigned short alpha=255); // Nouveau pixel avec red=blue=green et alpha (opaque par defaut)
   Pixel(const Pixel &autre); // Copie depuis un autre pixel
   
   Pixel& operator=(const Pixel &autre); // Affectation depuis un autre pixel
   
   friend bool operator==(const Pixel &gauche, const Pixel &droite); // Vrai si deux pixels sont de couleurs identiques (4 canaux identiques)
   friend bool operator!=(const Pixel &gauche, const Pixel &droite); // Vrai si deux pixels sont de couleurs differentes
   
   unsigned short red() const; // Valeur rouge du pixel entre 0 et 255
   unsigned short& red(); // Valeur rouge du pixel entre 0 et 255
   
   unsigned short blue() const; // Valeur bleue du pixel entre 0 et 255
   unsigned short& blue(); // Valeur bleue du pixel entre 0 et 255
   
   unsigned short green() const; // Valeur verte du pixel entre 0 et 255
   unsigned short& green(); // Valeur verte du pixel entre 0 et 255
   
   unsigned short alpha() const; // Transparence du pixel entre 0 et 255
   unsigned short& alpha(); // Transparence du pixel entre 0 et 255
};

const Pixel PIXEL_BLACK{0,0,0};
const Pixel PIXEL_WHITE{255,255,255};

const Pixel PIXEL_RED{255,0,0};
const Pixel PIXEL_BLUE{0,255,0};
const Pixel PIXEL_GREEN{0,0,255};

class ImagePNG {
private:
   std::unique_ptr<std::vector<std::vector<Pixel>>> pixels;
   void resize(const unsigned height, const unsigned width);
   
public:
   ImagePNG(); // Nouvelle image vide de taille nulle
   ImagePNG(const unsigned height, const unsigned width); // Nouvelle image blanche de taille (height x width)
   ImagePNG(const ImagePNG &autre); // Copie depuis une autre image
   ImagePNG(ImagePNG &&autre); // Déplacement depuis une autre image
   
   ImagePNG& operator=(const ImagePNG &autre); // Copie depuis une autre image
   ImagePNG& operator=(ImagePNG &&autre); // Déplacement depuis une autre image
   
   auto begin();
   auto begin() const;
   auto rbegin();
   auto rbegin() const;
   
   auto end();
   auto end() const;
   auto rend();
   auto rend() const;
   
   auto& operator[](const unsigned index);
   const auto& operator[](const unsigned index) const;
   
   unsigned height() const; // Hauteur de l'image
   unsigned width() const; // Largeur de l'image

   void load(const std::string &chemin); // Charge une image PNG
   void save(const std::string &chemin) const; // Enregistre une image PNG
};

auto ImagePNG::begin() { 
   return pixels->begin(); 
}

auto ImagePNG::begin() const { 
   return pixels->begin(); 
}

auto ImagePNG::rbegin() { 
   return pixels->rbegin(); 
}

auto ImagePNG::rbegin() const { 
   return pixels->rbegin(); 
}

auto ImagePNG::end() { 
   return pixels->end(); 
}

auto ImagePNG::end() const { 
   return pixels->end(); 
}

auto ImagePNG::rend() { 
   return pixels->rend(); 
}

auto ImagePNG::rend() const { 
   return pixels->rend(); 
}

auto& ImagePNG::operator[](const unsigned index) {
   return (*pixels)[index];
}
   
const auto& ImagePNG::operator[](const unsigned index) const {
   return (*pixels)[index];
}

#endif
