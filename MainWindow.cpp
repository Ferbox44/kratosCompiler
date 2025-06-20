#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QFile>
#include <QTextStream>
#include <vector>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <stack>
#include <QScreen>

//Matriz Lexica
int MatrizLexica [27][33]={
    //l,L,d,_,diferente,.,E,e,+,-,=,<,>,!,&,|,',",#,\n,\t,espacio,(,),[,],coma,;,{,},%,*,/
    {1,2,3,506,506,506,2,1,105,106,9,10,11,12,13,14,15,17,19,0,0,0,119,120,121,122,124,123,130,129,128,107,108},
    {1,2,2,2,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
    {2,2,2,2,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101},
    {102,102,3,102,102,4,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102},
    {500,500,5,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500},
    {103,103,5,103,103,500,6,6,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103},
    {501,501,8,501,501,501,501,501,7,7,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501},
    {502,502,8,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502},
    {104,104,8,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104},
    {109,109,109,109,109,109,109,109,109,109,21,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109},
    {111,111,111,111,111,111,111,111,111,111,22,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111},
    {113,113,113,113,113,113,113,113,113,113,23,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113},
    {116,116,116,116,116,116,116,116,116,116,24,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116},
    {503,503,503,503,503,503,503,503,503,503,503,503,503,503,25,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503},
    {504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,26,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504},
    {16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,505,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},
    {507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,20,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507},
    {17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,18,17,508,17,17,17,17,17,17,17,17,17,17,17,17,17},
    {126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,17,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126},
    {19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,127,19,19,19,19,19,19,19,19,19,19,19,19,19},
    {125,125,125,125,507,125,125,125,125,125,125,125,125,125,125,125,15,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125},
    {110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110},
    {112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112},
    {114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114},
    {115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115},
    {117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117},
    {118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118}

};

//Matriz Predictiva
int MPred[35][56]={
    {0,600,600,0,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,777},
    {2,601,601,1,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,601,777},
    {602,602,602,602,3,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,4,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,602,777},
    {603,603,603,603,603,603,603,5,6,7,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,603,777},
    {604,604,604,604,604,9,604,604,604,604,8,604,604,604,604,604,604,604,604,604,604,604,9,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,604,777},
    {605,605,605,605,605,605,605,605,605,605,605,10,605,605,605,11,11,11,11,11,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,605,777},
    {606,606,606,606,606,606,606,606,606,606,606,606,12,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,606,777},
    {607,607,607,607,607,607,607,607,607,607,13,607,607,607,14,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,607,777},
    {608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,15,16,17,18,19,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,608,777},
    {609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,20,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,609,777},
    {610,21,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,27,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,610,23,22,24,27,27,27,25,27,26,27,610,777},
    {611,28,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,611,777},
    {612,29,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,612,777},
    {613,613,613,613,613,613,31,613,613,613,31,613,30,613,31,613,613,613,613,613,613,613,31,613,31,31,31,612,31,31,31,31,31,31,31,31,31,31,31,613,613,613,613,613,613,613,613,613,613,613,613,613,613,613,777},
    {614,614,614,614,614,614,614,614,614,614,32,614,614,614,33,614,614,614,614,614,614,614,33,614,614,615,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,614,777},
    {615,34,615,615,615,615,615,615,615,615,615,615,615,34,615,615,615,615,615,615,615,34,615,615,615,615,615,34,615,615,615,615,615,615,615,615,615,615,615,34,34,34,34,615,615,615,615,615,615,615,615,615,615,615,777},
    {616,616,616,616,616,616,36,616,616,616,36,616,616,616,36,616,616,616,616,616,616,616,36,616,616,35,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,616,777},
    {617,37,617,617,617,617,617,617,617,617,617,617,617,37,617,617,617,617,617,617,617,37,617,617,617,617,617,37,617,617,617,617,617,617,617,617,617,617,617,37,37,37,37,617,617,617,617,617,617,617,617,617,617,617,777},
    {618,618,618,618,618,618,39,618,618,618,39,618,618,618,39,618,618,618,618,618,618,618,39,618,618,39,38,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,618,777},
    {619,41,619,619,619,619,619,619,619,619,619,619,619,41,619,619,619,619,619,619,619,41,619,619,619,619,619,40,619,619,619,619,619,619,619,619,619,619,619,41,41,41,41,619,619,619,619,619,619,619,619,619,619,619,777},
    {620,42,620,620,620,620,620,620,620,620,620,620,620,42,620,620,620,620,620,620,620,42,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,620,42,42,42,42,620,620,620,620,620,620,620,620,620,620,620,777},
    {621,621,621,621,621,621,44,621,621,621,44,621,621,621,44,621,621,621,621,621,621,621,44,621,621,44,44,621,621,621,43,43,43,43,43,43,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,621,777},
    {622,45,622,622,622,622,622,622,622,622,622,622,622,45,622,622,622,622,622,622,622,45,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,622,45,45,45,45,622,622,622,622,622,622,622,622,622,622,622,777},
    {623,623,623,623,623,623,48,623,623,623,48,623,623,623,48,623,623,623,623,623,623,623,48,623,623,48,48,623,46,47,48,48,48,48,48,48,623,623,623,623,623,623,623,623,623,623,623,623,623,623,623,623,623,623,777},
    {624,55,624,624,624,624,624,624,624,624,624,624,624,55,624,624,624,624,624,624,624,55,624,624,624,624,624,624,624,624,49,50,51,52,53,54,624,624,624,55,55,55,55,624,624,624,624,624,624,624,624,624,624,624,777},
    {625,55,625,625,625,625,625,625,625,625,625,625,625,55,625,625,625,625,625,625,625,55,625,625,625,625,625,625,625,625,625,625,625,625,625,625,625,625,625,55,55,55,55,625,625,625,625,625,625,625,625,625,625,625,777},
    {626,626,626,626,626,626,59,626,626,626,59,626,626,626,626,626,626,626,626,626,626,626,59,626,626,59,59,626,59,59,59,59,59,59,59,59,56,57,58,626,626,626,626,626,626,626,626,626,626,626,626,626,626,626,777},
    {627,66,627,627,627,627,627,627,627,627,627,627,627,60,627,627,627,627,627,627,627,65,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,627,61,62,63,64,627,627,627,627,627,627,627,627,627,627,627,777},
    {628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,628,67,628,628,628,628,628,628,628,628,628,777},
    {629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,629,68,629,629,629,629,629,629,629,629,629,629,777},
    {630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,630,69,630,630,630,630,630,630,630,630,777},
    {631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,631,71,70,71,631,631,631,631,631,777},
    {632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,632,73,632,72,632,632,632,632,632,777},
    {633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,633,74,633,633,633,633,777},
    {634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,634,75,634,634,777}
};


std::stack<int> PilaEjecucion;

std::stack<QString> PilaNombreId;
std::stack<int> PilaTipos;
std::stack<int> PilaTiposUI;
std::stack<int> PilaTiposLogica;
std::stack<QString> PilaOperadores;
std::stack<QString> PilaOperadoresLogica;

QMap<QString, int> tablaSimbolos;

struct Cuadruplo {
    int num;
    QString operador;
    QString operando1;
    QString operando2;
    QString resultado;
};


QVector<Cuadruplo> tablaCuadruplos;
std::stack<int> PilaSaltos;
std::stack<int> PilaSaltosLogica;

std::stack<QString> PilaOperadoresCodIn;
std::stack<QString> PilaOperandos;
std::stack<QString> PilaOperandosLogica;

//Tablas de tipos
int tablaSumaRestaMultiplicacion[5][5] = {
    // E   R   C   S   B
    {202, 203, -1, -1, -1}, // E
    {203, 203, -1, -1, -1}, // R
    {-1, -1, -1, -1, -1},   // C
    {-1, -1, -1, -1, -1},   // S
    {-1, -1, -1, -1, -1}    // B
};

int tablaMod[5][5] = {
    // E   R   C   S   B
    {202, -1, -1, -1, -1}, // E
    {-1, -1, -1, -1, -1}, // R
    {-1, -1, -1, -1, -1},   // C
    {-1, -1, -1, -1, -1},   // S
    {-1, -1, -1, -1, -1}    // B
};

int tablaDivision[5][5] = {
    // E   R   C   S   B
    {203, 203, -1, -1, -1}, // E
    {203, 203, -1, -1, -1}, // R
    {-1, -1, -1, -1, -1},   // C
    {-1, -1, -1, -1, -1},   // S
    {-1, -1, -1, -1, -1}    // B
};

int tablaOpLogicos[5][5] = {
    // E   R   C   S   B
    {-1, -1, -1, -1, -1}, // E
    {-1, -1, -1, -1, -1}, // R
    {-1, -1, -1, -1, -1},   // C
    {-1, -1, -1, -1, -1},   // S
    {-1, -1, -1, -1, 206}    // B
};

int tablaOpRelacionales[5][5] = {
    // E   R   C   S   B
    {206, 206, 206, 206, 206}, // E
    {206, 206, 206, 206, 206}, // R
    {206, 206, 206, 206, 206},   // C
    {206, 206, 206, 206, 206},   // S
    {206, 206, 206, 206, 206}    // B
};

struct PalabraReservada {
    QString palabra;
    int id;
};

//Diccionario de palabras reservadas y su identificador
PalabraReservada PalabrasReservadas[30] = {
    {"lib", 200},
    {"class", 201},
    {"int", 202},
    {"float", 203},
    {"char", 204},
    {"string", 205},
    {"bool", 206},
    {"if", 207},
    {"else", 208},
    {"elseif", 209},
    {"do", 210},
    {"dowhile", 211},
    {"enddo", 212},
    {"while", 213},
    {"input", 214},
    {"output", 215},
    {"def", 216},
    {"as", 217},
    {"array", 218},
    {"endclass", 219},
    {"private", 220},
    {"public", 221},
    {"protected", 222},
    {"main", 223},
    {"end", 224},
    {"endif", 225},
    {"endwhile", 226}
};

//Matriz de Producciones Con acciones
int producciones[76][13] = {
    /* 0*/  {1, 201, 101, 2, 9, 219},
    /* 1*/  {200, 101, 123, 1},
    /* 2*/  {-1},
    /* 3*/  {216, 3, 101, 4, 217, 5, 8, 123, 2},
    /* 4*/  {-1},
    /* 5*/  {221},
    /* 6*/  {220},
    /* 7*/  {222},
    /* 8*/  {124, 101, 4},
    /* 9*/  {-1},
    /*10*/  {218, 6},
    /*11*/  {-1},
    /*12*/  {121, 102, 7, 122},
    /*13*/  {124, 102, 7},
    /*14*/  {-1},
    /*15*/  {202},
    /*16*/  {203},
    /*17*/  {204},
    /*18*/  {206},
    /*19*/  {205},
    /*20*/  {223, 119, 120, 10, 224},
    /*21*/  {11, 10},
    /*22*/  {28, 10},
    /*23*/  {29, 10},
    /*24*/  {30, 10},
    /*25*/  {33, 10},
    /*26*/  {34, 10},
    /*27*/  {-1},
    /*28*/  {12,802,702,109,15, 813,706,123},
    /*29*/  {701,101, 13},
    /*30*/  {121, 15, 14, 122},
    /*31*/  {-1},
    /*32*/  {124, 15, 14},
    /*33*/  {-1},
    /*34*/  {17, 806, 16},
    /*35*/  {810, 118, 15},
    /*36*/  {-1},
    /*37*/  {19,805, 18},
    /*38*/  {809,117, 17},
    /*39*/  {-1},
    /*40*/  {802, 116, 20},
    /*41*/  {20},
    /*42*/  {22,815, 21},
    /*43*/  {24, 22,814,708},
    /*44*/  {-1},
    /*45*/  {25, 804,704, 23},
    /*46*/  {808,702, 105, 22},
    /*47*/  {808,702, 106, 22},
    /*48*/  {-1},
    /*49*/  {802,702, 110},
    /*50*/  {802,702, 115},
    /*51*/  {802,702, 111},
    /*52*/  {802,702, 112},
    /*53*/  {802,702, 114},
    /*54*/  {802,702, 113},
    /*55*/  {27, 803,705, 26},
    /*56*/  {807,702, 107, 25},
    /*57*/  {807,702, 108, 25},
    /*58*/  {807,702, 128, 25},
    /*59*/  {-1},
    /*60*/  {801,701, 102},
    /*61*/  {801,701, 103},
    /*62*/  {801,701, 104},
    /*63*/  {801,701, 125},
    /*64*/  {801,701, 126},
    /*65*/  {811,703,119, 15,812,707,120},
    /*66*/  {12},
    /*67*/  {214, 119, 721,101, 4, 120, 123},
    /*68*/  {215, 119, 15, 14, 120,722, 123},
    /*69*/  {703,207, 119, 15,709, 120,10,31,32,712,225,707},
    /*70*/  {713,209,711,119, 15,709,120,10,31},
    /*71*/  {-1},
    /*72*/  {208,711,10},
    /*73*/  {-1},
    /*74*/  {213,716, 119, 15,717, 120, 10,718, 226},
    /*75*/  {719,210, 10, 211, 119, 15, 120,720, 212}
};

Kratos::Kratos(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Kratos)
{
    ui->setupUi(this);

    QPixmap pix("C:\\Users\\ferba\\Development\\Kratos\\recursos\\omega1.ico");
    ui->lblImagen->setPixmap(pix.scaled(30,30,Qt::KeepAspectRatio));
    ui->lblImagen_2->setPixmap(pix.scaled(30,30,Qt::KeepAspectRatio));
    ui->lblImagen_3->setPixmap(pix.scaled(30,30,Qt::KeepAspectRatio));
    ui->lblImagen_4->setPixmap(pix.scaled(30,30,Qt::KeepAspectRatio));
    ui->lblImagen_5->setPixmap(pix.scaled(30,30,Qt::KeepAspectRatio));
    ui->lblImagen_6->setPixmap(pix.scaled(30,30,Qt::KeepAspectRatio));
    ui->lblImagen_7->setPixmap(pix.scaled(30,30,Qt::KeepAspectRatio));
    ui->lblImagen_8->setPixmap(pix.scaled(30,30,Qt::KeepAspectRatio));
    ui->lblImagen_9->setPixmap(pix.scaled(30,30,Qt::KeepAspectRatio));
    ui->lblImagen_10->setPixmap(pix.scaled(30,30,Qt::KeepAspectRatio));

    ui->txtTokens->setReadOnly(true);
    ui->txtErrores->setReadOnly(true);

    connect(ui->BtnSalir, &QPushButton::clicked, [=]() {
        close();
    });

    connect(ui->btnLimpiar, &QPushButton::clicked, [=]() {
        ui->txtCodigo->clear();
        ui->txtTokens->clear();
        ui->txtErrores->clear();
        ui->txtFuncRel->clear();
        tablaSimbolos.clear();
        tablaCuadruplos.clear();
        while (!PilaTiposUI.empty()) {
            PilaTiposUI.pop();
        }
        while (!PilaTiposLogica.empty()) {
            PilaTiposLogica.pop();
        }

        while (!PilaOperadores.empty()) {
            PilaOperadores.pop();
        }

        while (!PilaOperadoresLogica.empty()) {
            PilaOperadoresLogica.pop();
        }

        while (!PilaOperadoresCodIn.empty()) {
            PilaOperadoresCodIn.pop();
        }

        while (!PilaSaltos.empty()) {
            PilaSaltos.pop();
        }
        while (!PilaSaltosLogica.empty()) {
            PilaSaltosLogica.pop();
        }

        while (!PilaOperandosLogica.empty()) {
            PilaOperandosLogica.pop();
        }
        while (!PilaOperandos.empty()) {
            PilaOperandos.pop();
        }


        mostrarTablaSimbolos();
        mostrarTablaTipos();
        mostrarTablaOper();
        mostrarTablaOperandos();
        mostrarTablaSaltos();
        mostrarTablaCuadruplos();
    });

    connect(ui->btnBorrar, &QPushButton::clicked, [=]() {
        ui->txtErrores->clear();
        ui->tablaTiposWidget->clear();


    });

    connect(ui->btnAbrir, &QPushButton::clicked, this, &Kratos::AbrirArchivo);
    connect(ui->BtnGuardar, &QPushButton::clicked, this, &Kratos::guardarArchivo);

    connect(ui->BtnAnalizar, &QPushButton::clicked, this, &Kratos::SintacticoSemantico);

}

Kratos::~Kratos()
{
    delete ui;
}

void Kratos::AbrirArchivo(){
    // Abre un cuadro de diálogo para que el usuario seleccione un archivo
    QString archivo = QFileDialog::getOpenFileName(this, tr("Abrir archivo de texto"), "", tr("Archivos de texto (*.kcod)"));

    // Verifica si el usuario ha cancelado la selección del archivo
    if (archivo.isEmpty())
        return;

    QFile file(archivo); //Objeto tipo file

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("No se pudo abrir el archivo."));
        return;
    }

    // Lee el contenido del archivo
    QTextStream leer(&file);
    QString contenido = leer.readAll();

    // Cierra el archivo
    file.close();

    // Carga el contenido en el QTextEdit
    ui->txtCodigo->setPlainText(contenido);
}

int Kratos::ErroresSintac(int estado){
    QString errorMessage;
    switch(estado){
    case 600: errorMessage = "600: Error, espera lib o class"; break;
    case 601: errorMessage = "601: Error, se espera lib"; break;
    case 602: errorMessage = "602: Error se espera main o def"; break;
    case 603: errorMessage = "603: Error, se espera modificador de acceso"; break;
    case 604: errorMessage = "604: Error, se espera coma"; break;
    case 605: errorMessage = "605: Error, se espera array"; break;
    case 606: errorMessage = "606: Error, se espera corchete que abre"; break;
    case 607: errorMessage = "607: Error, Espera coma"; break;
    case 608: errorMessage = "608: Error, Espera tipo de dato"; break;
    case 609: errorMessage = "609: Error, espera main"; break;
    case 610: errorMessage = "610: Error, se espera estatutos"; break;
    case 611: errorMessage = "611: Error se espera identificador"; break;
    case 612: errorMessage = "612: Error, se espera identificador"; break;
    case 613: errorMessage = "613: Error, se espera Corchete que abre"; break;
    case 614: errorMessage = "614: Error, se Espera coma"; break;
    case 615: errorMessage = "615: Error, se espera Constante, identificador, ! o ("; break;
    case 616: errorMessage = "616: Error, Espera ||"; break;
    case 617: errorMessage = "617: Error, se espera Constante, identificador, ! o ("; break;
    case 618: errorMessage = "618: Error, se espera and &&"; break;
    case 619: errorMessage = "619: Error, se espera Constante, identificador, ! o ("; break;
    case 620: errorMessage = "620: Error, se espera Constante, identificador o ("; break;
    case 621: errorMessage = "621: Error, se espera operador de asignacion"; break;
    case 622: errorMessage = "622: Error, se espera Constante, identificador o ("; break;
    case 623: errorMessage = "623: Error, se espera + o -"; break;
    case 624: errorMessage = "624: Error, se espera operador de asignacion"; break;
    case 625: errorMessage = "625: Error, se espera Constante, identificador o ("; break;
    case 626: errorMessage = "626: Error, se espera *, /, o %"; break;
    case 627: errorMessage = "627: Error, se espera Constante, identificador o ("; break;
    case 628: errorMessage = "628: Error, se espera input"; break;
    case 629: errorMessage = "629: Error, se espera output"; break;
    case 630: errorMessage = "630: Error, Espera if"; break;
    case 631: errorMessage = "631: Error, Espera elseif"; break;
    case 632: errorMessage = "632: Error, se espera else"; break;
    case 633: errorMessage = "633: Error, se espera while"; break;
    case 634: errorMessage = "634: Error, espera do"; break;
    default: errorMessage = "Error Inesperado"; break;
    }
    ui->txtErrores->append(errorMessage);
}

//Metodo que recibe el identificador del tipo y lo pasa a palabra reservada para la pila de tipos
QString Kratos::obtenerNombreTipo(int tipoVar) {
    switch (tipoVar) {
    case 202:
        return "int";
    case 203:
        return "float";
    case 204:
        return "char";
    case 205:
        return "string";
    case 206:
        return "bool";
    case 0:
        return "MFF";
    default:
        return "desconocido";  // Para casos donde no haya un tipo válido
    }
}

void Kratos::mostrarTablaSimbolos() {
    // Limpiar cualquier contenido anterior del widget
    ui->tablaSimbolosWidget->clear();

    // Establecer el número de columnas y encabezados
    ui->tablaSimbolosWidget->setColumnCount(2);  // Una columna para la variable, otra para el tipo
    QStringList headers;
    headers << "Variable" << "Tipo";
    ui->tablaSimbolosWidget->setHorizontalHeaderLabels(headers);

    // Establecer el número de filas basadas en el tamaño de la tabla de símbolos
    int row = 0;
    ui->tablaSimbolosWidget->setRowCount(tablaSimbolos.size());

    // Iterar sobre la tabla de símbolos y agregar cada entrada al QTableWidget
    for (auto it = tablaSimbolos.begin(); it != tablaSimbolos.end(); ++it) {
        // Insertar nombre de la variable
        QTableWidgetItem *variableItem = new QTableWidgetItem(it.key());
        ui->tablaSimbolosWidget->setItem(row, 0, variableItem);

        // Insertar tipo de la variable, convertido a texto
        QString tipoTexto = obtenerNombreTipo(it.value());
        QTableWidgetItem *tipoItem = new QTableWidgetItem(tipoTexto);
        ui->tablaSimbolosWidget->setItem(row, 1, tipoItem);

        row++;
    }
}
void Kratos::mostrarTablaTipos() {
    // Limpiar cualquier contenido anterior del widget
    ui->tablaTiposWidget->clear();

    // Establecer el número de columnas y encabezados
    ui->tablaTiposWidget->setColumnCount(1);  // Una columna para el tipo
    QStringList headers;
    headers << "Tipo";
    ui->tablaTiposWidget->setHorizontalHeaderLabels(headers);

    // Establecer el número de filas basadas en el tamaño de la pila
    ui->tablaTiposWidget->setRowCount(PilaTiposUI.size());

    // Iterar sobre la pila y agregar cada tipo al QTableWidget
    std::stack<int> tempStack = PilaTiposUI;  // Copia la pila para no perder los elementos originales
    int row = -1;

    while (!tempStack.empty()) {
        int tipo = tempStack.top();
        tempStack.pop();

        QString tipoTexto = obtenerNombreTipo(tipo);
        QTableWidgetItem *tipoItem = new QTableWidgetItem(tipoTexto);
        ui->tablaTiposWidget->setItem(row, 1, tipoItem);

        row++;
    }

}
void Kratos::mostrarTablaOper() {
    // Limpiar cualquier contenido anterior del widget
    ui->tablaOperWidget->clear();

    // Establecer el número de columnas y encabezados
    ui->tablaOperWidget->setColumnCount(1);  // Una columna para el tipo
    QStringList headers;
    headers << "Operador";
    ui->tablaOperWidget->setHorizontalHeaderLabels(headers);

    // Establecer el número de filas basadas en el tamaño de la pila
    ui->tablaOperWidget->setRowCount(PilaOperadores.size());

    // Iterar sobre la pila y agregar cada tipo al QTableWidget
    std::stack<QString> tempStack = PilaOperadores;  // Copia la pila para no perder los elementos originales
    int row = -1;

    while (!tempStack.empty()) {
        QString tipo = tempStack.top();
        tempStack.pop();

        QString tipoTexto = tipo;
        QTableWidgetItem *tipoItem = new QTableWidgetItem(tipoTexto);
        ui->tablaOperWidget->setItem(row, 1, tipoItem);

        row++;
    }

}

void Kratos::mostrarTablaOperandos() {
    // Limpiar cualquier contenido anterior del widget
    ui->tablaOpernWidget->clear();

    // Establecer el número de columnas y encabezados
    ui->tablaOpernWidget->setColumnCount(1);  // Una columna para el tipo
    QStringList headers;
    headers << "Operandos";
    ui->tablaOpernWidget->setHorizontalHeaderLabels(headers);

    // Establecer el número de filas basadas en el tamaño de la pila
    ui->tablaOpernWidget->setRowCount(PilaOperandos.size());

    // Iterar sobre la pila y agregar cada tipo al QTableWidget
    std::stack<QString> tempStack = PilaOperandos;  // Copia la pila para no perder los elementos originales
    int row = -1;

    while (!tempStack.empty()) {
        QString tipo = tempStack.top();
        tempStack.pop();

        QString tipoTexto = tipo;
        QTableWidgetItem *tipoItem = new QTableWidgetItem(tipoTexto);
        ui->tablaOpernWidget->setItem(row, 1, tipoItem);

        row++;
    }

}
void Kratos::mostrarTablaSaltos() {
    // Limpiar cualquier contenido anterior del widget
    ui->PilaSaltosWidget->clear();

    // Establecer el número de columnas y encabezados
    ui->PilaSaltosWidget->setColumnCount(1);  // Una columna para mostrar los saltos
    QStringList headers;
    headers << "Saltos";
    ui->PilaSaltosWidget->setHorizontalHeaderLabels(headers);

    // Establecer el número de filas basadas en el tamaño de la pila
    ui->PilaSaltosWidget->setRowCount(PilaSaltos.size());

    // Iterar sobre la pila y agregar cada valor al QTableWidget
    std::stack<int> tempStack = PilaSaltos;  // Copia la pila para no modificar el original
    int row = 0;  // Inicializar el índice de fila correctamente

    while (!tempStack.empty()) {
        int salto = tempStack.top();
        tempStack.pop();

        // Crear un ítem para la celda con el valor del salto
        QTableWidgetItem *saltoItem = new QTableWidgetItem(QString::number(salto));
        ui->PilaSaltosWidget->setItem(row, 0, saltoItem);  // Columna 0 ya que solo hay una columna

        row++;
    }
}


void Kratos::mostrarTablaCuadruplos() {
    ui->tablaCuadruplosWidget->clear();
    ui->tablaCuadruplosWidget->setColumnCount(5); // Num, Operador, Operando1, Operando2, Resultado
    QStringList headers{"Num", "Operador", "Operando1", "Operando2", "Resultado"};
    ui->tablaCuadruplosWidget->setHorizontalHeaderLabels(headers);

    ui->tablaCuadruplosWidget->setRowCount(tablaCuadruplos.size());

    for (int i = 0; i < tablaCuadruplos.size(); ++i) {
        const auto& cuad = tablaCuadruplos[i];
        ui->tablaCuadruplosWidget->setItem(i, 0, new QTableWidgetItem(QString::number(cuad.num)));
        ui->tablaCuadruplosWidget->setItem(i, 1, new QTableWidgetItem(cuad.operador));
        ui->tablaCuadruplosWidget->setItem(i, 2, new QTableWidgetItem(cuad.operando1));
        ui->tablaCuadruplosWidget->setItem(i, 3, new QTableWidgetItem(cuad.operando2));
        ui->tablaCuadruplosWidget->setItem(i, 4, new QTableWidgetItem(cuad.resultado));
    }
}



int Kratos::relaciona(QChar prevChar, QChar c, QChar nextChar) {
    int asciiValue = c.unicode(); // Obtener el valor ASCII del QChar
    char ch = asciiValue;

    if ((c == 'E') && prevChar.isDigit() && (nextChar.isDigit() || nextChar == '+' || nextChar == '-'|| nextChar.isSpace())) {
        return 6;
    }else if((c == 'e') && prevChar.isDigit() && (nextChar.isDigit() || nextChar == '+' || nextChar == '-'|| nextChar.isSpace())){
        return 7;
    }

    if (c >= 'a' && c <= 'z'){
        return 0;
    }
    if (c >= 'A' && c <= 'Z'){
        return 1;
    }
    if (c >= '0' && c <= '9'){
        return 2;
    }
    switch (ch) {
    case '_':return 3; break;
    case '.':return 5; break;
    case 'E':return 6; break;
    case 'e':return 7; break;
    case '+':return 8; break;
    case '-':return 9; break;
    case '=':return 10; break;
    case '<':return 11; break;
    case '>':return 12; break;
    case '!':return 13; break;
    case '&':return 14; break;
    case '|':return 15; break;
    case '\'':return 16; break;
    case '"':return 17; break;
    case '#':return 18; break;
    case '\n':return 19; break;
    case '\t':return 20; break;
    case ' ':return 21; break;
    case '(':return 22; break;
    case ')':return 23; break;
    case '[':return 24; break;
    case ']':return 25; break;
    case ',':return 26; break;
    case ';':return 27; break;
    case '{':return 28; break;
    case '}':return 29; break;
    case '%':return 30; break;
    case '*':return 31; break;
    case '/':return 32; break;
    //case '$':return 33; break;
    default:
        return 4; break;
    }
}



void Kratos::mostrarTipoDeToken(int e, QString token){
    QString tipoToken;
    switch (e){
    case 100: tipoToken = "Palabras Reservadas"; break;
    case 101: tipoToken = "Identificador"; break;
    case 102: tipoToken = "Enteros"; break;
    case 103: tipoToken = "Reales"; break;
    case 104: tipoToken = "Not. Cient."; break;
    case 105: tipoToken = "Suma"; break;
    case 106: tipoToken = "Resta"; break;
    case 107: tipoToken = "Multiplicacion"; break;
    case 108: tipoToken = "Division"; break;
    case 109: tipoToken = "Asigna"; break;
    case 110: tipoToken = "Igual"; break;
    case 111: tipoToken = "Menor"; break;
    case 112: tipoToken = "Menor Igual"; break;
    case 113: tipoToken = "Mayor"; break;
    case 114: tipoToken = "Mayor Igual"; break;
    case 115: tipoToken = "Diferente"; break;
    case 116: tipoToken = "Not"; break;
    case 117: tipoToken = "And"; break;
    case 118: tipoToken = "Or"; break;
    case 119: tipoToken = "Parentesis Abre"; break;
    case 120: tipoToken = "Parentesis Cierra"; break;
    case 121: tipoToken = "Corchete abre"; break;
    case 122: tipoToken = "Corchete cierra"; break;
    case 123: tipoToken = "Punto y coma"; break;
    case 124: tipoToken = "Coma"; break;
    case 125: tipoToken = "Cte Caracter"; break;
    case 126: tipoToken = "Cte String"; break;
    case 127: tipoToken = "Comentario de linea"; break;
    case 128: tipoToken = "Modulo"; break;
    case 129: tipoToken = "Llave cierra"; break;
    case 130: tipoToken = "Llave abre"; break;
    }
    //QString tokenTrimmed = token.trimmed();
    QString tokenText = QString("%1: %2").arg(token, tipoToken);
    ui->txtTokens->append(tokenText); // Agregar el token y su tipo al QTextEdit txtTokens
}


void Kratos::mostrarErrorEnToken(int e, QString token) {
    QString errorMessage;
    switch (e) {
    case 500: errorMessage = "500: Error, real espera digito"; break;
    case 501: errorMessage = "501: Error, se espera digito, + o -"; break;
    case 502: errorMessage = "502: Error se espera digito"; break;
    case 503: errorMessage = "503: Error, se espera &&"; break;
    case 504: errorMessage = "504: Error, se espera ||"; break;
    case 505: errorMessage = "505: Error, comillas vacias"; break;
    case 506: errorMessage = "506: Error, Caracter no reconocido"; break;
    case 507: errorMessage = "507: Error, Espera comilla de cierre"; break;
    case 508: errorMessage = "508: Error, Espera comilla de cierre"; break;
        //default: errorMessage = QString("Error desconocido con código %1").arg(e); break;
    }
    // Añade el token al mensaje de error si está disponible
    if (!token.isEmpty()) {
        errorMessage += QString(" - Token causante: '%1'").arg(token);
    }
    ui->txtErrores->append(errorMessage);
}

int Kratos::RelCol(int estado){
    switch (estado) {
    case 201: return 0;break;
    case 101: return 1;break;
    case 219: return 2;break;
    case 200: return 3;break;
    case 216: return 4;break;
    case 217: return 5;break;
    case 123: return 6;break;
    case 221: return 7;break;
    case 220: return 8;break;
    case 222: return 9;break;
    case 124: return 10;break;
    case 218: return 11;break;
    case 121: return 12;break;
    case 102: return 13;break;
    case 122: return 14;break;
    case 202: return 15;break;
    case 203: return 16;break;
    case 204: return 17;break;
    case 206: return 18;break;
    case 205: return 19;break;
    case 223: return 20;break;
    case 119: return 21;break;
    case 120: return 22;break;
    case 224: return 23;break;
    case 109: return 24;break;
    case 118: return 25;break;
    case 117: return 26;break;
    case 116: return 27;break;
    case 105: return 28;break;
    case 106: return 29;break;
    case 110: return 30;break;
    case 115: return 31;break;
    case 111: return 32;break;
    case 112: return 33;break;
    case 114: return 34;break;
    case 113: return 35;break;
    case 107: return 36;break;
    case 108: return 37;break;
    case 128: return 38;break;
    case 103: return 39;break;
    case 104: return 40;break;
    case 125: return 41;break;
    case 126: return 42;break;
    case 215: return 43;break;
    case 214: return 44;break;
    case 207: return 45;break;
    case 225: return 46;break;
    case 209: return 47;break;
    case 208: return 48;break;
    case 213: return 49;break;
    case 226: return 50;break;
    case 210: return 51;break;
    case 211: return 52;break;
    case 212: return 53;break;
        //case 999: return 54;break;
    }
}

//Parse para las filas y las columnas de las tablas de tipos de datos
int Kratos::ParseTipoVar(int tipoVar) {
    switch (tipoVar) {
    case 202:
        return 0;
    case 203:
        return 1;
    case 204:
        return 2;
    case 205:
        return 3;
    case 206:
        return 4;
    }
}

//Lista enumerada porque QT no deja usar QStrings en un switch
enum Operador {
    OP_ADD,    // +
    OP_SUB,    // -
    OP_MUL,    // *
    OP_DIV,    // /
    OP_MOD,
    OP_OR,
    OP_AND,
    OP_NOT,
    OP_IGUAL,
    OP_DIFF,
    OP_MEN,
    OP_MAY,
    OP_MENIG,
    OP_MAYIG,
    OP_INVALID // Valor predeterminado para operadores inválidos
};

//Switch que segun el operador devuelve un valor de la lista enumerada
Operador obtenerOperador(QString operador) {
    if (operador == "+") return OP_ADD;
    if (operador == "-") return OP_SUB;
    if (operador == "*") return OP_MUL;
    if (operador == "/") return OP_DIV;
    if (operador == "%") return OP_MOD;
    if (operador == "||") return OP_OR;
    if (operador == "&&") return OP_AND;
    if (operador == "!") return OP_NOT;
    if (operador == "==") return OP_IGUAL;
    if (operador == "!=") return OP_DIFF;
    if (operador == "<") return OP_MEN;
    if (operador == ">") return OP_MAY;
    if (operador == "<=") return OP_MENIG;
    if (operador == ">=") return OP_MAYIG;
    return OP_INVALID;  // Si no coincide con ningún operador
}

//Metodo que verifica si una operacion es valida con dos operandos y un operador
int Kratos::verificarOperacion(int tipo1, int tipo2, QString operadorStr) {
    int op1 = ParseTipoVar(tipo1);
    int op2 = ParseTipoVar(tipo2);

    // Convertir QString a enum
    Operador operador = obtenerOperador(operadorStr);

    //switch que segun el operador, compara los operandos con las tablas de tipos
    switch (operador) {
    case OP_ADD:
        return tablaSumaRestaMultiplicacion[op2][op1];
    case OP_SUB:
        return tablaSumaRestaMultiplicacion[op2][op1];
    case OP_MUL:
        return tablaSumaRestaMultiplicacion[op2][op1];
    case OP_MOD:
        return tablaMod[op2][op1];
    case OP_DIV:
        return tablaDivision[op2][op1];
    case OP_OR:
        return tablaOpLogicos[op2][op1];
    case OP_AND:
        return tablaOpLogicos[op2][op1];
    case OP_NOT:
        return tablaOpLogicos[op2][op1];
    case OP_IGUAL:
        return tablaOpRelacionales[op2][op1];
    case OP_DIFF:
        return tablaOpRelacionales[op2][op1];
    case OP_MEN:
        return tablaOpRelacionales[op2][op1];
    case OP_MAY:
        return tablaOpRelacionales[op2][op1];
    case OP_MENIG:
        return tablaOpRelacionales[op2][op1];
    case OP_MAYIG:
        return tablaOpRelacionales[op2][op1];
    default:
        return -1;  // Operador inválido
    }
}

//Sintactico - Semantico
void Kratos::SintacticoSemantico() {
    // Limpiar todo al llamar el metodo
    ui->txtTokens->clear();
    ui->txtErrores->clear();
    ui->tablaTiposWidget->clear();
    ui->tablaOpernWidget->clear();
    ui->tablaCuadruplosWidget->clear();
    ui->txtFuncRel->clear();

    tablaSimbolos.clear();
    tablaCuadruplos.clear();
    while (!PilaTiposUI.empty()) {
        PilaTiposUI.pop();
    }
    while (!PilaTiposLogica.empty()) {
        PilaTiposLogica.pop();
    }

    while (!PilaOperadores.empty()) {
        PilaOperadores.pop();
    }

    while (!PilaOperadoresLogica.empty()) {
        PilaOperadoresLogica.pop();
    }

    while (!PilaOperadoresCodIn.empty()) {
        PilaOperadoresCodIn.pop();
    }

    while (!PilaSaltos.empty()) {
        PilaSaltos.pop();
    }
    while (!PilaSaltosLogica.empty()) {
        PilaSaltosLogica.pop();
    }

    while (!PilaOperandosLogica.empty()) {
        PilaOperandosLogica.pop();
    }
    while (!PilaOperandos.empty()) {
        PilaOperandos.pop();
    }


    //Inicializacion de variables
    QString textoCodigo = ui->txtCodigo->toPlainText();
    QString topePilaOpe="";
    QString topePilaOperCodIn="";
    int posicionLexico = 0;
    int estadoLexico = 0;
    int palabResevID = 0;
    int topePila = 0;
    int columna =0;
    int produccion=0;
    int filaMPred = 0;
    int tipoVar=0;
    int size = 0;
    int contador=1;
    int contadorResultados = 0;
    bool banderadeclara = false;
    bool banderaEstAsig = false;
    bool banderaOutput = false;
    bool banderaMFF = true;
    bool banderaElseIf = false;
    //Push de producciones iniciales
    PilaEjecucion.push(999);
    PilaEjecucion.push(0);

    //Llamar token de inicio
    QString textoToken = "";
    QString nombreVariable="";
    estadoLexico = dameToken(posicionLexico, textoCodigo, textoToken);//Simbolo de entrada actual

    //Mostrar tokens o errores (Lexico)
    if (estadoLexico >= 100 && estadoLexico <= 130) {
        mostrarTipoDeToken(estadoLexico, textoToken);  // Procesar token válido
    } else if(estadoLexico >=500 && estadoLexico <=508) {
        mostrarErrorEnToken(estadoLexico, textoToken);  // Llamar a Error si el estado final no es válido
    }


    do{
        //Buscar la palabra reservada
        if (estadoLexico == 100) {
            palabResevID = dameTokenPalResID(estadoLexico, textoToken);
            if (palabResevID == 0) {
                estadoLexico = 101;
            }
        }
        // Sintactico
        topePila = PilaEjecucion.top();
        if(topePila == 999){
            ui->txtTokens->append("¡CÓDIGO ANALIZADO CORRECTAMENTE!");
            PilaEjecucion.pop();
        }else{
            if(topePila >=100 && topePila <= 230){
                if(topePila == 999){
                    ui->txtTokens->append("¡CÓDIGO ANALIZADO CORRECTAMENTE!");
                }else{
                    //Cambiar el estado del token de la palabra reservada por su ID
                    if(estadoLexico== 100){
                        estadoLexico = palabResevID;
                    }
                    //Bandera para terminar la declaracion de variables con ;
                    if(topePila == 123){
                        banderadeclara = false;
                    }
                    //Guarda en una pila el nombre de todas las variables que se vaya encontrando
                    if(estadoLexico== 101 && banderadeclara == true){
                        nombreVariable = textoToken;
                        PilaNombreId.push(nombreVariable);
                    }
                    //Una vez que ya encontro toda las variables de esa linea, inserta en el mapa la variable y su tipo
                    if(!PilaTipos.empty()){
                        QString var = PilaNombreId.top();
                        tipoVar = PilaTipos.top();
                        if (!tablaSimbolos.contains(var)) {
                            tipoVar = PilaTipos.top();
                            tablaSimbolos.insert(var, tipoVar);  // Insertar variable en la tabla de símbolos
                            PilaNombreId.pop();
                            PilaTipos.pop();
                        } else {
                            if (!ui->txtErrores->toPlainText().contains(QString("Error Semantico: Variable %1 ya declarada").arg(var))) {
                                ui->txtErrores->append(QString("Error Semantico: Variable %1 ya declarada").arg(var));
                            }
                            PilaNombreId.pop();  // Asegurarse de quitar la variable de la pila para evitar múltiples mensajes
                            PilaTipos.pop();  // Evitar que se siga procesando esta variable
                        }
                    }
                    //Condicion que añade la variable de la tabla de simbolos a la pila de tipos
                    if(banderaEstAsig == true){
                        QString var=textoToken;
                        if (tablaSimbolos.contains(var)) {
                            int tipo =0;
                            tipo = tablaSimbolos.value(var);
                            PilaTiposUI.push(tipo);
                            PilaTiposLogica.push(tipo);
                            //qDebug()<<PilaTiposUI.top();
                        }else{
                            if (!ui->txtErrores->toPlainText().contains(QString("Error Semantico: Variable %1 no declarada").arg(var))) {
                                ui->txtErrores->append(QString("Error Semantico: Variable %1 no declarada").arg(var));
                                tablaSimbolos.insert(var, 203);
                                int tipo =0;
                                tipo = tablaSimbolos.value(var);
                                PilaTiposUI.push(tipo);
                                PilaTiposLogica.push(tipo);
                            }
                        }
                        banderaEstAsig = false;
                    }

                    if((topePila == estadoLexico) &&(topePila !=999)){
                        PilaEjecucion.pop();
                        textoToken = "";
                        estadoLexico = dameToken(posicionLexico, textoCodigo, textoToken);//Simbolo de entrada actual
                        if (estadoLexico == 100) {
                            palabResevID = dameTokenPalResID(estadoLexico, textoToken);
                            if (palabResevID == 0) {
                                estadoLexico = 101;
                            }
                        }
                        if (estadoLexico >= 100 && estadoLexico <= 130) {
                            mostrarTipoDeToken(estadoLexico, textoToken);  // Procesar token válido
                        } else if(estadoLexico >=500 && estadoLexico <=508) {
                            mostrarErrorEnToken(estadoLexico, textoToken);  // Llamar a Error si el estado final no es válido
                            break;
                        }
                    }else{
                        QString error = QString ("%1: %2").arg("Error sintactico no se esperaba ", textoToken);
                        ui->txtErrores->append(error);
                        break;
                    }
                }
                //Semantico
            }else if(topePila >= 700 && topePila <= 722){
                //Saca de la pila de ejecucion la accion
                PilaEjecucion.pop();
                if(!PilaOperadoresCodIn.empty()){
                    topePilaOperCodIn = PilaOperadoresCodIn.top();
                }
                //qDebug()<<"ID: "<<textoToken;
                if(topePila==701){
                    PilaOperandosLogica.push(textoToken);
                    PilaOperandos.push(textoToken);
                }
                if(topePila==702){
                    PilaOperadoresCodIn.push(textoToken);
                    //qDebug()<<"OPE: "<<textoToken;
                }
                if(topePila==703){

                        PilaOperadoresCodIn.push("MMF");
                        qDebug() << "Parentesis? "<< textoToken;
                        PilaOperadores.push("MFF");
                        //PilaOperadoresLogica.push("MFF");


                }
                if(topePila==704){
                    if(topePilaOperCodIn == "+"||topePilaOperCodIn == "-"){
                        QString operador = PilaOperadoresCodIn.top();
                        PilaOperadoresCodIn.pop();
                        QString operando2 = PilaOperandosLogica.top();
                        PilaOperandosLogica.pop();
                        QString operando1 = PilaOperandosLogica.top();
                        PilaOperandosLogica.pop();
                        // Contador estático para resultados
                        contadorResultados++;
                        QString resultado = QString("Res %1").arg(contadorResultados);
                        //QString resultado = "res";
                        agregarCuadruplo(contador,operador,operando1,operando2,resultado);
                        contador++;
                        PilaOperandosLogica.push(resultado);
                        PilaOperandos.push(resultado);
                    }
                }
                if(topePila==705){
                    if(topePilaOperCodIn == "*"||topePilaOperCodIn == "/"||topePilaOperCodIn == "%"){
                        QString operador = PilaOperadoresCodIn.top();
                        PilaOperadoresCodIn.pop();
                        QString operando2 = PilaOperandosLogica.top();
                        PilaOperandosLogica.pop();
                        QString operando1 = PilaOperandosLogica.top();
                        PilaOperandosLogica.pop();
                        contadorResultados++;
                        QString resultado = QString("Res %1").arg(contadorResultados);
                        //QString resultado = "res";
                        agregarCuadruplo(contador,operador,operando1,operando2,resultado);
                        contador++;
                        PilaOperandosLogica.push(resultado);
                        PilaOperandos.push(resultado);
                    }
                }
                if(topePila==706){
                    if(topePilaOperCodIn== "="){
                        QString operando2 = "NULL";

                        QString resultado = PilaOperandosLogica.top();
                        PilaOperandosLogica.pop();

                        QString operador = PilaOperadoresCodIn.top();
                        PilaOperadoresCodIn.pop();

                        QString operando1 = PilaOperandosLogica.top();
                        PilaOperandosLogica.pop();
                        agregarCuadruplo(contador,operador,operando1,operando2, resultado);
                        contador++;
                    }

                }
                if(topePila==707){
                    PilaOperadoresCodIn.pop();
                    banderaMFF= false;
                    //qDebug() << "Saco MFF ";
                }

                if(topePila==708){
                    if(topePilaOperCodIn == "==" || topePilaOperCodIn == "!="|| topePilaOperCodIn == ">"|| topePilaOperCodIn == "<"|| topePilaOperCodIn == "<="|| topePilaOperCodIn == ">="){
                        QString operador = PilaOperadoresCodIn.top();
                        PilaOperadoresCodIn.pop();
                        QString operando2 = PilaOperandosLogica.top();
                        PilaOperandosLogica.pop();
                        QString operando1 = PilaOperandosLogica.top();
                        PilaOperandosLogica.pop();
                        contadorResultados++;
                        QString resultado = QString("Res %1").arg(contadorResultados);
                        //QString resultado = "res";
                        agregarCuadruplo(contador,operador,operando1,operando2,resultado);
                        contador++;
                        PilaOperandosLogica.push(resultado);
                        PilaOperandos.push(resultado);
                    }

                }

                if(topePila==709){
                    //qDebug() << PilaOperandosLogica.top();
                    QString operador = "SF";
                    QString operando1 = PilaOperandosLogica.top();
                    PilaOperandosLogica.pop();
                    QString operando2 = "";
                    QString resultado ="";
                    PilaSaltosLogica.push(contador);
                    PilaSaltos.push(contador);
                    //qDebug() <<"709: " <<PilaSaltosLogica.top();
                    //qDebug() << PilaSaltos.top();
                    agregarCuadruplo(contador,operador,operando1,operando2,resultado);
                    contador++;
                }

                if(topePila==710){

                }
                if(topePila==711){
                    QString operador = "SI";
                    QString operando1 = "";
                    QString operando2 = "";
                    QString resultado ="";
                    PilaSaltosLogica.push(contador);
                    PilaSaltos.push(contador);
                    agregarCuadruplo(contador,operador,operando1,operando2,resultado);

                    int temp = PilaSaltosLogica.top();
                    PilaSaltosLogica.pop();
                    int valor = PilaSaltosLogica.top();

                    QString cont = QString::number(contador+1);
                    qDebug()<< "Contador " << cont;
                    funcionRellenar(valor, cont);

                    PilaSaltosLogica.pop();
                    PilaSaltosLogica.push(temp);
                    contador++;

                }
                if(topePila==712){
                    if (!PilaSaltosLogica.empty()) {
                        int numero = PilaSaltosLogica.top();
                        qDebug()<< "Tope que llena SI:  " << numero;
                        PilaSaltosLogica.pop();

                        QString direccion = QString::number(contador);  // Dirección actual
                        funcionRellenar(numero, direccion);

                        // if (!PilaSaltosLogica.empty()) {
                        //     int numero2 = PilaSaltosLogica.top();
                        //     qDebug()<< "Tope que llena SI:  " << numero2;
                        //     PilaSaltosLogica.pop();
                        //     QString num = QString::number(numero);
                        //     funcionRellenar(numero2, num);
                        // }
                    }
                }
                if(topePila==713){
                    banderaElseIf = true;
                }

                if(topePila==714){

                    if (!PilaSaltosLogica.empty()) {
                        int numero = PilaSaltosLogica.top();
                        //qDebug()<< "Tope que llena SI:  " << numero;
                        PilaSaltosLogica.pop();
                        QString direccion = QString::number(contador);  // Dirección actual
                        funcionRellenar(numero, direccion);
                    }
                }

                if(topePila==715){
                    int valor = PilaSaltosLogica.top();
                    PilaSaltosLogica.pop();
                    QString cont1 = QString::number(contador);
                    funcionRellenar(valor,cont1);
                }

                if(topePila==716){
                    PilaSaltosLogica.push(contador);
                    PilaSaltos.push(contador);
                }

                if(topePila==717){
                    QString operador = "SF";
                    QString operando1 = PilaOperandosLogica.top();
                    PilaOperandosLogica.pop();
                    QString operando2 = "";
                    QString resultado ="";
                    PilaSaltosLogica.push(contador);
                    PilaSaltos.push(contador);
                    agregarCuadruplo(contador,operador,operando1,operando2,resultado);
                    contador++;

                }

                if(topePila==718){

                    QString operador = "SI";
                    QString operando1 = "";
                    QString operando2 = "";
                    //tope
                    int temp= PilaSaltosLogica.top();
                    PilaSaltosLogica.pop();

                    //tope -1
                    int valor = PilaSaltosLogica.top();

                    QString res = QString::number(valor);
                    QString resultado = res;

                    agregarCuadruplo(contador,operador,operando1,operando2,resultado);
                    PilaSaltosLogica.pop();
                    PilaSaltosLogica.push(temp);

                    QString cont = QString::number(contador+1);
                    funcionRellenar(PilaSaltosLogica.top(),cont);
                    PilaSaltosLogica.pop();
                    contador++;
                }

                if(topePila==719){
                    PilaSaltos.push(contador);
                    PilaSaltosLogica.push(contador);
                }

                if(topePila==720){
                    QString operador = "SF";
                    QString operando1 = PilaOperandosLogica.top();
                    QString operando2 = "";
                    QString resultado = QString::number(PilaSaltosLogica.top());
                    PilaSaltosLogica.pop();

                    agregarCuadruplo(contador,operador,operando1,operando2,resultado);
                    QString cont = QString::number(contador);
                    QString rellenar = QString("%1 (%2,%3)").arg("Funcion Rellenar",cont, resultado);
                    ui->txtFuncRel->append(rellenar);
                    contador++;
                    //qDebug() <<"Do while tope" << PilaSaltosLogica.top();

                }

                if (topePila == 721) {
                    QString operador = "Input";
                    QString operando1 = "";
                    QString operando2 = "";

                    // Suponemos que el identificador está en una variable llamada "identificador"
                    QString resultado = textoToken; // Aquí debes asegurarte de que `identificador` esté accesible y válido

                    // Buscar en la tabla de símbolos
                    if (tablaSimbolos.contains(resultado)) {
                        // Si el ID existe en la tabla de símbolos, generar el cuádruplo
                        agregarCuadruplo(contador, operador, operando1, operando2, resultado);
                        contador++;
                    } else {
                        // Manejar el error si el ID no existe en la tabla
                        QString mensajeError = QString("Error: Identificador '%1' no declarado.").arg(resultado);
                        ui->txtErrores->append(mensajeError);
                        tablaSimbolos.insert(resultado, 203);
                        int tipo =0;
                        tipo = tablaSimbolos.value(resultado);
                        PilaTiposUI.push(tipo);
                        PilaTiposLogica.push(tipo);
                        agregarCuadruplo(contador, operador, operando1, operando2, resultado);
                        contador++;
                    }
                }

                if(topePila==722){
                    QString operador = "Output";
                    QString operando1 = "";
                    QString operando2 = "";
                    QString resultado = PilaOperandosLogica.top();
                    agregarCuadruplo(contador,operador,operando1,operando2,resultado);
                    contador++;
                }


            }else if(topePila >= 800 && topePila <= 815){
                //Saca de la pila de ejecucion la accion
                PilaEjecucion.pop();
                if(!PilaOperadoresLogica.empty()){
                    topePilaOpe = PilaOperadoresLogica.top();
                }
                //qDebug() << "topePilaOpe: " << topePilaOpe;
                //Acciones

                if(topePila==801){
                    //EstadoLexico es el estado que tiene el token analizado al momento de la accion, en este caso para las constantes
                    if(estadoLexico==102){
                        PilaTiposUI.push(202);
                        PilaTiposLogica.push(202);
                    }else if(estadoLexico==103){
                        PilaTiposUI.push(203);
                        PilaTiposLogica.push(203);
                    }else if(estadoLexico==125){
                        PilaTiposUI.push(204);
                        PilaTiposLogica.push(204);
                    }else if(estadoLexico==126){
                        PilaTiposUI.push(205);
                        PilaTiposLogica.push(205);
                    }
                }else if(topePila==802){
                    PilaOperadores.push(textoToken);
                    PilaOperadoresLogica.push(textoToken);
                }else if(topePila == 803){
                    //qDebug() << "Operador: " << topePilaOpe;
                    if (topePilaOpe == "*" ||topePilaOpe == "%"||topePilaOpe == "/"){
                        //qDebug() << "Operador: " << topePilaOpe;
                        int tipo1 = PilaTiposLogica.top();
                        PilaTiposLogica.pop();  // Hacer pop para obtener el siguiente valor en la pila

                        // Verificar si la pila tiene al menos un segundo valor

                        int tipo2 = PilaTiposLogica.top();  // Obtener el valor debajo del tope original

                        PilaTiposLogica.push(tipo1);


                        if(verificarOperacion(tipo1,tipo2,topePilaOpe) !=-1){
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            int resultado = verificarOperacion(tipo1,tipo2,topePilaOpe);
                            PilaTiposLogica.push(resultado);
                            PilaTiposUI.push(resultado);
                            PilaOperadoresLogica.pop();

                            //qDebug()<<"Funciona *";
                        }else if(topePilaOpe == "%"){
                            QString tipo1Texto = obtenerNombreTipo(tipo1);  // Convierte el tipo 1 a texto
                            QString tipo2Texto = obtenerNombreTipo(tipo2);  // Convierte el tipo 2 a texto
                            if (!ui->txtErrores->toPlainText().contains(QString("Error Semantico: Error en operacion. Tipos incompatibles entre %1 %2 %3")
                                                                            .arg(tipo2Texto).arg(topePilaOpe).arg(tipo1Texto))) {
                                ui->txtErrores->append(QString("Error Semantico: Error en operacion. Tipos incompatibles entre ""%1 %2 %3")
                                                           .arg(tipo2Texto).arg(topePilaOpe).arg(tipo1Texto));
                            }
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            PilaTiposLogica.push(202);
                            PilaTiposUI.push(202);
                            PilaOperadoresLogica.pop();
                        }
                        else{

                            QString tipo1Texto = obtenerNombreTipo(tipo1);  // Convierte el tipo 1 a texto
                            QString tipo2Texto = obtenerNombreTipo(tipo2);  // Convierte el tipo 2 a texto
                            if (!ui->txtErrores->toPlainText().contains(QString("Error Semantico: Error en operacion. Tipos incompatibles entre %1 %2 %3")
                                                                            .arg(tipo2Texto).arg(topePilaOpe).arg(tipo1Texto))) {
                                ui->txtErrores->append(QString("Error Semantico: Error en operacion. Tipos incompatibles entre ""%1 %2 %3")
                                                           .arg(tipo2Texto).arg(topePilaOpe).arg(tipo1Texto));
                            }
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            PilaTiposLogica.push(203);
                            PilaTiposUI.push(203);
                            PilaOperadoresLogica.pop();
                        }
                    }
                }else if(topePila == 804){
                    if (topePilaOpe == "+" ||topePilaOpe == "-"){
                        //qDebug() << "Operador: " << topePilaOpe;
                        int tipo1 = PilaTiposLogica.top();
                        PilaTiposLogica.pop();  // Hacer pop para obtener el siguiente valor en la pila

                        // Verificar si la pila tiene al menos un segundo valor

                        int tipo2 = PilaTiposLogica.top();  // Obtener el valor debajo del tope original

                        PilaTiposLogica.push(tipo1);

                        if(verificarOperacion(tipo1,tipo2,topePilaOpe) !=-1){
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            int resultado = verificarOperacion(tipo1,tipo2,topePilaOpe);
                            PilaTiposLogica.push(resultado);
                            PilaTiposUI.push(resultado);
                            PilaOperadoresLogica.pop();

                            //qDebug()<<"Funciona *";

                        }else{

                            QString tipo1Texto = obtenerNombreTipo(tipo1);  // Convierte el tipo 1 a texto
                            QString tipo2Texto = obtenerNombreTipo(tipo2);  // Convierte el tipo 2 a texto
                            if (!ui->txtErrores->toPlainText().contains(QString("Error Semantico: Error en operacion. Tipos incompatibles entre %1 %2 %3")
                                                                            .arg(tipo2Texto).arg(topePilaOpe).arg(tipo1Texto))) {
                                ui->txtErrores->append(QString("Error Semantico: Error en operacion. Tipos incompatibles entre ""%1 %2 %3")
                                                           .arg(tipo2Texto).arg(topePilaOpe).arg(tipo1Texto));
                            }
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            PilaTiposLogica.push(203);
                            PilaTiposUI.push(203);
                            PilaOperadoresLogica.pop();
                        }
                    }
                }else if(topePila==805){
                    if (topePilaOpe == "&&"){
                        //qDebug() << "Operador: " << topePilaOpe;
                        int tipo1 = PilaTiposLogica.top();
                        PilaTiposLogica.pop();  // Hacer pop para obtener el siguiente valor en la pila

                        // Verificar si la pila tiene al menos un segundo valor

                        int tipo2 = PilaTiposLogica.top();  // Obtener el valor debajo del tope original

                        PilaTiposLogica.push(tipo1);


                        if(verificarOperacion(tipo1,tipo2,topePilaOpe) !=-1){
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            int resultado = verificarOperacion(tipo1,tipo2,topePilaOpe);
                            PilaTiposLogica.push(resultado);
                            PilaTiposUI.push(resultado);
                            PilaOperadoresLogica.pop();

                            //qDebug()<<"Funciona *";

                        }else{

                            QString tipo1Texto = obtenerNombreTipo(tipo1);  // Convierte el tipo 1 a texto
                            QString tipo2Texto = obtenerNombreTipo(tipo2);  // Convierte el tipo 2 a texto
                            if (!ui->txtErrores->toPlainText().contains(QString("Error Semantico: Error en operacion. Tipos incompatibles entre %1 %2 %3")
                                                                            .arg(tipo2Texto).arg(topePilaOpe).arg(tipo1Texto))) {
                                ui->txtErrores->append(QString("Error Semantico: Error en operacion. Tipos incompatibles entre ""%1 %2 %3")
                                                           .arg(tipo2Texto).arg(topePilaOpe).arg(tipo1Texto));
                            }
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            PilaTiposLogica.push(206);
                            PilaTiposUI.push(206);
                            PilaOperadoresLogica.pop();
                        }
                    }

                }
                else if(topePila==806){
                    if (topePilaOpe == "||"){
                        //qDebug() << "Operador: " << topePilaOpe;
                        int tipo1 = PilaTiposLogica.top();
                        PilaTiposLogica.pop();  // Hacer pop para obtener el siguiente valor en la pila

                        // Verificar si la pila tiene al menos un segundo valor

                        int tipo2 = PilaTiposLogica.top();  // Obtener el valor debajo del tope original

                        PilaTiposLogica.push(tipo1);


                        if(verificarOperacion(tipo1,tipo2,topePilaOpe) !=-1){
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            int resultado = verificarOperacion(tipo1,tipo2,topePilaOpe);
                            PilaTiposLogica.push(resultado);
                            PilaTiposUI.push(resultado);
                            PilaOperadoresLogica.pop();

                            //qDebug()<<"Funciona *";

                        }else{

                            QString tipo1Texto = obtenerNombreTipo(tipo1);  // Convierte el tipo 1 a texto
                            QString tipo2Texto = obtenerNombreTipo(tipo2);  // Convierte el tipo 2 a texto
                            if (!ui->txtErrores->toPlainText().contains(QString("Error Semantico: Error en operacion. Tipos incompatibles entre %1 %2 %3")
                                                                            .arg(tipo2Texto).arg(topePilaOpe).arg(tipo1Texto))) {
                                ui->txtErrores->append(QString("Error Semantico: Error en operacion. Tipos incompatibles entre ""%1 %2 %3")
                                                           .arg(tipo2Texto).arg(topePilaOpe).arg(tipo1Texto));
                            }
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            PilaTiposLogica.push(203);
                            PilaTiposUI.push(203);
                            PilaOperadoresLogica.pop();
                        }
                    }
                }else if(topePila==807){
                    PilaOperadores.push(textoToken);
                    PilaOperadoresLogica.push(textoToken);
                }else if(topePila==808){

                    PilaOperadores.push(textoToken);
                    PilaOperadoresLogica.push(textoToken);

                }else if(topePila==809){

                    PilaOperadores.push(textoToken);
                    PilaOperadoresLogica.push(textoToken);

                }else if(topePila==810){
                    PilaOperadores.push(textoToken);
                    PilaOperadoresLogica.push(textoToken);
                }
                else if(topePila==811){
                    //qDebug() << "Operador: " << textoToken;
                    //PilaOperadores.push("MFF");
                    PilaOperadoresLogica.push(textoToken);
                    //qDebug() << "Operador: " << textoToken;
                }else if(topePila==812){
                    //qDebug() << "Operador: " << textoToken;
                    //PilaOperadores.pop();
                    //qDebug() << "TopePila: " << PilaOperadoresLogica.top();
                    PilaOperadoresLogica.pop();
                }else if(topePila==813){
                    if (topePilaOpe == "=") {
                        // Obtener el tipo en el tope de la pila
                        int tipo1 = PilaTiposLogica.top();
                        PilaTiposLogica.pop();
                        int tipo2 = PilaTiposLogica.top();
                        PilaTiposLogica.push(tipo1);  // Restaurar tipo1 para la verificación

                        //qDebug() << "Tipo 1: " << tipo1;
                        //qDebug() << "Tipo 2: " << tipo2;
                        if (tipo1 == tipo2) {
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            PilaOperadoresLogica.pop();
                        } else {
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            PilaOperadoresLogica.pop();

                            // Registrar error de tipos incompatibles
                            QString tipo1Texto = obtenerNombreTipo(tipo1);
                            QString tipo2Texto = obtenerNombreTipo(tipo2);
                            ui->txtErrores->append(QString("Error Semantico: Error en Asignacion: Tipos incompatibles entre %1 y %2").arg(tipo2Texto).arg(tipo1Texto));
                        }
                    }
                }else if(topePila==814){
                    if (topePilaOpe == "==" || topePilaOpe == "!="|| topePilaOpe == ">"|| topePilaOpe == "<"|| topePilaOpe == "<="|| topePilaOpe == ">="){
                        //qDebug() << "Operador: " << topePilaOpe;
                        int tipo1 = PilaTiposLogica.top();
                        PilaTiposLogica.pop();  // Hacer pop para obtener el siguiente valor en la pila

                        // Verificar si la pila tiene al menos un segundo valor

                        int tipo2 = PilaTiposLogica.top();  // Obtener el valor debajo del tope original

                        PilaTiposLogica.push(tipo1);


                        if(verificarOperacion(tipo1,tipo2,topePilaOpe) !=-1){
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            int resultado = verificarOperacion(tipo1,tipo2,topePilaOpe);
                            //qDebug() << "Resultado: " << resultado;
                            PilaTiposLogica.push(resultado);
                            PilaTiposUI.push(resultado);
                            PilaOperadoresLogica.pop();

                            //qDebug()<<"Funciona *";

                        }else{

                            QString tipo1Texto = obtenerNombreTipo(tipo1);  // Convierte el tipo 1 a texto
                            QString tipo2Texto = obtenerNombreTipo(tipo2);  // Convierte el tipo 2 a texto
                            if (!ui->txtErrores->toPlainText().contains(QString("Error Semantico: Error en operacion. Tipos incompatibles entre %1 %2 %3")
                                                                            .arg(tipo2Texto).arg(topePilaOpe).arg(tipo1Texto))) {
                                ui->txtErrores->append(QString("Error Semantico: Error en operacion. Tipos incompatibles entre ""%1 %2 %3")
                                                           .arg(tipo2Texto).arg(topePilaOpe).arg(tipo1Texto));
                            }
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            PilaTiposLogica.push(206);
                            PilaTiposUI.push(206);
                            PilaOperadoresLogica.pop();
                        }
                    }
                }else if(topePila==815){

                    if (topePilaOpe == "!"){
                        //qDebug() << "Operador: " << topePilaOpe;
                        int tipo1 = PilaTiposLogica.top();
                        PilaTiposLogica.pop();  // Hacer pop para obtener el siguiente valor en la pila

                        // Verificar si la pila tiene al menos un segundo valor

                        int tipo2 = PilaTiposLogica.top();  // Obtener el valor debajo del tope original

                        PilaTiposLogica.push(tipo1);


                        if(verificarOperacion(tipo1,tipo2,topePilaOpe) !=-1){
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            int resultado = verificarOperacion(tipo1,tipo2,topePilaOpe);
                            PilaTiposLogica.push(resultado);
                            PilaTiposUI.push(resultado);
                            PilaOperadoresLogica.pop();

                            //qDebug()<<"Funciona *";

                        }else{

                            QString tipo1Texto = obtenerNombreTipo(tipo1);  // Convierte el tipo 1 a texto
                            QString tipo2Texto = obtenerNombreTipo(tipo2);  // Convierte el tipo 2 a texto
                            if (!ui->txtErrores->toPlainText().contains(QString("Error Semantico: Error en operacion. Tipos incompatibles entre %1 %2 %3")
                                                                            .arg(tipo2Texto).arg(topePilaOpe).arg(tipo1Texto))) {
                                ui->txtErrores->append(QString("Error Semantico: Error en operacion. Tipos incompatibles entre ""%1 %2 %3")
                                                           .arg(tipo2Texto).arg(topePilaOpe).arg(tipo1Texto));
                            }
                            PilaTiposLogica.pop();
                            PilaTiposLogica.pop();
                            PilaTiposLogica.push(206);
                            PilaTiposUI.push(206);
                            PilaOperadoresLogica.pop();
                        }
                    }

                }
            }else{
                if(estadoLexico == 100){
                    columna = RelCol(palabResevID);
                }else{
                    columna = RelCol(estadoLexico);
                }
                produccion = MPred[topePila][columna];
                if(produccion < 600 && (produccion == topePila || producciones[produccion][0] > 0)){
                    PilaEjecucion.pop();
                    for (int i = 12; i >= 0; --i) {
                        int valor = producciones[produccion][i];
                        if (valor > 0) {
                            PilaEjecucion.push(valor);
                            if(valor>=202 && valor <= 206){
                                size = PilaNombreId.size();
                                for (int i = 0; i < size; ++i) {  // Llenar PilaOperandos con el mismo número de tipos
                                    PilaTipos.push(valor);  // Agregar el tipo a la pila PilaOperandos
                                }
                            }
                            if(valor == 216){
                                banderadeclara = true;
                            }
                            if(valor == 215){
                                qDebug() <<valor;
                                banderaOutput = true;
                            }
                            if(valor ==11 ||valor==12){
                                banderaEstAsig=true;
                            }

                        }
                    }
                }else if(produccion < 600 && producciones[produccion][0] == -1){
                    PilaEjecucion.pop();
                } else {
                    int error = 0;
                    if(topePila <= 34 && columna < 54){
                        ErroresSintac(MPred[topePila][columna]);
                        QString error = QString ("%1: %2").arg("Error sintactico no se esperaba ", textoToken);
                        ui->txtErrores->append(error);
                    }else{
                        QString error = QString ("%1: %2").arg("Error sintactico no se esperaba ", textoToken);
                        //ui->txtErrores->append(error);
                        break;
                    }
                    //qDebug() << "Error sintactico";
                    break;
                }
            }
        }

    } while(estadoLexico != 999 || !PilaEjecucion.empty());
    mostrarTablaSimbolos();
    mostrarTablaTipos();
    mostrarTablaOper();
    mostrarTablaOperandos();
    mostrarTablaSaltos();
    mostrarTablaCuadruplos();
    CodigoObjeto();

}

void Kratos::CodigoObjeto() {
    // Crear un archivo para guardar los datos
    QFile file("C:\\Users\\ferba\\Development\\Kratos\\cuadruplos.txt");

    // Abrir el archivo en modo de escritura
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error al abrir el archivo para escribir.";
        return;
    }

    QTextStream out(&file);

    // Recorrer las filas y columnas de la tabla
    int rowCount = ui->tablaCuadruplosWidget->rowCount();
    int columnCount = ui->tablaCuadruplosWidget->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < columnCount; ++col) {
            // Obtener el texto de la celda
            QTableWidgetItem *item = ui->tablaCuadruplosWidget->item(row, col);
            if (item) {
                out << item->text();
            }

            // Si no es la última columna, agregar una coma (para formato CSV)
            if (col < columnCount - 1) {
                out << ", ";
            }
        }
        out << "\n";  // Nueva línea al final de cada fila
    }

    file.close();  // Cerrar el archivo
    qDebug() << "Exportación completada.";
}


void Kratos::agregarCuadruplo(int numero, const QString& operador,
                      const QString& operando1, const QString& operando2,const QString& resultado) {

    tablaCuadruplos.append({numero, operador, operando1,operando2, resultado});

}

void Kratos::funcionRellenar(int numero, const QString& direccion) {
    int indice = numero - 1;  // Restar 1 porque QVector usa base 0

    if (indice >= 0 && indice < tablaCuadruplos.size()) {
        tablaCuadruplos[indice].resultado = direccion;
        QString num = QString::number(numero);
        QString rellenar = QString("%1 (%2,%3)").arg("Funcion Rellenar",num, direccion);
        ui->txtFuncRel->append(rellenar);
        qDebug() << "Cuádruplo en posición" << numero << "rellenado con dirección:" << direccion;
    } else {
        qDebug() << "Error: índice del cuádruplo fuera de rango.";
    }
}

int Kratos::dameTokenPalResID(int estadoLexico, QString textoToken){
    int palabResevID = 0;
    if (estadoLexico == 100) {
        // Verificar si el token es una palabra reservada
        auto it = std::find_if(std::begin(PalabrasReservadas), std::end(PalabrasReservadas), [&textoToken](const PalabraReservada& pr) {
            return pr.palabra == textoToken;
        });
        if (it != std::end(PalabrasReservadas)) {
            palabResevID = it->id;
        }
    }
    return palabResevID;
}


int Kratos::dameToken(int &posicionLexico, QString textoCodigo, QString &textoToken) {

    int edo = 0;
    int col = 0;

    QChar car;
    QChar prevCar = '\0';
    QChar nextCar;

    int apCadInicio = posicionLexico;

    QString myTextoCodigo = textoCodigo;

    myTextoCodigo = myTextoCodigo.append("\n");

    int cadenaSize = myTextoCodigo.size();
    int estadoToken = 0; // Variable para almacenar el estado del último token analizado

    while (posicionLexico < cadenaSize && textoToken.isEmpty()) {
        car = myTextoCodigo[posicionLexico];
        nextCar = (posicionLexico + 1 < cadenaSize) ? myTextoCodigo[posicionLexico + 1] : '\0';

        col = relaciona(prevCar, car, nextCar);
        edo = MatrizLexica[edo][col];  // Actualizar el estado con el carácter actual

        // Preparar prevCar para la próxima iteración
        prevCar = car;

        if (edo > 27) {  // Asegurar que el token tenga contenido
            int tokenSize = 1;

            if (posicionLexico <= apCadInicio) {
                posicionLexico++;
            } else {
                tokenSize = posicionLexico - apCadInicio;
            }

            textoToken = myTextoCodigo.mid(apCadInicio, tokenSize).trimmed(); // Recortar espacios al final
        } else {
            posicionLexico++;
            if(car.isSpace()){
                apCadInicio++;
            }
        }

    }

    if (posicionLexico >= cadenaSize){
        return 999;
    }

    return edo;
}






void Kratos::guardarArchivo() {
    //guardar variable del nombre en string

    // Obtener el texto del QTextEdit
    QString texto = ui->txtCodigo->toPlainText();

    // Abrir un cuadro de diálogo para que el usuario seleccione la ubicación y el nombre del archivo
    QString NomArchivo = QFileDialog::getSaveFileName(this, tr("Guardar archivo de texto"), "", tr("Archivos de texto (*.kcod)"));

    // Verificar si el usuario ha cancelado la selección del archivo
    if (NomArchivo.isEmpty())
        return;

    // Intentar abrir el archivo para escribir
    QFile file(NomArchivo);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("No se pudo abrir el archivo para escribir."));
        return;
    }

    // Escribir el contenido del QTextEdit en el archivo
    QTextStream out(&file);
    out << texto;

    // Cerrar el archivo
    file.close();
    QMessageBox::information(this, tr("Guardado exitoso"), tr("El archivo se ha guardado correctamente"));

}
