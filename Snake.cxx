// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
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
        if (i == 0)
        {
            glColor3f(1.0, 0.0, 0.0);
        }
        else
        {
            glColor3fv(qaSnake);
        }

        glTranslatef(this->m_Body[i], this->m_Body[i + 1], 0);
        glutSolidSphere(0.5, 20, 20);
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
                         (this->m_Body[0] - fruit[0]);
    if (distance == 4)
        return true;
    else if (distance > 4)
        return false;
    else
    {
        return true;
    }
}

// eof - Snake.cxx
