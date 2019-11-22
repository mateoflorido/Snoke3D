// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------
#ifndef __Snake__h__
#define __Snake__h__

#include "Vector.h"
#include "Mesh.h"
#include <chrono>

/**
 */
class Snake
{

public:
    //! Memory management
    //@{
    Snake();
    Snake(const std::string &fname);
    virtual ~Snake();
    //@}

    //! Snake Movement
    //@{
    std::vector<float> Move(float dx, float dy);
    void Draw();
    bool Eat(std::vector<float> fruit);
    void Grow();
    //@}
protected:
    std::string m_Name;
    int m_Length;
    std::vector<float> m_Body; 
};

#endif // __Snake__h__

// eof - Snake.h
