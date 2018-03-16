#include "include/Motion.h"

//-------------------------------------------------------------------------------

Motion::Motion()
{
  m_numDOF = 0;
  m_numFrames = 0;
  m_frameRate = 0.f;
  m_numJoints = 0;
}

//-------------------------------------------------------------------------------

Motion::~Motion()
{
  m_frames.clear();
}

//-------------------------------------------------------------------------------

void Motion::DeallocateFrameStorage()
{
  m_frames.clear();
  m_numFrames = 0;
  m_numJoints = 0;
}

//-------------------------------------------------------------------------------

bool Motion::Load( std::istream& _str, Skeleton* _skeleton )
{
  DeallocateFrameStorage();

  std::string line;
  m_separators = boost::char_separator< char >( " \t\r\n" );

  while( _str.good() )
  {
    std::getline( _str, line );
    if( line.size() != 0 ) // If line not empty
    {
      Tokenizer token( line, m_separators );
      auto firstWord = token.begin();

      if( *firstWord == "MOTION" )
      {
        // Retrieve number of frames
        std::getline( _str, line );
        if( line.size() != 0 )
        {
          Tokenizer token( line, m_separators );
          Tokenizer::iterator tok = token.begin();
          if( *tok == "Frames:" )
          {
            m_numFrames = boost::lexical_cast< unsigned int >( *++tok );
          }
        }

        // Retrieve frame time
        std::getline( _str, line );
        if( line.size() != 0 )
        {
          Tokenizer token( line, m_separators );
          Tokenizer::iterator tok = token.begin();
          if( *tok == "Frame")
          {
            ++tok;
            m_frameRate = boost::lexical_cast< float >( *++tok ) * 500;
          }
        }

        unsigned int nDOF = _skeleton->GetNumDOF();

        m_numJoints = _skeleton->GetNumJoints();
        AllocateFrameStorage();

        float* motionData = new float[ nDOF ];

        for( auto& frame : m_frames )
        {
          std::getline( _str, line );
          if( line.size() != 0 )
          {
            Tokenizer token( line, m_separators );
            Tokenizer::iterator tok = token.begin();

            for( unsigned int channel = 0; channel < nDOF; channel++ )
            {
              motionData[ channel ] = boost::lexical_cast< float >( *tok++ );
            }

            ExtractMotionData( _skeleton->GetRootJoint(), motionData, frame );
          }
        }
      }
    }
  }

  return true;
}

//-------------------------------------------------------------------------------

void Motion::AllocateFrameStorage()
{
  std::shared_ptr< Frame > frame;
  for( unsigned int i = 0; i < m_numFrames; i++ )
  {
    frame = std::make_shared< Frame >( i );
    frame->SetNumOfJoints( m_numJoints );
    m_frames.push_back( frame );
  }
}

//-------------------------------------------------------------------------------

void Motion::ExtractMotionData( const std::shared_ptr<Joint> &_joint, float *_motionData, std::shared_ptr<Frame> _frame )
{
  ngl::Mat4 rotX, rotY, rotZ, currentOrientM;

  if( _joint->m_parent == nullptr )
  {
    ngl::Vec3 rootLocalTranslation;
    float scaleFactor = 1.f;

    rootLocalTranslation[ _joint->m_translationOrder[ 0 ] ] = _motionData[ 0 ] / scaleFactor;
    rootLocalTranslation[ _joint->m_translationOrder[ 1 ] ] = _motionData[ 1 ] / scaleFactor;
    rootLocalTranslation[ _joint->m_translationOrder[ 2 ] ] = _motionData[ 2 ] / scaleFactor;
    _frame->SetRootTranslation( rootLocalTranslation );

    unsigned int i, j;
    for( i = 0, j = 3; i < 3; i++, j++ )
    {
      switch( _joint->m_rotationOrder[ i ])
      {
        case 0:
        {
          rotX.rotateX( _motionData[ j ] );
          currentOrientM *= rotX;
          break;
        }

        case 1:
        {
          rotY.rotateY( _motionData[ j ] );
          currentOrientM *= rotY;
          break;
        }

        case 2:
        {
          rotZ.rotateZ( _motionData[ j ] );
          currentOrientM *= rotZ;
          break;
        }
      }
    }

    _frame->SetJointRotation( 0, currentOrientM );
  }
  else if( _joint->m_children.size() != 0)
  {
    unsigned int i, j;
    for( i = 0, j = 6; i < 3; i++, j++ )
    {
      switch( _joint->m_rotationOrder[ i ])
      {
        case 0:
        {
          rotX.rotateX( _motionData[ ( _joint->m_id - 1 ) * 3 + j ] );
          currentOrientM *= rotX;
          break;
        }

        case 1:
        {
          rotY.rotateY( _motionData[ ( _joint->m_id - 1 ) * 3 + j ] );
          currentOrientM *= rotY;
          break;
        }

        case 2:
        {
          rotZ.rotateZ( _motionData[ ( _joint->m_id - 1 ) * 3 + j ] );
          currentOrientM *= rotZ;
          break;
        }
      }
    }

    _frame->SetJointRotation( _joint->m_id, currentOrientM );
  }

  for( auto& child : _joint->m_children )
  {
    ExtractMotionData( child, _motionData, _frame );
  }
}

//-------------------------------------------------------------------------------
