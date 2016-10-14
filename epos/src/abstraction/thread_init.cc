// EPOS Thread Abstraction Initialization

#include <system/kmalloc.h>
#include <system.h>
#include <thread.h>
#include <alarm.h>

__BEGIN_SYS

void Thread::init()
{
    // The installation of the scheduler timer handler must precede the
    // creation of threads, since the constructor can induce a reschedule
    // and this in turn can call timer->reset()
    // Letting reschedule() happen during thread creation is harmless, since
    // MAIN is created first and dispatch won't replace it nor by itself
    // neither by IDLE (which has a lower priority)

    // initialize the thread idle and puts it in the ready queue
    db<Thread>(WRN) << "Initializing Thread::_idle" << endl;

    Thread::_idle = new (kmalloc(sizeof(Thread)))
                      Thread(Thread::Configuration(Thread::READY, Thread::IDLE), &idle);

    db<Thread>(WRN) << "Initialized Thread::_idle = " << _idle << endl;
    // db<Init>(WRN) << "Thread::_ready queue size = "<< Thread::_ready.size() << endl;
    // db<Init>(WRN) << "Thread::_ready head = "<< Thread::_ready.head() << endl;

    if(preemptive)
        _timer = new (kmalloc(sizeof(Scheduler_Timer))) Scheduler_Timer(QUANTUM, time_slicer);
}

__END_SYS
