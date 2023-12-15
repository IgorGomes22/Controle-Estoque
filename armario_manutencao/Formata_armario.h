#ifndef FORMATA_ARMARIO_H
#define FORMATA_ARMARIO_H

class FormataArmario{
public:

    QString armario(QString armario, QString linha){
        if (armario == "MECANICO"   and linha == "FIRE")   { return "mecanico_fire";}
        if (armario == "MECANICO"   and linha == "FIREFLY"){ return "mecanico_firefly";}
        if (armario == "MECANICO"   and linha == "TURBO")  { return "mecanico_turbo";}
        if (armario == "ELETRONICO" and linha == "FIRE")   { return "eletronico_fire";}
        if (armario == "ELETRONICO" and linha == "FIREFLY"){ return "eletronico_firefly";}
        if (armario == "ELETRONICO" and linha == "TURBO")  { return "eletronico_turbo";}
    }
};

#endif // FORMATA_ARMARIO_H
