/********************************************************************************
** Form generated from reading UI file 'dialogedit.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGEDIT_H
#define UI_DIALOGEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_DialogEdit
{
public:
    QGridLayout *gridLayout;
    QLineEdit *cxDesenhoEdit;
    QPushButton *btnSalvarEdit;
    QPlainTextEdit *cxObservacaoEdit;
    QLabel *label_4;
    QLabel *label_6;
    QLineEdit *cxComponenteEdit;
    QLineEdit *cxNormalEdit;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QPushButton *btnCancelarEdit;
    QSpinBox *spinQuantidadeEdit;
    QLabel *label_5;

    void setupUi(QDialog *DialogEdit)
    {
        if (DialogEdit->objectName().isEmpty())
            DialogEdit->setObjectName("DialogEdit");
        DialogEdit->resize(725, 312);
        DialogEdit->setMinimumSize(QSize(725, 312));
        DialogEdit->setMaximumSize(QSize(725, 312));
        DialogEdit->setStyleSheet(QString::fromUtf8("QLabel{\n"
"color: rgb(115, 115, 115);\n"
"}\n"
"QLineEdit{\n"
"border:1px solid  ;\n"
"border-radius:6px;\n"
"	border-color: rgb(194, 194, 194);\n"
"\n"
"}"));
        gridLayout = new QGridLayout(DialogEdit);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setContentsMargins(6, 0, 6, 6);
        cxDesenhoEdit = new QLineEdit(DialogEdit);
        cxDesenhoEdit->setObjectName("cxDesenhoEdit");
        cxDesenhoEdit->setMinimumSize(QSize(200, 40));
        QFont font;
        font.setPointSize(12);
        cxDesenhoEdit->setFont(font);

        gridLayout->addWidget(cxDesenhoEdit, 2, 2, 1, 1);

        btnSalvarEdit = new QPushButton(DialogEdit);
        btnSalvarEdit->setObjectName("btnSalvarEdit");
        btnSalvarEdit->setMinimumSize(QSize(0, 40));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        btnSalvarEdit->setFont(font1);
        btnSalvarEdit->setCursor(QCursor(Qt::PointingHandCursor));
        btnSalvarEdit->setStyleSheet(QString::fromUtf8("#btnSalvarEdit{\n"
"	background-color: rgb(230, 183, 69);\n"
"color: rgb(255, 255, 255);\n"
"border-radius:10px;\n"
"}\n"
"#btnSalvarEdit:hover{\n"
"	\n"
"	background-color: rgba(230, 183, 69, 150);\n"
"}"));

        gridLayout->addWidget(btnSalvarEdit, 5, 0, 1, 3);

        cxObservacaoEdit = new QPlainTextEdit(DialogEdit);
        cxObservacaoEdit->setObjectName("cxObservacaoEdit");
        cxObservacaoEdit->setFont(font);

        gridLayout->addWidget(cxObservacaoEdit, 4, 0, 1, 5);

        label_4 = new QLabel(DialogEdit);
        label_4->setObjectName("label_4");
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        label_4->setFont(font2);

        gridLayout->addWidget(label_4, 1, 4, 1, 1);

        label_6 = new QLabel(DialogEdit);
        label_6->setObjectName("label_6");
        QFont font3;
        font3.setPointSize(20);
        font3.setBold(true);
        label_6->setFont(font3);
        label_6->setStyleSheet(QString::fromUtf8("background-color: rgb(125, 0, 94);\n"
"color: rgb(255, 255, 255);"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_6, 0, 0, 1, 5);

        cxComponenteEdit = new QLineEdit(DialogEdit);
        cxComponenteEdit->setObjectName("cxComponenteEdit");
        cxComponenteEdit->setMinimumSize(QSize(200, 40));
        cxComponenteEdit->setFont(font);

        gridLayout->addWidget(cxComponenteEdit, 2, 0, 1, 2);

        cxNormalEdit = new QLineEdit(DialogEdit);
        cxNormalEdit->setObjectName("cxNormalEdit");
        cxNormalEdit->setMinimumSize(QSize(200, 40));
        cxNormalEdit->setFont(font);

        gridLayout->addWidget(cxNormalEdit, 2, 3, 1, 1);

        label_2 = new QLabel(DialogEdit);
        label_2->setObjectName("label_2");
        label_2->setFont(font2);

        gridLayout->addWidget(label_2, 1, 2, 1, 1);

        label = new QLabel(DialogEdit);
        label->setObjectName("label");
        label->setFont(font2);

        gridLayout->addWidget(label, 1, 0, 1, 2);

        label_3 = new QLabel(DialogEdit);
        label_3->setObjectName("label_3");
        label_3->setFont(font2);

        gridLayout->addWidget(label_3, 1, 3, 1, 1);

        btnCancelarEdit = new QPushButton(DialogEdit);
        btnCancelarEdit->setObjectName("btnCancelarEdit");
        btnCancelarEdit->setMinimumSize(QSize(0, 40));
        btnCancelarEdit->setFont(font1);
        btnCancelarEdit->setCursor(QCursor(Qt::PointingHandCursor));
        btnCancelarEdit->setStyleSheet(QString::fromUtf8("#btnCancelarEdit{\n"
"	background-color: rgb(255, 0, 0);\n"
"	color: rgb(255, 255, 255);\n"
"	border-radius:10px;\n"
"}\n"
"#btnCancelarEdit:hover{\n"
"	\n"
"	background-color: rgba(255, 0, 0, 150);\n"
"}"));

        gridLayout->addWidget(btnCancelarEdit, 5, 3, 1, 2);

        spinQuantidadeEdit = new QSpinBox(DialogEdit);
        spinQuantidadeEdit->setObjectName("spinQuantidadeEdit");
        spinQuantidadeEdit->setMinimumSize(QSize(50, 40));
        spinQuantidadeEdit->setFont(font);

        gridLayout->addWidget(spinQuantidadeEdit, 2, 4, 1, 1);

        label_5 = new QLabel(DialogEdit);
        label_5->setObjectName("label_5");
        label_5->setFont(font2);

        gridLayout->addWidget(label_5, 3, 0, 1, 1);


        retranslateUi(DialogEdit);
        QObject::connect(btnCancelarEdit, &QPushButton::clicked, DialogEdit, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(DialogEdit);
    } // setupUi

    void retranslateUi(QDialog *DialogEdit)
    {
        DialogEdit->setWindowTitle(QCoreApplication::translate("DialogEdit", "Editar registro", nullptr));
        btnSalvarEdit->setText(QCoreApplication::translate("DialogEdit", "SALVAR ALTERA\303\207\303\203O", nullptr));
        label_4->setText(QCoreApplication::translate("DialogEdit", "QUANTIDADE", nullptr));
        label_6->setText(QCoreApplication::translate("DialogEdit", "EDITAR REGISTRO", nullptr));
        label_2->setText(QCoreApplication::translate("DialogEdit", "DESENHO", nullptr));
        label->setText(QCoreApplication::translate("DialogEdit", "COMPONENTE", nullptr));
        label_3->setText(QCoreApplication::translate("DialogEdit", "NORMAL", nullptr));
        btnCancelarEdit->setText(QCoreApplication::translate("DialogEdit", "CANCELAR", nullptr));
        label_5->setText(QCoreApplication::translate("DialogEdit", "OBSERVA\303\207\303\203O", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogEdit: public Ui_DialogEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGEDIT_H
