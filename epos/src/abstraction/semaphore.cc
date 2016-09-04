// EPOS Semaphore Abstraction Implementation

#include <semaphore.h>

__BEGIN_SYS

Semaphore::Semaphore(int v): _value(v)
{
    db<Synchronizer>(TRC) << "Semaphore(value=" << _value << ") => " << this << endl;
}


Semaphore::~Semaphore()
{
    db<Synchronizer>(TRC) << "~Semaphore(this=" << this << ")" << endl;
}


void Semaphore::p()
{
  begin_atomic(); // ensure that the operation will be atomic

    db<Synchronizer>(TRC) << "Semaphore::p(this=" << this << ",value=" << _value << ")" << endl;

    fdec(_value);
    // while(_value < 0)
    //     sleep();
    if(_value < 0){ // avoid the loop that would make the cpu busy while _value < 0 (while the semaphore is locked)
      sleep();
    } else {
      end_atomic();
    }
}


void Semaphore::v()
{
  begin_atomic(); // ensure that the operation will be atomic

    db<Synchronizer>(TRC) << "Semaphore::v(this=" << this << ",value=" << _value << ")" << endl;

    finc(_value);
    if(_value < 1) {
        wakeup();
    } else {
      end_atomic();
    }
}

__END_SYS
