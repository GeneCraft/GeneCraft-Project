#ifndef AXIS_H
#define AXIS_H

#include <QtOpenGL>
#include "../Drawable.h"

class Axis : public Drawable
{
private :
   int size;

public :

    Axis(int size)
    {
        this->size = size;
    }

    void draw()
    {
        /* OX (rouge) */
        glColor3f (1.0, 0.0, 0.0);
        glBegin(GL_LINES);
            glVertex3i(0,0,0);
            glVertex3i(size,0,0);
        glEnd();

        /* OY (vert) */
        glColor3f (0.0, 1.0, 0.0);
        glBegin(GL_LINES);
            glVertex3i(0,0,0);
            glVertex3i(0,size,0);
        glEnd();

        /* OZ (bleu) */
        glColor3f (0.0, 0.0, 1.0);
        glBegin(GL_LINES);
            glVertex3i(0,0,0);
            glVertex3i(0,0,size);
        glEnd();


        // cube unitaire
        // TOP
        glBegin(GL_LINES);
            glVertex3i(0,1,0);
            glVertex3i(1,1,0);
        glEnd();

        glBegin(GL_LINES);
            glVertex3i(0,1,0);
            glVertex3i(0,1,1);
        glEnd();

        glBegin(GL_LINES);
            glVertex3i(1,1,1);
            glVertex3i(0,1,1);
        glEnd();

        glBegin(GL_LINES);
            glVertex3i(1,1,1);
            glVertex3i(1,1,0);
        glEnd();

        // BOTTOM
        glBegin(GL_LINES);
            glVertex3i(1,0,1);
            glVertex3i(0,0,1);
        glEnd();

        glBegin(GL_LINES);
            glVertex3i(1,0,1);
            glVertex3i(1,0,0);
        glEnd();

        // VERTICAL
        glBegin(GL_LINES);
            glVertex3i(1,1,1);
            glVertex3i(1,0,1);
        glEnd();

        glBegin(GL_LINES);
            glVertex3i(0,1,1);
            glVertex3i(0,0,1);
        glEnd();

        glBegin(GL_LINES);
            glVertex3i(1,1,0);
            glVertex3i(1,0,0);
        glEnd();
    }
};



#endif // AXIS_H
