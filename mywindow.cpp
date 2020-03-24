#include "mywindow.h"
#include <cmath>
#include <QDebug>
#include "ui_mywindow.h"
#include <iostream>
using namespace std;
MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    ui->setupUi(this);
    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();
    img = new QImage(szer,wys,QImage::Format_RGB32);
    Back = new QImage(":/yellow.jpg");
    Left = new QImage(":/green.jpg");
    Front = new QImage(":/white.jpg");
    Right = new QImage(":/blue.jpg");
    Up = new QImage(":/red.jpg");
    Down = new QImage(":/orange.jpg");
    wykonaj();
}

MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
}

void MyWindow::czysc()
{
    unsigned char *ptr;
    ptr = img->bits();
    int i,j;
    for(i=0; i<wys; i++)
    {
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j] = 0;
            ptr[szer*4*i + 4*j + 1] = 0;
            ptr[szer*4*i + 4*j + 2] = 0;
        }
    }
}

void MyWindow::rysujPunkty(int x, int y, int r, int g, int b){
    int i,j;
    for(i = x - 2; i <= x + 2; i++){
        for(j = y - 2; j <= y + 2; j++){
            rysujPiksel(i,j,r,g,b);
        }
    }
}

void MyWindow::rysujPiksel(int x, int y, int r, int g, int b){
    unsigned char *ptr;
    ptr = img->bits();
    if(x >= 0 && y >= 0 && x < szer && y < wys){
        ptr[szer * 4 * y + 4 * x] = static_cast<unsigned char>(b);
        ptr[szer * 4 * y + 4 * x + 1] = static_cast<unsigned char>(g);
        ptr[szer * 4 * y + 4 * x + 2] = static_cast<unsigned char>(r);
    }
}

pair<int,int> MyWindow::convert(Punkt punkt){
    double tmp;
    tmp = (Dwidza + punkt.getZ()) / Dwidza;
    if(tmp == 0.0){
        tmp = 0.0001;
    }
    return make_pair(static_cast<int>(punkt.getX() / tmp) + 250,static_cast<int>(-punkt.getY() / tmp) + 250);
}

void MyWindow::wykonaj(){
    czysc();
    swiatlo.set(swiatloOX,swiatloOY,swiatloOZ);
    pair<int,int> sw = convert(swiatlo);
    rysujPunkty(sw.first,sw.second,255,255,255);
    kostka.set(250,250,0,50);
    kostka.rotate(obrotOX,obrotOY,obrotOZ);
    kostka.slope(pochylenieOX,pochylenieOY,pochylenieOZ);
    kostka.scale(skalowanieOX,skalowanieOY,skalowanieOZ);
    kostka.move(przesuniecieOX,przesuniecieOY,przesuniecieOZ);
    if(kostka.checkFront()){
        pair<int,int> *punkt = kostka.Front();
        Teksturowanie(make_pair(0,0),make_pair(500,0),make_pair(0,500),punkt[0],punkt[1],punkt[2],Front->bits(),kostka.normalFront(),kostka.lightPositionFrontUp(swiatlo));
        Teksturowanie(make_pair(0,500),make_pair(500,500),make_pair(500,0),punkt[2],punkt[3],punkt[1],Front->bits(),kostka.normalFront(),kostka.lightPositionFrontDown(swiatlo));
    }
    if(kostka.checkUp()){
        pair<int,int> *punkt = kostka.Up();
        Teksturowanie(make_pair(0,0),make_pair(500,0),make_pair(0,500),punkt[0],punkt[1],punkt[2],Down->bits(),kostka.normalUp(),kostka.lightPositionUpUp(swiatlo));
        Teksturowanie(make_pair(0,500),make_pair(500,500),make_pair(500,0),punkt[2],punkt[3],punkt[1],Down->bits(),kostka.normalUp(),kostka.lightPositionUpDown(swiatlo));
    }
    if(kostka.checkDown()){
        pair<int,int> *punkt = kostka.Down();
        Teksturowanie(make_pair(0,0),make_pair(500,0),make_pair(0,500),punkt[0],punkt[1],punkt[2],Up->bits(),kostka.normalDown(),kostka.lightPositionDownUp(swiatlo));
        Teksturowanie(make_pair(0,500),make_pair(500,500),make_pair(500,0),punkt[2],punkt[3],punkt[1],Up->bits(),kostka.normalDown(),kostka.lightPositionDownDown(swiatlo));
    }
    if(kostka.checkLeft()){
        pair<int,int> *punkt = kostka.Left();
        Teksturowanie(make_pair(0,0),make_pair(500,0),make_pair(0,500),punkt[0],punkt[1],punkt[2],Left->bits(),kostka.normalLeft(),kostka.lightPositionLeftUp(swiatlo));
        Teksturowanie(make_pair(0,500),make_pair(500,500),make_pair(500,0),punkt[2],punkt[3],punkt[1],Left->bits(),kostka.normalLeft(),kostka.lightPositionLeftDown(swiatlo));
    }
    if(kostka.checkRight()){
        pair<int,int> *punkt = kostka.Right();
        Teksturowanie(make_pair(0,0),make_pair(500,0),make_pair(0,500),punkt[0],punkt[1],punkt[2],Right->bits(),kostka.normalRight(),kostka.lightPositionRightUp(swiatlo));
        Teksturowanie(make_pair(0,500),make_pair(500,501),make_pair(500,0),punkt[2],punkt[3],punkt[1],Right->bits(),kostka.normalRight(),kostka.lightPositionRightDown(swiatlo));
    }
    if(kostka.checkBack()){
        pair<int,int> *punkt = kostka.Back();
        Teksturowanie(make_pair(0,0),make_pair(500,0),make_pair(0,500),punkt[0],punkt[1],punkt[2],Back->bits(),kostka.normalBack(),kostka.lightPositionBackUp(swiatlo));
        Teksturowanie(make_pair(0,500),make_pair(500,500),make_pair(500,0),punkt[2],punkt[3],punkt[1],Back->bits(),kostka.normalBack(),kostka.lightPositionBackDown(swiatlo));
    }
    update();
}

double MyWindow::Interpolacja(int x, int y, double dx){
    return (1-dx)*x+dx*y;
}

void MyWindow::Teksturowanie(pair<int,int> A, pair<int,int> B, pair<int,int> C,
                             pair<int,int> At, pair<int,int> Bt, pair<int,int> Ct,
                             unsigned char *org, Punkt N, Punkt L){
    int Xmin,Xmax,Ymin,Ymax;
    double a,b,v,w,u,delta;
    int i,j,x,y,xn,yn;
    int r,g,blue;
    Xmin = Xmax = At.first;
    Ymin = Ymax = At.second;
    if(Bt.first < Xmin){
        Xmin = Bt.first;
    }
    if(Ct.first < Xmin){
        Xmin = Ct.first;
    }
    if(Bt.first > Xmax){
        Xmax = Bt.first;
    }
    if(Ct.first > Xmax){
        Xmax = Ct.first;
    }
    if(Bt.second < Ymin){
        Ymin = Bt.second;
    }
    if(Ct.second < Ymin){
        Ymin = Ct.second;
    }
    if(Bt.second > Ymax){
        Ymax = Bt.second;
    }
    if(Ct.second > Ymax){
        Ymax = Ct.second;
    }
    delta = (((Bt.first - At.first) * (Ct.second - At.second)) - ((Ct.first - At.first) * (Bt.second - At.second)));
    L = L.normalizacja();
    N = N.normalizacja();
    int oswietl;
    if(N.iloczyn(L) > 0)
        oswietl = static_cast<int>( 20 + N.iloczyn(L) * 40);
    else
        oswietl = static_cast<int>( N.iloczyn(L) * 60);

    for(i=Ymin; i<=Ymax; i++)
    {
        for(j=Xmin; j<=Xmax; j++)
        {
            v = (((j - At.first) * (Ct.second - At.second)) - ((Ct.first - At.first) * (i - At.second))) / delta;
            w = (((Bt.first - At.first) * (i - At.second)) - ((j - At.first) * (Bt.second - At.second))) / delta;
            u = 1 - v - w;
            if (u >= 0 && u <= 1 && v >= 0 && v <= 1 && w >= 0 && w <= 1){
                a = static_cast<double>(u * A.first + v * B.first + w * C.first);
                b = static_cast<double>(u * A.second + v * B.second + w * C.second);
                x = static_cast<int>(a);
                y = static_cast<int>(b);
                xn = x + 1;
                yn = y + 1;
                a -=x;
                b -=y;
                if(yn == wys)
                    yn--;
                if(xn == szer)
                    xn--;
                r = static_cast<int>(round(Interpolacja(static_cast<int>(Interpolacja(org[szer*4*y + 4*x + 2],org[szer*4*yn + 4*x + 2],b)),
                                     static_cast<int>(Interpolacja(org[szer*4*y + 4*xn + 2],org[szer*4*yn + 4*xn + 2],b)),a)));
                g = static_cast<int>(round(Interpolacja(static_cast<int>(Interpolacja(org[szer*4*y + 4*x + 1],org[szer*4*yn + 4*x + 1],b)),
                                     static_cast<int>(Interpolacja(org[szer*4*y + 4*xn + 1],org[szer*4*yn + 4*xn + 1],b)),a)));
                blue = static_cast<int>(round(Interpolacja(static_cast<int>(Interpolacja(org[szer*4*y + 4*x],org[szer*4*yn + 4*x],b)),
                                        static_cast<int>(Interpolacja(org[szer*4*y + 4*xn],org[szer*4*yn + 4*xn],b)),a)));
                if(r + oswietl > 255){
                    r = 255;
                }
                else if(r + oswietl < 0){
                    r = 0;
                }
                else {
                    r += oswietl;
                }
                if(g + oswietl > 255){
                    g = 255;
                }
                else if(g + oswietl < 0){
                    g = 0;
                }
                else {
                    g += oswietl;
                }
                if(blue + oswietl > 255){
                    blue = 255;
                }
                else if(blue + oswietl < 0){
                    blue = 0;
                }
                else {
                    blue += oswietl;
                }
                rysujPiksel(j,i,r,g,blue);
            }
        }
    }
}

void MyWindow::on_horizontalSlider_4_valueChanged(int value)
{
    skalowanieOX = value / 250.0;
    wykonaj();
}
void MyWindow::on_horizontalSlider_5_valueChanged(int value)
{
    skalowanieOY = value / 250.0;
    wykonaj();
}
void MyWindow::on_horizontalSlider_6_valueChanged(int value)
{
    skalowanieOZ = value / 250.0;
    wykonaj();
}
void MyWindow::on_dial_valueChanged(int value)
{
    obrotOX = value / 180.0 * M_PI;
    wykonaj();
}
void MyWindow::on_dial_2_valueChanged(int value)
{
    obrotOY = value / 180.0 * M_PI;
    wykonaj();
}
void MyWindow::on_dial_3_valueChanged(int value)
{
    obrotOZ = value / 180.0 * M_PI;
    wykonaj();
}
void MyWindow::on_horizontalSlider_7_valueChanged(int value)
{
    pochylenieOX = 1 - (value/250.0);
    wykonaj();
}
void MyWindow::on_horizontalSlider_8_valueChanged(int value)
{
    pochylenieOY = 1 - (value/250.0);
    wykonaj();
}
void MyWindow::on_horizontalSlider_9_valueChanged(int value)
{
    pochylenieOZ = 1 - (value/250.0);
    wykonaj();
}
void MyWindow::on_horizontalSlider_valueChanged(int value)
{
    przesuniecieOX = value - 250;
    wykonaj();
}
void MyWindow::on_horizontalSlider_2_valueChanged(int value)
{
    przesuniecieOY = value - 250;
    wykonaj();
}
void MyWindow::on_horizontalSlider_3_valueChanged(int value)
{
    przesuniecieOZ = value - 250;
    wykonaj();
}
void MyWindow::on_horizontalSlider_10_valueChanged(int value)
{
    swiatloOX = value - 250;
    wykonaj();
}
void MyWindow::on_horizontalSlider_11_valueChanged(int value)
{
    swiatloOY = value - 250;
    wykonaj();
}
void MyWindow::on_horizontalSlider_12_valueChanged(int value)
{
    swiatloOZ = value - 150;
    wykonaj();
}
void MyWindow::on_pushButton_clicked()
{
    przesuniecieOX = 0;
    przesuniecieOY = 0;
    przesuniecieOZ = 0;
    skalowanieOX = 1;
    skalowanieOY = 1;
    skalowanieOZ = 1;
    pochylenieOX = 0;
    pochylenieOY = 0;
    pochylenieOZ = 0;
    obrotOX = 0;
    obrotOY = 0;
    obrotOZ = 0;
    swiatloOX = 0;
    swiatloOY = 0;
    swiatloOZ = 100;
    ui->horizontalSlider->setValue(250);
    ui->horizontalSlider_2->setValue(250);
    ui->horizontalSlider_3->setValue(250);
    ui->horizontalSlider_4->setValue(250);
    ui->horizontalSlider_5->setValue(250);
    ui->horizontalSlider_6->setValue(250);
    ui->horizontalSlider_7->setValue(250);
    ui->horizontalSlider_8->setValue(250);
    ui->horizontalSlider_9->setValue(250);
    ui->dial->setValue(0);
    ui->dial_2->setValue(0);
    ui->dial_3->setValue(0);
    ui->horizontalSlider_10->setValue(250);
    ui->horizontalSlider_11->setValue(250);
    ui->horizontalSlider_12->setValue(250);
    wykonaj();
}
