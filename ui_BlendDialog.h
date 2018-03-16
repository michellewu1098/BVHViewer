/********************************************************************************
** Form generated from reading UI file 'BlendDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLENDDIALOG_H
#define UI_BLENDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_BlendDialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QLabel *From;
    QLabel *To;
    QLabel *Animation1;
    QLabel *Animation2;
    QLabel *Frame1;
    QLabel *Frame2;
    QSpinBox *m_frameCount0;
    QSpinBox *m_frameCount1;
    QFrame *line;
    QLabel *Description;
    QLabel *For;
    QLabel *Using;
    QRadioButton *m_cubicRadioButton;
    QRadioButton *m_slerpRadioButton;
    QSpinBox *m_blendRange;
    QLabel *label;
    QLabel *m_totFrame0;
    QLabel *label_2;
    QLabel *m_totFrame1;

    void setupUi(QDialog *BlendDialog)
    {
        if (BlendDialog->objectName().isEmpty())
            BlendDialog->setObjectName(QStringLiteral("BlendDialog"));
        BlendDialog->resize(321, 300);
        buttonBox = new QDialogButtonBox(BlendDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(110, 250, 201, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(BlendDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 301, 231));
        From = new QLabel(groupBox);
        From->setObjectName(QStringLiteral("From"));
        From->setGeometry(QRect(0, 70, 45, 20));
        To = new QLabel(groupBox);
        To->setObjectName(QStringLiteral("To"));
        To->setGeometry(QRect(0, 120, 45, 20));
        Animation1 = new QLabel(groupBox);
        Animation1->setObjectName(QStringLiteral("Animation1"));
        Animation1->setGeometry(QRect(55, 70, 81, 20));
        Animation2 = new QLabel(groupBox);
        Animation2->setObjectName(QStringLiteral("Animation2"));
        Animation2->setGeometry(QRect(55, 120, 81, 20));
        Frame1 = new QLabel(groupBox);
        Frame1->setObjectName(QStringLiteral("Frame1"));
        Frame1->setGeometry(QRect(140, 70, 60, 20));
        Frame2 = new QLabel(groupBox);
        Frame2->setObjectName(QStringLiteral("Frame2"));
        Frame2->setGeometry(QRect(140, 120, 60, 20));
        m_frameCount0 = new QSpinBox(groupBox);
        m_frameCount0->setObjectName(QStringLiteral("m_frameCount0"));
        m_frameCount0->setGeometry(QRect(190, 68, 51, 24));
        m_frameCount0->setMinimum(1);
        m_frameCount0->setMaximum(500);
        m_frameCount0->setValue(10);
        m_frameCount1 = new QSpinBox(groupBox);
        m_frameCount1->setObjectName(QStringLiteral("m_frameCount1"));
        m_frameCount1->setGeometry(QRect(190, 118, 51, 24));
        m_frameCount1->setMinimum(1);
        m_frameCount1->setMaximum(500);
        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 150, 301, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        Description = new QLabel(groupBox);
        Description->setObjectName(QStringLiteral("Description"));
        Description->setGeometry(QRect(10, 40, 231, 16));
        For = new QLabel(groupBox);
        For->setObjectName(QStringLiteral("For"));
        For->setGeometry(QRect(0, 170, 45, 20));
        Using = new QLabel(groupBox);
        Using->setObjectName(QStringLiteral("Using"));
        Using->setGeometry(QRect(120, 170, 91, 20));
        m_cubicRadioButton = new QRadioButton(groupBox);
        m_cubicRadioButton->setObjectName(QStringLiteral("m_cubicRadioButton"));
        m_cubicRadioButton->setGeometry(QRect(220, 170, 71, 20));
        m_cubicRadioButton->setChecked(true);
        m_slerpRadioButton = new QRadioButton(groupBox);
        m_slerpRadioButton->setObjectName(QStringLiteral("m_slerpRadioButton"));
        m_slerpRadioButton->setGeometry(QRect(220, 190, 100, 20));
        m_blendRange = new QSpinBox(groupBox);
        m_blendRange->setObjectName(QStringLiteral("m_blendRange"));
        m_blendRange->setGeometry(QRect(57, 168, 51, 24));
        m_blendRange->setMinimum(1);
        m_blendRange->setValue(5);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(245, 70, 21, 20));
        m_totFrame0 = new QLabel(groupBox);
        m_totFrame0->setObjectName(QStringLiteral("m_totFrame0"));
        m_totFrame0->setGeometry(QRect(255, 70, 31, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(245, 120, 16, 20));
        m_totFrame1 = new QLabel(groupBox);
        m_totFrame1->setObjectName(QStringLiteral("m_totFrame1"));
        m_totFrame1->setGeometry(QRect(255, 120, 31, 20));

        retranslateUi(BlendDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), BlendDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), BlendDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(BlendDialog);
    } // setupUi

    void retranslateUi(QDialog *BlendDialog)
    {
        BlendDialog->setWindowTitle(QApplication::translate("BlendDialog", "Interpolation options", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("BlendDialog", "Interpolation", Q_NULLPTR));
        From->setText(QApplication::translate("BlendDialog", "<html><head/><body><p align=\"right\"><span style=\" font-weight:600;\">From</span></p></body></html>", Q_NULLPTR));
        To->setText(QApplication::translate("BlendDialog", "<html><head/><body><p align=\"right\"><span style=\" font-weight:600;\">To</span></p></body></html>", Q_NULLPTR));
        Animation1->setText(QApplication::translate("BlendDialog", "<html><head/><body><p><span style=\" font-style:italic;\">Animation 1</span></p></body></html>", Q_NULLPTR));
        Animation2->setText(QApplication::translate("BlendDialog", "<html><head/><body><p><span style=\" font-style:italic;\">Animation 2</span></p></body></html>", Q_NULLPTR));
        Frame1->setText(QApplication::translate("BlendDialog", "Frame:", Q_NULLPTR));
        Frame2->setText(QApplication::translate("BlendDialog", "Frame:", Q_NULLPTR));
        Description->setText(QApplication::translate("BlendDialog", "Choose range of frames for blending:", Q_NULLPTR));
        For->setText(QApplication::translate("BlendDialog", "<html><head/><body><p align=\"right\">For</p></body></html>", Q_NULLPTR));
        Using->setText(QApplication::translate("BlendDialog", "frames, using", Q_NULLPTR));
        m_cubicRadioButton->setText(QApplication::translate("BlendDialog", "Cubic", Q_NULLPTR));
        m_slerpRadioButton->setText(QApplication::translate("BlendDialog", "SLERP", Q_NULLPTR));
        label->setText(QApplication::translate("BlendDialog", "/", Q_NULLPTR));
        m_totFrame0->setText(QString());
        label_2->setText(QApplication::translate("BlendDialog", "/", Q_NULLPTR));
        m_totFrame1->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BlendDialog: public Ui_BlendDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLENDDIALOG_H
