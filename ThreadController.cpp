#include "Thread.h"
#include "ThreadController.h"

ThreadController::ThreadController(){
	cached_size = 0;
	clear();
}

/*
	ThreadController run() (cool stuf)
*/
void ThreadController::loop(){
	unsigned long time = micros();
	int checks = 0;
	for(int i = 0; i < MAX_THREADS && checks <= cached_size; i++){
		// Object exists? Is enabled? Timeout exceeded?
		if(thread[i]){
			checks++;
			thread[i]->start(time);
		}
	}
}


/*
	List controller (boring part)
*/
bool ThreadController::add(Thread* _thread){
	// Check if the Thread already exists on the array
	for(int i = 0; i < MAX_THREADS; i++){
		if(thread[i] != NULL && thread[i]->ThreadID == _thread->ThreadID)
			return true;
	}

	// Find an empty slot
	for(int i = 0; i < MAX_THREADS; i++){
		if(!thread[i]){
			// Found a empty slot, now add Thread
			thread[i] = _thread;
			cached_size++;
			return true;
		}
	}

	// Array is full
	return false;
}

void ThreadController::remove(int id){
	// Find Threads with the id, and removes
	for(int i = 0; i < MAX_THREADS; i++){
		if(thread[i]->ThreadID == id){
			thread[i] = NULL;
			cached_size--;
			return;
		}
	}
}

void ThreadController::remove(Thread* _thread){
	remove(_thread->ThreadID);
}

void ThreadController::clear(){
	for(int i = 0; i < MAX_THREADS; i++){
		thread[i] = NULL;
	}
	cached_size = 0;
}

int ThreadController::size(bool cached){
	if(cached)
		return cached_size;

	int size = 0;
	for(int i = 0; i < MAX_THREADS; i++){
		if(thread[i])
			size++;
	}
	cached_size = size;

	return cached_size;
}

Thread* ThreadController::get(int index){
	int pos = -1;
	for(int i = 0; i < MAX_THREADS; i++){
		if(thread[i] != NULL){
			pos++;

			if(pos == index)
				return thread[i];
		}
	}

	return NULL;
}
