#include <thread>
#include <mutex>
#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <random>
#include <time.h>
#include "HW8DynIntQueue.h"

using namespace std;

HW8DynIntQueue CustomerQueue;
mutex myMutex, coutMutex, mutex2;
int customers, threshold, intarr_min, intarr_max, checkout_min, checkout_max, remcust;
int queuesize= 0;

int random_range(const int & min, const int & max) //random int generator
{
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

void formqueue()	//customer func, forms a queue as customers come
{
	for(int i = 1; i < customers+1; i++)
	{
		int randotime = random_range(intarr_min, intarr_max);

		myMutex.lock();	//lock before modify the critical area
		if (queuesize < customers+1) 
		{  
			CustomerQueue.enqueue(i);
			queuesize++;
			myMutex.unlock();

			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout <<"New customer with ID "<< i << " has arrived (queue size is "<< queuesize << ") : " << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();

			this_thread::sleep_for(chrono::seconds(randotime));
		}
		else
		{
			myMutex.unlock();
			i--;
		}
	}
}

void cashier(int cashierid)	//cashier func, deques the customers
{
	int item;
	int randomtime = random_range(checkout_min, checkout_max);
	this_thread::sleep_for(chrono::seconds(randomtime));

	if(cashierid==1)	//first cashier always works
	{
		mutex2.lock();	//lock before access remaining customer count
		while(remcust>0)
		{	
			myMutex.lock();	//lock before modify critical area
			if (!CustomerQueue.isEmpty())
			{
				CustomerQueue.dequeue(item);
				queuesize--;
				remcust--;
				myMutex.unlock();
				mutex2.unlock();

				coutMutex.lock();
				time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				cout<< "Cashier" << cashierid <<" started transaction with customer "<< item <<" (queue size is  " << queuesize <<")" << put_time(ptm,"%X") <<endl;
				coutMutex.unlock();
				this_thread::sleep_for(chrono::seconds(randomtime)); // simulation for consume

				coutMutex.lock();
				tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				cout<< "Cashier" << cashierid <<" finished transaction with customer "<< item << " " << put_time(ptm,"%X") <<endl;
				coutMutex.unlock();
			}
			else
			{
				myMutex.unlock();
				mutex2.unlock();
			}
			mutex2.lock();
		}
		mutex2.unlock();
	}
	else //cashier 2
	{
		mutex2.lock();
		while(remcust>0)
		{	
			myMutex.lock();
			if (threshold <= CustomerQueue.getCurrentSize() && !CustomerQueue.isEmpty())	//works when customer count is larger than threshold
			{
				CustomerQueue.dequeue(item);
				queuesize--;
				remcust--;
				myMutex.unlock();
				mutex2.unlock();

				coutMutex.lock();
				time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				struct tm *ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				cout<< "Cashier" << cashierid <<" started transaction with customer "<< item <<" (queue size is " << queuesize <<") " << put_time(ptm,"%X") <<endl;
				coutMutex.unlock();

				this_thread::sleep_for(chrono::seconds(randomtime)); // simulation for consume

				coutMutex.lock();
				tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
				ptm = new struct tm; 
				localtime_s(ptm, &tt); 
				cout<< "Cashier" << cashierid <<" finished transaction with customer "<< item << put_time(ptm,"%X") <<endl;
				coutMutex.unlock();
			}
			else
			{
				myMutex.unlock();
				mutex2.unlock();
			}
			mutex2.lock();
		}
		mutex2.unlock();
	}
}


int main()
{
	//keyboard inputs 

	cout << "Please enter the total number of customers: " ;
	cin >> customers;

	cout << "Please enter the number of customers waiting in the queue to open the second cashier: ";
	cin >> threshold;

	cout << "Please enter the inter-arrival time range between two customers: " << "Min: ";
	cin >> intarr_min ;
	cout << "Max: ";
	cin >> intarr_max;

	cout << "Please enter the checkout time range of cashiers: " << "Min: ";
	cin >> checkout_min ;
	cout << "Max: ";
	cin >> checkout_max;

	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt); 
	cout << "Simulation starts" << put_time(ptm,"%X") <<endl; //starting time

	remcust=customers;

	//threads 

	thread thr0(formqueue);
	thread thr1(cashier,1);
	thread thr2(cashier,2);

	thr0.join();
	thr1.join();
	thr2.join();

	time_t tr = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptr = new struct tm; 
	localtime_s(ptr, &tr); 
	cout<< "End of the simulation ends: "<< put_time(ptr,"%X") <<endl; //end time

	return 0;
}