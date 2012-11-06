#ifndef E_SLOT_H
#define E_SLOT_H

#include <set>

#include "W_MultithreadedLocal.h"

namespace W {
    class __SignalBase;

    class Slot : public MultithreadedLocal {
        public:
            inline Slot();
            inline Slot(const Slot& hs);
            virtual inline ~Slot();

            inline void signal_connect(__SignalBase* sender);
            inline void signal_disconnect(__SignalBase* sender);
            inline void disconnect_all();

        private:
            std::set< __SignalBase* > m_senders;
    };
}

/*
 * Implementation
 * Solves circular dependency problems without separate .cpp file
 */
#include "W_Slot.h"
#include "W_SignalBase.h"

namespace W {

    Slot::Slot() {}

    Slot::Slot(const Slot& hs): MultithreadedLocal(hs) {
        LockBlock lock(this);

        for(auto &sender: hs.m_senders) {
            sender->slot_duplicate(&hs, this);
            m_senders.insert(sender);
        }
    } 

    Slot::~Slot() {
        disconnect_all();
    }

    void Slot::signal_connect(__SignalBase* sender) {
        LockBlock lock(this);
        m_senders.insert(sender);
    }

    void Slot::signal_disconnect(__SignalBase* sender) {
        LockBlock lock(this);
        m_senders.erase(sender);
    }


    void Slot::disconnect_all() {
        LockBlock lock(this);

        for(auto &sender: m_senders) {
            sender->slot_disconnect(this);
        }

        m_senders.erase(m_senders.begin(), m_senders.end());
    }

} /* W */

#endif /* end of include guard: E_SLOT_H */
