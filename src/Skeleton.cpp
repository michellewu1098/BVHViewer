#include "include/Skeleton.h"
#include <ngl/VAOFactory.h>
#include <ngl/Util.h>

//-------------------------------------------------------------------------------

Skeleton::Skeleton()
{
  m_root = nullptr;
  m_numJoints = 0;
  m_numDOF = 0;
}

//-------------------------------------------------------------------------------

bool Skeleton::Init( std::istream &_str )
{
  if( Load( _str ) )
  {
    return true;
  }
  else
  {
    std::cerr << "ERROR: When loading file\n";
    return false;
  }
}

//-------------------------------------------------------------------------------

void Skeleton::PreProcessMotionData( std::vector< std::shared_ptr< Frame > > _frames )
{
  m_root->initFrameDataStorage( _frames.size() );

  for( auto& frame : _frames )
  {
    ExtractDataFromFrame( m_root, frame );
  }

  CreateVAO();
}

//-------------------------------------------------------------------------------

void Skeleton::CreateVAO()
{
  m_vao.reset( ngl::VAOFactory::createVAO( "simpleIndexVAO", GL_LINES ) );
  UpdateVAO( 0 );
}

//-------------------------------------------------------------------------------

void Skeleton::UpdateVAO( const unsigned int& _currentFrame )
{
  std::vector< ngl::Vec3 > verts;
  std::vector< GLshort > indices;

  ExtractVerts( m_root, verts, indices, 0, _currentFrame );

  m_vao->bind();
  m_vao->setData( ngl::SimpleIndexVAO::VertexData( verts.size() * sizeof( ngl::Vec3 ),
                                                   verts[ 0 ].m_x,
                                                   indices.size() * sizeof( indices[ 0 ] ),
                                                   &indices[ 0 ],
                                                   GL_UNSIGNED_SHORT,
                                                   GL_DYNAMIC_DRAW ) );

  m_vao->setVertexAttributePointer( 0, 3, GL_FLOAT, 0, 0 );
  m_vao->setNumIndices( indices.size() );
  m_vao->unbind();
}

//-------------------------------------------------------------------------------

bool Skeleton::Load( std::istream &_str )
{
  if( m_numJoints > 0 )
  {
    m_numJoints = 0;
    m_root = nullptr;
    m_numDOF = 0;
  }

  std::string line;
  m_separators = boost::char_separator< char >( " \t\r\n" );

  while( _str.good() )
  {
    std::getline( _str, line );
    if( line.size() != 0 ) // If line not empty
    {
      Tokenizer token( line, m_separators );
      Tokenizer::iterator firstWord = token.begin();

      if( *firstWord == "HIERARCHY" )
      {
        if( !LoadHierarchy( _str ) )
        {
          std::cerr << "ERROR: Loading hierarchy data failed\n";
          return false;
        }
       return true;
      }
    }
  }
  return true;
}

//-------------------------------------------------------------------------------

bool Skeleton::LoadHierarchy( std::istream& _str )
{
  std::string line;

  while( _str.good() )
  {
    std::getline( _str, line );
    if( line.size() != 0 ) // If line not empty
    {
      Tokenizer token( line, m_separators );
      auto firstWord = token.begin();

      if( *firstWord == "ROOT" )
      {
        m_root = LoadJoint( _str, firstWord, nullptr );
        if( m_root != nullptr )
        {
          m_numJoints += 1;
          return true;
        }
      }
    }
  }
  return false;
}

//-------------------------------------------------------------------------------

std::shared_ptr< Joint > Skeleton::LoadJoint( std::istream& _str, Tokenizer::iterator& _firstWord, std::shared_ptr< Joint > _parent )
{
  std::shared_ptr< Joint > currentJoint = std::make_shared< Joint >();

  ++_firstWord;
  currentJoint->m_name = *_firstWord;
  currentJoint->m_transform.identity();
  currentJoint->m_parent = _parent;

  std::string line;

  // Parse joint data
  while( _str.good() )
  {
    std::getline( _str, line );
    if( line.size() != 0 )
    {
      Tokenizer token( line, m_separators );
      for( Tokenizer::iterator t = token.begin(); t != token.end(); ++t )
      {
        if( *t == "}" )
        {
          return currentJoint;
        }
        else if( *t == "OFFSET" )
        {
          currentJoint->m_offset[ 0 ] = boost::lexical_cast< float >( *++t );
          currentJoint->m_offset[ 1 ] = boost::lexical_cast< float >( *++t );
          currentJoint->m_offset[ 2 ] = boost::lexical_cast< float >( *++t );
        }
        else if( *t == "CHANNELS" )
        {
          currentJoint->m_numChannels = boost::lexical_cast< float >( *++t );
          std::string pos;

          if( currentJoint->m_numChannels == 6 ) // Root joint
          {
            currentJoint->m_id = 0;
            for( unsigned int i = 0; i < 3; ++i )
            {
              pos = *++t;
              if( pos == "Xposition" ) { currentJoint->m_translationOrder[ i ] = 0; }
              if( pos == "Yposition" ) { currentJoint->m_translationOrder[ i ] = 1; }
              if( pos == "Zposition" ) { currentJoint->m_translationOrder[ i ] = 2; }
            }

            for( unsigned int i = 0; i < 3; ++i )
            {
              pos = *++t;
              if( pos == "Xrotation" ) { currentJoint->m_rotationOrder[ i ] = 0; }
              if( pos == "Yrotation" ) { currentJoint->m_rotationOrder[ i ] = 1; }
              if( pos == "Zrotation" ) { currentJoint->m_rotationOrder[ i ] = 2; }
            }

            m_numDOF += 6;
          }
          else if( currentJoint->m_numChannels == 3 )
          {
            //m_joints.push_back( currentJoint );
            m_numJoints += 1;
            currentJoint->m_id = m_numJoints;

            for( unsigned int i = 0; i < 3; ++i )
            {
              pos = *++t;
              if( pos == "Xrotation" ) { currentJoint->m_rotationOrder[ i ] = 0; }
              if( pos == "Yrotation" ) { currentJoint->m_rotationOrder[ i ] = 1; }
              if( pos == "Zrotation" ) { currentJoint->m_rotationOrder[ i ] = 2; }
            }

            m_numDOF += 3;
          }
          else
          {
            std::cerr << "ERROR: Something wrong with number of channels\n";
          }
        }
        else if( *t == "JOINT" )
        {
          Tokenizer token( line, m_separators );
          auto firstWord = token.begin();
          std::shared_ptr< Joint > tmpJoint = LoadJoint( _str, firstWord, currentJoint );
          currentJoint->m_children.push_back( tmpJoint );
        }
        else if( *t == "End" )
        {
          std::shared_ptr< Joint > endJoint = std::make_shared< Joint >();;
          endJoint->m_numChannels = 0;
          endJoint->m_name = "EndSite";
          endJoint->m_transform.identity();
          endJoint->m_parent = currentJoint;
          currentJoint->m_children.push_back( endJoint );

          std::getline( _str, line );
          std::getline( _str, line );

          Tokenizer token( line, m_separators );
          for( Tokenizer::iterator t = token.begin(); t != token.end(); ++t )
          {
            if( *t == "OFFSET" )
            {
              endJoint->m_offset[ 0 ] = boost::lexical_cast< float >( *++t );
              endJoint->m_offset[ 1 ] = boost::lexical_cast< float >( *++t );
              endJoint->m_offset[ 2 ] = boost::lexical_cast< float >( *++t );
            }
          }

          std::getline( _str, line ); // Skip the "}" after End Site
        }
      }
    }
  }

  return nullptr;
}

//-------------------------------------------------------------------------------

void Skeleton::Draw()
{
  m_vao->bind();
  //m_vao->draw();
  glDrawElements( GL_LINES, m_vao->numIndices(), GL_UNSIGNED_SHORT, ( GLvoid* ) 0 );
  glPointSize( 5.f );
  glDrawElements( GL_POINTS, m_vao->numIndices(), GL_UNSIGNED_SHORT, ( GLvoid* ) 0 );

  m_vao->unbind();
}

//-------------------------------------------------------------------------------

ngl::Vec3 Skeleton::GetSkeletonVertices( const std::shared_ptr< Joint > _joint, const unsigned int &_frame )
{
  return _joint->m_frameDataStorage[ _frame ];
}

//-------------------------------------------------------------------------------

void Skeleton::Update( const unsigned int& _currentFrame )
{
  UpdateVAO( _currentFrame );
}

//-------------------------------------------------------------------------------

void Skeleton::ExtractVerts( std::shared_ptr<Joint> _joint, std::vector<ngl::Vec3> &_verts, std::vector<GLshort> &_indices, GLshort _parentIndex, const unsigned int& _currentFrame )
{
  _verts.push_back( GetSkeletonVertices( _joint, _currentFrame ) );

  GLshort currentIndex = _verts.size() - 1;
  if( _parentIndex != currentIndex )
  {
    _indices.push_back( _parentIndex );
    _indices.push_back( currentIndex );
  }

  for( auto& child : _joint->m_children )
  {
    ExtractVerts( child, _verts, _indices, currentIndex, _currentFrame );
  }
}

//-------------------------------------------------------------------------------

void Skeleton::ExtractDataFromFrame( std::shared_ptr< Joint > _joint, std::shared_ptr<Frame> _frame )
{
  if( m_numJoints != _frame->GetNumOfJoints() )
  {
    return;
  }

  ngl::Mat4 translate;
  translate.translate( _joint->m_offset.m_x, _joint->m_offset.m_y, _joint->m_offset.m_z );

  if( _joint == m_root )
  {
    ngl::Mat4 rootTranslate;
    rootTranslate.translate( _frame->GetRootTranslation().m_x,
                             _frame->GetRootTranslation().m_y,
                             _frame->GetRootTranslation().m_z );
    translate *= rootTranslate;
  }

  ngl::Mat4 currentOrientM;
  if( _joint->m_children.size() != 0)
  {
    currentOrientM = _frame->GetJointRotation( _joint->m_id );
  }

  _joint->m_transform = translate * currentOrientM;

  if( _joint->m_parent != nullptr )
  {
    _joint->m_transform = _joint->m_parent->m_transform * _joint->m_transform;
  }

  ngl::Vec3 vertex = ngl::Vec3( _joint->m_transform.m_30, _joint->m_transform.m_31, _joint->m_transform.m_32 );
  _joint->m_frameDataStorage[ _frame->GetFrameID() ] = vertex;

  for( auto& child : _joint->m_children )
  {
    ExtractDataFromFrame( child, _frame );
  }
}

//-------------------------------------------------------------------------------

