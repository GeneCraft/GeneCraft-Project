#include "GLCreatureViewer.h"

// lumiere
static GLfloat lPrincipaleAmb[] = {0.0,    0.0,    0.0,    1.0f};
static GLfloat lPrincipaleDif[] = {1.0f,   1.0f,   1.0f,   1.0f};
static GLfloat lPrincipaleSpe[] = {1.0f,   1.0f,   1.0f,   1.0f};
static GLfloat lPrincipaleDir[] = {0.0f,  -1.0f,   0.0f,   0.0f};
static GLfloat lPrincipalePos[] = {0.0f, 500.0f,   0.0f,   1.0f};

GLCreatureViewer::GLCreatureViewer()
{
    physicEnable = false;
    focused = false;


    // widget properties
    setMouseTracking(TRUE);

    // create world
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();

    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-10,0));

    // SCENE OBJECTS
    // camera
    camera = new Camera(30, 30, 30, 0, 0, 0);
    camera->initialiser(ANGLE_DE_VUE,(GLdouble)800/600,DIST_PROCH_V,DIST_LOIN_V);

    // Axis
    Axis *axis = new Axis(10);
    drawableObjects.push_back(axis);

    // Surface
    Surface *ground = new Surface(0,-10,0,300);
    drawableObjects.push_back(ground);
    dynamicsWorld->addRigidBody(ground->rigidBody);

    // Human
    //human = new Human(dynamicsWorld);
    //drawableObjects.push_back(human);

    //snake  = new Snake(dynamicsWorld);
    //drawableObjects.push_back(snake);

    //arm = new Arm(dynamicsWorld);
    //drawableObjects.push_back(arm);


    motorisedArm = new MotorisedArm();
    motorisedArm->addToWorld(dynamicsWorld);
    drawableObjects.push_back(motorisedArm);


    /*
    Box * b = new Box(0,0,0,1,1,1);
    b->setColor(0,1,0);
    drawableObjects.push_back(b);
    dynamicsWorld->addRigidBody(b->rigidBody);

    b = new Box(1,0,0,1,1,1);
    b->setColor(1,0,0);
    drawableObjects.push_back(b);
    dynamicsWorld->addRigidBody(b->rigidBody);

    b = new Box(0,1,0,1,1,1);
    b->setColor(1,1,1);
    drawableObjects.push_back(b);
    dynamicsWorld->addRigidBody(b->rigidBody);
    */

/*
    Sphere * s = new Sphere(0,0,0,1);
    s->setColor(0,1,0);
    drawableObjects.push_back(s);

    s = new Sphere(1,0,0,1);
    s->setColor(1,0,0);
    drawableObjects.push_back(s);

*/

    // CUBE OF CUBES
    /*
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
    }*/

    // Refreshing thread
    Thread *thread = new Thread( this );
    thread->start();
}


void GLCreatureViewer::initializeGL()
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

void GLCreatureViewer::resizeGL(int width, int height )
{
}

void GLCreatureViewer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLightfv(GL_LIGHT0, GL_POSITION, lPrincipalePos);

    // 3. configuration
    camera->initialiser(ANGLE_DE_VUE,
                        (GLdouble)800/600,
                        DIST_PROCH_V,
                        DIST_LOIN_V);

    // 2. move and adapt scene
    camera->adapterLaScene();

    // 1. draw drawable objects
    for(unsigned int i=0;i<drawableObjects.size();i++)
        drawableObjects.at(i)->draw();

    /*
    btCollisionObjectArray coa = dynamicsWorld->getCollisionObjectArray();

    for(int i=0;i<coa.m_size;i++)
        coa.at(i)->
    */

    /*
    int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
    for (int i=0;i<numManifolds;i++)
    {
            btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
            btRigidBody* obA = static_cast<btRigidBody*>(contactManifold->getBody0());
            btRigidBody* obB = static_cast<btRigidBody*>(contactManifold->getBody1());

            int numContacts = contactManifold->getNumContacts();
            for (int j=0;j<numContacts;j++)
            {
                    btManifoldPoint& pt = contactManifold->getContactPoint(j);
                    if (pt.getDistance()<0.f)
                    {

                            //From : http://www.sjbaker.org/wiki/index.php?title=Physics_-_Bullet_Tutorial2_example

                            //Note here that two points are used. One (A) is actually a little redundant.
                            // Two points are actually specified because of object penetration - the calculations are not perfect,
                            //and one object can penetrate into another. As such, there are different graphical points of contact
                            //for what should be the one collision point. The value m_distance1 of the manifold point shows the
                            //penetration depth.

                            const btVector3& ptA = pt.getPositionWorldOnA();
                            const btVector3& ptB = pt.getPositionWorldOnB();
                            const btVector3& normalOnA = pt.m_normalWorldOnB; // FIXME pourquoi pas de normal world on A ?
                            const btVector3& normalOnB = pt.m_normalWorldOnB;

                            //obA->applyCentralImpulse(normalOnA * 10);
                            //obB->applyCentralImpulse(normalOnB * 10);

                            //Sphere *s = new Sphere(ptA.getX(), ptA.getY(), ptA.getZ(),pt.m_appliedImpulse / 10);
                            //drawableObjects.push_back(s);




                            // FIXME pt.m_appliedImpulse... une seule impulsion mais 2 corps ???

                            DrawableVector *vA = new DrawableVector(normalOnA * pt.m_appliedImpulse,ptA);
                            drawableObjects.push_back(vA);

                            DrawableVector *vB = new DrawableVector(normalOnB * pt.m_appliedImpulse,ptB);
                            drawableObjects.push_back(vB);


                            //dynamicsWorld->removeRigidBody(obB);
                            //drawableObjects.erase



//                            GLdouble radius = 0.5;// pt.m_appliedImpulse / 10;

//                            glPushMatrix();

//                            // position
//                            glTranslated(ptA.getX(), ptA.getY(), ptA.getZ());

//                            // scale
//                            glScaled(radius, radius, radius);

//                            // draw sphere with glu
//                            gluSphere(gluNewQuadric(),1,10,10);

//                            glPopMatrix();


                            qDebug() << "collision applied Impulse : " << pt.m_appliedImpulse;
                    }
            }
    }

    */
    glFlush();
}

void GLCreatureViewer::timeOut()
{
}

void GLCreatureViewer::drawScene()
{
    mutex.lock();

    if(physicEnable)
        dynamicsWorld->stepSimulation(1.f/60.f); // bullet action
    //physicEnable = false; // step by step with pressing 'p'
    camera->bouger(16); // camera

    update(); // GL

    mutex.unlock();
}

void GLCreatureViewer::mousePressEvent(QMouseEvent * e)
{
    // get focus
    if(!focused)
    {
        setFocus(Qt::NoFocusReason); // get the focus for keys events
        //setCursor( QCursor( Qt::BlankCursor ) ); // hide cursor
        focused = true;
        return;
    }

    // report to the camera
    camera->sourisBoutons(e->button(),1,e->pos().x(),e->pos().y());

    // right click : shoot a cube
    if(e->button() == 2)
    {
        // create a box with camera position
        Box * b = new Box(camera->getX(),camera->getY(),camera->getZ(),1,1,1);

        // add to drawable objects and world
        drawableObjects.push_back(b);
        dynamicsWorld->addRigidBody(b->rigidBody);

        // compute angle of impulse
        btVector3 target(camera->getX(),camera->getY(),camera->getZ());
        btVector3 origin(camera->vCible.x,camera->vCible.y,camera->vCible.z);
        btVector3 initialImpulse = origin - target;
        initialImpulse.normalize();
        initialImpulse *= 200;

        // apply impulse from the center of the box
        b->rigidBody->applyCentralImpulse(initialImpulse);
    }
}

void GLCreatureViewer::mouseReleaseEvent(QMouseEvent * e)
{
    camera->sourisBoutons(e->button(),0,e->pos().x(),e->pos().y());
}

void GLCreatureViewer::mouseMoveEvent(QMouseEvent * e)
{
    // no move -> generate by QCursor::setPos
    if(!focused || camera->getSourisXOld() == e->pos().x() && camera->getSourisYOld() == e->pos().y())
        return;

    // report to the camera
    camera->sourisBouge(e->pos().x(),e->pos().y());

    // get center of the GL widget
    QPoint p = this->mapToGlobal(QPoint(0,0));
    int x = p.x() + this->size().width() / 2;
    int y = p.y() + this->size().height() / 2;

    camera->setSourisXOld(x);
    camera->setSourisYOld(y);

    QCursor::setPos(this->mapToGlobal(QPoint(x,y)));
}

void GLCreatureViewer::keyPressEvent(QKeyEvent *e)
{
    camera->evenementTouchePressee(e->key());
}

void GLCreatureViewer::keyReleaseEvent(QKeyEvent *e)
{
    qDebug() << "key pressed : " << e->key();

    mutex.lock();
    camera->evenementToucheLevee(e->key());

    // B
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
    // V
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
    //
    //else if(e->key() == 75)
    //    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);   // mode facette
    else if(e->key() == 76)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else if(e->key() == 77)
        glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
    else if(e->key() == 70)
    {
        if(glIsEnabled(GL_LIGHTING))
            glDisable(GL_LIGHTING);
        else
            glEnable(GL_LIGHTING);
    }
    else if(e->key() == 74)
    {
        //human->jump();
        snake->jump();
        //arm->contractA();
    }
    else if(e->key() == 72)
    {
        arm->contractB();
    }
    else if(e->key() == 80)
        physicEnable = !physicEnable;
    else if(e->key() == 16777216)
    {
        setCursor( QCursor( Qt::ArrowCursor ) );
        focused = false;
    }

    mutex.unlock();
}

void GLCreatureViewer::enterEvent ( QEvent * event ){
    qDebug() << "enterEvent";
}

void GLCreatureViewer::leaveEvent ( QEvent * event ){
    qDebug() << "leaveEvent";
}
