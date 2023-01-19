#include "keypad_checker.h"
#include <QDebug>

Keypad_checker::Keypad_checker(RingBuffer *buffer)
{
    keypad_buffer = buffer;
}


void Keypad_checker::run(){
     running = true;

    keypadRead();

}

void Keypad_checker::keypadRead(){

    qInfo()<<"Starting Keypad checker thread";
    while(running){

        if (isNewinput()){

            emit keypadinputNotify(keypad_buffer->pull());
            //QThread::msleep(500);
            running=false;
        }

    }
    qInfo()<<"Stopping Keypad checker thread";
}

bool Keypad_checker::isNewinput(){

    return !keypad_buffer->isEmpty();
}

void Keypad_checker::stopKeypadread(){
    const QMutexLocker locker(&m_mutex);
    running = false;
}

bool Keypad_checker::isRunning(){

    const QMutexLocker locker(&m_mutex);
    return running;

}
