//----------------------------------------------------------------------------------------------------------------------
/// @file Frame.h
/// @brief Frame class represents each frame of an animation sequence
/// @author Michelle Wu
/// @version 1.0
//----------------------------------------------------------------------------------------------------------------------

#ifndef FRAME_H
#define FRAME_H

#include <ngl/Mat4.h>
#include <ngl/Quaternion.h>
#include <vector>
#include <math.h>

class Frame
{
public:

  //-------------------------------------------------------------------------------
  /// @brief Default ctor
  //-------------------------------------------------------------------------------
  Frame();
  //-------------------------------------------------------------------------------
  /// @brief Ctor
  /// @param [in] _id Frame id
  //-------------------------------------------------------------------------------
  Frame( const unsigned int& _id );
  //-------------------------------------------------------------------------------
  /// @brief Dtor
  //-------------------------------------------------------------------------------
  ~Frame();
  //-------------------------------------------------------------------------------
  /// @brief Get frame id
  /// @return m_id Frame id
  //-------------------------------------------------------------------------------
  unsigned int GetFrameID() const { return m_id; }
  //-------------------------------------------------------------------------------
  /// @brief Get tot number of joints per frame
  /// @return m_totJoints
  //-------------------------------------------------------------------------------
  unsigned int GetNumOfJoints() const { return m_numJoints; }
  //-------------------------------------------------------------------------------
  /// @brief Set tot number of joints per frame
  /// @param [in] _totJoints Tot number of joints
  //-------------------------------------------------------------------------------
  void SetNumOfJoints( const unsigned int& _totJoints );
  //-------------------------------------------------------------------------------
  /// @brief Set root local translation
  /// @param [in] _translation Translation vector
  //-------------------------------------------------------------------------------
  void SetRootTranslation( const ngl::Vec3& _translation ) { m_rootLocTranslation = _translation; }
  //-------------------------------------------------------------------------------
  /// @brief Get root local translation
  /// @return m_rootLocTranslation Root local translation
  //-------------------------------------------------------------------------------
  ngl::Vec3 GetRootTranslation() const { return m_rootLocTranslation; }
  //-------------------------------------------------------------------------------
  /// @brief Returns the joint rotation matrix
  /// @param [in] _id Joint id
  //-------------------------------------------------------------------------------
  ngl::Mat4 GetJointRotation( const unsigned int& _id ) const { return m_rotationData[ _id ]; }
  //-------------------------------------------------------------------------------
  /// @brief Set the joint rotation matrix, it will internally set the corresponding quaternion
  /// @param [in] _id Joint id
  /// @param [in] _rot Rotation matrix
  //-------------------------------------------------------------------------------
  void SetJointRotation( const unsigned int& _id, const ngl::Mat4& _rot );
  //-------------------------------------------------------------------------------
  /// @brief Set the joint orientation matrix, it will internally set the corresponding rotation
  /// @param [in] _id Joint id
  /// @param [in] _quat Quaternion representing orientation
  //-------------------------------------------------------------------------------
  void SetJointQuaternion( const unsigned int& _id, const ngl::Quaternion& _quat );
  //-------------------------------------------------------------------------------
  /// @brief Clones a frame, all its translation, rotation and quaternion data
  /// @param [in] _frame Frame to clone
  //-------------------------------------------------------------------------------
  void CloneFrame( const Frame& _frame );
  //-------------------------------------------------------------------------------
  // SMOOTH INTERPOLATION BETWEEN FRAMES
  //-------------------------------------------------------------------------------
  /// @brief Cubic interpolation between frame1 and frame2
  /// @param [in] _frame0 Frame before frame1 (could be from different animation)
  /// @param [in] _frame1 First frame that will be interpolated
  /// @param [in] _frame2 Second frame that will be interpolated
  /// @param [in] _frame3 Frame after frame2 (could be from different animation)
  /// @param [in] _targetFrame Interpolation result
  /// @param [in] _interval Interpolation interval
  //-------------------------------------------------------------------------------
  void Cubic( const Frame& _frame0, const Frame& _frame1, const Frame& _frame2, const Frame& _frame3, Frame& _targetFrame, float _interval );
  //-------------------------------------------------------------------------------
  /// @brief SLERP interpolation
  /// @param [in] _frame0 First frame that will be interpolated
  /// @param [in] _frame1 Second frame that will be interpolated
  /// @param [in] _targetFrame Interpolation result
  /// @param [in] _interval Interpolation interval
  //-------------------------------------------------------------------------------
  void Slerp( const Frame& _frame0, const Frame& _frame1, Frame& _targetFrame, float _interval );
  //-------------------------------------------------------------------------------

private:

  //-------------------------------------------------------------------------------
  /// @brief Tot number of joints
  //-------------------------------------------------------------------------------
  unsigned int m_numJoints;
  //-------------------------------------------------------------------------------
  /// @brief Root local translation
  //-------------------------------------------------------------------------------
  ngl::Vec3 m_rootLocTranslation;
  //-------------------------------------------------------------------------------
  /// @brief Quaternion data for each joint
  //-------------------------------------------------------------------------------
  std::vector< ngl::Quaternion > m_quaternionData;
  //-------------------------------------------------------------------------------
  /// @brief Rotation matrices for each joint
  //-------------------------------------------------------------------------------
  std::vector< ngl::Mat4 > m_rotationData;
  //-------------------------------------------------------------------------------
  /// @brief Frame id
  //-------------------------------------------------------------------------------
  unsigned int m_id;
  //-------------------------------------------------------------------------------

};

#endif // FRAME_H
