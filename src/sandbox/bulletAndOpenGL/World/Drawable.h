#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QtOpenGL>

class Drawable
{
public :

    virtual void draw() = 0;

    GLfloat* getColor()
    {
        return color;
    }

    void setColor(GLfloat r, GLfloat g, GLfloat b)
    {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }

protected:
    GLfloat color[3];
};


#endif // DRAWABLE_H
