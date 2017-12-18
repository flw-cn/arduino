# include <math.h>
# include "log.h"

class Motor {
private:
    String m_name;
    bool m_isAttached;
    int m_maxSpeed;
    int m_speedPin;
    int m_forwardPin;
    int m_backwardPin;

public:
    Motor(String name) {
        m_name = name;
        m_maxSpeed = 255;
        m_isAttached = false;
    }

    void attach(int speedPin, int forwardPin, int backwardPin) {
        m_speedPin = speedPin;
        m_forwardPin = forwardPin;
        m_backwardPin = backwardPin;

        pinMode(m_speedPin, OUTPUT);
        pinMode(m_forwardPin, OUTPUT);
        pinMode(m_backwardPin, OUTPUT);

        DBG_LOG("Motor %s has been attached, SPEED/FORWARD/BACKWARD PIN=%d/%d/%d.",
                m_name.c_str(), m_speedPin, m_forwardPin, m_backwardPin);

        m_isAttached = true;
    }

    bool attached() {
        return m_isAttached;
    }

    void forward(int speed) {
        digitalWrite(m_forwardPin, HIGH);
        digitalWrite(m_backwardPin, LOW);
        speed = map(speed, 0, 10, 0, 255);
        analogWrite(m_speedPin, speed);

        DBG_LOG("Motor %s acting: forward/%d.", m_name.c_str(), speed);
    }

    void backward(int speed) {
        digitalWrite(m_forwardPin, LOW);
        digitalWrite(m_backwardPin, HIGH);
        speed = map(speed, 0, 10, 0, 255);
        analogWrite(m_speedPin, speed);

        DBG_LOG("Motor %s acting: backward/%d.", m_name.c_str(), speed);
    }

    void stop() {
        digitalWrite(m_forwardPin, LOW);
        digitalWrite(m_backwardPin, LOW);
        analogWrite(m_speedPin, 0);

        DBG_LOG("Motor %s has been stopped.", m_name.c_str());
    }
};
