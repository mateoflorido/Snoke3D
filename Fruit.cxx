// -------------------------------------------------------------------------
// @author Mateo Florido Sanchez (floridom@javeriana.edu.co)
// -------------------------------------------------------------------------

#include "Fruit.h"
#include <GL/freeglut.h>
#include <cmath>
#include <fstream>
#include <map>
#include <sstream>
#include <random>

// -------------------------------------------------------------------------
Fruit::
    Fruit()
{
    std::random_device rD;
    std::mt19937 gen(rD());
    std::uniform_int_distribution<> dist(1, 3);
    this->powerClass = dist(gen);
    if (this->powerClass == 0)
        this->points = 10;
    else if (this->powerClass == 1)
        this->points = 50;
    else if (this->powerClass == 2)
        this->points = 80;
    else if (this->powerClass == 3)
        this->points = 100;
}
// -------------------------------------------------------------------------
Fruit::
    Fruit(const int type)
{
    this->powerClass = type;
    if (this->powerClass == 0)
        this->points = 10;
    else if (this->powerClass == 1)
        this->points = 50;
    else if (this->powerClass == 2)
        this->points = 80;
    else if (this->powerClass == 3)
        this->points = 100;
}
// -------------------------------------------------------------------------
Fruit::
    ~Fruit()
{
}
// -------------------------------------------------------------------------
void Fruit::
    Spawn(float xmin, float xmax, float ymin, float ymax)
{
    std::random_device rD;
    std::mt19937 gen(rD());
    std::uniform_real_distribution<float> distX(xmin + 2, xmax - 2);
    std::uniform_real_distribution<float> distY(ymin + 2, ymax - 2);
    this->m_Coordinates.push_back(distX(gen));
    this->m_Coordinates.push_back(distY(gen));
}

// -------------------------------------------------------------------------
void Fruit::
    Draw()
{
    if (this->powerClass == 0)
    {
        GLfloat qaFruit[] = {0.0, 0.50, 1.0, 1.0};
        glColor4fv(qaFruit);
        glMaterialfv(GL_FRONT, GL_AMBIENT, qaFruit);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, qaFruit);
    }
    else if (this->powerClass == 1)
    {
        GLfloat qaFruit[] = {1.0, 0.77, 0.0, 1.0};
        glColor4fv(qaFruit);
        glMaterialfv(GL_FRONT, GL_AMBIENT, qaFruit);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, qaFruit);
    }
    else if (this->powerClass == 2)
    {
        GLfloat qaFruit[] = {0.61, 0.02, 0.02, 1.0};
        glColor4fv(qaFruit);
        glMaterialfv(GL_FRONT, GL_AMBIENT, qaFruit);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, qaFruit);
    }
    else if (this->powerClass == 3)
    {
        GLfloat qaFruit[] = {0.51, 0.39, 0.0, 1.0};
        glColor4fv(qaFruit);
        glMaterialfv(GL_FRONT, GL_AMBIENT, qaFruit);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, qaFruit);
    }
    else
        GLfloat qaFruit[] = {0.51, 0.39, 0.0, 1.0};

    GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess[] = {60.0};

    glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glPushMatrix();

    glTranslatef(this->m_Coordinates[0], this->m_Coordinates[1], 0);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
}
// -------------------------------------------------------------------------
std::vector<float> Fruit::
    getCoordinates()
{
    return this->m_Coordinates;
}
// -------------------------------------------------------------------------
int Fruit::
    getPoints()
{
    return this->points;
}
// -------------------------------------------------------------------------
int Fruit::
    getPowerClass()
{
    return this->powerClass;
}

// eof - Fruit.cxx
