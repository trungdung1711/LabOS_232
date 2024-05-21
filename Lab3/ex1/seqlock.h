#ifndef PTHREAD_H
#include <pthread.h>
#endif

typedef struct pthread_seqlock 
{
   size_t seq;
   pthread_mutex_t m;
} pthread_seqlock_t;

static inline void pthread_seqlock_init(pthread_seqlock_t *rw)
{
   rw->seq = 0;
   pthread_mutex_init(&rw->m,NULL);
}

static inline void pthread_seqlock_wrlock(pthread_seqlock_t *rw)
{
   pthread_mutex_lock(&rw->m);
   rw->seq++;
}

static inline void pthread_seqlock_wrunlock(pthread_seqlock_t *rw)
{
   rw->seq++;
   pthread_mutex_unlock(&rw->m);
}

static inline unsigned pthread_seqlock_rdlock(pthread_seqlock_t *rw)
{
   while (rw->seq % 2 != 0);
   return rw->seq;
}


static inline unsigned pthread_seqlock_rdunlock(pthread_seqlock_t *rw, size_t seq)
{
   if (seq != rw->seq)
      return - 1;
   return 0;
}

