// -------------------------------------------------------------------------
// @author Mateo Florido Sanchez (floridom@javeriana.edu.co)
// -------------------------------------------------------------------------

#include "Snake.h"
#include <GL/freeglut.h>
#include <cmath>
#include <fstream>
#include <map>
#include <sstream>

// -------------------------------------------------------------------------
Snake::
    Snake()
{
    this->m_Body.push_back(0);
    this->m_Body.push_back(0);
    this->m_Body.push_back(0);
    this->m_Body.push_back(1);

    this->m_Body.push_back(0);
    this->m_Body.push_back(2);

    this->m_Body.push_back(0);
    this->m_Body.push_back(3);

    this->m_Body.push_back(0);
    this->m_Body.push_back(4);
    firstRun = true;
}

// -------------------------------------------------------------------------
Snake::
    Snake(const std::string &fname)
{
}

// -------------------------------------------------------------------------
Snake::
    ~Snake()
{
}
// -------------------------------------------------------------------------
std::vector<float> Snake::
    Move(float dx, float dy)
{
    auto itBegin = this->m_Body.begin();
    this->m_Body.insert(itBegin, this->m_Body[1] + dy);
    itBegin = this->m_Body.begin();
    this->m_Body.insert(itBegin, this->m_Body[1] + dx);
    std::vector<float> response;
    response.push_back(this->m_Body[2]);
    response.push_back(this->m_Body[3]);
    this->m_Body.pop_back();
    this->m_Body.pop_back();

    return response;
}
// -------------------------------------------------------------------------
void Snake::
    Draw()
{
    GLfloat qaSnake[] = {0.20, 0.80, 0.20, 1.0};
    GLfloat qaWhite[] = {0.0, 1.0, 0.76, 1.0};
    GLfloat shininess[] = {60.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, qaSnake);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaSnake);
    glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glPushMatrix();
    for (int i = 0; i < this->m_Body.size(); i += 2)
    {
        glPushMatrix();
        glColor3fv(qaSnake);
        glTranslatef(this->m_Body[i], this->m_Body[i + 1], 0);
        glutSolidSphere(1, 20, 20);
        glPopMatrix();
    }
    glPopMatrix();
}
// -------------------------------------------------------------------------
bool Snake::
    Eat(std::vector<float> fruit)
{
    float distance = (this->m_Body[0] - fruit[0]) *
                         (this->m_Body[0] - fruit[0]) +
                     (this->m_Body[1] - fruit[1]) *
                         (this->m_Body[1] - fruit[1]);
    if (distance == 4)
    {
        this->Grow();
        return true;
    }
    else if (distance > 4)
        return false;
    else
    {
        this->Grow();
        return true;
    }
}
// -------------------------------------------------------------------------
bool Snake::
    Itself()
{
    float distance;
    for (int i = 4; i < this->m_Body.size(); i += 2)
    {
        distance = (this->m_Body[0] - this->m_Body[i]) *
                       (this->m_Body[0] - this->m_Body[i]) +
                   (this->m_Body[1] - this->m_Body[i + 1]) *
                       (this->m_Body[1] - this->m_Body[i + 1]);
        if (distance > 4)

            return false;
        else
        {
            return true;
        }
    }
    return false;
}
// -------------------------------------------------------------------------
void Snake::
    Grow()
{
    int sizeBody = this->m_Body.size();
    float lastX = this->m_Body[sizeBody - 2];
    sizeBody++;
    float lastY = this->m_Body[sizeBody - 2];
    lastX = this->m_Body[sizeBody - 2];
    sizeBody++;
    lastY = this->m_Body[sizeBody - 2];
    firstRun = false;
}
// -------------------------------------------------------------------------
std::vector<float> Snake::
    getHead()
{
    std::vector<float> response;
    response.push_back(this->m_Body[0]);
    response.push_back(this->m_Body[1]);
    return response;
}
// -------------------------------------------------------------------------
bool Snake::
    Die(float dx, float dy, std::vector<float> boundaries)
{
    float checkX, checkY;
    if (dx < 0)
    {
        checkX = this->m_Body[0] - 1;
        if (checkX <= boundaries[0])
            return true;
    }
    else if (dx > 0)
    {
        checkX = this->m_Body[0] + 1;
        if (checkX >= boundaries[1])
            return true;
    }
    if (dy < 0)
    {
        checkX = this->m_Body[1] - 1;
        if (checkX <= boundaries[2])
            return true;
    }
    else if (dx > 0)
    {
        checkX = this->m_Body[1] + 1;
        if (checkX >= boundaries[3])
            return true;
    }
    if (!firstRun)
        return (Itself());
    else
    {
        return false;
    }
}

// eof - Snake.cxx
