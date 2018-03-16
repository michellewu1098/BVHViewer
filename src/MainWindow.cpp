#include "include/MainWindow.h"
#include "ui_MainWindow.h"

#include <QGroupBox>
#include <QIcon>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardItemModel>

//-------------------------------------------------------------------------------

MainWindow::MainWindow( QWidget* _parent) : QMainWindow( _parent ), m_ui( new Ui::MainWindow )
{
  m_ui->setupUi( this );
  m_glWidget = new NGLScene( this );

  m_ui->s_mainWindowGridLayout->addWidget( m_glWidget, 1, 0, 2, 1 );

  // Disable all buttons before loading .bvh file
  m_ui->m_playButton->setEnabled( false );
  m_ui->m_pauseButton->setEnabled( false );
  m_ui->m_backwardButton->setEnabled( false );
  m_ui->m_forwardButton->setEnabled( false );
  m_ui->m_nextFrameButton->setEnabled( false );
  m_ui->m_prevFrameButton->setEnabled( false );

  QStringList menuItems = { "Animation 1", "Animation 2", "Blended Animation" };
  m_ui->m_fileMenu->addItems( menuItems );

  connect( m_ui->m_loadButton, SIGNAL( clicked() ), this, SLOT( loadButtonClicked() ) );
  connect( m_ui->m_playButton, SIGNAL( clicked() ), this, SLOT( playButtonClicked() ) );
  connect( m_ui->m_pauseButton, SIGNAL( clicked() ), this, SLOT( pauseButtonClicked() ) );
  connect( m_ui->m_backwardButton, SIGNAL( clicked() ), this, SLOT( backwardButtonClicked() ) );
  connect( m_ui->m_forwardButton, SIGNAL( clicked() ), this, SLOT( forwardButtonClicked() ) );
  connect( m_ui->m_nextFrameButton, SIGNAL( clicked() ), this, SLOT( nextFrameButtonClicked() ) );
  connect( m_ui->m_prevFrameButton, SIGNAL( clicked() ), this, SLOT( previousFrameButtonClicked() ) );
  connect( m_ui->m_fileMenu, SIGNAL( currentIndexChanged( int ) ), this, SLOT( indexChanged( int ) ) );
  connect( m_ui->m_blendButton, SIGNAL( clicked() ), this, SLOT( blendButtonClicked() ) );
  connect( m_ui->m_resetAnimation, SIGNAL( clicked() ), this, SLOT( resetButtonClicked() ) );
}

//-------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
  delete m_ui;
}

//-------------------------------------------------------------------------------

void MainWindow::loadButtonClicked()
{
  QString filename = QFileDialog::getOpenFileName( this,
                                                   tr( "Open File" ),
                                                   "bvh/",
                                                   "BVH File (*.bvh)" );

  if( !filename.endsWith( tr( "bvh" ) ) )
  {
    QMessageBox::information( this, tr( "Error" ), QString( "No file selected.") );
  }
  else
  {
    QString file = filename.mid( filename.lastIndexOf("/" ) );
    m_ui->m_filename->setText( file );
    m_glWidget->SetBVHFilePath( filename.toStdString() );

    m_ui->m_playButton->setEnabled( true );
    m_ui->m_pauseButton->setEnabled( false );
    m_ui->m_backwardButton->setEnabled( true );
    m_ui->m_forwardButton->setEnabled( true );
  }
}

//-------------------------------------------------------------------------------

void MainWindow::playButtonClicked()
{
  m_glWidget->PauseAnimation( false );

  m_ui->m_pauseButton->setEnabled( true );
  m_ui->m_forwardButton->setEnabled( true );
  m_ui->m_backwardButton->setEnabled( true );

  m_ui->m_playButton->setEnabled( false );
  m_ui->m_nextFrameButton->setEnabled( false );
  m_ui->m_prevFrameButton->setEnabled( false );
}

//-------------------------------------------------------------------------------

void MainWindow::pauseButtonClicked()
{
  m_glWidget->PauseAnimation( true );

  m_ui->m_playButton->setEnabled( true );
  m_ui->m_nextFrameButton->setEnabled( true );
  m_ui->m_prevFrameButton->setEnabled( true );

  m_ui->m_pauseButton->setEnabled( false );
  m_ui->m_backwardButton->setEnabled( false );
  m_ui->m_forwardButton->setEnabled( false );
}

//-------------------------------------------------------------------------------

void MainWindow::backwardButtonClicked()
{
  m_glWidget->BackwardAnimation();
}

//-------------------------------------------------------------------------------

void MainWindow::forwardButtonClicked()
{
  m_glWidget->ForwardAnimation();
}

//-------------------------------------------------------------------------------

void MainWindow::nextFrameButtonClicked()
{
  m_glWidget->NextFrame();
}

//-------------------------------------------------------------------------------

void MainWindow::previousFrameButtonClicked()
{
  m_glWidget->PreviousFrame();
}

//-------------------------------------------------------------------------------

void MainWindow::indexChanged( const int &_changedIndex )
{
  m_glWidget->SetCurrentMotion( _changedIndex );
}

//-------------------------------------------------------------------------------

void MainWindow::blendButtonClicked()
{
  std::vector< unsigned int > numFramesAnim = m_glWidget->CheckBlendingReady();

  if( numFramesAnim[ 0 ] == 0 || numFramesAnim[ 1 ] == 0 )
  {
    QMessageBox::information( this, tr( "Error" ), QString( "Load two animations first.") );
  }
  else
  {
    m_blendDialog = new BlendDialog( m_glWidget, this );
    m_blendDialog->setFrameCount( numFramesAnim[ 0 ], numFramesAnim[ 1 ] );
    m_blendDialog->show();
  }
}

//-------------------------------------------------------------------------------

void MainWindow::resetButtonClicked()
{
  m_glWidget->ResetAnimation();
}

//-------------------------------------------------------------------------------
