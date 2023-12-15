#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "conexao.h"
#include "Formata_armario.h"
#include <QtWidgets>
#include <QDebug>
#include "dialogedit.h"
#include "xlsxdocument.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    inicializar();
    preenche_combo();

    connect(ui->comboArmarioEstoque, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::combo_ativado);
    connect(ui->comboLinhasEstoque, QOverload<int>::of(&QComboBox::activated),this,&MainWindow::combo_ativado);

}

MainWindow::~MainWindow(){delete ui;}

void MainWindow::inicializar(){
    //manipula colunas da tabela:
    ui->tabela->setColumnHidden(0,true);
    ui->tabela->setColumnWidth(1,150);
    ui->tabela->setColumnWidth(2,100);
    ui->tabela->setColumnWidth(3,100);
    ui->tabela->setColumnWidth(4,85);
    ui->tabela->setColumnWidth(5,200);

    ui->tabelaPlanilha->setColumnWidth(0,150);
    ui->tabelaPlanilha->setColumnWidth(1,100);
    ui->tabelaPlanilha->setColumnWidth(2,100);
    ui->tabelaPlanilha->setColumnWidth(3,85);
    ui->tabelaPlanilha->setColumnWidth(4,200);

    ui->sideBotao->hide();
    ui->btnSideMenu->setChecked(1);
    ui->btnIcoCadastro->setChecked(1);
    ui->stackedWidget->setCurrentIndex(0);

    if (!con.abrir(bd)){
        ui->statusBar->showMessage("Fechado!");
        message_box("Erro","Nao foi possivel abrir o banco\n"+query.lastError().text());
    }else{
        ui->statusBar->showMessage("Aberto!");
    }
}

//Acoes de navegacao das telas
void MainWindow::on_btnCadastro_clicked(){muda_tela(0);}
void MainWindow::on_btnInventario_clicked(){muda_tela(1);}
void MainWindow::on_btnMapa_clicked(){quantidadeItens();muda_tela(2);}
void MainWindow::on_btnImpExp_clicked(){muda_tela(3);}
void MainWindow::on_btnIcoCadastro_clicked(){muda_tela(0);}
void MainWindow::on_btnIcoInventario_clicked(){muda_tela(1);}
void MainWindow::on_btnIcoMapa_clicked(){quantidadeItens();muda_tela(2);}
void MainWindow::on_btnIcoImpExp_clicked(){muda_tela(3);}


//Funcoes de acoes dos botoes
void MainWindow::muda_tela(int n){ui->stackedWidget->setCurrentIndex(n);}

void MainWindow::on_btnCadastrar_clicked(){
    FormataArmario  formata;
    QString armario = ui->comboArmario->currentText();
    QString linha = ui->comboLinha->currentText();
    QString componente = ui->cxComponente->text().toUpper();
    QString desenho = ui->cxDesenho->text().toUpper();
    QString normal = ui->cxNormal->text().toUpper();
    QString observacao = ui->cxObservacao->toPlainText().toUpper();
    int quantidade = ui->spinQuantidade->value();
    bool verificado = false;

    if (armario.isEmpty() || linha.isEmpty() || componente.isEmpty()){
        ui->statusBar->showMessage("Preencha os campos obrigatorios*!");
        QMessageBox::information(this,"Cadastro","Preencha os campos obrigatorios*");
        return;
    }
    QString armario_formatado = formata.armario(armario,linha);
    QSqlQuery query(con.bancoDeDados);

    if(!con.abrir(bd)){
        ui->statusBar->showMessage("Falha na conexao!");
        QMessageBox::information(this,"Cadastro","Falha na conexao com o banco de dados\n"+query.lastError().text());
        return;
    }
        //veririfica se desenho ou o normal já está cadastrado
    if(!desenho.isEmpty() || !normal.isEmpty()){
        QString consulta = "SELECT * FROM \""+armario_formatado+"\" WHERE ";
        bool pesquisado = false;

        if (!normal.isEmpty()){
            pesquisado = true;
        }

        if (!normal.isEmpty()){
            consulta += " NORMAL = :normal";
        }
        if (!desenho.isEmpty()){
            if (pesquisado){
                consulta += " OR DESENHO = :desenho";
            }else{
                consulta += " DESENHO = :desenho";
            }
        }

        query.prepare(consulta);

        if (!normal.isEmpty()){
            query.bindValue(":normal",normal);
        }
        if (!desenho.isEmpty()){
            query.bindValue(":desenho",desenho);
        }
        if (query.exec()){
            int cont = 0;

            while(query.next()){
                cont++;
            }

            if (cont > 0){
                ui->statusBar->showMessage("Já cadastrado!");
                int resultado = message_box("Duplicidade de cadastro","Já possui "+QString::number(cont)+" registros com este Desenho ou Normal cadastrado!\n\nDeseja cadastrar mesmo assim?");

                if (resultado == 0){
                    verificado = false;
                }else if(resultado == 1){
                    verificado = true;
                    return;
                }
            }
        }
    }
    if (!verificado){
        sql = "INSERT INTO \""+armario_formatado+"\" (COMPONENTE,DESENHO,NORMAL,QUANTIDADE,OBSERVACAO) VALUES(:componente,:desenho,:normal,:quantidade,:observacao)";
        query.prepare(sql);
        query.bindValue(":componente",componente);
        query.bindValue(":desenho",desenho);
        query.bindValue(":normal",normal);
        query.bindValue(":quantidade",quantidade);
        query.bindValue(":observacao",observacao);

        if (query.exec()){
            ui->statusBar->showMessage("Cadastrado com sucesso!");
            QMessageBox::information(this,"\nCadastro","Componente cadastrado com sucesso!");
            limpa_campos();
        }else{
            ui->statusBar->showMessage("Falha ao cadastrar");
            QMessageBox::information(this,"Cadastro","Falha ao cadastrar componente!");
        }
    }
    con.fechar();
}

void MainWindow::limpa_campos(){
    //ui->comboArmario->setCurrentIndex(0);
    //ui->comboLinha->setCurrentIndex(0);
    ui->cxComponente->clear();
    ui->cxDesenho->clear();
    ui->cxNormal->clear();
    ui->cxObservacao->clear();
    ui->spinQuantidade->setValue(0);
}

void MainWindow::combo_ativado(){
    QString armario = ui->comboArmarioEstoque->currentText();
    QString linha = ui->comboLinhasEstoque->currentText();
    if (!armario.isEmpty() and !linha.isEmpty()){
        MainWindow::on_btnBuscaEstoque_clicked();
    }else{
        ui->statusBar->showMessage("Selecione o armario e a linha");
    }
}

void MainWindow::on_btnBuscaEstoque_clicked(){
    FormataArmario  formata;
    QString armario = ui->comboArmarioEstoque->currentText();
    QString linha = ui->comboLinhasEstoque->currentText();
    ui->cxPesquisa->setText("");
    ui->tabela->clearContents();
    ui->tabela->setRowCount(0);

    if (armario.isEmpty() || linha.isEmpty()){
        ui->statusBar->showMessage("Selecione o armario e a linha!");
        QMessageBox::information(this,"Busca dados","Selecione armario e linha");
        return;
    }

    QString armario_formatado = formata.armario(armario,linha);

    if(con.abrir(bd)){
        exibirDadosNaTabela(armario_formatado);
    }else{
        ui->statusBar->showMessage("Falha na conexão!");
        QMessageBox::information(this, "Busca dados", "Falha na conexão com o banco de dados\n"+query.lastError().text());
        return;
    }
    con.fechar();
}

void MainWindow::exibirDadosNaTabela(const QString &armario_formatado){
    QSqlQuery query(con.bancoDeDados);

    if(con.abrir(bd)){
        if (query.exec("SELECT * FROM \""+armario_formatado+"\"")){
            if (query.next()){ //verifica se ha pelo menos um registro
                //ui->tabela->setColumnCount(7);
                ui->tabela->clearContents();
                ui->tabela->setRowCount(0);

                int row = 0;
                do{
                    ui->tabela->insertRow(row);

                    for (int column =0; column <6; ++column){
                        QTableWidgetItem *item = new QTableWidgetItem(query.value(column).toString());
                        ui->tabela->setItem(row,column,item);
                    }
                    row++;
                }while (query.next());

                ui->tabela->resizeRowsToContents();
                ui->tabela->resizeColumnsToContents();
                ui->statusBar->showMessage("Busca realizada!");
            }else{
                QMessageBox::information(this,"Busca de dados","Nao foi encontrados registros.");
                ui->statusBar->showMessage("Nenhum registro encontrado.");
            }
        }else{
            QMessageBox::warning(this,"Erro","Erro ao buscar dados");
            ui->statusBar->showMessage("Erro ao buscar dados: ");
        }
    }
    con.fechar();
}

void MainWindow::on_cxPesquisa_textChanged(const QString &arg1){
    FormataArmario formata;
    QString armario = ui->comboArmarioEstoque->currentText();
    QString linha = ui->comboLinhasEstoque->currentText();
    QString texto = ui->cxPesquisa->text().toUpper();

    if (!armario.isEmpty() and !linha.isEmpty()){
        if(con.abrir(bd)){
            QSqlQuery query(con.bancoDeDados);
            QString armario_formatado = formata.armario(armario,linha);
            QString consulta = "SELECT * FROM \""+armario_formatado+"\" WHERE COMPONENTE LIKE :texto OR DESENHO LIKE :texto OR NORMAL LIKE :texto";
            query.prepare(consulta);
            query.bindValue(":texto","%" + texto + "%");
            if (query.exec()){
                int row = 0;
                ui->tabela->clearContents();
                ui->tabela->setRowCount(0);
                while (query.next()){
                    ui->tabela->insertRow(row);
                    for (int column =0; column <6; ++column){
                        QTableWidgetItem *item = new QTableWidgetItem(query.value(column).toString());
                        ui->tabela->setItem(row,column,item);
                    }
                    row++;
                }
                ui->statusBar->showMessage("Busca realizada!");
            }
        }
    }else{
        QMessageBox::information(this,"Pesquisa","Selecione armario e linha!");
        ui->statusBar->showMessage("Selecione armario e linha");
    }
    con.fechar();
}

void MainWindow::quantidadeItens(){
    QMap<QString, int>quantidades;
    //lista com os nomes das tabelas
    QStringList tabelas = {"eletronico_fire","eletronico_firefly","eletronico_turbo","mecanico_fire","mecanico_firefly","mecanico_turbo"};
    QSqlQuery query(con.bancoDeDados);

    if (con.abrir(bd)){
        for (const QString &tabela : tabelas){
            QString consulta = "SELECT COUNT(*) FROM " +tabela;
            if (query.exec(consulta)){
                if (query.next()){
                    int quantidade = query.value(0).toInt();
                    quantidades[tabela] = quantidade;
                    ui->statusBar->showMessage("Busca realizada com sucesso!");
                }else{
                    ui->statusBar->showMessage("Nenhum resultado encontrado");
                }
            }else{
                ui->statusBar->showMessage("Erro ao executar a consulta");
            }
        }
    }

    ui->lbEletronicoFire->setText(QString::number(quantidades.value("eletronico_fire")));
    ui->lbEletronicoFirefly->setText(QString::number(quantidades.value("eletronico_firefly")));
    ui->lbEletronicoTurbo->setText(QString::number(quantidades.value("eletronico_turbo")));
    ui->lbMecanicoFire->setText(QString::number(quantidades.value("mecanico_fire")));
    ui->lbMecanicoFirefly->setText(QString::number(quantidades.value("mecanico_firefly")));
    ui->lbMecanicoTurbo->setText(QString::number(quantidades.value("mecanico_turbo")));

    int totalFire =0,totalFirefly = 0, totalTurbo = 0;
    totalFire = quantidades.value("eletronico_fire") + quantidades.value("mecanico_fire");
    totalFirefly = quantidades.value("eletronico_firefly") + quantidades.value("mecanico_firefly");
    totalTurbo = quantidades.value("eletronico_turbo") + quantidades.value("mecanico_turbo");

    ui->lbTotalFire->setText(QString::number(totalFire));
    ui->lbTotalFirefly->setText(QString::number(totalFirefly));
    ui->lbTotalTurbo->setText(QString::number(totalTurbo));

    con.fechar();
}

void MainWindow::on_btnEditarEstoque_clicked(){editarLinha();}

void MainWindow::editarLinha(){
    linhaTabelaSelecionada = ui->tabela->currentRow();

    if (linhaTabelaSelecionada !=-1){
        QTableWidgetItem *id1 = ui->tabela->item(linhaTabelaSelecionada,0);
        QTableWidgetItem *componente1= ui->tabela->item(linhaTabelaSelecionada,1);
        QTableWidgetItem *desenho1 = ui->tabela->item(linhaTabelaSelecionada,2);
        QTableWidgetItem *normal1 = ui->tabela->item(linhaTabelaSelecionada,3);
        QTableWidgetItem *quantidade1 = ui->tabela->item(linhaTabelaSelecionada,4);
        QTableWidgetItem *observacao1 = ui->tabela->item(linhaTabelaSelecionada,5);

        QString id = id1->text();
        QString componente = componente1->text();
        QString desenho = desenho1->text();
        QString normal = normal1->text();
        QString quantidade = quantidade1->text();
        QString observacao = observacao1->text();


        FormataArmario  formata;
        QString armario = ui->comboArmarioEstoque->currentText();
        QString linha = ui->comboLinhasEstoque->currentText();
        QString tabela_formatada = formata.armario(armario,linha);

        DialogEdit dialogEdit;
        dialogEdit.setDadosParaEdicao(id,componente,desenho,normal,quantidade,observacao,tabela_formatada);


        int resultado = dialogEdit.exec();
        if(resultado == QDialog::Accepted){
            on_btnBuscaEstoque_clicked();
            //atualizar edicoes no banco aqui

        }
    }
    con.fechar();
}

void MainWindow::on_btnExcluir_clicked(){
    int linhaDelete = ui->tabela->currentRow();

    if (linhaDelete ==-1){
        return;
    }else{
        FormataArmario formata;
        QString armario = ui->comboArmarioEstoque->currentText();
        QString linha = ui->comboLinhasEstoque->currentText();
        QString armario_formatado = formata.armario(armario,linha);
        int resultado = message_box("Delete","Deseja excluir este registro?");

        if (resultado == 0){

            QTableWidgetItem *idDelete = ui->tabela->item(linhaDelete,0);
            QString id = idDelete->text();

            QSqlDatabase db = QSqlDatabase::database();
            if(db.open()){
                QSqlQuery query;

                if (query.exec("DELETE FROM \""+armario_formatado+"\" WHERE id = "+id)){
                    ui->statusBar->showMessage("Registro deletado!");
                    on_btnBuscaEstoque_clicked();
                }else{
                    QMessageBox::critical(this, "Erro", "Erro ao excluir o registro: " + query.lastError().text());
                }
            }
        }
    }
    con.fechar();
}

void MainWindow::preenche_combo(){
    QSqlQuery query(con.bancoDeDados);
    if(con.abrir(bd)){
        if(query.exec("SELECT * FROM linhas")){
            while(query.next()){
                QString linhas = query.value(1).toString();
                ui->comboLinha->addItem(linhas);
                ui->comboLinhasEstoque->addItem(linhas);
                ui->comboLinhaExcel->addItem(linhas);

            }
        }
        if(query.exec("SELECT * FROM armarios")){
            while(query.next()){
                QString armarios = query.value(1).toString();
                ui->comboArmario->addItem(armarios);
                ui->comboArmarioEstoque->addItem(armarios);
                ui->comboArmarioExcel->addItem(armarios);
            }
        }
    }
    con.fechar();
}


void MainWindow::on_btnBuscaPlanilha_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Selecione o arquivo da planilha", QDir::currentPath(), "Arquivos XLSX (*.xlsx)");
    if (!filePath.isEmpty()) {
        QXlsx::Document planilha(filePath);

        ui->tabelaPlanilha->horizontalHeader()->setVisible(true);
        ui->tabelaPlanilha->setColumnCount(5);
        ui->tabelaPlanilha->clearContents();
        ui->tabelaPlanilha->setRowCount(0);
        //QStringList titulos;
        QString colunas[] = {"A","B","C","D","E"};
        //QXlsx::Document planilha(QDir::currentPath()+"\\controleEstoque.xlsx");

        int linha{2};
        int contLinha{0};
        try {
            while(true){
                ui->tabelaPlanilha->insertRow(contLinha);
                for (int c{0}; c < std::size(colunas); ++c) {
                    QString cellValue = planilha.read(colunas[c] + QString::number(linha)).toString();
                    QTableWidgetItem *item = new QTableWidgetItem(cellValue);
                    ui->tabelaPlanilha->setItem(contLinha, c,item);//new QTableWidgetItem(cellValue));
                    qDebug()<<"FOR : " <<cellValue;

                }
                ++linha;
                ++contLinha;
                if (planilha.read("A" +QString::number(linha)).isNull()){
                    QMessageBox::information(this,"Registro","Dados carreagados com sucesso!|");
                    break;
                }
            }
        } catch (QException &e) {
            // Handle the exception, e.g., by breaking out of the loop
            QMessageBox::information(this,"Erro","Erro ao carregar planilha.");
            qDebug() << "Error reading from the spreadsheet: " << e.what();
        }

        ui->tabelaPlanilha->resizeRowsToContents();
        //ui->tabelaPlanilha->resizeColumnsToContents();
    }
}


void MainWindow::on_btnExportar_clicked()
{
    int rowCount = ui->tabela->rowCount();
    if (rowCount >0){
        QString filePath = QFileDialog::getSaveFileName(this,"Salvar Arquivo XLSX",QDir::currentPath(),"Arquivos XLSX (*.xlsx)");

        if(!filePath.isEmpty()){
            QXlsx::Document planilha;

            planilha.write("A1","COMPONENTE");
            planilha.write("B1","DESENHO");
            planilha.write("C1","NORMAL");
            planilha.write("D1","QUANTIDADE");
            planilha.write("E1","OBSERVACAO");


                for (int row = 0; row < rowCount; row++){
                    for(int col = 1; col < 6; col++){
                        QTableWidgetItem *item = ui->tabela->item(row,col);

                        if(item){
                            planilha.write(row + 2,col, item->text());
                        }
                    }
                }
                if(planilha.saveAs(filePath)){
                    QMessageBox::information(this,"Salvo","Dados da tabela salvo em "+filePath);
                }
            }
    }else{
        QMessageBox::information(this,"Exportar","Tabela vazia");
    }

}



void MainWindow::on_btnSalvarNoBanco_clicked()
{
    FormataArmario formata;
    QString armario = ui->comboArmarioExcel->currentText();
    QString linha = ui->comboLinhaExcel->currentText();

    if (!armario.isEmpty() and !linha.isEmpty()){
        int resultado = message_box("Banco de dados", "Deseja salvar no banco de dados?");

        if (resultado == 0) {

            if (con.abrir(bd)) {
                QString armario_formatado = formata.armario(armario, linha);
                QSqlDatabase bancoDeDados = con.getDatabase();
                QSqlDatabase db = QSqlDatabase::database(); // Obtenha a instância do banco de dados


                int rowCount = ui->tabelaPlanilha->rowCount();

                if (rowCount > 0){
                    QString cmdInsert = "INSERT INTO " + armario_formatado +
                                        " (COMPONENTE, DESENHO, NORMAL, QUANTIDADE, OBSERVACAO) VALUES ";

                    QString placeholders = "(:componente, :desenho, :normal, :quantidade, :observacao)";

                    cmdInsert += placeholders;

                    QSqlQuery query;
                    db.transaction(); // Inicie a transação

                    query.prepare(cmdInsert);

                    for (int i = 0; i <rowCount; i++){
                        query.bindValue(":componente", ui->tabelaPlanilha->item(i, 0)->text());
                        query.bindValue(":desenho",    ui->tabelaPlanilha->item(i, 1)->text());
                        query.bindValue(":normal",     ui->tabelaPlanilha->item(i, 2)->text());
                        query.bindValue(":quantidade", ui->tabelaPlanilha->item(i, 3)->text());
                        query.bindValue(":observacao", ui->tabelaPlanilha->item(i, 4)->text());

                        qDebug()<<"For bindvalue: "<< i;

                        if (!query.exec()){
                            qDebug() << "Erro ao executar a query: "<<query.lastError().text();
                            bancoDeDados.rollback();
                            break;
                        }
                        if (i % 10 == 0){
                            db.commit();
                            db.transaction();

                        }
                    }
                    db.commit();
                    ui->statusBar->showMessage("Registros inseridos: "+QString::number(rowCount));
                    QMessageBox::information(this,"Banco de dados","Registros inseridos com sucesso!");
                }
                con.fechar();

            }
        }
    }else{
        QMessageBox::information(this,"Pesquisa","Selecione armario e linha!");
        ui->statusBar->showMessage("Selecione armario e linha");
    }
}

