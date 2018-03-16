#include "NGLScene.h"

#include <ngl/NGLInit.h>
#include <ngl/Material.h>
#include <ngl/NGLStream.h>

#include <QApplication>

//----------------------------------------------------------------------------------------------------------------------

NGLScene::NGLScene( QWidget *_parent ) : QOpenGLWidget( _parent )
{
  setFocus();
  this->resize( _parent->size() );
  m_isLoaded = false;
  m_timerID = 0;
}

//----------------------------------------------------------------------------------------------------------------------

NGLScene::~NGLScene()
{
  std::cout << "Shutting down NGL, removing VAO's and Shaders\n";
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::resizeGL( int _w , int _h )
{
  m_cam.setShape( 45.0f, static_cast< float >( _w ) / _h, 0.05f, 350.0f );
  m_win.width  = static_cast< int >( _w * devicePixelRatio() );
  m_win.height = static_cast< int >( _h * devicePixelRatio() );
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::SetBVHFilePath( const std::string &_path )
{
  if( !_path.empty() )
  {
    m_filename = _path;
    if( m_scene.LoadBVHFile( m_filename ) )
    {
      m_isLoaded = true;
//      if( m_timerID != 0 )
//        killTimer( m_timerID );
//      m_timerID = startTimer( m_scene.GetFrameRate() );
      startTimer( 10 );
    }
  }
  else
  {
    std::cerr << "Invalid file name or path\n";
  }
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::initializeGL()
{
  // We need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash

  ngl::NGLInit::instance();
  glClearColor( 0.7f, 0.7f, 0.7f, 1.0f );
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_MULTISAMPLE );

  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  // PHONG SHADER

  shader->createShaderProgram( "Phong" );

  shader->attachShader( "PhongVertex", ngl::ShaderType::VERTEX );
  shader->attachShader( "PhongFragment", ngl::ShaderType::FRAGMENT );

  shader->loadShaderSource( "PhongVertex", "shaders/PhongVertex.glsl" );
  shader->loadShaderSource( "PhongFragment", "shaders/PhongFragment.glsl" );

  shader->compileShader( "PhongVertex" );
  shader->compileShader( "PhongFragment" );

  shader->attachShaderToProgram( "Phong", "PhongVertex" );
  shader->attachShaderToProgram( "Phong", "PhongFragment" );

  shader->linkProgramObject( "Phong" );

  ( *shader )[ "Phong" ]->use();

  ngl::Material m( ngl::STDMAT::POLISHEDSILVER );
  m.loadToShader( "material" );

  // Now we will create a basic Camera from the graphics library
  // This is a static camera so it only needs to be set once
  // First create Values for the camera position

  ngl::Vec3 from( 0, 25, 65 );
  ngl::Vec3 to( 0, 0, 0 );
  ngl::Vec3 up( 0, 1, 0 );

  m_cam.set( from, to, up );

  // Set the shape using FOV 45 Aspect Ratio based on Width and Height
  // The final two are near and far clipping planes of 0.5 and 10

  m_cam.setShape( 45.0f, 720.0f / 576.0f, 0.05f, 350.0f );

  shader->setUniform( "viewerPos", m_cam.getEye().toVec3() );

  // Now create our light that is done after the camera so we can pass the
  // transpose of the projection matrix to the light to do correct eye space
  // transformations
  ngl::Mat4 iv = m_cam.getViewMatrix();
  iv.transpose();
  ngl::Light light( ngl::Vec3( 0, 10, 10 ), ngl::Colour( 1, 1, 1, 1 ), ngl::Colour( 1, 1, 1, 1 ), ngl::LightModes::POINTLIGHT );
  light.setTransform( iv );
  light.loadToShader( "light" );

  //--------------------------------------------------
  // CONSTANT COLOUR SHADER
  //--------------------------------------------------

  shader->createShaderProgram( "Colour" );

  shader->attachShader( "ColourVertex", ngl::ShaderType::VERTEX );
  shader->attachShader( "ColourFragment", ngl::ShaderType::FRAGMENT );

  shader->loadShaderSource( "ColourVertex", "shaders/ConstantVertex.glsl" );
  shader->loadShaderSource( "ColourFragment", "shaders/ConstantFragment.glsl" );

  shader->compileShader( "ColourVertex" );
  shader->compileShader( "ColourFragment" );

  shader->attachShaderToProgram( "Colour", "ColourVertex" );
  shader->attachShaderToProgram( "Colour", "ColourFragment" );

  shader->linkProgramObject( "Colour" );

  //--------------------------------------------------
  // Create floor
  //--------------------------------------------------
  ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();
  prim->createLineGrid( "floor", 100, 100, 20 );
  //prim->createTrianglePlane("plane", 20.f, 20.f, 10, 10, ngl::Vec3( 0.f, 1.f, 0.f ) );

  //--------------------------------------------------
  // TEXT
  //--------------------------------------------------

  m_text.reset( new ngl::Text( QFont( "Arial", 16 ) ) );
  m_text->setScreenSize( this->size().width(), this->size().height() );
  m_text->setColour( 0.f, 0.f, 0.f ); // Text colour

}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glViewport( 0, 0, m_win.width, m_win.height );

  // Rotation based on the mouse position for our global transform
  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  // create the rotation matrices
  rotX.rotateX( m_win.spinXFace );
  rotY.rotateY( m_win.spinYFace );
  // multiply the rotations
  m_mouseGlobalTX = rotX * rotY;
  // add the translations
  m_mouseGlobalTX.m_m[ 3 ][ 0 ] = m_modelPos.m_x;
  m_mouseGlobalTX.m_m[ 3 ][ 1 ] = m_modelPos.m_y;
  m_mouseGlobalTX.m_m[ 3 ][ 2 ] = m_modelPos.m_z;

  m_scene.DrawFloor( m_mouseGlobalTX, m_cam );
  if( m_isLoaded )
  {
    m_scene.Draw( m_mouseGlobalTX, m_cam );
  }

  std::string totFrames = std::to_string( GetTotNumFrames() );
  std::string currentFrame = std::to_string( GetCurrentFrame() );
  std::string text = "Frame " + currentFrame + "/" + totFrames;
  m_text->renderText( 10, 15, QString::fromStdString( text ) );
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent( QKeyEvent *_event )
{
  // This method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch ( _event->key() )
  {
  // Escape key to quite
  case Qt::Key_Escape : QApplication::exit( EXIT_SUCCESS ); break;
  case Qt::Key_Space :
      m_win.spinXFace = 0;
      m_win.spinYFace = 0;
      m_modelPos.set( ngl::Vec3::zero() );
  break;
  default : break;
  }

  // Finally update the GLWindow and re-draw
  update();
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::timerEvent( QTimerEvent *_event )
{
  NGL_UNUSED( _event );
  if( m_isLoaded)
  {
    m_scene.Update();
  }

  update();
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::PauseAnimation( bool _pause )
{
  if( m_isLoaded )
  {
    m_scene.PauseAnimation( _pause );
  }
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::BackwardAnimation()
{
  if( m_isLoaded )
  {
    m_scene.BackwardAnimation();
  }
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::ForwardAnimation()
{
  if( m_isLoaded )
  {
    m_scene.ForwardAnimation();
  }
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::ResetAnimation()
{
  if( m_isLoaded )
  {
    m_scene.ResetAnimation();
  }
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::NextFrame()
{
  if( m_isLoaded )
  {
    m_scene.NextFrame();
  }
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::PreviousFrame()
{
  if( m_isLoaded )
  {
    m_scene.PreviousFrame();
  }
}

//----------------------------------------------------------------------------------------------------------------------

unsigned int NGLScene::GetTotNumFrames()
{
  if( m_isLoaded )
  {
    return m_scene.GetTotFrames();
  }
  else
  {
    return 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------

unsigned int NGLScene::GetCurrentFrame()
{
  if( m_isLoaded )
  {
    return m_scene.GetCurrentFrame();
  }
  else
  {
    return 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::SetCurrentMotion( const int& _currentMotion )
{
  m_scene.SetCurrentMotion( _currentMotion );
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::SetBlendingOptions( const unsigned int &_startFrame, const unsigned int &_endFrame, const unsigned int &_blendRange, const unsigned int &_type )
{
  m_scene.SetBlendingOptions( _startFrame, _endFrame, _blendRange, _type );
}

//----------------------------------------------------------------------------------------------------------------------

std::vector< unsigned int > NGLScene::CheckBlendingReady()
{
  return m_scene.CheckBlendingReady();
}

//----------------------------------------------------------------------------------------------------------------------
