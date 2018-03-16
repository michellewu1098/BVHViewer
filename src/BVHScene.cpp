#include "include/BVHScene.h"

//-------------------------------------------------------------------------------

BVHScene::BVHScene()
{
  m_paused = true;
}

//-------------------------------------------------------------------------------

BVHScene::~BVHScene()
{

}

//-------------------------------------------------------------------------------

bool BVHScene::LoadBVHFile( const std::string &_path )
{
  if( !m_character.LoadBVHFile( _path ) )
  {
    std::cerr << "ERROR: When initiliasing Skeleton object\n";
    return false;
  }

  m_paused = true;
  return true;
}

//-------------------------------------------------------------------------------

void BVHScene::LoadMatricesToShader(const std::string &_shaderName, const ngl::Mat4 &_globalMat, ngl::Camera &_cam )
{
  ngl::ShaderLib* shader = ngl::ShaderLib::instance();
  ( *shader )[ _shaderName ]->use();

  ngl::Mat4 M = _globalMat;
  ngl::Mat4 MV = _cam.getViewMatrix() * M;
  ngl::Mat4 MVP = _cam.getVPMatrix() * M;

  ngl::Mat3 normalMatrix = MV;
  normalMatrix.inverse().transpose();

  shader->setUniform( "M", M );
  shader->setUniform( "MV", MV );
  shader->setUniform( "MVP", MVP );
  shader->setUniform( "normalMatrix", normalMatrix );
}

//-------------------------------------------------------------------------------

void BVHScene::DrawFloor( const ngl::Mat4& _globalMat, ngl::Camera& _cam )
{
  //ngl::ShaderLib* shader = ngl::ShaderLib::instance();
  //( *shader )[ "Colour" ]->use();

  LoadMatricesToShader( "Colour", _globalMat, _cam );

  // Draw floor
  ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();
  prim->draw("floor");
}

//-------------------------------------------------------------------------------

void BVHScene::Draw( const ngl::Mat4& _globalMat, ngl::Camera& _cam )
{
  ngl::Mat4 scale;
  scale.scale( 0.15f, 0.15f, 0.15f );

  ngl::ShaderLib* shader = ngl::ShaderLib::instance();
  ( *shader )[ "Colour" ]->use();

  ngl::Mat4 MVP = _cam.getVPMatrix() * _globalMat * scale;
  shader->setUniform( "MVP", MVP );

  // Draw character
  m_character.Draw();
}

//-------------------------------------------------------------------------------

void BVHScene::Update()
{
  if( m_paused )
  {
    return;
  }

  m_character.SetForwardAnimation();
  m_character.Update();
}

//-------------------------------------------------------------------------------

void BVHScene::BackwardAnimation()
{
  m_character.BackwardAnimation();
}

//-------------------------------------------------------------------------------

void BVHScene::ForwardAnimation()
{
  m_character.ForwardAnimation();
}

//-------------------------------------------------------------------------------

void BVHScene::NextFrame()
{
  m_character.ForwardAnimation();
  m_character.SetForwardAnimation();
  m_character.Update();
}

//-------------------------------------------------------------------------------

void BVHScene::PreviousFrame()
{
  m_character.BackwardAnimation();
  m_character.SetForwardAnimation();
  m_character.Update();
}

//-------------------------------------------------------------------------------

void BVHScene::SetCurrentMotion( const int& _currentMotion )
{
  m_paused = true;
  m_character.SetCurrentMotion( _currentMotion );
  m_character.PreprocessData();
}

//-------------------------------------------------------------------------------

void BVHScene::SetBlendingOptions( const unsigned int &_startFrame, const unsigned int &_endFrame, const unsigned int &_blendRange, const unsigned int &_type )
{
  m_paused = true;
  m_character.Blend( _startFrame, _endFrame, _blendRange, _type );
  m_character.SetCurrentMotion( 2 );
}

//-------------------------------------------------------------------------------

std::vector< unsigned int > BVHScene::CheckBlendingReady()
{
  unsigned int frameCount0;
  unsigned int frameCount1;
  std::vector< unsigned int > frames( 2, 0 );

  if( m_character.BlendingReady( frameCount0, frameCount1 ) )
  {
    frames[ 0 ] = frameCount0;
    frames[ 1 ] = frameCount1;
  }

  return frames;
}

//-------------------------------------------------------------------------------

void BVHScene::ResetAnimation()
{
  m_character.ResetAnimation();
  if( m_paused )
  {
    m_character.Update();
  }
}

//-------------------------------------------------------------------------------
