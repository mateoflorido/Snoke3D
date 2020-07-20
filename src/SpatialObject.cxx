// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------

#include "SpatialObject.h"
#include <cmath>
#include <fstream>
#include <map>
#include <sstream>

// -------------------------------------------------------------------------
SpatialObject::
SpatialObject( )
  : m_Mesh( nullptr ),
    m_Path( nullptr ),
    m_CurrentAngle( 0 ),
    m_Animating( false )
{
  this->_createPath( );
}

// -------------------------------------------------------------------------
SpatialObject::
SpatialObject( const std::string& fname )
  : m_Mesh( nullptr ),
    m_Path( nullptr ),
    m_CurrentAngle( 0 ),
    m_Animating( false )
{
  // Open file and put its contents into a string buffer
  if( this->m_Mesh != nullptr )
    delete this->m_Mesh;
  this->m_Mesh = new Mesh( fname );
  this->m_Scale = 2;
  /*
  std::ifstream in( fname.c_str( ) );
  if( !in )
  {
    in.close( );
    throw std::runtime_error(
      std::string( "Error: Could not open \"" ) + fname + "\""
      );
  } // end if
  std::istringstream buffer(
    std::string(
      ( std::istreambuf_iterator< char >( in ) ),
      std::istreambuf_iterator< char >( )
      )
    );
  in.close( );
  std::cout << "Loaded info from File - Continue to Classify \n";
  // Read file
  buffer >> this;
  */
}

// -------------------------------------------------------------------------
SpatialObject::
~SpatialObject( )
{
  if( this->m_Mesh != nullptr )
    delete this->m_Mesh;
  if( this->m_Path != nullptr )
    delete this->m_Path;
  for( SpatialObject* c: this->m_Children )
    delete c;
  this->m_Children.clear( );
}

// -------------------------------------------------------------------------
Mesh* SpatialObject::
getMesh( )
{
  return( this->m_Mesh );
}

// -------------------------------------------------------------------------
const Mesh* SpatialObject::
getMesh( ) const
{
  return( this->m_Mesh );
}

// -------------------------------------------------------------------------
void SpatialObject::
addChild( SpatialObject* o )
{
  this->m_Children.push_back( o );
}

// -------------------------------------------------------------------------
unsigned long SpatialObject::
getNumberOfChildren( ) const
{
  return( this->m_Children.size( ) );
}

// -------------------------------------------------------------------------
SpatialObject* SpatialObject::
getChild( unsigned long i )
{
  return( this->m_Children[ i ] );
}

// -------------------------------------------------------------------------
const SpatialObject* SpatialObject::
getChild( unsigned long i ) const
{
  return( this->m_Children[ i ] );
}

// -------------------------------------------------------------------------
const std::string& SpatialObject::
getName( ) const
{
  return( this->m_Name );
}

// -------------------------------------------------------------------------
const float& SpatialObject::
getScale( ) const
{
  return( this->m_Scale );
}

// -------------------------------------------------------------------------
void SpatialObject::
setPath( float r1, float r2, float nx, float ny, float nz )
{
  this->m_Radius1 = r1;
  this->m_Radius2 = r2;
  this->m_Normal[ 0 ] = nx;
  this->m_Normal[ 1 ] = ny;
  this->m_Normal[ 2 ] = nz;
  this->m_Normal.normalize( );
}

// -------------------------------------------------------------------------
void SpatialObject::
startAnimation( )
{
  this->m_Animating = true;
  this->m_StartAnimation = std::chrono::high_resolution_clock::now( );
  for( SpatialObject* child: this->m_Children )
    child->startAnimation( );
}

// -------------------------------------------------------------------------
void SpatialObject::
stopAnimation( )
{
  this->m_Animating = false;
  for( SpatialObject* child: this->m_Children )
    child->stopAnimation( );
}

// -------------------------------------------------------------------------
void SpatialObject::
drawInOpenGLContext( GLenum mode )
{
  if( this->m_Mesh == nullptr )
    return;

  // Save call matrix
  glPushMatrix( );

  // Show path
  glPushMatrix( );
  glScalef( this->m_Radius1, this->m_Radius2, 1 );
  //this->m_Path->drawInOpenGLContext( GL_LINE_LOOP );
  glPopMatrix( );

  // Show spatial body
  if( this->m_Animating && this->m_Frequency > 0 )
  {
    // Compute ellapsed milliseconds since aninamtion has started
    double s =
      std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::high_resolution_clock::now( ) - this->m_StartAnimation
        ).count( );
    this->m_CurrentAngle = 2.0 * _PI * s / ( this->m_Frequency * 1000.0 );
  } // end if
  glTranslatef(
    this->m_Radius1 * std::cos( this->m_CurrentAngle ),
    this->m_Radius2 * std::sin( this->m_CurrentAngle ),
    0
    );
  glPushMatrix( );
  glScalef( this->m_Scale, this->m_Scale, this->m_Scale );
  this->m_Mesh->drawInOpenGLContext( mode );
  glPopMatrix( );

  /* Show children
  for( SpatialObject* child: this->m_Children )
    child->drawInOpenGLContext( mode );
*/
  // Get call matrix
  glPopMatrix( );
}

// -------------------------------------------------------------------------
void SpatialObject::
_createPath( )
{
  if( this->m_Path != nullptr )
    delete this->m_Path;
  this->m_Path = new Mesh( );

  unsigned int nSamples = 100;
  std::vector< unsigned int > face;
  for( unsigned int i = 0; i < nSamples; ++i )
  {
    float a = 2.0 * _PI * float( i ) / float( nSamples );
    this->m_Path->addPoint( std::cos( a ), std::sin( a ), 0 );
    face.push_back( i + 1 );
  } // end for
    face.push_back( 1 );
  this->m_Path->addFace( face );
}

// -------------------------------------------------------------------------
void SpatialObject::
_strIn( std::istream& in )
{
  typedef std::map< char, std::string > _TMap;

  // Read data for this spatial object
  std::string line;
  std::getline( in, line );
  _TMap data;
  while( line.substr( 0, 2 ) != "--" )
  {
    std::istringstream d( line );
    char data_type;
    d >> data_type;

    std::string data_value;
    std::string v;
    d >> data_value;
    while( !d.eof( ) )
    {
      std::string v;
      d >> v;
      data_value += " " + v;
    } // end while
    data[ data_type ] = data_value;
    std::getline( in, line );
  } // end while

  // Check name
  _TMap::const_iterator dIt = data.find( 'N' );
  if( dIt == data.end( ) )
    throw std::runtime_error( "Field \"N\" is required." );
  this->m_Name = dIt->second;

  // Check path
  dIt = data.find( 'P' );
  if( dIt == data.end( ) )
    throw std::runtime_error( "Field \"P\" is required." );
  std::istringstream path_str( dIt->second );
  std::vector< float > path;
  while( !path_str.eof( ) )
  {
    path.push_back( 0 );
    path_str >> path.back( );
  } // end while
  if( path.size( ) == 4 )
    this->setPath( path[ 0 ], path[ 0 ], path[ 1 ], path[ 2 ], path[ 3 ] );
  else if( path.size( ) == 5 )
    this->setPath( path[ 0 ], path[ 1 ], path[ 2 ], path[ 3 ], path[ 4 ] );
  else
    throw std::runtime_error( "Malformed path." );

  // Check base model
  dIt = data.find( 'M' );
  if( dIt == data.end( ) )
    throw std::runtime_error( "Field \"M\" is required." );
  if( this->m_Mesh != nullptr )
    delete this->m_Mesh;
  this->m_Mesh = new Mesh( dIt->second );

  // Check color
  dIt = data.find( 'C' );
  float r = 1, g = 1, b = 1;
  if( dIt != data.end( ) )
  {
    std::istringstream d( dIt->second );
    d >> r >> g >> b;
  } // end if
  this->m_Mesh->setColor( r, g, b );

  // Check scale
  dIt = data.find( 'S' );
  if( dIt != data.end( ) )
  {
    std::istringstream d( dIt->second );
    d >> this->m_Scale;
  }
  else
    this->m_Scale = 1;

  // Check frequency
  dIt = data.find( 'F' );
  if( dIt != data.end( ) )
  {
    std::istringstream d( dIt->second );
    d >> this->m_Frequency;
  }
  else
    this->m_Frequency = 0;

  // Check recursion
  dIt = data.find( 'D' );
  if( dIt != data.end( ) )
  {
    std::istringstream d( dIt->second );
    unsigned int nRecs;
    d >> nRecs;
    for( unsigned int i = 0; i < nRecs; ++i )
    {
      SpatialObject* child = new SpatialObject( );
      in >> child;
      this->addChild( child );
    } // end for
  } // end if
}

// -------------------------------------------------------------------------
void SpatialObject::
_strOut( std::ostream& out ) const
{
}

// eof - SpatialObject.cxx
