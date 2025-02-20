/* -------------------------------------------------------------------------
 * @brief Main Driver of Snake 3D
 * @author Mateo Florido Sanchez (floridom@javeriana.edu.co)
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
#include "Fruit.h"

// Aliases

using Clock = std::chrono::time_point<std::chrono::high_resolution_clock>;

// -------------------------------------------------------------------------
Camera myCamera;
SpatialObject *myStar = nullptr;
Snake *mySnake = nullptr;
Scenary *myScenary = nullptr;
Fruit *currentFruit = nullptr;
Fruit *specialFruit = nullptr;
std::vector<float> boundaries;
std::vector<bool> powerUps;
Clock fruitTimeout;
Clock mangoTime;
Clock guaranaTime;
bool play = false;
int points = 0;
int pointMulti = 1;
float velocity = 10.0;
bool mangoAct = false;
bool guaranaAct = false;
bool ancientAct = false;
int width, height;

float rotA = 90;
float dx = 2.0;
float dy = 0.0;
GLfloat light0Pos[] = {0.0, 0.0, 100.0, 1.0};
GLfloat light0Amb[] = {0.2, 0.2, 0.2, 1.0};
GLfloat light0Diff[] = {0.8, 0.8, 0.8, 1.0};
GLfloat light0Spec[] = {1.0, 1.0, 1.0, 1.0};

GLfloat light1Pos[] = {0.0, 0.0, 100.0, 1.0};
GLfloat light1Amb[] = {1.0, 1.0, 0.0, 1.0};
GLfloat light1Diff[] = {1.0, 1.0, 0.0, 1.0};
GLfloat light1Spec[] = {1.0, 1.0, 0.0, 1.0};

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
void outputText(float x, float y, float r, float g, float b, void *font, const char *string);
void EffectLights();
void MangoPower();
void GuaranaPower();
// -------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  // Init OpenGL context
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(1024, 768);
  glutCreateWindow("Snake3D - FF Alpha 0.5");
  width = 1024;
  height = 768;
  // Init world
  try
  {
    //myStar = initWorld( argc, argv );
    mySnake = new Snake();
    myScenary = new Scenary();
    boundaries = myScenary->getBoundaries();
    currentFruit = new Fruit(0);
    specialFruit = new Fruit();
    currentFruit->Spawn(boundaries[0],
                        boundaries[1],
                        boundaries[2],
                        boundaries[3]);
    specialFruit->Spawn(boundaries[0],
                        boundaries[1],
                        boundaries[2],
                        boundaries[3]);
    fruitTimeout = std::chrono::high_resolution_clock::now();
    powerUps.push_back(false);
    powerUps.push_back(false);
    powerUps.push_back(false);
    myCamera.rotY(-90);
    myCamera.rotZ(-90);
    myCamera.upward(2.5);
    myCamera.forward(-15);

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
  glEnable(GL_LIGHT1);
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
void outputText(float x, float y, float r, float g, float b, void *font, const char *string)
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, width, height, 0.0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glColor3f(r, g, b);
  glRasterPos2f(x, y);
  glutBitmapString(font, (const unsigned char *)string);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
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
 
  glutWireCube (0.5);
 */
  EffectLights();
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
void EffectLights()
{
  if (mangoAct)
  {
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Spec);
    glLightfv(GL_LIGHT1, GL_SHININESS, light1Diff);
    glEnable(GL_LIGHT1);
  }
  else
  {
    glDisable(GL_LIGHT1);
  }

  if (guaranaAct)
  {
    glLightfv(GL_LIGHT2, GL_POSITION, light2Pos);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2Diff);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2Spec);
    glLightfv(GL_LIGHT2, GL_SHININESS, light2Diff);
    glEnable(GL_LIGHT2);
  }
  else
  {
    glDisable(GL_LIGHT2);
  }

  if (ancientAct)
  {
    glLightfv(GL_LIGHT3, GL_POSITION, light3Pos);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light3Diff);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light3Spec);
    glLightfv(GL_LIGHT3, GL_SHININESS, light3Diff);
    glEnable(GL_LIGHT3);
  }
  else
  {
    glDisable(GL_LIGHT3);
  }
}
// -------------------------------------------------------------------------
void MangoEffect()
{
  std::random_device rD;
  std::mt19937 gen(rD());
  std::uniform_int_distribution<int> dist(2, 5);
  pointMulti = dist(gen);
}
// -------------------------------------------------------------------------
void GuaranaEffect()
{
  if (guaranaAct)
    velocity = velocity * 5;
}
// -------------------------------------------------------------------------
void displayCbk()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glShadeModel(GL_SMOOTH);
  glCullFace(GL_BACK);
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
  GLfloat qaGrey[] = {0.74, 0.79, 0.85, 1.0};
  GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0};

  glMaterialfv(GL_FRONT, GL_AMBIENT, qaGrey);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGrey);
  glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  myScenary->DrawScenary();
  mySnake->Draw();
  if (mySnake->Die(dx, dy, boundaries) && play)
  {
    std::vector<float> reboot = mySnake->getHead();
    myCamera.move(Vector(-1 * reboot[0], -1 * reboot[1], 0));
    myCamera.rotY(-1 * (90 - rotA));
    rotA = 90;
    play = false;
    points = 0;
    delete (mySnake);
    mySnake = new Snake();
    dx = 1;
    dy = 0.0;
    velocity = 1;
  }
  if (mySnake->Eat(currentFruit->getCoordinates()))
  {
    points += currentFruit->getPoints() * pointMulti;
    mySnake->Grow();
    delete (currentFruit);
    currentFruit = new Fruit(0);
    currentFruit->Spawn(boundaries[0], boundaries[1], boundaries[2], boundaries[3]);
    velocity += 8;
  }
  else if (mySnake->Eat(specialFruit->getCoordinates()))
  {
    if (specialFruit->getPowerClass() == 1)
    {
      powerUps[0] = true;
    }
    else if (specialFruit->getPowerClass() == 2)
    {
      powerUps[1] = true;
    }
    else if (specialFruit->getPowerClass() == 3)
    {
      powerUps[2] = true;
    }
    points += specialFruit->getPoints() * pointMulti;
    velocity += 0.2;
    mySnake->Grow();
    fruitTimeout = std::chrono::high_resolution_clock::now();
    delete (specialFruit);
    specialFruit = new Fruit();
    specialFruit->Spawn(boundaries[0], boundaries[1], boundaries[2], boundaries[3]);
  }
  if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - fruitTimeout).count() >= 100000)
  {
    fruitTimeout = std::chrono::high_resolution_clock::now();
    delete (specialFruit);
    specialFruit = new Fruit();
    specialFruit->Spawn(boundaries[0], boundaries[1], boundaries[2], boundaries[3]);
  }
  else
  {
    specialFruit->Draw();
  }
  glMaterialfv(GL_FRONT, GL_AMBIENT, qaGrey);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGrey);
  glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  currentFruit->Draw();
  std::string msg = "Points: " + std::to_string(points);
  outputText(20.0, 20.0, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_18, msg.c_str());
  msg.clear();
  msg = "Power-Ups: ";
  if (mangoAct)
  {
    msg += "x" + std::to_string(pointMulti) + " points ";
  }
  else if (powerUps[0])
  {
    msg += " Mango Available ";
  }
  if (guaranaAct)
  {
    msg += " Speed Improved by Guarana! ";
  }
  else if (powerUps[1])
  {
    msg += " Guarana Available ";
  }
  if (powerUps[2])
  {
    msg += " Resurrection Available ";
  }
  outputText(20.0, 40.0, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_18, msg.c_str());

  // Finish
  glutSwapBuffers();
  glPopMatrix();
  glDisable(GL_CULL_FACE);
}

// -------------------------------------------------------------------------
void idleCbk()
{
  if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - fpsClock).count() >= 1000 - velocity)
  {
    if (play)
    {
      std::cout << "FPS: " << fpsCounter << std::endl;
      fpsClock = std::chrono::high_resolution_clock::now();
      fpsCounter = 0;
      std::cout << "Degrees: [" << rotA << "] Delta X: [" << dx << "] Delta Y: [" << dy << "]\n";
      myCamera.move(Vector(dx, dy, 0));
      mySnake->Move(dx, dy);
    }
  }
  else
  {
    fpsCounter++;
  }
  if (mangoAct)
  {
    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - mangoTime).count() >= 10)
    {
      mangoAct = false;
      pointMulti = 1;
    }
  }
  if (guaranaAct)
  {
    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - guaranaTime).count() >= 10)
    {
      guaranaAct = false;
      guaranaTime = std::chrono::high_resolution_clock::now();
    }
  }
  glutPostRedisplay();
}

// -------------------------------------------------------------------------
void resizeCbk(int w, int h)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  myCamera.setWindow(w, h);
  width = w;
  height = h;
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
      rotA -= 1;
    }
  }
  if (change == 1)
  {
    if ((rotA + 1) >= 360)
    {
      rotA = 0;
    }
    else
    {
      rotA += 1;
    }
  }
}
// -------------------------------------------------------------------------
void CalcDeltas()
{
  if (rotA <= 90)
  {
    dx = std::cos((90 - rotA) * _PI_180) * 2;
    dy = std::sin((90 - rotA) * _PI_180) * 2;
  }
  else if (rotA <= 180)
  {
    float intAngle = 90 - (180 - rotA);
    dx = std::cos(intAngle * _PI_180) * 2;
    dy = std::sin(intAngle * _PI_180) * -1 * 2;
  }
  else if (rotA <= 270)
  {
    dx = std::cos((270 - rotA) * _PI_180) * -1 * 2;
    dy = std::sin((270 - rotA) * _PI_180) * -1 * 2;
  }
  else if (rotA <= 360)
  {
    float intAngle = 90 - (360 - rotA);
    dx = std::cos(intAngle * _PI_180) * -1 * 2;
    dy = std::sin(intAngle * _PI_180) * 2;
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
    myCamera.strafe(0.3);
    RotateSnake(-1);
    CalcDeltas();
    myCamera.rotY(1);
    glutPostRedisplay();
  }
  break;
  case 'd':
  case 'D':
  {
    myCamera.strafe(-0.3);
    RotateSnake(1);
    CalcDeltas();
    myCamera.rotY(-1);
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
    play = true;
    glutPostRedisplay();
  }
  break;
  case '1':
  {
    mangoAct = powerUps[0] ? true : false;
    if (mangoAct)
    {
      powerUps[0] = false;
      MangoEffect();
      mangoTime = std::chrono::high_resolution_clock::now();
    }
    glutPostRedisplay();
  }
  break;
  case '2':
  {
    guaranaAct = powerUps[1] ? true : false;
    if (guaranaAct)
    {
      powerUps[1] = false;
      GuaranaEffect();
      guaranaTime = std::chrono::high_resolution_clock::now();
    }

    glutPostRedisplay();
  }
  break;
  case '3':
  {
    ancientAct = powerUps[2] ? true : false;
    powerUps[2] = false;
    glutPostRedisplay();
  }
  break;
  case 27: // ESC
    std::exit(0);
    break;
  default:
    break;
  } // end switch
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