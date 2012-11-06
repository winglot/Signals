#ifndef W_MULTITHREADEDLOCAL_H
#define W_MULTITHREADEDLOCAL_H

#ifdef _WIN32_

#include <windows.h>
namespace W {
    class MultithreadedLocal {
        public:
            MultithreadedLocal() {
                InitializeCriticalSection(&m_critsec);
            }

            MultithreadedLocal(const MultithreadedLocal&) {
                InitializeCriticalSection(&m_critsec);
            }

            virtual ~MultithreadedLocal() {
                DeleteCriticalSection(&m_critsec);
            }

            virtual void lock() {
                EnterCriticalSection(&m_critsec);
            }

            virtual void unlock() {
                LeaveCriticalSection(&m_critsec);
            }

        private:
            CRITICAL_SECTION m_critsec;
    };
}

#else

#include <pthread.h>
namespace W {
    class MultithreadedLocal {
        public:
            MultithreadedLocal() {
                pthread_mutex_init(&m_mutex, 0);
            }

            MultithreadedLocal(const MultithreadedLocal&) {
                pthread_mutex_init(&m_mutex, 0);
            }

            virtual ~MultithreadedLocal() {
                pthread_mutex_destroy(&m_mutex);
            }

            virtual void lock() {
                pthread_mutex_lock(&m_mutex);
            }

            virtual void unlock() {
                pthread_mutex_unlock(&m_mutex);
            }

        private:
            pthread_mutex_t m_mutex;
    };
} /* W */

#endif

namespace W {
    class LockBlock {
        public:
            MultithreadedLocal *m_mutex;

            LockBlock(MultithreadedLocal *mtx):
                m_mutex(mtx) {
                    m_mutex->lock();
                }

            ~LockBlock() {
                m_mutex->unlock();
            }
    };
}

#endif /* end of include guard: W_MULTITHREADEDLOCAL_H */
