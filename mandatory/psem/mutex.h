// Pthreads mutexes may not enforce ownership ...

// https://stackoverflow.com/a/5492499

// TODO: Add experiments to find out.

// Implement your own mutex that checks ownership ...

#include "psem.h"

#include <pthread.h> // thread_t, pthread_self()


#define MUTEX_SUCCESS        0
#define MUTEX_ERROR_OWNER   -1
#define MUTEX_ERROR_COUNTER -2

typedef struct {
  psem_t *block;
  psem_t *mtx;
  int counter;
  pthread_t owner;
} mutex_t;


const char* mutex_error_to_string(int error);

mutex_t *mutex_new();
void     mutex_free(mutex_t *mutex);
int      mutex_lock(mutex_t *mutex);
int      mutex_unlock(mutex_t *mutex);
