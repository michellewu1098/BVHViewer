/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *s_mainWindowGridLayout;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QPushButton *m_loadButton;
    QFrame *line;
    QPushButton *m_playButton;
    QPushButton *m_pauseButton;
    QPushButton *m_backwardButton;
    QPushButton *m_forwardButton;
    QLabel *m_filename;
    QLabel *label;
    QComboBox *m_fileMenu;
    QPushButton *m_prevFrameButton;
    QPushButton *m_nextFrameButton;
    QPushButton *m_blendButton;
    QPushButton *m_resetAnimation;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(972, 656);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        s_mainWindowGridLayout = new QGridLayout(centralwidget);
        s_mainWindowGridLayout->setObjectName(QStringLiteral("s_mainWindowGridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        s_mainWindowGridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMaximumSize(QSize(16777215, 55));
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        m_loadButton = new QPushButton(groupBox);
        m_loadButton->setObjectName(QStringLiteral("m_loadButton"));
        m_loadButton->setGeometry(QRect(0, 22, 51, 32));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/icons/load.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_loadButton->setIcon(icon);
        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(45, 20, 16, 31));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        m_playButton = new QPushButton(groupBox);
        m_playButton->setObjectName(QStringLiteral("m_playButton"));
        m_playButton->setGeometry(QRect(760, 22, 51, 32));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/icons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_playButton->setIcon(icon1);
        m_pauseButton = new QPushButton(groupBox);
        m_pauseButton->setObjectName(QStringLiteral("m_pauseButton"));
        m_pauseButton->setGeometry(QRect(805, 22, 51, 32));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_pauseButton->sizePolicy().hasHeightForWidth());
        m_pauseButton->setSizePolicy(sizePolicy1);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/icons/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pauseButton->setIcon(icon2);
        m_backwardButton = new QPushButton(groupBox);
        m_backwardButton->setObjectName(QStringLiteral("m_backwardButton"));
        m_backwardButton->setGeometry(QRect(715, 22, 51, 32));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/icons/backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_backwardButton->setIcon(icon3);
        m_forwardButton = new QPushButton(groupBox);
        m_forwardButton->setObjectName(QStringLiteral("m_forwardButton"));
        m_forwardButton->setGeometry(QRect(850, 22, 51, 32));
        sizePolicy1.setHeightForWidth(m_forwardButton->sizePolicy().hasHeightForWidth());
        m_forwardButton->setSizePolicy(sizePolicy1);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/icons/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_forwardButton->setIcon(icon4);
        m_filename = new QLabel(groupBox);
        m_filename->setObjectName(QStringLiteral("m_filename"));
        m_filename->setGeometry(QRect(160, 27, 191, 20));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 27, 81, 20));
        m_fileMenu = new QComboBox(groupBox);
        m_fileMenu->setObjectName(QStringLiteral("m_fileMenu"));
        m_fileMenu->setGeometry(QRect(375, 24, 151, 26));
        m_prevFrameButton = new QPushButton(groupBox);
        m_prevFrameButton->setObjectName(QStringLiteral("m_prevFrameButton"));
        m_prevFrameButton->setGeometry(QRect(670, 22, 51, 32));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/icons/previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_prevFrameButton->setIcon(icon5);
        m_nextFrameButton = new QPushButton(groupBox);
        m_nextFrameButton->setObjectName(QStringLiteral("m_nextFrameButton"));
        m_nextFrameButton->setGeometry(QRect(895, 22, 51, 32));
        sizePolicy1.setHeightForWidth(m_nextFrameButton->sizePolicy().hasHeightForWidth());
        m_nextFrameButton->setSizePolicy(sizePolicy1);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/icons/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_nextFrameButton->setIcon(icon6);
        m_blendButton = new QPushButton(groupBox);
        m_blendButton->setObjectName(QStringLiteral("m_blendButton"));
        m_blendButton->setGeometry(QRect(525, 22, 101, 32));
        m_resetAnimation = new QPushButton(groupBox);
        m_resetAnimation->setObjectName(QStringLiteral("m_resetAnimation"));
        m_resetAnimation->setGeometry(QRect(625, 22, 51, 32));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icons/icons/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_resetAnimation->setIcon(icon7);

        s_mainWindowGridLayout->addWidget(groupBox, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 972, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "BVH Viewer", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        m_loadButton->setText(QString());
        m_playButton->setText(QString());
        m_pauseButton->setText(QString());
        m_backwardButton->setText(QString());
        m_forwardButton->setText(QString());
        m_filename->setText(QString());
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Current File:</span></p></body></html>", Q_NULLPTR));
        m_prevFrameButton->setText(QString());
        m_nextFrameButton->setText(QString());
        m_blendButton->setText(QApplication::translate("MainWindow", "Interpolate", Q_NULLPTR));
        m_resetAnimation->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
