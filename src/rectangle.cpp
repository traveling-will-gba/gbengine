#include "rectangle.h"

#include "utils.h"

#include <iostream>

using std::min;
using std::max;
using std::pair;
using std::make_pair;

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

bool Rectangle::intersection(const Rectangle& r) const
{
    double xa = x() - w() / 2;
    double xb = x() + w() / 2;

    double xc = r.x() - r.w() / 2;
    double xd = r.x() + r.w() / 2;

    double ya = y() - h() / 2;
    double yb = y() + h() / 2;

    double yc = r.y() - r.h() / 2;
    double yd = r.y() + r.h() / 2;

    pair <int, int> interX = make_pair(max(xa, xc), min(xb, xd));
    pair <int, int> interY = make_pair(max(ya, yc), min(yb, yd));

    return (interX.second - interX.first >=0 && interY.second - interY.first >= 0);
}
