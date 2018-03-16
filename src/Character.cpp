#include "include/Character.h"
#include <fstream>

//-------------------------------------------------------------------------------

Character::Character()
{
  m_currentMotion = &m_motion1;
  m_currentFrame = 0;
  m_isForwardAnimation = true;
}

//-------------------------------------------------------------------------------

bool Character::LoadBVHFile(const std::string &_path)
{
  if( _path.empty() )
  {
    std::cerr << "ERROR: No file name specified\n";
    return false;
  }

  // Open .bvh file to parse
  std::ifstream file;
  file.open( _path.c_str(), std::ios_base::in );
  if( !file.is_open() )
  {
    std::cerr << "ERROR: Could not open " << _path << ". File not found!\n";
    return false;
  }

  //m_skeleton = std::make_shared< Skeleton >();
  if( !m_skeleton.Init( file ) )
  {
    std::cerr << "ERROR: When initiliasing Skeleton object\n";
    return false;
  }
  if( !m_currentMotion->Load( file, &m_skeleton ) )
  {
    std::cerr << "ERROR: When initiliasing Motion object\n";
    return false;
  }

  if( m_skeleton.GetNumJoints() > 0 && m_currentMotion && m_currentMotion->GetNumFrames() > 0 )
  {
    m_skeleton.PreProcessMotionData( m_currentMotion->GetFrames() );
  }

  return true;

}

//-------------------------------------------------------------------------------

void Character::Draw()
{
  m_skeleton.Draw();
}

//-------------------------------------------------------------------------------

void Character::Update()
{
  m_skeleton.Update( m_currentFrame );
}

//-------------------------------------------------------------------------------

void Character::SetForwardAnimation()
{
  if( m_isForwardAnimation )
  {
    if( m_currentFrame >= m_currentMotion->GetNumFrames() - 1 )
    {
      m_currentFrame = 0;
    }
    else
    {
      m_currentFrame++;
    }
  }
  else
  {
    if( m_currentFrame > 0 )
    {
      m_currentFrame--;
    }
    else
    {
      m_currentFrame = m_currentMotion->GetNumFrames() - 1;
    }
  }
}

//-------------------------------------------------------------------------------

void Character::ForwardAnimation()
{
  m_isForwardAnimation = true;
}

//-------------------------------------------------------------------------------

void Character::BackwardAnimation()
{
  m_isForwardAnimation = false;
}

//-------------------------------------------------------------------------------

void Character::ResetAnimation()
{
  m_currentFrame = 0;
}

//-------------------------------------------------------------------------------

void Character::SetCurrentMotion( const int &_motion )
{
  switch( _motion )
  {
    case MOTION1:
    {
      m_currentMotion = &m_motion1;
      break;
    }

    case MOTION2:
    {
      m_currentMotion = &m_motion2;
      break;
    }

    case BLENDED:
    {
      m_currentMotion = &m_motion3;
      break;
    }

    default:
    {
      break;
    }
  }

  m_currentFrame = 0;
}

//-------------------------------------------------------------------------------

void Character::PreprocessData()
{
  if( m_skeleton.GetNumJoints() > 0 && m_currentMotion && m_currentMotion->GetNumFrames() > 0 )
  {
    m_skeleton.PreProcessMotionData( m_currentMotion->GetFrames() );
  }
}

//-------------------------------------------------------------------------------

bool Character::BlendingReady( unsigned int &_frameCount0, unsigned int &_frameCount1 )
{
  _frameCount0 = m_motion1.GetNumFrames();
  _frameCount1 = m_motion2.GetNumFrames();

  // Check that both motions have
  // - same number of joints in skeleton
  // - motion1 tot frame number is > 0
  // - motion2 tot frame number is > 0
  return( ( m_motion1.GetNumJoints() == m_motion2.GetNumJoints() ) && _frameCount0 > 0 && _frameCount1 > 0 );
}

//-------------------------------------------------------------------------------

// http://www.dreamincode.net/forums/topic/163469-calculating-the-difference-between-two-angles/

float DifferenceAngle( const float& _a1, const float& _a2 )
{
  float value = _a1 - _a2;
  while( value > ngl::PI )
  {
    value -= ngl::TWO_PI;
  }

  while( value < -ngl::PI )
  {
    value += ngl::TWO_PI;
  }

  return value;
}

//-------------------------------------------------------------------------------

// See https://piazza-resources.s3.amazonaws.com/hz95jx955a87i8/i0c1j8fq62t11b/CS662__Homework_2__Kinematics.pdf

void Character::Blend( const unsigned int &_startFrame, const unsigned int &_endFrame, const unsigned int &_blendRange, const unsigned int &_type )
{
  // Compute total frame number for the final blended animation
  unsigned int totFrames = _startFrame + _blendRange + m_motion2.GetNumFrames() - _endFrame + 1;

  // Preparing motion3 to hold interpolated data
  m_motion3.DeallocateFrameStorage();
  m_motion3.SetNumJoints( m_skeleton.GetNumJoints() );
  m_motion3.SetNumFrames( totFrames );
  m_motion3.AllocateFrameStorage();

  // Copy frames from 0 to the startFrame picked through dialog windowd, from motion1 to motion3
  for( unsigned int i = 0; i < ( _startFrame + 2 ); i++ )
  {
    m_motion3.GetFrameAt( i )->CloneFrame( *( m_motion1.GetFrameAt( i ) ) );
  }

  // Estimate root translation and rotation for motion3 interpolated part (startFrame + blendFrame + 1)
  ngl::Vec3 rootPos0 = m_motion1.GetFrameAt( _startFrame - 1 )->GetRootTranslation();
  ngl::Vec3 rootPos1 = m_motion1.GetFrameAt( _startFrame )->GetRootTranslation();
  ngl::Vec3 rootPos2 = m_motion2.GetFrameAt( _endFrame )->GetRootTranslation();
  ngl::Vec3 rootPos3 = m_motion2.GetFrameAt( _endFrame + 1 )->GetRootTranslation();

  ngl::Mat4 rootRot1 = m_motion1.GetFrameAt( _startFrame )->GetJointRotation( 0 );
  ngl::Mat4 rootRot2 = m_motion2.GetFrameAt( _endFrame )->GetJointRotation( 0 );

  ngl::Vec2 vel1( rootPos1.m_x - rootPos0.m_x, rootPos1.m_z - rootPos0.m_z );
  ngl::Vec2 vel2( rootPos3.m_x - rootPos2.m_x, rootPos3.m_z - rootPos2.m_z );

  float offset1 = vel1.length();
  float offset2 = vel2.length();

  float dist = ( ( offset1 + offset2 ) * _blendRange ) / 2.0f;
  vel1 /= offset1;
  vel2 /= offset2;

  ngl::Vec3 newRootPos = rootPos1 + ngl::Vec3( vel1.m_x * dist, 0.f, vel1.m_y * dist );
  newRootPos.m_y = rootPos2.m_y;

  vel1 = ngl::Vec2( rootRot1.m_20, rootRot1.m_22 );
  vel2 = ngl::Vec2( rootRot2.m_20, rootRot2.m_22 );

  vel1.normalize();
  vel2.normalize();

  float angle1 = atan2( vel1.m_x, vel1.m_y );
  float angle2 = atan2( vel2.m_x, vel2.m_y );

  float deltaAngle = DifferenceAngle( angle2, angle1 );
  ngl::Mat4 deltaRot;
  deltaRot.rotateY( ngl::degrees( deltaAngle ) );
  deltaRot = deltaRot.transpose();

  // Copy frames from endFrame to the end from motion2 to motion3, taking into account the blend range as well
  ngl::Vec3 r;
  ngl::Vec3 o = m_motion2.GetFrameAt( _endFrame )->GetRootTranslation();

  std::shared_ptr< Frame > tmpFrame;

  unsigned int i, j;
  for( i = ( _endFrame - 1 ), j = _startFrame + _blendRange; i < m_motion2.GetNumFrames(); i++, j++ )
  {
    tmpFrame = m_motion3.GetFrameAt( j );
    tmpFrame->CloneFrame( *( m_motion2.GetFrameAt( i ) ) );

    r = tmpFrame->GetRootTranslation() - o;
    r = deltaRot * r + newRootPos;

    tmpFrame->SetRootTranslation( r );
    tmpFrame->SetJointRotation( 0, deltaRot * tmpFrame->GetJointRotation( 0 ) );
  }

  // Compute interpolation from frames in blending range

  float interval; // Between 0 and 1

  for( i = _startFrame + 1, j = 0; i < _startFrame + _blendRange + 1; i++, j++ )
  {
    interval = float( j + 1 ) / ( float )( _blendRange + 1 );

    Frame tmpFrame;

    switch( _type )
    {
      case CUBIC:
      {
        tmpFrame.Cubic( *( m_motion3.GetFrameAt( _startFrame - 1 ) ),
                      *( m_motion3.GetFrameAt( _startFrame ) ),
                      *( m_motion3.GetFrameAt( _startFrame + _blendRange + 1 ) ),
                      *( m_motion3.GetFrameAt( _startFrame + _blendRange + 2 ) ),
                      *( m_motion3.GetFrameAt( i ) ),
                      interval );
        break;
      }

      case SLERP:
      {
        tmpFrame.Slerp( *( m_motion3.GetFrameAt( _startFrame ) ),
                      *( m_motion3.GetFrameAt( _startFrame + _blendRange + 1 ) ),
                      *( m_motion3.GetFrameAt( i ) ),
                      interval );
        break;
      }
    }
  }
}

//-------------------------------------------------------------------------------

