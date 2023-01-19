#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    key_buffer = new RingBuffer(100);

    k_worker= new Keypad_worker(key_buffer);
    if (k_worker->keypadInit("/dev/input/event2")){

    connect(k_worker, &QThread::finished,k_worker,&QObject::deleteLater);
    connect(k_worker,&Keypad_worker::newinputNotifier, this, &Controller::printKey);

    k_worker->start();

    }
}

Controller::~Controller(){

    k_worker->quit();
    k_worker->wait();
}

void Controller::printKey(){

      while(!key_buffer->isEmpty()){
      qInfo()<<"Key Input : "<<QString::number(key_buffer->pull());
      }
}
