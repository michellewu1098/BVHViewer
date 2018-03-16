#include "include/Frame.h"
#include "ngl/Util.h"
#include <assert.h>

//-------------------------------------------------------------------------------

Frame::Frame()
{
  m_numJoints = 0;
}

//-------------------------------------------------------------------------------

Frame::Frame( const unsigned int &_id )
{
  m_id = _id;
  m_numJoints = 0;
}

//-------------------------------------------------------------------------------

Frame::~Frame()
{

}

//-------------------------------------------------------------------------------

void Frame::SetNumOfJoints( const unsigned int &_totJoints )
{
  if( m_numJoints != _totJoints )
  {
    m_numJoints = _totJoints;

    if( !m_rotationData.empty())
    {
      m_rotationData.clear();
    }
    m_rotationData.resize( m_numJoints );

    if( !m_quaternionData.empty() )
    {
      m_quaternionData.clear();
    }
    m_quaternionData.resize( m_numJoints );
  }
}

//-------------------------------------------------------------------------------

void Frame::CloneFrame( const Frame &_frame )
{
  SetNumOfJoints( _frame.m_numJoints );
  m_rootLocTranslation = _frame.m_rootLocTranslation;
  for( unsigned int i = 0; i < m_numJoints; i++ )
  {
    m_rotationData[ i ] = _frame.m_rotationData[ i ] ;
    m_quaternionData[ i ] = _frame.m_quaternionData[ i ];
  }
}

//-------------------------------------------------------------------------------

// As in here (p.222 onwards) https://doc.lagout.org/Others/Game%20Development/Programming/Graphics%20Gems%204.pdf

bool ToEulerAngles( const ngl::Mat4& _mat, ngl::Vec3& _angles )
{
  _angles[ 0 ] = asin( _mat.m_12 );
  if( _angles[ 0 ] > -ngl::PI2 + 0.001 )
  {
    if( _angles[ 0 ] < ngl::PI2 - 0.001 )
    {
      _angles[ 2 ] = atan2( -_mat.m_10, _mat.m_11 );
      _angles[ 1 ] = atan2( -_mat.m_02, _mat.m_22 );
      return true;
    }
    else
    {
      _angles[ 1 ] = 0.f;
      _angles[ 2 ] = atan2( _mat.m_20, _mat.m_00 );
      return false;
    }
  }
  else
  {
    _angles[ 1 ] = 0.f;
    _angles[ 2 ] = -atan2( _mat.m_20, _mat.m_00 );
    return false;
  }
}

//-------------------------------------------------------------------------------

void Frame::Cubic( const Frame &_frame0, const Frame &_frame1, const Frame &_frame2, const Frame &_frame3, Frame &_targetFrame, float _interval )
{
  _targetFrame.m_rootLocTranslation = _frame1.m_rootLocTranslation * ( 1.f - _interval ) + _frame2.m_rootLocTranslation * _interval;

  for( unsigned int i = 0; i < _frame0.m_numJoints; i++ )
  {
    const ngl::Mat4& rot0 = _frame0.GetJointRotation( i );
    const ngl::Mat4& rot1 = _frame1.GetJointRotation( i );
    const ngl::Mat4& rot2 = _frame2.GetJointRotation( i );
    const ngl::Mat4& rot3 = _frame3.GetJointRotation( i );

    ngl::Vec3 angles0, angles1, angles2, angles3, angles;
    ToEulerAngles( rot0, angles0 );
    ToEulerAngles( rot1, angles1 );
    ToEulerAngles( rot2, angles2 );
    ToEulerAngles( rot3, angles3 );

    angles = angles1 * ( 1.f - _interval ) + angles2 * _interval;

    ngl::Mat4 rotX, rotY, rotZ, rot;

    rotX.rotateX( ngl::degrees( angles.m_x ) );
    rotY.rotateY( ngl::degrees( angles.m_y ) );
    rotZ.rotateZ( ngl::degrees( angles.m_z ) );

    rot = rotZ * rotX * rotY;
    _targetFrame.SetJointRotation( i, rot );

  }
}

//-------------------------------------------------------------------------------

void Frame::Slerp( const Frame &_frame0, const Frame &_frame1, Frame &_targetFrame, float _interval )
{
  _targetFrame.m_rootLocTranslation = _frame0.m_rootLocTranslation * ( 1.f - _interval ) + _frame1.m_rootLocTranslation * _interval;

  for( unsigned int i = 0; i < _frame0.m_numJoints; i++ )
  {
    const auto& q0 = _frame0.m_quaternionData[ i ];
    const auto& q1 = _frame1.m_quaternionData[ i ];

    auto q = ngl::Quaternion::slerp( q0, q1, _interval );

    _targetFrame.SetJointQuaternion( i, q );
  }
}

//-------------------------------------------------------------------------------

void Frame::SetJointRotation( const unsigned int &_id, const ngl::Mat4 &_rot )
{
  assert( _id >= 0 && _id < m_numJoints );
  m_rotationData[ _id ] = _rot;
  m_quaternionData[ _id ] = ngl::Quaternion( _rot );
}

//-------------------------------------------------------------------------------

void Frame::SetJointQuaternion( const unsigned int& _id, const ngl::Quaternion& _quat )
{
  assert( _id >= 0 && _id < m_numJoints );
  m_rotationData[ _id ] = _quat.toMat4();
  m_quaternionData[ _id ] = _quat;
}

//-------------------------------------------------------------------------------
