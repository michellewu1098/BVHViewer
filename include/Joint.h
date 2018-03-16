//----------------------------------------------------------------------------------------------------------------------
/// @file Joint.h
/// @brief Struct for Joint which is the fundamental component of the skeleton
/// @author Michelle Wu
/// @version 1.0
//----------------------------------------------------------------------------------------------------------------------

#ifndef JOINT_H
#define JOINT_H

#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <string>
#include <vector>

struct Joint
{
  //------------------------------------------------
  /// @brief Joint name
  //------------------------------------------------
  std::string m_name;
  //------------------------------------------------
  /// @brief Offset of joint from parent
  //------------------------------------------------
  ngl::Vec3 m_offset;
  //------------------------------------------------
  /// @brief Joint's children
  //------------------------------------------------
  std::vector< std::shared_ptr< Joint > > m_children;
  //------------------------------------------------
  /// @brief Number of channels
  //------------------------------------------------
  unsigned int m_numChannels;
  //------------------------------------------------
  /// @brief Rotation order
  //------------------------------------------------
  unsigned int m_rotationOrder[ 3 ];
  //------------------------------------------------
  /// @brief Root translation order
  //------------------------------------------------
  unsigned int m_translationOrder[ 3 ];
  //------------------------------------------------
  /// @brief Local transformation matrix
  //------------------------------------------------
  ngl::Mat4 m_transform;
  //------------------------------------------------
  /// @brief Joint's parent
  //------------------------------------------------
  std::shared_ptr< Joint > m_parent;
  //------------------------------------------------
  /// @brief Joint id
  //------------------------------------------------
  unsigned int m_id;
  //------------------------------------------------
  /// @brief Store the vertex data for every frame in animation
  //------------------------------------------------
  ngl::Vec3* m_frameDataStorage;
  //------------------------------------------------
  /// @brief Ctor
  //------------------------------------------------
  Joint()
  {
      m_numChannels = 0;
      m_parent = NULL;
  }
  //------------------------------------------------
  /// @brief Dtor
  //------------------------------------------------
  ~Joint()
  {
      delete [] m_frameDataStorage;
  }
  //------------------------------------------------
  /// @brief Initialise frame storage data
  /// @param [in] _nFrames Number of frames
  //------------------------------------------------
  void initFrameDataStorage( const unsigned int &_nFrames )
  {
      m_frameDataStorage = new ngl::Vec3[ _nFrames ];
      for( auto &child : m_children)
      {
          child->initFrameDataStorage( _nFrames );
      }
  }
  //------------------------------------------------

};

#endif // JOINT_H
