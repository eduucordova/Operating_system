// EPOS Synchronizer Abstractions Common Package

#ifndef __synchronizer_h
#define __synchronizer_h

#include <cpu.h>
#include <thread.h>

__BEGIN_SYS

class Synchronizer_Common
{
protected:
    Synchronizer_Common() {}

    // Atomic operations
    bool tsl(volatile bool & lock) { return CPU::tsl(lock); }
    int finc(volatile int & number) { return CPU::finc(number); }
    int fdec(volatile int & number) { return CPU::fdec(number); }

    // Thread operations
    void begin_atomic() { Thread::lock(); }
    void end_atomic() { Thread::unlock(); }

    void sleep() {
      // Thread::yield();
      Thread::sleep(); // calling the method sleep of the thread
    } // implicit unlock()
    void wakeup() {
      // end_atomic();
      Thread::wakeup();
    }
    void wakeup_all() {
      end_atomic();
      // Thread::wakeup_all();
    }
};

__END_SYS

#endif
