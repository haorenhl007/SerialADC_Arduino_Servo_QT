#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class QSerialPort; //Definimos la nueva clase para el puerto serial

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void fTimer();

private:
    Ui::MainWindow *ui;

    QSerialPort *hw; //Creamos el objeto
    QString hw_port_name;
    bool hw_is_available;
};

#endif // MAINWINDOW_H
