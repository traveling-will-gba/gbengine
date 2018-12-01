#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
    public:
        Rectangle(int x = 0.0, int y = 0.0, int w = 1.0, int h = 1.0);

        int x() const;
        int y() const;
        int w() const;
        int h() const;
        int area() const;

        bool intersection(const Rectangle& r) const;

    private:
        int m_x; // coordinate x of the rectangle's CENTER
        int m_y; // coordinate y of the rectangle's CENTER
        int m_w; // width of the rectangle
        int m_h; // height of the rectangle
};

#endif
