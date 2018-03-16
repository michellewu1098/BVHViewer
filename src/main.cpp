#include <QApplication>
#include "MainWindow.h"

int main( int argc, char **argv )
{
  // Create an OpenGL format specifier
  QSurfaceFormat format;

  // Set the number of samples for multisampling
  // Will need to enable glEnable(GL_MULTISAMPLE); once we have a context
  format.setSamples( 4 );
  #if defined( __APPLE__ )
    // At present mac osx Mountain Lion only supports GL3.2
    // The new mavericks will have GL 4.x so can change
    format.setMajorVersion( 4 );
    format.setMinorVersion( 2 );
  #else
    // With luck we have the latest GL version so set to this
    format.setMajorVersion( 4 );
    format.setMinorVersion( 3 );
  #endif

  // now we are going to set to CoreProfile OpenGL so we can't use and old Immediate mode GL
  format.setProfile( QSurfaceFormat::CoreProfile );
  // now set the depth buffer to 24 bits
  format.setDepthBufferSize( 24 );

  QSurfaceFormat::setDefaultFormat( format );
  QApplication app( argc, argv );
  MainWindow window;
  // set the window size
  //window.resize( 1024, 720 );
  // and finally show
  window.show();

  return app.exec();
}



