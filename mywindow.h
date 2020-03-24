#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
using namespace std;

#include "cube.h"
#include "punkt.h"
namespace Ui {
    class MyWindow;
}

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit MyWindow(QWidget *parent = 0);
    ~MyWindow();

private:
    Ui::MyWindow *ui;
    Cube kostka;
    QImage *img;
    QImage *Front,*Back,*Left,*Right,*Down,*Up;
    int szer;
    int wys;
    int poczX;
    int poczY;
    int Dwidza = -500;
    int przesuniecieOX = 0;
    int przesuniecieOY = 0;
    int przesuniecieOZ = 0;
    double skalowanieOX = 1;
    double skalowanieOY = 1;
    double skalowanieOZ = 1;
    double pochylenieOX = 0;
    double pochylenieOY = 0;
    double pochylenieOZ = 0;
    double obrotOX = 0;
    double obrotOY = 0;
    double obrotOZ = 0;
    double swiatloOX = 0;
    double swiatloOY = 0;
    double swiatloOZ = 100;
    Punkt swiatlo;
    pair<int,int> convert(Punkt punkt);
    void czysc();
    void rysujPiksel(int x, int y, int r, int g, int b);
    void wykonaj();
    void rysujPunkty(int x, int y, int r, int g, int b);
    void Teksturowanie(pair<int,int> A, pair<int,int> B, pair<int,int> C,
                       pair<int,int> At, pair<int,int> Bt, pair<int,int> Ct,
                       unsigned char *org, Punkt N, Punkt L);
    double Interpolacja(int x,int y,double dx);
private slots:
    void paintEvent(QPaintEvent*);
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);
    void on_horizontalSlider_4_valueChanged(int value);
    void on_horizontalSlider_5_valueChanged(int value);
    void on_horizontalSlider_6_valueChanged(int value);
    void on_dial_valueChanged(int value);
    void on_dial_2_valueChanged(int value);
    void on_dial_3_valueChanged(int value);
    void on_horizontalSlider_7_valueChanged(int value);
    void on_horizontalSlider_8_valueChanged(int value);
    void on_horizontalSlider_9_valueChanged(int value);
    void on_horizontalSlider_10_valueChanged(int value);
    void on_horizontalSlider_11_valueChanged(int value);
    void on_horizontalSlider_12_valueChanged(int value);
    void on_pushButton_clicked();
};

#endif // MYWINDOW_H
