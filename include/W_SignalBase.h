#ifndef WE_SIGNALBASE_H
#define WE_SIGNALBASE_H

#include <list>

#include "W_ConnectionBase.h"
#include "W_MultithreadedLocal.h"
#include "W_Slot.h"

namespace W {

    class __SignalBase: public MultithreadedLocal {
        public:
            virtual void slot_disconnect(Slot *pslot) = 0;
            virtual void slot_duplicate(const Slot *oldtarget, Slot *newtarget) = 0;
    };

    template <typename ...T>
    class SignalBase: public __SignalBase {

        protected:
            std::list< ConnectionBase<T...>* > m_connected_slots;

        public:
            SignalBase() {}

            SignalBase(const SignalBase<T...> &s) {
                LockBlock lock(this);

                typename std::list< ConnectionBase<T...>* >::const_iterator it = s.m_connected_slots.begin();
                typename std::list< ConnectionBase<T...>* >::const_iterator itEnd = s.m_connected_slots.end();

                while(it != itEnd) {
                    (*it)->getdest()->signal_connect(this);
                    m_connected_slots.push_back((*it)->clone());

                    it++;
                }

            }

            ~SignalBase() {
                disconnect_all();
            }

            void disconnect_all() {
                LockBlock lock(this);

                typename std::list< ConnectionBase<T...>* >::const_iterator it = m_connected_slots.begin();
                typename std::list< ConnectionBase<T...>* >::const_iterator itEnd = m_connected_slots.end();

                while(it != itEnd) {
                    (*it)->getdest()->signal_disconnect(this);
                    delete *it;

                    it++;
                }

                m_connected_slots.erase(m_connected_slots.begin(), m_connected_slots.end());
            }

            void disconnect(Slot *pclass) {
                LockBlock lock(this);

                typename std::list< ConnectionBase<T...>* >::const_iterator it = m_connected_slots.begin();
                typename std::list< ConnectionBase<T...>* >::const_iterator itEnd = m_connected_slots.end();

                while(it != itEnd) {
                    if((*it)->getdest() == pclass) {
                        delete *it;
                        m_connected_slots.erase(it);
                        pclass->signal_disconnect(this);
                        return;
                    }

                    it++;
                }
            }

            void slot_disconnect(Slot *pslot) {
                LockBlock lock(this);

                typename std::list< ConnectionBase<T...>* >::iterator it = m_connected_slots.begin();
                typename std::list< ConnectionBase<T...>* >::iterator itEnd = m_connected_slots.end();

                while(it != itEnd) {
                    typename std::list< ConnectionBase<T...>* >::iterator itNext = it;
                    itNext++;

                    if((*it)->getdest() == pslot) {
                        m_connected_slots.erase(it);
                    }

                    it = itNext;
                }
            }

            void slot_duplicate(const Slot* oldtarget, Slot* newtarget) {
                LockBlock lock(this);

                typename std::list< ConnectionBase<T...>* >::const_iterator it = m_connected_slots.begin();
                typename std::list< ConnectionBase<T...>* >::const_iterator itEnd = m_connected_slots.end();
                
                while(it != itEnd) {
                    if((*it)->getdest() == oldtarget) {
                        m_connected_slots.push_back((*it)->duplicate(newtarget));
                    }

                    it++;
                }
            }
    };

} /* W */

#endif /* end of include guard: WE_SIGNALBASE_H */
