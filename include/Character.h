//----------------------------------------------------------------------------------------------------------------------
/// @file Character.h
/// @brief Represents a character in a scene made up of a skeleton and of motion data parsed from .bvh file
/// @author Michelle Wu
/// @version 1.0
//----------------------------------------------------------------------------------------------------------------------

#ifndef CHARACTER_H
#define CHARACTER_H

#include "Skeleton.h"
#include "Motion.h"

class Character
{
public:

  //-------------------------------------------------------------------------------
  /// @brief Ctor
  //-------------------------------------------------------------------------------
  Character();
  //-------------------------------------------------------------------------------
  /// @brief Loads .bvh file
  /// @param [in] _path Path to file
  //-------------------------------------------------------------------------------
  bool LoadBVHFile( const std::string &_path );
  //-------------------------------------------------------------------------------
  /// @brief Updates skeleton structure
  //-------------------------------------------------------------------------------
  void Update();
  //-------------------------------------------------------------------------------
  /// @brief Draws skeleton
  //-------------------------------------------------------------------------------
  void Draw();
  //-------------------------------------------------------------------------------
  /// @brief Preprocesses motion data for skeleton
  //-------------------------------------------------------------------------------
  void PreprocessData();
  //-------------------------------------------------------------------------------
  /// @brief Set current motion used
  /// @param [in] _motion Motion type: (0, motion1) (1, motion2) (2, motion3)
  //-------------------------------------------------------------------------------
  void SetCurrentMotion( const int &_motion );
  //-------------------------------------------------------------------------------
  /// @brief Checks if system is ready for blending/interpolation
  /// @param [in] _frameCount0 Frame count for Animation 1
  /// @param [in] _frameCount1 Frame count for Animation 2
  //-------------------------------------------------------------------------------
  bool BlendingReady( unsigned int &_frameCount0, unsigned int &_frameCount1 );
  //-------------------------------------------------------------------------------
  /// @brief Performs interpolation between frames
  /// @param [in] _startFrame Start frame number from Animation 1
  /// @param [in] _endFrame End frame number from Animation 2
  /// @param [in] _blendRange Range of frames where to perform interpolation
  /// @param [in] _type Blend type (cubic or slerp)
  //-------------------------------------------------------------------------------
  void Blend( const unsigned int &_startFrame,
              const unsigned int &_endFrame,
              const unsigned int &_blendRange,
              const unsigned int &_type );
  //-------------------------------------------------------------------------------
  /// @brief Returns total numbers of frames in .bvh file
  //-------------------------------------------------------------------------------
  unsigned int GetNumFrames() const { return m_currentMotion->GetNumFrames(); }
  //-------------------------------------------------------------------------------
  /// @brief Returns frame rate of animation
  //-------------------------------------------------------------------------------
  float GetFrameRate() const { return m_currentMotion->GetFrameRate(); }
  //-------------------------------------------------------------------------------
  /// @brief Returns current frame
  /// @return m_currentFrame Current frame
  //-------------------------------------------------------------------------------
  unsigned int GetCurrentFrame() const { return m_currentFrame; }
  //-------------------------------------------------------------------------------
  // ANIMATION CONTROLLERS
  //-------------------------------------------------------------------------------
  /// @brief Sets animation to play backward
  //-------------------------------------------------------------------------------
  void BackwardAnimation();
  //-------------------------------------------------------------------------------
  /// @brief Sets animation to play forward
  //-------------------------------------------------------------------------------
  void ForwardAnimation();
  //-------------------------------------------------------------------------------
  /// @brief Increases/decreases frames for animation
  //-------------------------------------------------------------------------------
  void SetForwardAnimation();
  //-------------------------------------------------------------------------------
  /// @brief Reset animation froms start
  //-------------------------------------------------------------------------------
  void ResetAnimation();
  //-------------------------------------------------------------------------------
  /// @brief Motion types
  //-------------------------------------------------------------------------------
  enum MotionType { MOTION1, MOTION2, BLENDED };
  //-------------------------------------------------------------------------------
  /// @brief Blend/interpolation types
  //-------------------------------------------------------------------------------
  enum BlendType { CUBIC, SLERP };
  //-------------------------------------------------------------------------------

private:

  //-------------------------------------------------------------------------------
  /// @brief Skeleton structure
  //-------------------------------------------------------------------------------
  Skeleton m_skeleton;
  //-------------------------------------------------------------------------------
  /// @brief Current motion associated to skeleton
  //-------------------------------------------------------------------------------
  Motion* m_currentMotion = nullptr;
  //-------------------------------------------------------------------------------
  /// @brief Motion data for Animation 1
  //-------------------------------------------------------------------------------
  Motion m_motion1;
  //-------------------------------------------------------------------------------
  /// @brief Motion data for Animation 2
  //-------------------------------------------------------------------------------
  Motion m_motion2;
  //-------------------------------------------------------------------------------
  /// @brief Motion data for Blended Animation of Anim1 and Anim2
  //-------------------------------------------------------------------------------
  Motion m_motion3;
  //-------------------------------------------------------------------------------
  /// @brief Current frame
  //-------------------------------------------------------------------------------
  unsigned int m_currentFrame;
  //-------------------------------------------------------------------------------
  /// @brief Handles if animation is being played backward or forward
  //-------------------------------------------------------------------------------
  bool m_isForwardAnimation;
  //-------------------------------------------------------------------------------

};

#endif // CHARACTER_H
