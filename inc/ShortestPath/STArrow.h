#ifndef STARROW_H
#define STARROW_H

#include <GUI/Arrow.h>

class STArrow : public Arrow{
    public:
        STArrow(Vector2 pos,int to);
        void setDestination(Vector2 targetDes) override;
        void draw(bool isWeighted, bool isDirected);
        void setWeight(int weight);
        int getWeight();
        void setTo(int to);
        int getTo();
        void setFrom(int from);
        int getFrom();

        void setHighlight();
        void deHighlight();
        void setLine();
        void deLine();

    private:
        int from;
        int to;
        int weight;

        bool isHighlight=false;
        bool isLine=false;
};

#endif