#include <iostream>

class P {
public:
    static int num;
    
    static void up() {
        num++;
    }
    static void print() {
        printf("%d\n", num);
    }
    
};

int P::num = 1;

class C : public P {

};

int main(int argv, char** args) {
    P* p2 = new P();
    P* pc = new C();
    
    P::print();
    P::up();
    P::print();
    p2->print();
    p2->up();
    p2->print();
    P::print();
    C::up();
    C::print();
    pc->print();
    pc->up();
    pc->print();
    P::print();
    C::print();
    return 0;
}

