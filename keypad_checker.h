#ifndef KEYPAD_CHECKER_H
#define KEYPAD_CHECKER_H

#include <QObject>
#include <linux/input.h>
#include "ringbuffer.h"
#include <QThread>
#include <QMutex>

class Keypad_checker : public QThread
{
    Q_OBJECT
    void run() override;

public:
    explicit Keypad_checker(RingBuffer *buffer);
    void keypadRead();
    void stopKeypadread();
    bool isRunning();
signals:
    void keypadinputNotify(char key_val);

private:
    bool isNewinput();
    RingBuffer *keypad_buffer;
    bool running;

    mutable QMutex m_mutex;

};

#endif // KEYPAD_CHECKER_H
