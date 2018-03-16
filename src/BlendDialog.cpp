#include "include/BlendDialog.h"
#include "ui_BlendDialog.h"

//-------------------------------------------------------------------------------

BlendDialog::BlendDialog( NGLScene *_glWidget, QWidget *parent ) : QDialog( parent ), m_ui( new Ui::BlendDialog )
{
  m_ui->setupUi( this );
  m_glWidget = _glWidget;

  connect( m_ui->buttonBox, SIGNAL( accepted() ), this, SLOT( acceptValues() ) );
}

//-------------------------------------------------------------------------------

BlendDialog::~BlendDialog()
{
  delete m_ui;
}

//-------------------------------------------------------------------------------

void BlendDialog::acceptValues()
{
  unsigned int blendType = m_ui->m_cubicRadioButton->isChecked() ? 0 : 1;

  m_glWidget->SetBlendingOptions( ( unsigned int )m_ui->m_frameCount0->value(),
                                  ( unsigned int )m_ui->m_frameCount1->value(),
                                  ( unsigned int )m_ui->m_blendRange->value(),
                                  blendType );
}

//-------------------------------------------------------------------------------

void BlendDialog::setFrameCount( const unsigned int &_frameCount0, const unsigned int &_frameCount1 )
{
  m_ui->m_frameCount0->setMaximum( _frameCount0 - 2 );
  m_ui->m_totFrame0->setText( QString::number( _frameCount0 ) );

  m_ui->m_frameCount1->setMaximum( _frameCount1 - 2 );
  m_ui->m_totFrame1->setText( QString::number( _frameCount1 ) );
}

//-------------------------------------------------------------------------------
