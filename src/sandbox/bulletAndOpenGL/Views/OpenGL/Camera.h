#ifndef DEF_CAMERA
#define DEF_CAMERA

//------------------------------------------------------------------------------
//-- Fichier    : Camera.h
//-- Auteur     : Da Campo Aurélien
//-- Date       : 10 decembre 2009
//-- Cours      : IGR, heig-vd, LABO 4
//-- But        : Classe de gestion d'une caméra libre et volante.
//              NB : cette caméra fonction en systeme d'axes américain :
//                Y = axe vertical
//------------------------------------------------------------------------------
#define GRAB_BUTTON 1
#define KEY_DOWN 1
#define KEY_UP 0

#define AVANCER 87
#define RECULER 83
#define DEPLACEMENT_GAUCHE 65
#define DEPLACEMENT_DROITE 68

//----------------
//-- INCLUSIONS --
//----------------
#include <QtOpenGL>
#include <math.h>
#include "geometrie.h"
#include <iostream>

class Camera
{
    public :

    //------------------
    //-- constructeur --
    //------------------
    Camera(GLfloat x, GLfloat y, GLfloat z,
           GLfloat cibleX, GLfloat cibleY, GLfloat cibleZ);

    //------------
    //-- outils --
    //------------
    /* initialiser les parametres de la camera */
    // -> faire une fois
    void initialiser(GLdouble fovy,
                     GLdouble aspect,
                     GLdouble zNear,
                     GLdouble zFar);

    /* ajouter a la scene, a chaque  */
    // -> a chaque display
    void adapterLaScene();

    //------------
    //-- regard --
    //------------
    /* tourner la camera */
    void tourner(GLfloat angle);

    /* regarder en haut ou en bas */
    void leverBaisser(GLfloat angle);

    /* souris qui clique */
    void sourisBoutons(int bouton, int etat,int x,int y);

    /* souris qui bouge */
    bool sourisBouge(int x,int y);

    //----------------
    //-- mouvements --
    //----------------
    /* avancer */
    void avancer(GLfloat distance);

    /* deplacer de cote */
    void deplacerLateralement(GLfloat distance);

    /* clavier */
    void evenementTouchePressee(unsigned int touche);
    void evenementToucheLevee(unsigned int touche);

    /* calculer la nouvelle position */
    // -> tous les x milisecondes
    void bouger(long timeElapsed);

    /* getter de position */
    GLfloat getX();
    GLfloat getY();
    GLfloat getZ();
    Vecteur3d vCible;	        // vecteur de cible de la camera


    void setSourisXOld(int sourisXOld)
    {
        this->sourisXOld = sourisXOld;
    }

    void setSourisYOld(int sourisYOld)
    {
        this->sourisYOld = sourisYOld;
    }

    int getSourisXOld()
    {
        return sourisXOld;
    }

    int getSourisYOld()
    {
        return sourisYOld;
    }

    private:

    //----------------------
    //-- attributs privés --
    //----------------------
    Vecteur3d vPosition;        // vecteur de position de la camera

    Vecteur3d vAxeVertical;     // vecteur de definition de l'axe vertical

    bool cliquePresse;          // variable d'état du clique
    int sourisXOld;             // sauvegarde de la souris
    int sourisYOld;             // sauvegarde de la souris

    GLfloat vitesseDeplacement; // vitesse de déplacement
    GLfloat vitesseDeplacementInitiale; // vitesse de déplacement initiale
    GLfloat vitesseDeplacementMax; // vitesse de déplacement maximale
    GLfloat vitesseRegard;      // vitesse du regard
    GLfloat acceleration;
    GLfloat deceleration;
    int dernierDeplacement;

    /* gestion des touches clavier */
    bool toucheAvancerPressee;
    bool toucheReculerPressee;
    bool toucheDeplacementLateralDroitPressee;
    bool toucheDeplacementLateralGauchePressee;

    void decelerer();
    void accelerer();
};

#endif
