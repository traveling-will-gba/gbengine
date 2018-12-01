#include "rectangle.h"

#include "utils.h"

#include <iostream>

using std::min;
using std::max;
using std::pair;
using std::make_pair;

Rectangle::Rectangle(int xv, int yv, int wv, int hv) :
    m_x(xv), m_y(yv), m_w(wv), m_h(hv) { }   

int Rectangle::x() const {
    return m_x;
}   

int Rectangle::y() const {
    return m_y;
}   

int Rectangle::w() const {
    return m_w;
}   

int Rectangle::h() const {
    return m_h;
}   

int Rectangle::area() const
{   
    return m_w * m_h;
}   

bool Rectangle::intersection(const Rectangle& r) const
{
    int xa = x() - w() / 2;
    int xb = x() + w() / 2;

    int xc = r.x() - r.w() / 2;
    int xd = r.x() + r.w() / 2;

    int ya = y() - h() / 2;
    int yb = y() + h() / 2;

    int yc = r.y() - r.h() / 2;
    int yd = r.y() + r.h() / 2;

    pair <int, int> interX = make_pair(max(xa, xc), min(xb, xd));
    pair <int, int> interY = make_pair(max(ya, yc), min(yb, yd));

    return (interX.second - interX.first >=0 && interY.second - interY.first >= 0);
}
