#include "mutex.h"
#include <stdlib.h> // malloc()
#include <stdio.h>  // fprintf()
#include <stddef.h> // NULL

const char* mutex_error_to_string(int error) {
  switch (error) {
  case MUTEX_SUCCESS:       return "SUCCESS";
  case MUTEX_ERROR_OWNER:   return "OWNER";
  case MUTEX_ERROR_COUNTER: return "COUNTER";
  default:                  return "UNDEFINED";
  }
}

mutex_t *mutex_new(){

  mutex_t *m = malloc(sizeof(mutex_t));

  // Cannot trust (?) sem_getvalue().
  // https://stackoverflow.com/questions/16655153/sem-getvalue-dysfunctionality-in-mac-os-x-c

  m->block   = psem_init(1);
  m->mtx     = psem_init(1);
  m->counter = 1;

  return m;
}

void mutex_destroy(mutex_t *mutex) {
  psem_destroy(mutex->block);
  psem_destroy(mutex->mtx);
  free(mutex);
}

int mutex_lock(mutex_t *mutex) {
  psem_wait(mutex->block);
  psem_wait(mutex->mtx);

  if (mutex->counter != 1) {
    return MUTEX_ERROR_COUNTER;
  }

  mutex->counter = 0;
  mutex->owner = pthread_self();

  psem_signal(mutex->mtx);
  return MUTEX_SUCCESS;
}

int mutex_unlock(mutex_t *mutex) {

  if (!pthread_equal(pthread_self(), mutex->owner)) {
    return MUTEX_ERROR_OWNER;
  }

  psem_wait(mutex->mtx);

  if (mutex->counter != 0) {
    return MUTEX_ERROR_COUNTER;
  }

  psem_signal(mutex->block);
  mutex->counter = mutex->counter + 1;
  psem_signal(mutex->mtx);

  return MUTEX_SUCCESS;
}
