#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "keypad_checker.h"
#include "keypad_worker.h"
#include "ringbuffer.h"
#include <QDebug>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
public slots:
  void printKey();

private:

  Keypad_worker *k_worker;
  RingBuffer *key_buffer;
};

#endif // CONTROLLER_H
