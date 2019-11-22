// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------
#ifndef __Fruit__h__
#define __Fruit__h__

#include "Vector.h"
#include <string>
#include <chrono>
#include <vector>

/**
 */
class Fruit
{

public:
    //! Memory management
    //@{
    Fruit();
    Fruit(const int type);
    virtual ~Fruit();
    //@}

    //! Fruit Movement
    //@{
    void Draw();
    void Spawn(float xmin, float xmax, float ymin, float ymax);
    std::vector<float> getCoordinates();
    int getPoints();
    int getPowerClass();
    //@}
protected:
    std::string m_Name;
    int powerClass;
    int points;
    std::vector<float> m_Coordinates;
};

#endif // __Fruit__h__

// eof - Fruit.h
