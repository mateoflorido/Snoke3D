/* -------------------------------------------------------------------------
 * @brief Simulation of a simple solar system
 * @author Leonardo Fl�rez-Valencia (florez-l@javeriana.edu.co)
 * -------------------------------------------------------------------------
 */

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <random>
#include "Scenary.h"
#include "Snake.h"
#include "Camera.h"
#include "SpatialObject.h"

// Aliases

using Clock = std::chrono::time_point<std::chrono::high_resolution_clock>;

// -------------------------------------------------------------------------
Camera myCamera;
SpatialObject *myStar = nullptr;
Snake *mySnake = nullptr;
Scenary *myScenary = nullptr;

float rotA = 0;
float dx = 1;
float dy = 0;
GLfloat light0Pos[] = {0.0, 0.0, 100.0, 1.0};
GLfloat light0Amb[] = {0.2, 0.2, 0.2, 1.0};
GLfloat light0Diff[] = {0.8, 0.8, 0.8, 1.0};
GLfloat light0Spec[] = {1.0, 1.0, 1.0, 1.0};

GLfloat light1Pos[] = {10.0, 10.0, -10.0, 1.0};
GLfloat light1Amb[] = {0.0, 1.0, 0.0, 1.0};
GLfloat light1Diff[] = {0.0, 1.0, 0.0, 1.0};
GLfloat light1Spec[] = {0.0, 1.0, 0.0, 1.0};

GLfloat light2Pos[] = {10.0, -10.0, 10.0, 1.0};
GLfloat light2Amb[] = {0.0, 0.0, 1.0, 1.0};
GLfloat light2Diff[] = {0.0, 0.0, 1.0, 1.0};
GLfloat light2Spec[] = {0.0, 0.0, 1.0, 1.0};

GLfloat light3Pos[] = {-10.0, 10.0, 10.0, 1.0};
GLfloat light3Amb[] = {1.0, 0.0, 1.0, 1.0};
GLfloat light3Diff[] = {1.0, 0.0, 1.0, 1.0};
GLfloat light3Spec[] = {1.0, 0.0, 1.0, 1.0};

GLfloat light4Pos[] = {10.0, -10.0, -10.0, 1.0};
GLfloat light4Amb[] = {0.0, 1.0, 1.0, 1.0};
GLfloat light4Diff[] = {0.0, 1.0, 1.0, 1.0};
GLfloat light4Spec[] = {0.0, 1.0, 1.0, 1.0};

GLfloat light5Pos[] = {-10.0, -10.0, 10.0, 1.0};
GLfloat light5Amb[] = {0.5, 0.0, 1.0, 1.0};
GLfloat light5Diff[] = {0.5, 0.0, 1.0, 1.0};
GLfloat light5Spec[] = {0.5, 0.0, 1.0, 1.0};

GLfloat light6Pos[] = {-10.0, 10.0, -10.0, 1.0};
GLfloat light6Amb[] = {0.0, 0.5, 1.0, 1.0};
GLfloat light6Diff[] = {0.0, 0.5, 1.0, 1.0};
GLfloat light6Spec[] = {0.0, 0.5, 1.0, 1.0};

GLfloat light7Pos[] = {-10.0, -10.0, -10.0, 1.0};
GLfloat light7Amb[] = {1.0, 0.5, 1.0, 1.0};
GLfloat light7Diff[] = {1.0, 0.5, 1.0, 1.0};
GLfloat light7Spec[] = {1.0, 0.5, 1.0, 1.0};

GLfloat lightSpot[] = {0.0, 0.0, 0.0};
GLfloat lightCutoff = 20.0;

static GLfloat mat_specular[] = {0.5, 0.0, 0.0, 1.0};
static GLfloat mat_shininess[] = {60.0};
Clock fpsClock;
unsigned int fpsCounter;

// -------------------------------------------------------------------------
void initLights();
SpatialObject *initWorld(int argc, char *argv[]);

void destroyWorld(SpatialObject *star);

// -------------------------------------------------------------------------
void displayCbk();
void idleCbk();
void resizeCbk(int w, int h);
void keyboardCbk(unsigned char key, int x, int y);
void mouseClickCbk(int button, int state, int x, int y);
void mouseMoveCbk(int x, int y);
void RotateSnake(int change);
void CalcDeltas();
// -------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  // Init OpenGL context
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(1024, 768);
  glutCreateWindow("Snake3D - FF Alpha 0.1");

  // Init world
  try
  {
    //myStar = initWorld( argc, argv );
    mySnake = new Snake();
    myScenary = new Scenary();
    myCamera.rotY(-90);
    myCamera.rotZ(-90);
    myCamera.upward(2.5);

    glutDisplayFunc(displayCbk);
    glutIdleFunc(idleCbk);
    glutReshapeFunc(resizeCbk);
    glutKeyboardFunc(keyboardCbk);
    glutMouseFunc(mouseClickCbk);
    glutMotionFunc(mouseMoveCbk);
    initLights();
    glutMainLoop();

    destroyWorld(myStar);
    return (0);
  }
  catch (std::exception &err)
  {
    std::cerr << err.what() << std::endl;
    return (1);
  } // end if
}
/* Initialisation of OpenGL */
void initLights()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glShadeModel(GL_FLAT);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  /*
   glEnable(GL_LIGHT1);
   glEnable(GL_LIGHT2);
   glEnable(GL_LIGHT3);
   glEnable(GL_LIGHT4);
   glEnable(GL_LIGHT5);
   glEnable(GL_LIGHT6);
   glEnable(GL_LIGHT7);
   */
  glEnable(GL_DEPTH_TEST);
}
// -------------------------------------------------------------------------
SpatialObject *initWorld(int argc, char *argv[])
{
  // Initialize camera
  myCamera.setFOV(45);
  myCamera.setPlanes(1e-2, 100000);
  myCamera.move(Vector(0, 0, 0));

  // OpenGL initialization
  glClearColor(0.2, 0.2, 0.2, 0.2);

  fpsClock = std::chrono::high_resolution_clock::now();
  fpsCounter = 0;

  // Check input arguments
  if (argc < 2)
    throw std::runtime_error(
        std::string("Usage: ") + argv[0] + " example.obj");
  // Read world and keep the star of this solar system
  return (new SpatialObject(argv[1]));
}

// -------------------------------------------------------------------------
void destroyWorld(SpatialObject *star)
{
  if (star != nullptr)
    delete star;
}
// -------------------------------------------------------------------------

void rotateLights()
{
  std::random_device rD;
  std::mt19937 gen(rD());
  std::uniform_int_distribution<> dist(1, 3);
  std::uniform_int_distribution<> binDist(0, 1);
  glPushMatrix();
  glPushMatrix();
  unsigned int axisX = binDist(gen);
  unsigned int axisY = binDist(gen);
  unsigned int axisZ = binDist(gen);

  if (rotA >= 360)
    rotA = 0;
  //0,3,7
  glRotatef(rotA, 0, 0, 1);
  glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
  glRotatef(rotA, 0, 1, 0);
  glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
  glRotatef(rotA, 1, 0, 0);
  glLightfv(GL_LIGHT2, GL_POSITION, light2Pos);
  glRotatef(rotA, 1, 1, 0);
  glLightfv(GL_LIGHT3, GL_POSITION, light3Pos);
  glRotatef(rotA, 0, 1, 1);
  glLightfv(GL_LIGHT4, GL_POSITION, light4Pos);
  glRotatef(rotA, 1, 0, 1);
  glLightfv(GL_LIGHT5, GL_POSITION, light5Pos);
  glRotatef(rotA, 0, 1, 1);
  glLightfv(GL_LIGHT6, GL_POSITION, light6Pos);
  glRotatef(rotA, 1, 1, 1);
  glLightfv(GL_LIGHT7, GL_POSITION, light7Pos);

  rotA += 1;
  glPopMatrix();
  glPopMatrix();
}

// -------------------------------------------------------------------------
void sceneLights()
{

  //glLoadIdentity( );
  glEnable(GL_LIGHTING);
  //rotateLights( );
  glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diff);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0Spec);
  //glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, lightCutoff;

  /*glColor3f (0.0, 1.0, 0.0);
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightSpot );
 
  glDisable (GL_LIGHTING);
 
  glutWireCube (0.1);
 */

  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diff);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light1Spec);
  glLightfv(GL_LIGHT1, GL_SHININESS, light1Diff);
  //glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, lightCutoff );

  glLightfv(GL_LIGHT2, GL_DIFFUSE, light2Diff);
  glLightfv(GL_LIGHT2, GL_SPECULAR, light2Spec);
  glLightfv(GL_LIGHT2, GL_SHININESS, light2Diff);
  //glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, lightCutoff );

  glEnable(GL_LIGHT0);
  /*
  glEnable( GL_LIGHT1 );
  glEnable( GL_LIGHT2 );
  */
}

// -------------------------------------------------------------------------
void displayCbk()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  sceneLights();
  glMatrixMode(GL_MODELVIEW);

  glColorMaterial(GL_FRONT, GL_DIFFUSE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glLoadIdentity();

  // Prepare model matrix
  myCamera.loadCameraMatrix();

  // Draw the scene
  //myStar->drawInOpenGLContext( GL_TRIANGLES );
  GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0};
  GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0};

  glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGreen);
  glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  myScenary->DrawScenary();
  mySnake->Draw();

  // Finish
  glutSwapBuffers();
  glPopMatrix();
  glDisable(GL_CULL_FACE);
}

// -------------------------------------------------------------------------
void idleCbk()
{
  if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - fpsClock).count() >= 1000)
  {
    std::cout << "FPS: " << fpsCounter << std::endl;
    fpsClock = std::chrono::high_resolution_clock::now();
    fpsCounter = 0;
    std::cout << "Degrees: [" << rotA << "] Delta X: [" <<dx<< "] Delta Y: [" << dy << "]\n";
    mySnake->Move(dx, dy);
    myCamera.forward(1);

  }
  else
  {
    fpsCounter++;
  }

  glutPostRedisplay();
}

// -------------------------------------------------------------------------
void resizeCbk(int w, int h)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  myCamera.setWindow(w, h);
  myCamera.loadProjectionMatrix();
}
// -------------------------------------------------------------------------
void RotateSnake(int change)
{
  if (change == -1)
  {
    if ((rotA - 1) < 0)
    {
      rotA = 359;
    }
    else
    {
      rotA-=1;
    }
  }
  if (change == 1)
  {
    if ((rotA + 1) > 360)
    {
      rotA = 0;
    }
    else
    {
      rotA+=1;
    }
  }
}
// -------------------------------------------------------------------------
void CalcDeltas()
{
  if (rotA <= 90)
  {
    dx = std::cos((90 - rotA)* _PI_180);
    dy = std::sin((90 - rotA)* _PI_180);
  }
  else if(rotA <= 180)
  {
    float intAngle = 90-(180-rotA);
    dx = std::cos(intAngle * _PI_180);
    dy = std::sin(intAngle * _PI_180) * -1;
  }
  else if( rotA <=270 )
  {
    dx = std::cos((270 - rotA) * _PI_180) * -1;
    dy = std::sin((270 - rotA )* _PI_180) * -1;
  }
  else if( rotA <= 360)
  {
    float intAngle = 90-(360-rotA);
    dx = std::cos(intAngle* _PI_180) * -1;
    dy = std::sin(intAngle* _PI_180);
  }
}
// -------------------------------------------------------------------------
void keyboardCbk(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'w':
  case 'W':
  {
    //myCamera.forward(1);
    glutPostRedisplay();
  }
  break;
  case 's':
  case 'S':
  {
    //myCamera.forward(1);
    glutPostRedisplay();
  }
  break;
  case 'a':
  case 'A':
  {
    RotateSnake(-1);
    CalcDeltas();
    myCamera.rotY(1);
    mySnake->Move(dx, dy);
    glutPostRedisplay();
  }
  break;
  case 'd':
  case 'D':
  {
    RotateSnake(1);
    CalcDeltas();
    myCamera.rotY(-1);
    mySnake->Move(dx, dy);
    glutPostRedisplay();
  }
  break;
  case 'i':
  case 'I':
  {
    myCamera.forward(1);
    glutPostRedisplay();
  }
  break;
  case 'k':
  case 'K':
  {
    myCamera.forward(-1);
    glutPostRedisplay();
  }
  break;
  case 'j':
  case 'J':
  {
    myCamera.strafe(-1);
    glutPostRedisplay();
  }
  break;
  case 'l':
  case 'L':
  {
    myCamera.strafe(1);
    glutPostRedisplay();
  }
  break;
  case 'p':
  case 'P':
  {
    myStar->startAnimation();
    glutPostRedisplay();
  }
  break;
  case 'o':
  case 'O':
  {
    myStar->stopAnimation();
    glutPostRedisplay();
  }
  break;
  case 27: // ESC
    std::exit(0);
    break;
  default:
    break;
  } // end switch

  /* TODO
   void KeyDown(unsigned char key, int x, int y)
   {
   switch (key)
   {
   case 27:             //ESC
   // PostQuitMessage(0);
   break;
   case 'a':
   Camera.RotateY(5.0);
   Display();
   break;
   case 'd':
   Camera.RotateY(-5.0);
   Display();
   break;
   case 'w':
   Camera.MoveForward( -0.1 ) ;
   Display();
   break;
   case 's':
   Camera.MoveForward( 0.1 ) ;
   Display();
   break;
   case 'x':
   Camera.RotateX(5.0);
   Display();
   break;
   case 'y':
   Camera.RotateX(-5.0);
   Display();
   break;
   case 'c':
   Camera.StrafeRight(-0.1);
   Display();
   break;
   case 'v':
   Camera.StrafeRight(0.1);
   Display();
   break;
   case 'f':
   Camera.MoveUpward(-0.3);
   Display();
   break;
   case 'r':
   Camera.MoveUpward(0.3);
   Display();
   break;

   case 'm':
   Camera.RotateZ(-5.0);
   Display();
   break;
   case 'n':
   Camera.RotateZ(5.0);
   Display();
   break;

   }
   }
*/
}

// -------------------------------------------------------------------------
void mouseClickCbk(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN)
    myCamera.setReference(x, y);
  else
    myCamera.setReference(0, 0);
}

// -------------------------------------------------------------------------
void mouseMoveCbk(int x, int y)
{
  int dx, dy;
  myCamera.getReference(dx, dy, x, y);
  myCamera.setReference(x, y);

  // Apply rotations
  if (dx > 0)
    myCamera.rotY(-0.5);
  else if (dx < 0)
    myCamera.rotY(0.5);
  if (dy > 0)
    myCamera.rotX(0.5);
  else if (dy < 0)
    myCamera.rotX(-0.5);

  // Redraw
  glutPostRedisplay();
}

// eof - SolarSystem.cxx
