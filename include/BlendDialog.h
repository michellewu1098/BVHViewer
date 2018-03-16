//----------------------------------------------------------------------------------------------------------------------
/// @file BlendDialog.h
/// @brief Dialog window that handles the user interface design and interaction for interpolation/blending between animations
/// @author Michelle Wu
/// @version 1.0
//----------------------------------------------------------------------------------------------------------------------

#ifndef BLENDDIALOG_H
#define BLENDDIALOG_H

#include <QDialog>
#include "NGLScene.h"

namespace Ui
{
  class BlendDialog;
}

class BlendDialog : public QDialog
{
  Q_OBJECT

public:

  //-------------------------------------------------------------------------------
  /// @brief Ctor
  //-------------------------------------------------------------------------------
  explicit BlendDialog( NGLScene* _glWidget, QWidget *parent = 0 );
  //-------------------------------------------------------------------------------
  /// @brief Dtor
  //-------------------------------------------------------------------------------
  ~BlendDialog();
  //-------------------------------------------------------------------------------
  /// @brief Sets the frame count (total number of frames in animation) for both Animation 1 and Animation 2
  /// @param [in] _frameCount0 Frame count for Animation 1
  /// @param [in] _frameCount1 Frame count for Animation 2
  //-------------------------------------------------------------------------------
  void setFrameCount( const unsigned int& _frameCount0, const unsigned int& _frameCount1 );
  //-------------------------------------------------------------------------------

private slots:

  //-------------------------------------------------------------------------------
  /// @brief Accepts values and passes them to main window
  //-------------------------------------------------------------------------------
  void acceptValues();
  //-------------------------------------------------------------------------------

private:

  //-------------------------------------------------------------------------------
  /// @brief User interface
  //-------------------------------------------------------------------------------
  Ui::BlendDialog *m_ui;
  //-------------------------------------------------------------------------------
  /// @brief OpenGL widget (our scene)
  //-------------------------------------------------------------------------------
  NGLScene* m_glWidget;
  //-------------------------------------------------------------------------------

};

#endif // BLENDDIALOG_H
