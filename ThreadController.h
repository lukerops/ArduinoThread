/*
 	ThreadController.h - Controlls a list of Threads with different timings

	Basicaly, what it does is to keep track of current Threads and run when
	necessary.

	For instructions, go to https://github.com/ivanseidel/ArduinoThread

	Created by Lucas Campos Vieira, July, 2018.
	Based on Ivan Seidel Gomes library, https://github.com/ivanseidel/ArduinoThread.
*/

#ifndef ThreadController_h
#define ThreadController_h

#include "Thread.h"
#include "inttypes.h"

#define MAX_THREADS		15

class ThreadController {
    private:
        Thread* thread[MAX_THREADS];
        int cached_size;

    public:
        ThreadController();

        // loop to controll Threads
        void loop();

        // Adds a thread in the first available slot (remove first)
        // Returns if the Thread could be added or not
        bool add(Thread* _thread);

        // remove the thread (given the Thread* or ThreadID)
        void remove(int _id);
        void remove(Thread* _thread);

        // Removes all threads
        void clear();

        // Return the quantity of Threads
        int size(bool cached = true);

        // Return the I Thread on the array
        // Returns NULL if none found
        Thread* get(int index);
};

#endif
