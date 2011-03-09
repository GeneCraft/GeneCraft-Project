#ifndef DEF_GEOMETRIE_H
#define DEF_GEOMETRIE_H

//------------------------------------------------------------------------------
//-- Fichier    : geometrie.h
//-- Auteur     : Da Campo Aurélien
//-- Date       : 10 decembre 2009
//-- Cours      : IGR, heig-vd, LABO 3
//-- But        : Structure pour calcules vectoriels
//------------------------------------------------------------------------------

struct Vecteur3d
{
	float x, y, z; // coordonnées 3 dimensions

    //-----------------------
    //-- constructeur vide --
    //-----------------------
    Vecteur3d() {} // vide

    //------------------
    //-- constructeur --
    //------------------
	Vecteur3d (float x, float y, float z)
	{
        this->x = x;
        this->y = y;
        this->z = z;
    }

    //-------------------------------
    //-- definition des opérateurs --
    //-------------------------------
	/* + */
	Vecteur3d operator+(Vecteur3d vecteur)
    {
        return Vecteur3d(vecteur.x+x, vecteur.y+y, vecteur.z+z);
    }

	/* - */
	Vecteur3d operator-(Vecteur3d vecteur)
    {
        return Vecteur3d(x-vecteur.x, y-vecteur.y, z-vecteur.z);
    }

	/* * */
	Vecteur3d operator*(float nombre)
    {
        return Vecteur3d(x*nombre, y*nombre, z*nombre);
    }

	/* / */
	Vecteur3d operator/(float nombre)
    {
        return Vecteur3d(x/nombre, y/nombre, z/nombre);
    }

    /* vNormal = v1 x v2 */
    static void calculerVecteurNormal(Vecteur3d & vNormal, Vecteur3d v1, Vecteur3d v2)
    {
        vNormal.x = v1.y * v2.z - v1.z * v2.y;
        vNormal.y = v1.x * v2.z - v1.z * v2.x;
        vNormal.z = v1.x * v2.y - v1.y * v2.x;
    }

    /* pour etre plus pratique */
    static void calculerVecteurNormal(float vNormal[3], const float v1[3], const float v2[3])
    {
        vNormal[0] = v1[1] * v2[2] - v1[2] * v2[1];
        vNormal[1] = v1[0] * v2[2] - v1[2] * v2[0];
        vNormal[2] = v1[0] * v2[1] - v1[1] * v2[0];
    }
};

#endif
