#ifdef _STDC_NO_THREADS_
    #error I need threads to build this program!
#endif
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> //sleep()

#define SINGLE_THREAD
//#define FIVE_THREAD_RACED
//#define FIVE_THREAD_NORACE
//#define THREAD_DETACH
//#define STATICVAR_RACE
//#define TSS
//#define NOMUTEX
//#define MUTEX
//#define CONDITION_VAR

#ifdef SINGLE_THREAD

// This is the function the thread will run. It can be called anything.
// arg is the argument pointer passed to `pthread_create()`.
// The parent thread will get the return value back from `pthread_join()`'
// later.
void* run(void *arg)
{
	int *a = arg; // We'll pass in an int* from pthread_create()
	printf("THREAD: Running thread with arg %d\n", *a);
	return (void *) 12; // Value to be picked up by pthread_join() (chose 12 at random). typecast to avoid warning.
}

int main(void)
{
	pthread_t t; // t will hold the thread ID
	int arg = 3490;
	printf("Launching a thread\n");
	// Launch a thread to the run() function, passing a pointer to 3490
	// as an argument. Also stored the thread ID in t:
	pthread_create(&t, NULL, run, &arg);
	printf("Doing other things while the thread runs\n");
	printf("Waiting for thread to complete...\n");
	int res; // Holds return value from the thread exit
	// Wait here for the thread to complete; store the return value
	// in res:
	pthread_join(t, ((void *)&res)); //typecast to avoid warnings
	printf("Thread exited with return value %d\n", res);
}
#endif

#ifdef FIVE_THREAD_RACED
// Use an array of pthread_t s

int run(void *arg)
{
	int i = *(int*)arg;
	printf("THREAD %d: running!\n", i);
	return i;
}

#define THREAD_COUNT 5

int main(void)
{
	pthread_t t[THREAD_COUNT];
	int i;
	printf("Launching threads...\n");
	for (i = 0; i < THREAD_COUNT; i++)
	// NOTE! In the following line, we pass a pointer to i,
	// but each thread sees the same pointer. So they'll
	// print out weird things as i changes value here in
	// the main thread! (More in the text, below.)
		pthread_create(t + i, NULL, run, &i); //race conditions
	printf("Doing other things while the thread runs...\n");
	printf("Waiting for thread to complete...\n");
	for (int i = 0; i < THREAD_COUNT; i++) {
		int res;
		pthread_join(t[i], &res); //race condition
		printf("Thread %d complete!\n", res);
	}
	printf("All threads complete!\n");
}
#endif

#ifdef FIVE_THREAD_NORACE
// Use an array of pthread_t s

int run(void *arg)
{
	int i = *(int*)arg;
	int newVar=1;
	printf("THREAD %d: running! with local var at %d\n", i,&newVar);//new location for all local vars
	return i;
}

#define THREAD_COUNT 5

int main(void)
{
	pthread_t t[THREAD_COUNT];
	int a[THREAD_COUNT];
	int i;
	printf("Launching threads...\n");
	for (i = 0; i < THREAD_COUNT; i++) {
		a[i]=i;
		pthread_create(t + i, NULL, run, &a[i]); //race conditions avoided
		/*
		Another method: use malloc:
			int *arg = malloc(sizeof *arg);
			*arg = i;
			thrd_create(t + i, run, arg);
		*/
	}
	printf("Doing other things while the thread runs...\n");
	printf("Waiting for thread to complete...\n");
	int res[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++) {
		pthread_join(t[i], &res[i]); //race condition avoided
		printf("Thread %d complete!\n", res[i]);
	}
	printf("All threads complete!\n");
}
#endif


#ifdef THREAD_DETACH
int run(void *arg) {
	(void)arg;
	printf("Thread running! %lu\n", *pthread_self()); // non-portable!
	//printf("Thread running!\n");
	return 0;
}

#define THREAD_COUNT 10

int main(void)
{
	pthread_t t;
	for (int i = 0; i < THREAD_COUNT; i++) {
		pthread_create(&t,NULL, run, NULL);
		pthread_detach(t); // <-- DETACH!
	}
	// Sleep for a second to let all the threads finish
	//thrd_sleep(&(struct timespec){.tv_sec=1}, NULL); -> not working
	sleep(1);
}
#endif

#ifdef STATICVAR_RACE

int run(void *arg)
{
	int n = *(int*)arg; // Thread number for humans to differentiate
	free(arg);

	static int foo = 10; // Static value shared between threads
	//thread_local static int foo = 10; // <-- No longer shared!! Not valid with pthread



	int x = foo; // Automatic local variable--each thread has its own
	// We just assigned x from foo, so they'd better be equal here.
	// (In all my test runs, they were, but even this isn't guaranteed!)
	printf("Thread %d: x = %d, foo = %d\n", n, x, foo);
	// And they should be equal here, but they're not always!
	// (Sometimes they were, sometimes they weren't!)
	// What happens is another thread gets in and increments foo
	// right now, but this thread's x remains what it was before!
	if (x != foo) {
		printf("Thread %d: Craziness! x != foo! %d != %d\n", n, x, foo);
	}
	foo++; // Increment shared value
	return 0;
}

#define THREAD_COUNT 5

int main(void)
{
	pthread_t t[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++) {
		int *n = malloc(sizeof *n); // Holds a thread serial number
		*n = i;
		pthread_create(t + i,NULL, run, n);
	}
	for (int i = 0; i < THREAD_COUNT; i++) {
		pthread_join(t[i], NULL);
	}
}
#endif

#ifdef TSS

pthread_key_t theKey; //global //tss_t str;
void some_function(void)
{
	// Retrieve the per-thread value of this string
	char *tss_string;
	tss_string=pthread_getspecific(theKey);
	// And print it
	printf("TSS string: %s\n", tss_string);
}

int run(void *arg)
{
	int serial = *(int*)arg; // Get this thread's serial number
	free(arg);
	// malloc() space to hold the data for this thread
	char *s = malloc(64);
	sprintf(s, "thread %d! :)", serial); // Happy little string
	// Set this TSS variable to point at the string
	pthread_setspecific(theKey,s);//tss_set(str, s);
	// Call a function that will get the variable
	some_function();
	return 0; // Equivalent to thrd_exit(0)
}

#define THREAD_COUNT 15

int main(void)
{
	pthread_t t[THREAD_COUNT];
	// Make a new TSS variable, the free() function is the destructor
	pthread_key_create(&theKey,free); //tss_create(&str, free);
	
	for (int i = 0; i < THREAD_COUNT; i++) {
		int *n = malloc(sizeof *n); // Holds a thread serial number
		*n = i;
		pthread_create(t + i,NULL, run, n);
	}
	
	for (int i = 0; i < THREAD_COUNT; i++) {
		pthread_join(t[i], NULL);
	}
	
	// All threads are done, so we're done with this
	pthread_key_delete(theKey) ; //tss_delete(str);
}
#endif

#ifdef NOMUTEX

int run(void *arg)
{
	(void)arg;
	//Race condition start
	static int serial = 0; // Shared static variable!
	printf("Thread running! %d\n", serial);
	serial++;
	//Race condition end
	return 0;
}
#define THREAD_COUNT 10
int main(void)
{
	pthread_t t[THREAD_COUNT];
	
	for (int i = 0; i < THREAD_COUNT; i++) {
		pthread_create(t + i,NULL, run, NULL);
	}
	
	for (int i = 0; i < THREAD_COUNT; i++) {
		pthread_join(t[i], NULL);
	}
}
#endif

#ifdef MUTEX

pthread_mutex_t serial_mtx; // <-- MUTEX VARIABLE

int run(void *arg)
{
	(void)arg;
	static int serial = 0; // Shared static variable!
	// Acquire the mutex--all threads will block on this call until
	// they get the lock:
	pthread_mutex_lock(&serial_mtx); // <-- ACQUIRE MUTEX
	printf("Thread running! %d\n", serial);
	serial++;
	// Done getting and setting the data, so free the lock. This will
	// unblock threads on the mtx_lock() call:
	pthread_mutex_unlock(&serial_mtx); // <-- RELEASE MUTEX
	return 0;
}

#define THREAD_COUNT 10

int main(void)
{
	pthread_t t[THREAD_COUNT];
	// Initialize the mutex variable, indicating this is a normal
	// no-frills, mutex:
	pthread_mutex_init(&serial_mtx,NULL); // <-- CREATE MUTEX
	for (int i = 0; i < THREAD_COUNT; i++) {
		pthread_create(t + i, NULL, run, NULL);
	}
	for (int i = 0; i < THREAD_COUNT; i++) {
		pthread_join(t[i], NULL);
	}
	// Done with the mutex, destroy it:
	pthread_mutex_destroy(&serial_mtx); // <-- DESTROY MUTEX
}
#endif

#ifdef CONDITION_VAR
/*
Let’s write a contrived program that reads in groups of 5 numbers from the main thread one at a time.
The numbers will be stored in a global, shared array, as will the index into the array of the about-to-beentered
number.

Then, when 5 numbers have been entered, the child thread wakes up, sums up those 5 numbers, and prints
the result.

Let’s look at the outline of what the child thread will do:
1. Lock the mutex with mtx_lock()
2. If we haven’t entered all the numbers, wait on the condition variable with cnd_wait()
3. Do the work that needs doing
4. Unlock the mutex with mtx_unlock()

Meanwhile the main thread will be doing this:
1. Lock the mutex with mtx_lock()
2. Store the recently-read number into the array
3. If the array is full, signal the child to wake up with cnd_signal()
4. Unlock the mutex with mtx_unlock()

*/

#define VALUE_COUNT_MAX 5

int value[VALUE_COUNT_MAX]; // Shared global
int value_count = 0; // Shared global, too

pthread_mutex_t value_mtx; // Mutex around value
pthread_cond_t value_cnd; // Condition variable on value

int run(void *arg)
{
	(void)arg;
	for (;;) {
		pthread_mutex_lock(&value_mtx); // <-- GRAB THE MUTEX
		while (value_count < VALUE_COUNT_MAX) { //always put in while loop instead of if block
			printf("Thread: is waiting\n");
			pthread_cond_wait(&value_cnd, &value_mtx); // <-- CONDITION WAIT
		}
		printf("Thread: is awake!\n");
		int t = 0;
		// Add everything up
		for (int i = 0; i < VALUE_COUNT_MAX; i++)
			t += value[i];
		
		printf("Thread: total is %d\n", t);
		// Reset input index for main thread
		value_count = 0;
		pthread_mutex_unlock(&value_mtx); // <-- MUTEX UNLOCK
	}
	return 0;
}

int main(void)
{
	pthread_t t;
	// Spawn a new thread
	pthread_create(&t, NULL, run, NULL);
	pthread_detach(t);
	// Set up the mutex and condition variable
	pthread_mutex_init(&value_mtx,NULL);
	pthread_cond_init(&value_cnd,NULL);
	for (;;) {
		int n;
		scanf("%d", &n);
		pthread_mutex_lock(&value_mtx); // <-- LOCK MUTEX
		value[value_count++] = n;
		
		if (value_count == VALUE_COUNT_MAX) {
			printf("Main: signaling thread\n");
			pthread_cond_signal(&value_cnd); // <-- SIGNAL CONDITION
		}
		
		pthread_mutex_unlock(&value_mtx); // <-- UNLOCK MUTEX
	}
	
	// Clean up (I know that's an infinite loop above here, but I
	// want to at least pretend to be proper):
	
	pthread_mutex_destroy(&value_mtx);
	pthread_cond_destroy(&value_cnd);
}
#endif