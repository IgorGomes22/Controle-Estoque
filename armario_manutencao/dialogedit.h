#ifndef DIALOGEDIT_H
#define DIALOGEDIT_H

#include <QDialog>
#include "mainwindow.h"


namespace Ui {
class DialogEdit;
}
class DialogEdit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEdit(QWidget *parent = nullptr);
    ~DialogEdit();

    //Conexao con; //instancia classe Conexao

    int idBanco;
    QString armario_formatado;


    void setDadosParaEdicao(const QString id,const QString componente,const QString desenho,const QString normal,const QString observacao,const QString quantidade,const QString armario_formatado);
    void salvarEdicao();

private slots:

    void on_btnSalvarEdit_clicked();

private:
    Ui::DialogEdit *ui;

};

#endif // DIALOGEDIT_H
