#include "dialogedit.h"
#include "ui_dialogedit.h"
#include <QMessageBox>
#include <QtSql>


DialogEdit::DialogEdit(QWidget *parent) :QDialog(parent),ui(new Ui::DialogEdit)
{
    ui->setupUi(this);

}

DialogEdit::~DialogEdit(){delete ui;}


void DialogEdit::setDadosParaEdicao(const QString id,const QString componente,const QString desenho,const QString normal,const QString quantidade,const QString observacao,const QString armario_formatado){
    idBanco = id.toInt();
    this->armario_formatado = armario_formatado;
    ui->cxComponenteEdit->setText(componente);
    ui->cxDesenhoEdit->setText(desenho);
    ui->cxNormalEdit->setText(normal);
    ui->spinQuantidadeEdit->setValue(quantidade.toInt());
    ui->cxObservacaoEdit->setPlainText(observacao);
}

void DialogEdit::salvarEdicao() {
    int id = idBanco;
    QString armario = armario_formatado;
    QString componente = ui->cxComponenteEdit->text();
    QString desenho = ui->cxDesenhoEdit->text();
    QString normal = ui->cxNormalEdit->text();
    QString observacao = ui->cxObservacaoEdit->toPlainText();
    int quantidade = ui->spinQuantidadeEdit->value();


    QSqlDatabase db = QSqlDatabase::database();
    if (db.open()){

        QSqlQuery query;

        if (query.exec("UPDATE \""+armario+"\" SET componente = '" + componente + "', desenho = '" + desenho + "', normal = '" + normal + "', observacao = '" + observacao + "', quantidade = " + QString::number(quantidade) + " WHERE id = " + QString::number(id))) {
            accept(); // Fecha a janela de edição
        }else {
            // Trate o erro, por exemplo, exiba uma mensagem de erro
            QMessageBox::critical(this, "Erro", "Erro ao salvar as edições: " + query.lastError().text());
        }
    }
}


void DialogEdit::on_btnSalvarEdit_clicked()
{
    salvarEdicao();
}

