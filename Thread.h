/*
 	Thread.h - An runnable object

	Thread is responsable for holding the "action" for something,
	also, it responds if it "should" or "should not" run, based on
	the current time;

	For instructions, go to https://github.com/ivanseidel/ArduinoThread

	Created by Lucas Campos Vieira, July, 2018.
	Based on Ivan Seidel Gomes library, https://github.com/ivanseidel/ArduinoThread.
*/

#ifndef Thread_h
#define Thread_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif

#include <inttypes.h>

class Thread {
    private:
        // Desired interval between runs
        unsigned long interval;

        // Last runned time in microsseconds
        unsigned long last_run;

        // Scheduled run in microsseconds (MUST BE CACHED)
        unsigned long _cached_next_run;

        // If the current Thread is enabled or not
        bool enabled;

        // ID of the Thread (initialized from memory adr.)
        int ThreadID;

        // Thread Name (used for better UI).
        String ThreadName;

        /*
            IMPORTANT! Run after all calls to run()
            Updates last_run and cache next run.
            NOTE: This MUST be called if extending
            this class and implementing run() method
        */
        void runned(unsigned long time);

        // Default is to mark it runned "now"
        void runned() { runned(micros()); }

        // Return if the Thread should be runned or not
        virtual bool shouldRun(unsigned long time);

        // Default is to check whether it should run "now"
        bool shouldRun() {
            return shouldRun(micros());
        }

        // Callback for run() if not implemented
        void (*runCallback)(void);

        // Control runs
        void _run();

        // Runs Thread
        virtual void run();

    public:
        Thread(void (*callback)(void) = NULL, unsigned long _interval = 0);

        // Get Thread ID
        int getID();

        // Get if Thread is Enabled
        bool isEnable();

        // Get Thread Name
        String getName();

        // Set the desired interval for calls, and update _cached_next_run
        virtual void setInterval(unsigned long _interval);

        // Set the desired interval for calls, and update _cached_next_run in microsseconds
        virtual void setIntervalMicros(unsigned long _interval);

        // Callback set
        void setRun(void (*callback)(void));

        // Start Thread
        void start();

        // Run Thread
        void start(long time);
};

#endif
