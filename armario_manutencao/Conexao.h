#ifndef CONEXAO_H
#define CONEXAO_H
#include <QtSql>


class Conexao{
public:
    QSqlDatabase bancoDeDados;
    Conexao(){
        bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
    }



    bool abrir(QString bd){
        QString local = qApp->applicationDirPath();
        QString banco = local + bd;
        bancoDeDados.setDatabaseName(banco);

        if(!bancoDeDados.open()){
            return false;
        }else{
            return true;
        }
    }

    void fechar(){
        bancoDeDados.close();
    }

    QSqlDatabase getDatabase(){
        return bancoDeDados;
    }

};

#endif // CONEXAO_H
