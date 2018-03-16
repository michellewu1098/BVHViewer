//----------------------------------------------------------------------------------------------------------------------
/// @file BVHScene.h
/// @brief Scene that manages bvh character in the scene
/// @todo Handle multiple characters
/// @author Michelle Wu
/// @version 1.0
//----------------------------------------------------------------------------------------------------------------------

#ifndef BVHSCENE_H
#define BVHSCENE_H

#include <ngl/Transformation.h>
#include <ngl/SimpleIndexVAO.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Camera.h>

#include "Character.h"

class BVHScene
{
public:

  //-------------------------------------------------------------------------------
  /// @brief Default ctor
  //-------------------------------------------------------------------------------
  BVHScene();
  //-------------------------------------------------------------------------------
  /// @brief Dtor
  //-------------------------------------------------------------------------------
  ~BVHScene();
  //-------------------------------------------------------------------------------
  /// @brief Load .bvh file
  /// @param [in] _path Path to .bvh file
  //-------------------------------------------------------------------------------
  bool LoadBVHFile( const std::string &_path );
  //-------------------------------------------------------------------------------
  /// @brief Update method
  //-------------------------------------------------------------------------------
  void Update();
  //-------------------------------------------------------------------------------
  /// @brief Draw method for character in scene
  /// @param [in] _globalMat Global transform
  /// @param [in] _cam Camera
  //-------------------------------------------------------------------------------
  void Draw( const ngl::Mat4& _globalMat, ngl::Camera& _cam );
  //-------------------------------------------------------------------------------
  /// @brief Draw method for floor
  /// @param [in] _globalMat Global transform
  /// @param [in] _cam Camera
  //-------------------------------------------------------------------------------
  void DrawFloor( const ngl::Mat4& _globalMat, ngl::Camera& _cam );
  //-------------------------------------------------------------------------------
  /// @brief Method to load transform matrices to the shader
  /// @param [in] _shaderName Shader name
  /// @param [in] _globalMat Global transform
  /// @param [in] _cam Camera
  //-------------------------------------------------------------------------------
  void LoadMatricesToShader( const std::string& _shaderName, const ngl::Mat4& _globalMat, ngl::Camera& _cam );
  //-------------------------------------------------------------------------------
  // ANIMATION CONTROLLERS
  //-------------------------------------------------------------------------------
  /// @brief Pause animation
  /// @param [in] _pause
  //-------------------------------------------------------------------------------
  void PauseAnimation( bool _pause ) { m_paused = _pause; }
  //-------------------------------------------------------------------------------
  /// @brief Plays animation backward
  //-------------------------------------------------------------------------------
  void BackwardAnimation();
  //-------------------------------------------------------------------------------
  /// @brief Plays animation forward
  //-------------------------------------------------------------------------------
  void ForwardAnimation();
  //-------------------------------------------------------------------------------
  /// @brief Reset animation from start
  //-------------------------------------------------------------------------------
  void ResetAnimation();
  //-------------------------------------------------------------------------------
  /// @brief Shows next frame in animation
  //-------------------------------------------------------------------------------
  void NextFrame();
  //-------------------------------------------------------------------------------
  /// @brief Shows previous frame in animation
  //-------------------------------------------------------------------------------
  void PreviousFrame();
  //-------------------------------------------------------------------------------
  /// @brief Returns animation frame rate
  //-------------------------------------------------------------------------------
  float GetFrameRate() const { return m_character.GetFrameRate(); }
  //-------------------------------------------------------------------------------
  /// @brief Returns total number of frames
  //-------------------------------------------------------------------------------
  unsigned int GetTotFrames() const { return m_character.GetNumFrames(); }
  //-------------------------------------------------------------------------------
  /// @brief Returns id of current frame
  //-------------------------------------------------------------------------------
  unsigned int GetCurrentFrame() const { return m_character.GetCurrentFrame(); }
  //-------------------------------------------------------------------------------
  /// @brief Set current motion used
  /// @param [in] _currentMotion Motion type: (0, motion1) (1, motion2) (2, motion3)
  //-------------------------------------------------------------------------------
  void SetCurrentMotion( const int& _currentMotion );
  //-------------------------------------------------------------------------------
  /// @brief Sets and apply smooth interpolation between frames
  /// @param [in] _startFrame Start frame number from Animation 1
  /// @param [in] _endFrame End frame number from Animation 2
  /// @param [in] _blendRange Range of frames where to perform interpolation
  /// @param [in] _type Blend type (cubic or slerp)
  //-------------------------------------------------------------------------------
  void SetBlendingOptions( const unsigned int& _startFrame,
                           const unsigned int& _endFrame,
                           const unsigned int& _blendRange,
                           const unsigned int& _type );
  //-------------------------------------------------------------------------------
  /// @brief Allows to check if system is ready to perform interpolation
  //-------------------------------------------------------------------------------
  std::vector< unsigned int > CheckBlendingReady();
  //-------------------------------------------------------------------------------

private:

  //-------------------------------------------------------------------------------
  /// @brief Character in the scene
  //-------------------------------------------------------------------------------
  Character m_character;
  //-------------------------------------------------------------------------------
  /// @brief Flag used to check if animation is paused
  //-------------------------------------------------------------------------------
  bool m_paused;
  //-------------------------------------------------------------------------------

};

#endif // BVHSCENE_H
