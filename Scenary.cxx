// -------------------------------------------------------------------------
// @author Mateo Florido Sanchez (floridom@javeriana.edu.co)
// -------------------------------------------------------------------------

#include "Scenary.h"
#include <GL/freeglut.h>
#include <cmath>
#include <fstream>
#include <map>
#include <sstream>

// -------------------------------------------------------------------------
Scenary::
Scenary( )
{
  this->index = glGenLists(1);
  this->m_CurrentLevel = 0;
  CreateLab( 0 );

}

// -------------------------------------------------------------------------
Scenary::
Scenary( const std::string& fname )
{
}

// -------------------------------------------------------------------------
Scenary::
~Scenary( )
{
}
// -------------------------------------------------------------------------
void Scenary::
CreateLab(int offset)
{
    glNewList(this->index + offset, GL_COMPILE);
        //Floor
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(0,0.0,-1.0);
        glScalef(100.0,100.0,1.0);
        glutSolidCube(1);
        glPopMatrix();
        
        //LeftWall
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(-50.0,0.0,2.0);
        glScalef(1.0,100.0,10.0);
        glutSolidCube(1);
        glPopMatrix();
        
        //RightWall
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(50.0,0.0,2.0);
        glScalef(1.0,100.0,10.0);
        glutSolidCube(1);
        glPopMatrix();

        //TopWall
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(0.0,50.0,2.0);
        glScalef(100.0,1.0,10.0);
        glutSolidCube(1);
        glPopMatrix();

        //BottomWall
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(0.0,-50.0,2.0);
        glScalef(100.0,1.0,10.0);
        glutSolidCube(1);
        glPopMatrix();

        //Ceiling
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(0,0.0,9.0);
        glScalef(100.0,100.0,1.0);
        glutSolidCube(1);
        glPopMatrix();

    glEndList();
    this->m_Boundaries.push_back(-50.0);
    this->m_Boundaries.push_back(50.0);
    this->m_Boundaries.push_back(-50.0);
    this->m_Boundaries.push_back(50.0);  
        
}
// -------------------------------------------------------------------------
void Scenary::
DrawScenary( )
{
    glCallList(this->index+this->m_CurrentLevel);
        
}
// -------------------------------------------------------------------------
std::vector<float> Scenary::
getBoundaries()
{
    return this->m_Boundaries;
}
// -------------------------------------------------------------------------
bool Scenary::
CheckIntegrity(float x, float y)
{
    if( x > this->m_Boundaries[0+this->m_CurrentLevel])
        if( x < this->m_Boundaries[1+this->m_CurrentLevel])
            if(y > this->m_Boundaries[2+this->m_CurrentLevel])
               if(y < this->m_Boundaries[3+this->m_CurrentLevel])
                    return true;
    return false;
}
// eof - Scenary.cxx