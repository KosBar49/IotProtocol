#ifndef DOUBLEMAP_H
#define DOUBLEMAP_H


class DoubleMap
{
    public:
        double const k = 1.0;
        DoubleMap(double x, double u);
        double nextElem();
        void setX(double x);
        void setU(double u);
        double getX();
        double getU();
        void iterate(int iter);
        virtual ~DoubleMap();

    private:
        double u;
        double x;
};

#endif // DOUBLEMAP_H
