// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
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
    std::uniform_int_distribution<> dist(0, 3);
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
    std::uniform_real_distribution<float> distX(xmin+0.5, xmax-0.5);
    std::uniform_real_distribution<float> distY(ymin+0.5, ymax-0.5);
    this->m_Coordinates.push_back(distX(gen));
    this->m_Coordinates.push_back(distY(gen));
}

// -------------------------------------------------------------------------
void Fruit::
    Draw()
{
    glPushMatrix();

    glPopMatrix();
}

// eof - Fruit.cxx
