#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
    public:
        Rectangle(double x = 0.0, double y = 0.0, double w = 1.0, double h = 1.0);

        double x() const;
        double y() const;
        double w() const;
        double h() const;
        double area() const;

        Rectangle intersection(const Rectangle& r) const;

    private:
        double m_x; // coordinate x of the rectangle's CENTER
        double m_y; // coordinate y of the rectangle's CENTER
        double m_w; // width of the rectangle
        double m_h; // height of the rectangle
};

#endif
