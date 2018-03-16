//----------------------------------------------------------------------------------------------------------------------
/// @file Skeleton.h
/// @brief Skeleton class represent joints of skeleton as described in .bvh file
/// @author Michelle Wu
/// @version 1.0
//----------------------------------------------------------------------------------------------------------------------

#ifndef SKELETON_H
#define SKELETON_H

#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <ngl/ShaderLib.h>
#include <ngl/SimpleIndexVAO.h>

#include "Joint.h"
#include "Frame.h"

//-------------------------------------------------------------------------------
/// @brief Tokenizer for parsing .bvh file
//-------------------------------------------------------------------------------
typedef boost::tokenizer< boost::char_separator< char > > Tokenizer;
//-------------------------------------------------------------------------------

class Skeleton
{
public:

  //-------------------------------------------------------------------------------
  /// @brief Default ctor
  //-------------------------------------------------------------------------------
  Skeleton();
  //-------------------------------------------------------------------------------
  /// @brief Initialise method
  /// @param [in] _str File stream
  //-------------------------------------------------------------------------------
  bool Init( std::istream &_str );
  //-------------------------------------------------------------------------------
  /// @brief Process data loaded from motion section in relation to the skeleton
  /// @param [in] _frames All frames of the animation
  //-------------------------------------------------------------------------------
  void PreProcessMotionData( std::vector< std::shared_ptr< Frame > > _frames );
  //-------------------------------------------------------------------------------
  /// @brief Update method
  /// @param [in] _currentFrame Current frame
  //-------------------------------------------------------------------------------
  void Update( const unsigned int &_currentFrame );
  //-------------------------------------------------------------------------------
  /// @brief Update the skeleton VAO
  /// @param [in] _currentFrame Current frame
  //-------------------------------------------------------------------------------
  void UpdateVAO( const unsigned int& _currentFrame );
  //-------------------------------------------------------------------------------
  /// @brief Load BVH data from file
  /// @param [in] _str .bvh file stream
  //-------------------------------------------------------------------------------
  bool Load( std::istream &_str );
  //-------------------------------------------------------------------------------
  /// @brief Draw method
  //-------------------------------------------------------------------------------
  void Draw();
  //-------------------------------------------------------------------------------
  /// @brief Get root joint
  /// @return m_root
  //-------------------------------------------------------------------------------
  std::shared_ptr< Joint > GetRootJoint() const { return m_root; }
  //-------------------------------------------------------------------------------
  /// @brief Retrives vertices for each joint of the skeleton for drawing purposes
  /// @param [in] _joint Current joint
  /// @param [in] _frame Current frame number
  //-------------------------------------------------------------------------------
  ngl::Vec3 GetSkeletonVertices( const std::shared_ptr< Joint > _joint, const unsigned int &_frame );
  //-------------------------------------------------------------------------------
  /// @brief Get number of degrees of freedom
  /// @return m_numDOF Number of degrees of freedom
  //-------------------------------------------------------------------------------
  unsigned int GetNumDOF() const { return m_numDOF; }
  //-------------------------------------------------------------------------------
  /// @brief Returns number of joints in skeleton
  /// @return m_numJoints Total number of joints
  //-------------------------------------------------------------------------------
  unsigned int GetNumJoints() const { return m_numJoints; }
  //-------------------------------------------------------------------------------

private:

  //-------------------------------------------------------------------------------
  /// @brief Root joint
  //-------------------------------------------------------------------------------
  std::shared_ptr< Joint > m_root;
  //-------------------------------------------------------------------------------
  /// @brief Holds number of joints in skeleton
  //-------------------------------------------------------------------------------
  unsigned int m_numJoints;
  //-------------------------------------------------------------------------------
  /// @brief Holds total number of degrees of freedom
  //-------------------------------------------------------------------------------
  unsigned int m_numDOF;
  //-------------------------------------------------------------------------------
  /// @brief Delimeters for tokenizer
  //-------------------------------------------------------------------------------
  boost::char_separator< char > m_separators;
  //-------------------------------------------------------------------------------
  /// @brief Parse hierarchy data
  /// @param [in] _str Opened .bvh file
  //-------------------------------------------------------------------------------
  bool LoadHierarchy( std::istream &_str );
  //-------------------------------------------------------------------------------
  /// @brief Parse joint data
  /// @param [in] _str Opened .bvh file
  /// @param [in] _firstWord First token
  /// @param [in] _parent Parent joint
  //-------------------------------------------------------------------------------
  std::shared_ptr< Joint > LoadJoint( std::istream &_str,
                                      Tokenizer::iterator &_firstWord,
                                      std::shared_ptr< Joint > _parent );
  //-------------------------------------------------------------------------------
  // @brief Joints of skeleton
  //-------------------------------------------------------------------------------
  //std::vector< std::shared_ptr< Joint > > m_joints;
  //-------------------------------------------------------------------------------
  /// @brief Vertex array object for drawing skeleton
  //-------------------------------------------------------------------------------
  std::unique_ptr< ngl::AbstractVAO > m_vao;
  //-------------------------------------------------------------------------------
  /// @brief Creates the skeleton vao for drawing
  //-------------------------------------------------------------------------------
  void CreateVAO();
  //-------------------------------------------------------------------------------
  /// @brief Get vertices and indices to draw skeleton
  /// @param [in] _joint Joint
  /// @param [in] _verts Vertex container
  /// @param [in] _indices Index container
  /// @param [in] _parentIndex Parent joint index
  /// @param [in] _currentFrame Current frame
  //-------------------------------------------------------------------------------
  void ExtractVerts( std::shared_ptr< Joint > _joint,
                     std::vector< ngl::Vec3 >& _verts,
                     std::vector< GLshort >& _indices,
                     GLshort _parentIndex ,
                     const unsigned int& _currentFrame );
  //-------------------------------------------------------------------------------
  /// @brief This method extracts translation and rotation data previously stored in each frame
  /// @param [in] _joint Current joint
  /// @param [in] _frame Current frame
  //-------------------------------------------------------------------------------
  void ExtractDataFromFrame( std::shared_ptr<Joint> _joint, std::shared_ptr< Frame > _frame );
  //-------------------------------------------------------------------------------

};

#endif // SKELETON_H
