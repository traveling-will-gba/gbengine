#include "rectangle.h"

#include <iostream>

using std::min;
using std::max;

Rectangle::Rectangle(double xv, double yv, double wv, double hv) :
    m_x(xv), m_y(yv), m_w(wv), m_h(hv) { }   

double Rectangle::x() const {
    return m_x;
}   

double Rectangle::y() const {
    return m_y;
}   

double Rectangle::w() const {
    return m_w;
}   

double Rectangle::h() const {
    return m_h;
}   

double Rectangle::area() const
{   
    return m_w * m_h;
}   

Rectangle Rectangle::intersection(const Rectangle& r) const
{
    double xa = x() - w() / 2;
    double xb = x() + w() / 2;

    double xc = r.x() - r.w() / 2;
    double xd = r.x() + r.w() / 2;

    double xpos = 0, wv = 0;

    if ((xa <= xc and xb >= xc) or (xc <= xa and xd >= xa))
    {
        double left = max(xa, xc);
        double right = min(xb, xd);

        xpos = (left + right) / 2;
        wv = right - left;
    }

    double ya = y() - h() / 2;
    double yb = y() + h() / 2;

    double yc = r.y() - r.h() / 2;
    double yd = r.y() + r.h() / 2;

    double ypos = 0, hv = 0;

    if ((ya <= yc and yb >= yc) or (yc <= ya and yd >= ya))
    {
        double down = max(ya, yc);
        double up = min(yb, yd);

        ypos = (up + down) / 2;
        hv = up - down;
    }

    return Rectangle(xpos, ypos, wv, hv);
}
