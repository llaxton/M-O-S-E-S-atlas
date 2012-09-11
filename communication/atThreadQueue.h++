
#ifndef AT_THREAD_QUEUE_H
#define AT_THREAD_QUEUE_H


// INCLUDES
#include <sys/types.h>
#include "atItem.h++"
#include "atOSDefs.h++"


class ATLAS_SYM atThreadQueue : public atItem
{
   protected:
      SemKey     sem_key;
      SemID      sem_id;

      u_long     memory_increment_size;

      u_char *   queue_buffer;

      u_long     queue_head;
      u_long     queue_tail;
      u_long     queue_size;
      u_long     queue_used;

      bool     lock();
      bool     unlock();
      u_long   spaceAvailable();
      void     reallocateQueue(u_long minimumToAdd);


   public:
      atThreadQueue(SemKey key, u_long initialSize, u_long incrementSize);
      virtual ~atThreadQueue();

      virtual void   enqueue(u_char * buffer, u_long bufferLen);
      virtual bool   dequeue(u_char * buffer, u_long * bufferLen);
};


#endif

