#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include "conexao.h"
#include <QMessageBox>
#include "dialogedit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //inicializa as variaveis globais
    QString bd  = "/db/bd_armario.db";
    QString sql = "";
    QSqlQuery query;
    Conexao con;
    bool logado = false;
    int linhaTabelaSelecionada = -1;

    //Funcao que retorna a escolha do botao Caixa de dialogo
    int message_box(QString titulo,QString texto){
        QMessageBox msgBox;
        msgBox.setWindowTitle(titulo);
        msgBox.setText(texto);
        msgBox.addButton("Sim",QMessageBox::YesRole);
        msgBox.addButton("Cancelar",QMessageBox::NoRole);
        msgBox.setIcon(QMessageBox::Question);
        int resultado = msgBox.exec();
        return resultado;
    }

private slots:
    //Funcoes criadas
    void inicializar();
    void muda_tela(int n);
    void quantidadeItens();
    void limpa_campos();
    void combo_ativado();
    void editarLinha();
    void exibirDadosNaTabela(const QString &armario_formatado);
    void preenche_combo();

    //Acoes de navegacao das telas
    void on_btnCadastro_clicked();
    void on_btnInventario_clicked();
    void on_btnIcoCadastro_clicked();
    void on_btnIcoInventario_clicked();
    void on_btnIcoMapa_clicked();
    void on_btnMapa_clicked();
    void on_btnImpExp_clicked();
    void on_btnIcoImpExp_clicked();

    //Funcoes de acoes dos botoes
    void on_btnCadastrar_clicked();
    void on_btnEditarEstoque_clicked();
    void on_cxPesquisa_textChanged(const QString &arg1);
    void on_btnBuscaEstoque_clicked();
    void on_btnExcluir_clicked();
    void on_btnBuscaPlanilha_clicked();


    void on_btnExportar_clicked();

    void on_btnSalvarNoBanco_clicked();

public slots:


private:
    Ui::MainWindow *ui;
    QPushButton *botaoEditar;
};


#endif // MAINWINDOW_H
