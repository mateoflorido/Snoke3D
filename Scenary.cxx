// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
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
        glTranslatef(0,0,1.5);
        glScalef(5.0,5.0,1.5);
        glutSolidCube(1);
        glPopMatrix();
        
        
        //LeftWall
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(-1.0,0.0,0.0);
        glScalef(1.0,10.0,5.0);
        glutSolidCube(1);
        glPopMatrix();
    glEndList();        
        
}
// -------------------------------------------------------------------------
void Scenary::
DrawScenary( )
{
    glCallList(this->index+this->m_CurrentLevel);
        
}
// eof - Scenary.cxx
