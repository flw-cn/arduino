# include "motor.hpp"
# include "log.h"

class Car {
private:
    Motor m_leftWheel, m_rightWheel;

public:
    Car() : m_leftWheel(""), m_rightWheel("") {
    }

    void attach(Motor leftWheel, Motor rightWheel) {
        m_leftWheel = leftWheel;
        m_rightWheel = rightWheel;
    }

    void forward(int speed) {
        m_leftWheel.forward(speed);
        m_rightWheel.forward(speed);
    }

    void backward(int speed) {
        m_leftWheel.backward(speed);
        m_rightWheel.backward(speed);
    }

    void turnLeft(int speed) {
        m_leftWheel.backward(speed);
        m_rightWheel.forward(speed);
    }

    void turnRight(int speed) {
        m_leftWheel.forward(speed);
        m_rightWheel.backward(speed);
    }

    void stop() {
        m_leftWheel.stop();
        m_rightWheel.stop();
    }
};
