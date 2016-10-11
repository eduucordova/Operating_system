// EPOS Synchronizer Abstraction Test Program

#include <utility/ostream.h>
#include <thread.h>
#include <semaphore.h>
#include <alarm.h>

using namespace EPOS;

const int iterations = 20;

OStream cout;

const int BUF_SIZE = 16;
char buffer[BUF_SIZE];
Semaphore empty(BUF_SIZE);
Semaphore full(0);

int consumer()
{
    int out = 0;
    for(int i = 0; i < iterations; i++) {
        full.p();
        cout << "C<-" << buffer[out] << "\t";
        out = (out + 1) % BUF_SIZE;
        Alarm::delay(5000);
        empty.v();
    }

    // for(int i = iterations - 50; i > 0; --i) {
    // 	cout << "In loop for " << i << endl;
    // }

    return 0;
}

int main()
{
    Thread * cons = new Thread(&consumer);

    // producer
    int in = 0;
    for(int i = 0; i < iterations; i++) {
        empty.p();
        Alarm::delay(5000);
        buffer[in] = 'a' + in;
        cout << "P->" << buffer[in] << "\t";
        in = (in + 1) % BUF_SIZE;
        full.v();
    }
    cout << "Waiting for cons: " << cons << endl;
    cons->join();
    cout << "Ready to go!" << endl;

    cout << "The end!" << endl;

    delete cons;

    return 0;
}
