// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------
#ifndef __Vector__h__
#define __Vector__h__

#define _PI 3.1415926535897932384626433832795
#define _PI_180 ( _PI / 180.0 )

/**
 */
class Vector
{
public:
  //! Memory management
  //@{
  Vector( const float& x = 0, const float& y = 0, const float& z = 0 );
  Vector( float* p );
  Vector( double* p );
  Vector( const Vector& r );
  Vector& operator=( const Vector& r );
  virtual ~Vector( );
  //@}

  //! Random acces
  //@{
  float& operator[]( const unsigned int& i );
  const float& operator[]( const unsigned int& i ) const;
  //@}

  //! Base arithmetic
  //@{
  Vector operator+( const Vector& r ) const;
  Vector& operator+=( const Vector& r );

  Vector operator-( const Vector& r ) const;
  Vector& operator-=( const Vector& r );
  //@}

  //! Dot product
  //@{
  float operator/( const Vector& r ) const;
  //@}

  //! Cross product
  //@{
  Vector operator*( const Vector& r ) const;
  Vector& operator*=( const Vector& r );
  //@}

  //! Scalar product
  //@{
  Vector operator*( const float& r ) const;
  Vector operator*( const double& r ) const;

  Vector& operator*=( const float& r );
  Vector& operator*=( const double& r );

  Vector operator/( const float& r ) const;
  Vector operator/( const double& r ) const;

  Vector& operator/=( const float& r );
  Vector& operator/=( const double& r );
  //@}

  //! Normalization
  //@{
  float getNorm( ) const;
  void normalize( );
  //@}

protected:
  float m_V[ 3 ];
};

#endif // __Vector__h__

// eof - Vector.h
