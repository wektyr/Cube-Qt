#ifndef CUBE_H
#define CUBE_H
#include "punkt.h"
#include <algorithm>
using namespace std;
class Cube
{

public:
    Punkt A,B,C,D,E,F,G,H;
    Punkt center;
    double Dwidza = -500;
    double MacierzWynik[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    pair<int,int> a,b,c,d,e,f,g,h;
    Cube();
    Cube(double x, double y, double z, double large);
    void set(double x, double y, double z, double large);
    void update();
    void rotate(double obrotOX, double obrotOY, double obrotOZ);
    void scale(double skalowanieOX, double skalowanieOY, double skalowanieOZ);
    void slope(double pochylenieOX, double pochylenieOY, double pochylenieOZ);
    void move(double przesuniecieOX, double przesuniecieOY, double przesuniecieOZ);
    void matrix(double B[4][4]);

    pair<int,int> convert(Punkt punkt);

    bool checkTriangle(Punkt gora, Punkt dol, Punkt prawy, Punkt obserwator);
    bool checkFront();
    bool checkUp();
    bool checkDown();
    bool checkLeft();
    bool checkRight();
    bool checkBack();

    Punkt getNormal(Punkt gora, Punkt dol, Punkt prawy);
    Punkt normalFront();
    Punkt normalUp();
    Punkt normalDown();
    Punkt normalLeft();
    Punkt normalRight();
    Punkt normalBack();

    Punkt lightPositionFrontUp(Punkt oswietlenie);
    Punkt lightPositionFrontDown(Punkt oswietlenie);
    Punkt lightPositionUpUp(Punkt oswietlenie);
    Punkt lightPositionUpDown(Punkt oswietlenie);
    Punkt lightPositionDownUp(Punkt oswietlenie);
    Punkt lightPositionDownDown(Punkt oswietlenie);
    Punkt lightPositionLeftUp(Punkt oswietlenie);
    Punkt lightPositionLeftDown(Punkt oswietlenie);
    Punkt lightPositionRightUp(Punkt oswietlenie);
    Punkt lightPositionRightDown(Punkt oswietlenie);
    Punkt lightPositionBackUp(Punkt oswietlenie);
    Punkt lightPositionBackDown(Punkt oswietlenie);
    pair<int,int> *Front();
    pair<int,int> *Up();
    pair<int,int> *Down();
    pair<int,int> *Left();
    pair<int,int> *Right();
    pair<int,int> *Back();

};

#endif // CUBE_H
