#include <iostream>

#include "W_Slot.h"
#include "W_Signal.h"

class Switch {
    public:
        W::Signal<> Clicked;
};

class Light: public W::Slot {
    public:
        Light(): m_on(false) {}
        void Toggle() {
            if(m_on) {
                ToggleOff();
            } else {
                ToggleOn();
            }
        }

        void ToggleOn() {
            m_on = true;
            std::cout << "Light ON" << std::endl;
        }

        void ToggleOff() {
            m_on = false;
            std::cout << "Light OFF" << std::endl;
        }

    private:
        bool m_on;
};

int main(int argc, const char *argv[]) {

    Switch sw;
    Light l1;

    sw.Clicked.connect(&l1, &Light::Toggle);
    
    sw.Clicked.emit();
    sw.Clicked.emit();
    sw.Clicked.emit();

    return 0;
}
