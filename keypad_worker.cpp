#include "keypad_worker.h"
#include <QDebug>

Keypad_worker::Keypad_worker(RingBuffer *buffer){
    keypad_buffer= buffer;
}


void Keypad_worker::run(){

    running= true;
    keypad_thread();

}

void Keypad_worker::keypad_thread(){

    struct input_event ev;
    int rd;

    qInfo()<<"Starting Keypad thread";
    while(running){

        rd = read(inputdev_handler,&ev,sizeof(input_event));

        if (rd<(int)sizeof(input_event)){
            qCritical()<<"Error at reading input";
            return;
        }

        if ((ev.type == EV_KEY) && (ev.value == 1)) // only get Pressed Event
        {
            keypad_buffer->push((char)ev.code);
            emit newinputNotifier();
         //   qInfo()<<QString::number(ev.code);
        }

      //  QThread::msleep(500);
    }
    qInfo()<<"Stopping Keypad thread";
}

bool Keypad_worker::keypadInit(QString device){

    inputdev_handler = open(device.toStdString().c_str(), O_RDONLY);

    if (inputdev_handler<0){
        qCritical()<<"Error at opening device";
        return false;
    }
    return true;
}

void Keypad_worker::stopKeypad(){
    const QMutexLocker locker (&m_mutex);
    running= false;
}

bool Keypad_worker::isRunning(){
    const QMutexLocker locker (&m_mutex);
    return running;
}
