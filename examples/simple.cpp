#include <iostream>

#include "W_Slot.h"
#include "W_Signal.h"

class Switch {
    public:
        W::Signal<int> Clicked;
};

class Light: public W::Slot {
    public:
        Light(): m_on(false) {}
        void Toggle(int n) {
            if(m_on) {
                ToggleOff();
            } else {
                ToggleOn();
            }

            std::cout << n << std::endl;
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

class StaticLight {
    public:
        static void Toggle(int n) {
            if(m_on) {
                ToggleOff();
            } else {
                ToggleOn();
            }
            std::cout << n << std::endl;
        }

        static void ToggleOff() {
            m_on = false;
            std::cout << "StaticLight OFF" << std::endl;
        }

        static void ToggleOn() {
            m_on = true;
            std::cout << "StaticLight ON" << std::endl;
        }

    private:
        static bool m_on;
};

bool StaticLight::m_on = false;

int main(int argc, const char *argv[]) {

    Switch sw;
    Light l1;

    sw.Clicked.connect(&l1, &Light::Toggle);
    sw.Clicked.connect(StaticLight::Toggle);

    sw.Clicked.emit(1);


    sw.Clicked.emit(2);


    sw.Clicked.emit(3);

    return 0;
}
