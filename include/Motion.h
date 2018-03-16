//----------------------------------------------------------------------------------------------------------------------
/// @file Motion.h
/// @brief Motion class, parses motion data from bvh file, contains list of frames each storing the motion data
/// @author Michelle Wu
/// @version 1.0
//----------------------------------------------------------------------------------------------------------------------

#ifndef MOTION_H
#define MOTION_H

#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

#include "Skeleton.h"

//-------------------------------------------------------------------------------
/// @brief Tokenizer for parsing .bvh file
//-------------------------------------------------------------------------------
typedef boost::tokenizer< boost::char_separator< char > > Tokenizer;
//-------------------------------------------------------------------------------

class Motion
{
public:

  //-------------------------------------------------------------------------------
  /// @brief Default ctor
  //-------------------------------------------------------------------------------
  Motion();
  //-------------------------------------------------------------------------------
  /// @brief Dtor
  //-------------------------------------------------------------------------------
  ~Motion();
  //-------------------------------------------------------------------------------
  /// @brief Get tot number of frames
  /// @return m_numFrames Total number of frames
  //-------------------------------------------------------------------------------
  unsigned int GetNumFrames() const { return m_numFrames; }
  //-------------------------------------------------------------------------------
  /// @brief Set number of frames
  /// @param [in] _numFrames Number of frames
  //-------------------------------------------------------------------------------
  void SetNumFrames( const unsigned int &_numFrames ) { m_numFrames = _numFrames; }
  //-------------------------------------------------------------------------------
  /// @brief Get frame rate
  /// @return m_frameRate Frame rate
  //-------------------------------------------------------------------------------
  float GetFrameRate() const { return m_frameRate; }
  //-------------------------------------------------------------------------------
  /// @brief Set frame rate
  /// @param [in] _frameRate Frame rate
  //-------------------------------------------------------------------------------
  void SetFrameRate( const float &_frameRate ) { m_frameRate = _frameRate; }
  //-------------------------------------------------------------------------------
  /// @brief Get number of degree of freedom
  /// @return m_numDOF Number degrees of freedom
  //-------------------------------------------------------------------------------
  unsigned int GetNumDOF() const { return m_numDOF; }
  //-------------------------------------------------------------------------------
  /// @brief Set number of degree of freedom
  /// @param [in] _numDOF Number of degree of freedom
  //-------------------------------------------------------------------------------
  void SetNumDOF( const unsigned int &_numDOF ) { m_numDOF += _numDOF; }
  //-------------------------------------------------------------------------------
  /// @brief Set number of skeleton joints
  /// @param [in] _numJoints Number of joints
  //-------------------------------------------------------------------------------
  void SetNumJoints( const unsigned int& _numJoints ) { m_numJoints = _numJoints; }
  //-------------------------------------------------------------------------------
  /// @brief Returns tot number of joints
  /// @return m_numJoints Number of joints
  //-------------------------------------------------------------------------------
  unsigned int GetNumJoints() const { return m_numJoints; }
  //-------------------------------------------------------------------------------
  /// @brief Load motion data from .bvh file
  /// @param [in] _str File stream
  /// @param [in] _skeleton Skeleton structure
  //-------------------------------------------------------------------------------
  bool Load( std::istream &_str, Skeleton* _skeleton );
  //-------------------------------------------------------------------------------
  /// @brief Deallocates (frees) frames content
  //-------------------------------------------------------------------------------
  void DeallocateFrameStorage();
  //-------------------------------------------------------------------------------
  /// @brief Allocates data storage for frame content
  //-------------------------------------------------------------------------------
  void AllocateFrameStorage();
  //-------------------------------------------------------------------------------
  /// @brief Returns list of frames
  /// @return m_frames Animation frames
  //-------------------------------------------------------------------------------
  std::vector< std::shared_ptr< Frame > > GetFrames() const { return m_frames; }
  //-------------------------------------------------------------------------------
  /// @brief Get frame corresponding to id
  //-------------------------------------------------------------------------------
  std::shared_ptr< Frame > GetFrameAt( const unsigned int& _id ) const { return m_frames[ _id ]; }
  //-------------------------------------------------------------------------------
  /// @brief Extracts translation/rotations from motion data parsed from .bvh file
  /// @param [in] _joint Current joint to associate with data
  /// @param [in] _motionData Motion data retrieved from file
  /// @param [in] _frame Current frame where data will be stored to
  //-------------------------------------------------------------------------------
  void ExtractMotionData( const std::shared_ptr<Joint> &_joint , float *_motionData, std::shared_ptr<Frame> _frame );
  //-------------------------------------------------------------------------------

private:

  //-------------------------------------------------------------------------------
  /// @brief Delimeters for tokenizer
  //-------------------------------------------------------------------------------
  boost::char_separator< char > m_separators;
  //-------------------------------------------------------------------------------
  /// @brief Number of frames
  //-------------------------------------------------------------------------------
  unsigned int m_numFrames;
  //-------------------------------------------------------------------------------
  /// @brief Number of degree of freedom
  //-------------------------------------------------------------------------------
  unsigned int m_numDOF;
  //-------------------------------------------------------------------------------
  /// @brief Frame rate
  //-------------------------------------------------------------------------------
  float m_frameRate;
  //-------------------------------------------------------------------------------
  /// @brief List of animation frames container
  //-------------------------------------------------------------------------------
  std::vector< std::shared_ptr< Frame > > m_frames;
  //-------------------------------------------------------------------------------
  /// @brief Total number of joints
  //-------------------------------------------------------------------------------
  unsigned int m_numJoints;
  //-------------------------------------------------------------------------------

};

#endif // MOTION_H
