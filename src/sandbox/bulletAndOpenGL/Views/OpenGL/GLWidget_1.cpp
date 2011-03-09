#include "GLWidget_1.h"
#include "World/BasicShapes/Surface.h"
#include "World/BasicShapes/Sphere.h"
#include "World/Human.h"
#include "World/Arm.h"

// lumiere
GLfloat lPrincipaleAmb[] = {0.0,    0.0,    0.0,    1.0f};
GLfloat lPrincipaleDif[] = {1.0f,   1.0f,   1.0f,   1.0f};
GLfloat lPrincipaleSpe[] = {1.0f,   1.0f,   1.0f,   1.0f};
GLfloat lPrincipaleDir[] = {0.0f,  -1.0f,   0.0f,   0.0f};
GLfloat lPrincipalePos[] = {0.0f, 500.0f,   0.0f,   1.0f};

GLWidget_1::GLWidget_1()
{
    physicEnable = false;

    // widget properties
    setMouseTracking(TRUE);

    // create world
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();

    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-10,0));

    // create scene objects
    camera = new Camera(30, 30, 30, 0, 0, 0);
    camera->initialiser(ANGLE_DE_VUE,(GLdouble)800/600,DIST_PROCH_V,DIST_LOIN_V);

    Axis *axis = new Axis(10);
    drawableObjects.push_back(axis);

    Surface *ground = new Surface(0,-10,0,300);
    drawableObjects.push_back(ground);
    dynamicsWorld->addRigidBody(ground->rigidBody);


    // CUBE OF CUBES
    Box * b;
    for(int i=1;i<8;i++)
    {
        for(int j=1;j<8;j++)
        {
            for(int k=1;k<8;k++)
            {
                b = new Box(j*2,i*2-10,k*2,1,1,1);
                drawableObjects.push_back(b);
                dynamicsWorld->addRigidBody(b->rigidBody);
            }
        }
    }

    //Box * b;

    /*
  for(int k=0;k<10;k++)
  {
      b = new Box(0,k*8.f,0,8,2,4);
      b->setColor(0,0,1.f);
      drawableObjects.push_back(b);
      dynamicsWorld->addRigidBody(b->rigidBody);
  }
*/
    /*
  // CASTEL
  float w = 8.f;
  float h = 2.f;
  float l = 0.5f;
  Box * b;
  int hh = h/2.f;
  int hh2 = -h-0.5f;

  for(int i=1;i<3;i++)
  {
      for(int k=0;k<10;k++)
      {
          if(i == 1)
          {
              b = new Box(w/2,hh,0,l,h,w);
              b->setColor(0,0,1.f);
              drawableObjects.push_back(b);
              dynamicsWorld->addRigidBody(b->rigidBody);

              b = new Box(-w/2,hh,0,l,h,w);
              b->setColor(0,1.f,0);
              drawableObjects.push_back(b);
              dynamicsWorld->addRigidBody(b->rigidBody);

              hh += 4*h;
          }
          else
          {
              b = new Box(0,hh2,w/2,w,h,l);
              b->setColor(0,0,1.f);
              drawableObjects.push_back(b);
              dynamicsWorld->addRigidBody(b->rigidBody);

              b = new Box(0,hh2,-w/2,w,h,l);
              b->setColor(0,1.f,0);
              drawableObjects.push_back(b);
              dynamicsWorld->addRigidBody(b->rigidBody);

              hh2 += 4*h;
          }
      }
  }
    */



    // HEAVY CUBES
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            b = new Box(i+5,1200,j+5,0.1,0.1,0.1);
            drawableObjects.push_back(b);
            dynamicsWorld->addRigidBody(b->rigidBody);
        }
    }

    /*
  human = new Human(dynamicsWorld);
  drawableObjects.push_back(human);
*/

    // Refreshing thread
    Thread *thread = new Thread( this );
    thread->start();
    //this->start();
}

void GLWidget_1::addCameraView()
{
    // configuration
    camera->initialiser(ANGLE_DE_VUE,
                        (GLdouble)800/600,
                        DIST_PROCH_V,
                        DIST_LOIN_V);

    // move and adapt scene
    camera->adapterLaScene();
}

void GLWidget_1::initializeGL()
{
    glShadeModel(GL_SMOOTH);				// Enables Smooth Shading
    glEnable(GL_SHADE_MODEL);                          // activation de l'ombrage

    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);		// Background

    glClearDepth(1.0f);					// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);				// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);				// The Type Of Depth Test To Do

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

    //-----------------------------------
    //-- initialisations de la lumiere --
    //-----------------------------------
    // Proprietes lumineuses de la scène
    glEnable(GL_LIGHTING);  // lumiere activee
    glEnable(GL_NORMALIZE); // normalisation des vecteurs normaux

    // Lumière principale
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, lPrincipaleAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lPrincipaleDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lPrincipaleSpe);
}

void GLWidget_1::resizeGL(int width, int height )
{

}

void GLWidget_1::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLightfv(GL_LIGHT0, GL_POSITION, lPrincipalePos);

    addCameraView();

    // draw drawable objects
    for(unsigned int i=0;i<drawableObjects.size();i++)
        drawableObjects.at(i)->draw();
}

void GLWidget_1::timeOut()
{
}

void GLWidget_1::drawScene()
{
    mutex.lock();

    if(physicEnable)
        dynamicsWorld->stepSimulation(1.f/60.f); // bullet action

    camera->bouger(16); // camera

    update(); // GL

    mutex.unlock();
}

///-- THREAD --///
/*
void GLWidget_1::Thread::run()
{
    while(true)
    {
        mutex.lock();

        if(physicEnable)
            dynamicsWorld->stepSimulation(1.f/60.f); // bullet action

        camera->bouger(16); // camera

        update(); // GL

        mutex.unlock();
        thread->msleep(10);
    }

}*/




///-- THREAD --///
/*
void GLWidget_1::run(Thread * thread)
{
    while(true)
    {
        mutex.lock();

        if(physicEnable)
            dynamicsWorld->stepSimulation(1.f/60.f); // bullet action

        camera->bouger(16); // camera

        update(); // GL

        mutex.unlock();
        //thread->msleep(10);
    }
}
*/



///-- MOUSE EVENT --///

void GLWidget_1::mousePressEvent(QMouseEvent * e)
{
    setFocus(Qt::NoFocusReason);

    camera->sourisBoutons(e->button(),1,e->pos().x(),e->pos().y());

    // right click
    if(e->button() == 2)
    {
        // create a box with camera position
        Box * b = new Box(camera->getX(),camera->getY(),camera->getZ(),1,1,1);

        drawableObjects.push_back(b);
        dynamicsWorld->addRigidBody(b->rigidBody);

        // compute angle of impulse
        btVector3 cible(camera->getX(),camera->getY(),camera->getZ());
        btVector3 origin(camera->vCible.x,camera->vCible.y,camera->vCible.z);
        btVector3 initialImpulse = origin - cible;
        initialImpulse.normalize();
        initialImpulse *= 200;

        // apply impulse from the center of the box
        b->rigidBody->applyCentralImpulse(initialImpulse);
    }
}

void GLWidget_1::mouseReleaseEvent(QMouseEvent * e)
{
    camera->sourisBoutons(e->button(),0,e->pos().x(),e->pos().y());
}

void GLWidget_1::mouseMoveEvent(QMouseEvent * e)
{
    camera->sourisBouge(e->pos().x(),e->pos().y());
}

void GLWidget_1::keyPressEvent(QKeyEvent *e)
{
    camera->evenementTouchePressee(e->key());
}
void GLWidget_1::keyReleaseEvent(QKeyEvent *e)
{
    qDebug() << e->key();

    mutex.lock();
    camera->evenementToucheLevee(e->key());

    if(e->key() == 66)
    {
        Box * b;
        for(int i=1;i<100;i++)
        {
            b = new Box(5.0,10.0+10,2.0,1,1,1);
            dynamicsWorld->addRigidBody(b->rigidBody);
            drawableObjects.push_back(b);
        }
    }
    else if(e->key() == 86)
    {
        Sphere *sphere;
        for(int i=1;i<100;i++)
        {
            sphere = new Sphere(10+i/5.0,i*10+10,i/2.0,2);
            dynamicsWorld->addRigidBody(sphere->rigidBody);
            drawableObjects.push_back(sphere);
        }
    }
    else if(e->key() == 75)
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);   // mode facette
    else if(e->key() == 76)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else if(e->key() == 70)
    {
        if(glIsEnabled(GL_LIGHTING))
            glDisable(GL_LIGHTING);
        else
            glEnable(GL_LIGHTING);
    }
    else if(e->key() == 74)
        human->jump();
    else if(e->key() == 80)
        physicEnable = !physicEnable;

    mutex.unlock();
}

/*
void GLWidget_1::simulate()
{
    qDebug() << "toto";

    physicEnable = true;
}*/
