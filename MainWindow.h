#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Kratos;
}
QT_END_NAMESPACE

class Kratos : public QMainWindow
{
    Q_OBJECT

public:
    Kratos(QWidget *parent = nullptr);
    ~Kratos();
    struct Cuadruplo {
        int num;
        QString operador;
        QString operando1;
        QString operando2;
        QString resultado;
    };
    void AbrirArchivo();
    void guardarArchivo();
    int dameToken(int &posicionLexico, QString textoCodigo, QString &textoToken);
    int relaciona(QChar prevChar, QChar currChar, QChar nextChar);
    void mostrarTipoDeToken(int e,QString token);
    void mostrarErrorEnToken(int e,QString token);
    int PalabraReservadaToID(QString palRes);
    int dameTokenPalResID(int estadoLexico, QString textoToken);
    void Lexico();
    void ClearTokenQueue();
    void PrintTokenQueue() const;
    void SintacticoSemantico();
    int RelCol(int estado);
    int ErroresSintac(int estado);
    int ObtenerProd(int numeroProd);
    QString obtenerNombreTipo(int tipoVar);
    void mostrarTablaSimbolos();
    int ParseTipoVar(int tipoVar);
    int verificarOperacion(int tipo1, int tipo2, QString operador);
    void mostrarTablaTipos();
    void mostrarTablaOper();
    QString currentFilePath;
    void mostrarTablaOperandos();
    void mostrarTablaCuadruplos();
    void mostrarTablaSaltos();
    void funcionRellenar(int numero, const QString& direccion);
    void agregarCuadruplo(int numero, const QString& operador,
                          const QString& operando1, const QString& operando2, const QString& resultado
                          );
    void CodigoObjeto();
    // int posicionLexico;
    // QString textoCodigo;
    // QString textoToken;




private:
    Ui::Kratos *ui;
};
#endif // MAINWINDOW_H
