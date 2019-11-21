// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------
#ifndef __Scenary__h__
#define __Scenary__h__

#include "Vector.h"
#include "Mesh.h"
#include <chrono>

/**
 */
class Scenary
{

public:
    //! Memory management
    //@{
    Scenary();
    Scenary(const std::string &fname);
    virtual ~Scenary();
    //@}

    //! Scenary Initialization
    //@{
    void CreateLab(int offset);
    void DrawScenary();

    //@}
protected:
    std::string m_Name;
    int m_CurrentLevel;
    GLuint index;
    GLubyte lists[10];
    std::vector<float> m_Boundaries;
};

#endif // __Scenary__h__

// eof - Scenary.h
