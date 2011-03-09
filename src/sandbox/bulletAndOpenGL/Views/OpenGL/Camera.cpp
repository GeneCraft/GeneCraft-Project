#include "Camera.h"

//------------------------------------------------------------------------------
//-- Fichier    : Camera.cpp
//-- Auteur     : Da Campo Aurélien
//-- Date       : 10 decembre 2009
//-- Cours      : IGR, heig-vd, LABO 4
//-- But        : Classe de gestion d'une caméra libre et volante.
//                NB : cette caméra fonction en systeme d'axes américain :
//                Y = axe vertical
//------------------------------------------------------------------------------

//------------------
//-- constructeur --
//------------------
Camera::Camera(GLfloat x, GLfloat y, GLfloat z,
               GLfloat cibleX, GLfloat cibleY, GLfloat cibleZ)
{
    /* initialisation de la position de la caméra */
    vPosition	        = Vecteur3d(x, y, z);
    /* initialisation de la cible */
    vCible	        = Vecteur3d(cibleX, cibleY, cibleZ);
    /* standard americain ( Y = l'axe vertical) */
    vAxeVertical        = Vecteur3d(0.0, 1.0, 0.0);

    /* valeur par defaut */
    vitesseDeplacementInitiale              = 0.01;
    vitesseDeplacement                      = vitesseDeplacementInitiale;
    vitesseDeplacementMax                   = 0.08;
    acceleration                            = 1.00;
    deceleration                            = 0.8;
    vitesseRegard                           = 0.003;
    dernierDeplacement                      = 1;


    toucheAvancerPressee                    = false;
    toucheReculerPressee                    = false;
    toucheDeplacementLateralDroitPressee    = false;
    toucheDeplacementLateralGauchePressee   = false;
}

//------------
//-- outils --
//------------
/* initialiser la camera */
void Camera::initialiser(GLdouble	fovy,
                        GLdouble	aspect,
                        GLdouble	zNear,
                        GLdouble	zFar)
{
    // change la matrice courante en matrice de projection
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    // installe une matrice de projection
    gluPerspective(fovy,     // angle de vue
                   aspect,   // ratio d'aspet
                   zNear,    // distance la plus proche visible
                   zFar);    // distance la plus loin visible

    // change la matrice courante en matrice modelview
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}

/* ajouter la camera a la scene */
void Camera::adapterLaScene()
{
    // use this function for opengl target camera
	gluLookAt(this->vPosition.x,    this->vPosition.y,    this->vPosition.z,
			  this->vCible.x,       this->vCible.y,       this->vCible.z,
			  this->vAxeVertical.x, this->vAxeVertical.y, this->vAxeVertical.z);

}


//------------
//-- regard --
//------------

/* tourner la camera a droite ou a gauche sur son origine */
void Camera::tourner(GLfloat angle)
{
    // calcul du vecteur de la vue
    Vecteur3d vVector = vCible - vPosition;

    // calcul la nouvelle cible
    vCible.z = (GLfloat)(vPosition.z + sin(angle)*vVector.x
                                     + cos(angle)*vVector.z);
    vCible.x = (GLfloat)(vPosition.x + cos(angle)*vVector.x
                                     - sin(angle)*vVector.z);
}

/* lever ou baisse la camera sur son origine */
void Camera::leverBaisser(GLfloat angle)
{
    vCible.y = vCible.y + angle;
}

//------------------------------
//-- gestion des evenenements --
//------------------------------
/*  souris pressee,
    NB : a appeler lors d'un evenement souris /!\ POUR LIB GLUT /!\
*/
void Camera::sourisBoutons(int bouton, int etat,int x,int y)
{
  // si on appuie sur le bouton gauche
  if (bouton == GRAB_BUTTON && etat == KEY_DOWN)
  {
    cliquePresse    = true;
    sourisXOld      = x;
    sourisYOld      = y;
  }
  // si on relache le bouton gauche
  else if (bouton == GRAB_BUTTON && etat == KEY_UP)
    cliquePresse = false;
}

/*  souris bougee
    a appeler lors d'un evenement souris /!\ POUR LIB GLUT /!\
    returne true si rafraichissement nécéssaire
*/
bool Camera::sourisBouge(int x,int y)
{
    bool rafraichir = false;

    // si le bouton gauche est presse
    //if (cliquePresse)
    {
        // calcul de combien la souris a bougee.
        GLfloat sourisHorizontalDiff = x - sourisXOld;
        GLfloat sourisVerticalDiff   = y - sourisYOld;

        // pas de changement
        //if(!(sourisHorizontalDiff == 0 && sourisHorizontalDiff == 0))
        //    return false;

        tourner(sourisHorizontalDiff * vitesseRegard);
        leverBaisser(-sourisVerticalDiff * vitesseRegard * 20);

        rafraichir = true;
    }

    sourisXOld = x;
    sourisYOld = y;

    return rafraichir;
}


//----------------
//-- mouvements --
//----------------

/* avancer (valeur positive) ou reculer (valeur negative) */
void Camera::avancer(GLfloat distance)
{
    // calcul du vecteur de la vue
    Vecteur3d vVector = vCible - vPosition;

	// deplacement le long du vecteur de la vue
	vPosition.x  = vPosition.x  + vVector.x * distance;
	vPosition.z  = vPosition.z  + vVector.z * distance;
	vPosition.y  = vPosition.y  + vVector.y * distance;

	vCible.x     = vCible.x     + vVector.x * distance;
	vCible.z     = vCible.z     + vVector.z * distance;
        vCible.y     = vCible.y       + vVector.y * distance;

	// position actuelle de la camera
	//printf("%.2f, %.2f, %.2f, %.2f, %.2f, %.2f \n",
    //vPosition.x,vPosition.y,vPosition.z,vCible.x,vCible.y,vCible.z);
}

/* deplacer latéralement à droite ou à gauche */
void Camera::deplacerLateralement(GLfloat distance)
{
    // calcul du vecteur de la vue
    Vecteur3d vVector = vCible - vPosition;

	// calcul du vector orthogonal de la cible
	Vecteur3d vOrthoVector;
	vOrthoVector.x = -vVector.z;
	vOrthoVector.z =  vVector.x;

	// deplacement le long du vecteur orthogonal
	vPosition.x  = vPosition.x  + vOrthoVector.x * distance;
	vPosition.z  = vPosition.z  + vOrthoVector.z * distance;
	//vPosition.y  = vPosition.y  + vOrthoVector.y * distance;

	vCible.x     = vCible.x     + vOrthoVector.x * distance;
	vCible.z     = vCible.z     + vOrthoVector.z * distance;
	//vCible.y     = vCible.y     + vOrthoVector.y * distance;
}


void Camera::accelerer()
{

    this->vitesseDeplacement *= this->acceleration;

    if(this->vitesseDeplacement > vitesseDeplacementMax)
        this->vitesseDeplacement = vitesseDeplacementMax;
}

void Camera::decelerer()
{
    this->vitesseDeplacement *= this->deceleration;

    if(this->vitesseDeplacement < vitesseDeplacementInitiale)
        this->vitesseDeplacement = vitesseDeplacementInitiale;
}



/* calcul la nouvelle position de la camera en fonction des touches pressées */
void Camera::bouger(long timeElapsed)
{
    double secTimeElapsed = timeElapsed / 1000.0;

    if(!toucheAvancerPressee
    && !toucheReculerPressee
    && !toucheDeplacementLateralGauchePressee
    && !toucheDeplacementLateralDroitPressee)
    {
        decelerer();

        if(this->vitesseDeplacement > this->vitesseDeplacementInitiale)
            switch(this->dernierDeplacement)
            {
               case 0 : this->avancer(vitesseDeplacement*secTimeElapsed); break;
               case 1 : this->avancer(-vitesseDeplacement*secTimeElapsed); break;
               case 2 : this->deplacerLateralement(-vitesseDeplacement*secTimeElapsed); break;
               case 3 : this->deplacerLateralement(vitesseDeplacement*secTimeElapsed); break;
            }

        return;
    }

    // avance si on ne recule pas aussi
    if(toucheAvancerPressee && !toucheReculerPressee)
    {
        this->avancer(vitesseDeplacement);
        this->dernierDeplacement = 0;
    }

    // recule si on n'avance pas aussi
    if(toucheReculerPressee && !toucheAvancerPressee)
    {
        this->avancer(-vitesseDeplacement);
        this->dernierDeplacement = 1;
    }

    // déplacement latéral à gauche si pas de déplacement latéral à droite
    if(toucheDeplacementLateralGauchePressee && !toucheDeplacementLateralDroitPressee)
    {
        this->deplacerLateralement(-vitesseDeplacement);
        this->dernierDeplacement = 2;
    }

    // déplacement latéral à droite si pas de déplacement latéral à gauche
    if(toucheDeplacementLateralDroitPressee && !toucheDeplacementLateralGauchePressee)
    {
        this->deplacerLateralement(vitesseDeplacement);
        this->dernierDeplacement = 3;
    }

    accelerer();
}


//--------------------------------------
//-- gestion des evenenements clavier --
//--------------------------------------
/* à appeler si une touche du clavier est pressée */
void Camera::evenementTouchePressee(unsigned int touche)
{
    switch (touche)
    {
        case AVANCER:
            toucheAvancerPressee = true;
            break;

        case RECULER:
            toucheReculerPressee = true;
            break;

        case DEPLACEMENT_GAUCHE :
            toucheDeplacementLateralGauchePressee = true;
            break;

        case DEPLACEMENT_DROITE:
            toucheDeplacementLateralDroitPressee = true;
            break;
    }
}

/* à appeler si une touche du clavier est levée */
void Camera::evenementToucheLevee(unsigned int touche)
{
    switch (touche)
    {
         case AVANCER:
            toucheAvancerPressee = false;
            return;

         case RECULER:
            toucheReculerPressee = false;
            return;

         case DEPLACEMENT_GAUCHE :
            toucheDeplacementLateralGauchePressee = false;
            return;

         case DEPLACEMENT_DROITE:
            toucheDeplacementLateralDroitPressee = false;
            return;
    }
}

GLfloat Camera::getX()
{
    return vPosition.x;
}

GLfloat Camera::getY()
{
    return vPosition.y;
}

GLfloat Camera::getZ()
{
    return vPosition.z;
}
