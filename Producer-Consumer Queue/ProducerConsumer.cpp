#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iomanip>
#include"IntQueue.h"

using namespace std;

IntQueue myQueue(10);
mutex myMutex, coutMutex;
int maximum = 30;

void producer()
{
	for(int i = 0; i < 2 * maximum; i++)
	{
		myMutex.lock();
		if (!myQueue.isFull()) 
		{  
			myQueue.enqueue(i);
			myMutex.unlock();

			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout <<"Producer has produced item "<< i << " at "<< put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
		}
		else
		{
			myMutex.unlock();
			i--;
		}
		
	}
}

void consumer(int consId)
{
	int item;
	int counter = 0;
	while(counter < maximum)
	{	
		myMutex.lock();
		if (!myQueue.isEmpty()) 
		{  
			myQueue.dequeue(item);
			counter++;
			myMutex.unlock();

			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<< consId <<" started to consume item "<< item <<" at " << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
			
			this_thread::sleep_for(chrono::milliseconds(10)); // simulation for consume

			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<< consId <<" finished to consume item "<< item <<" at " << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
		}
		else
		{
			myMutex.unlock();
		}
	}
}

int main()
{
	thread thr0(producer);
	thread thr1(consumer, 1);
	thread thr2(consumer, 2);

	thr0.join();
	thr1.join();
	thr2.join();

	system("pause");
	return 0;
}