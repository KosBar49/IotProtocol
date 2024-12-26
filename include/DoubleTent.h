#ifndef DOUBLETENT_H
#define DOUBLETENT_H


class DoubleTent
{
    public:
        double const k = 1.0;
        double const c = 0.5;
        DoubleTent(double x, double u);
        double nextElem();
        void setX(double x);
        void setU(double u);
        double getX();
        double getU();
        void iterate(int iter);
        virtual ~DoubleTent();

    private:
        double u;
        double x;
};

#endif // DOUBLETENT_H
