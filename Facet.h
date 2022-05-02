
#ifndef NEO_FACET_H
#define NEO_FACET_H


class Facet {
public:
    Facet() = default;
    Facet(int a, int b, int c) {
        index[0] = a;
        index[1] = b;
        index[2] = c;
    }
    int index[3];
};


#endif //NEO_FACET_H
