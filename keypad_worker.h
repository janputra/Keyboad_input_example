#ifndef KEYPAD_WORKER_H
#define KEYPAD_WORKER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include "ringbuffer.h"
#include <linux/input.h>
#include <qplatformdefs.h>


class Keypad_worker : public QThread
{
    Q_OBJECT
    void run() override;

public:
    explicit Keypad_worker(RingBuffer *buffer);

    void stopKeypad();
    bool keypadInit(QString device);

signals:
    void newinputNotifier();
private:
    bool isRunning();
    bool running =false;
    mutable QMutex m_mutex;
    RingBuffer *keypad_buffer;
    void keypad_thread();
    int inputdev_handler =-1;
};

#endif // KEYPAD_WORKER_H
