#include "Thread.h"

Thread::Thread(void (*callback)(void), unsigned long _interval){
	enabled = false;
	setRun(callback);
	_cached_next_run = 0;
	last_run = micros();

	ThreadID = (int)this;
    ThreadName = "Thread ";
    ThreadName = ThreadName + ThreadID;

	setInterval(_interval);
};

bool Thread::isEnable(){
	return enabled;
}

String Thread::getName(){
	return ThreadName;
}

int Thread::getID(){
	return ThreadID;
}

void Thread::runned(unsigned long time){
	// Saves last_run
	last_run = time;

	// Cache next run
	_cached_next_run = last_run + interval;
}

void Thread::setInterval(unsigned long _interval){
	// Save interval
	interval = _interval * 1000;

	// Cache the next run based on the last_run
	_cached_next_run = last_run + interval;
}

void Thread::setIntervalMicros(unsigned long _interval){
	// Save interval
	interval = _interval;

	// Cache the next run based on the last_run
	_cached_next_run = last_run + interval;
}

bool Thread::shouldRun(unsigned long time){
	// If the "sign" bit is set the signed difference would be negative
	bool time_remaining = (time - _cached_next_run) & 0x80000000;

	// Exceeded the time limit, AND is enabled? Then should run...
	return !time_remaining && enabled;
}

void Thread::setRun(void (*callback)(void)){
	runCallback = callback;
}

void Thread::start(){
    // Enable the Thread
	if(!isEnable())
    	enabled = true;
}

void Thread::start(long time){
	if(shouldRun(time))
		_run();
}

void Thread::_run(){
	if(runCallback != NULL)
		runCallback();
    else
        run();

	// Update last_run and _cached_next_run
	runned();
}

void Thread::run(){
    return;
}