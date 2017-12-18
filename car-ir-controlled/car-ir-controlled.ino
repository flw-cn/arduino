# include <stdarg.h>
# include <IRremote.h>

# include "car.hpp"

int IR_RECV = 2;
IRrecv irRecv(IR_RECV);

void doIR(unsigned long code);

bool isRunning = false;
long timer;

# define TIMEOUT    150

# define SONY_IR_CODE_BACKWARD1 0x00000AF0
# define SONY_IR_CODE_BACKWARD2 0x086BD99C
# define SONY_IR_CODE_FORWARD1  0x000002F0
# define SONY_IR_CODE_FORWARD2  0xEC27D43D
# define SONY_IR_CODE_LEFT1     0x000002D0
# define SONY_IR_CODE_LEFT2     0x1A422E43
# define SONY_IR_CODE_RIGHT1    0x00000CD0
# define SONY_IR_CODE_RIGHT2    0xA23BD824

# define IR_CODE_FORWARD1       0xFF02FD
# define IR_CODE_BACKWARD1      0xFF9867
# define IR_CODE_LEFT1          0xF076C13B
# define IR_CODE_RIGHT1         0xFF906F

Car car;

void setup() {
#ifdef DEBUG
    Serial.begin(9600);
#endif
    Motor leftWheel("leftWheel"), rightWheel("rightWheel");
    leftWheel.attach(6, 9, 8);
    rightWheel.attach(5, 11, 12);
    car.attach(leftWheel, rightWheel);

    irRecv.enableIRIn();
}

void loop() {
    decode_results results;

    if ( irRecv.decode(&results) ){
        doIR(results.value);
        irRecv.resume();
    }

    long elapse = millis() - timer;
    if ( isRunning && elapse > TIMEOUT ) {
        car.stop();
        isRunning = false;
    }
}

void doIR(unsigned long code) {
    bool isValidCode = true;

    switch(code){
        case SONY_IR_CODE_FORWARD1:
        case SONY_IR_CODE_FORWARD2:
        case IR_CODE_FORWARD1:
            car.forward(6);
            break;
        case SONY_IR_CODE_BACKWARD1:
        case SONY_IR_CODE_BACKWARD2:
        case IR_CODE_BACKWARD1:
            car.backward(6);
            break;
        case SONY_IR_CODE_LEFT1:
        case SONY_IR_CODE_LEFT2:
        case IR_CODE_LEFT1:
            car.turnLeft(3);
            break;
        case SONY_IR_CODE_RIGHT1:
        case SONY_IR_CODE_RIGHT2:
        case IR_CODE_RIGHT1:
            car.turnRight(3);
            break;
        case REPEAT:
            break;
        default:
            DBG_LOG("Receive invalid IR code: %lX", code);
            isValidCode = false;
            break;
    }

    if ( isValidCode ){
        timer=millis();
        isRunning = true;
    }
}
