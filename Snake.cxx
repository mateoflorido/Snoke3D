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
            glColor3f(1.0, 1.0, 1.0);
        }

        glTranslatef(this->m_Body[i], this->m_Body[i + 1], 0);
        glutSolidSphere(0.5, 20, 20);
        glPopMatrix();
    }
    glPopMatrix();
}

// eof - Snake.cxx
