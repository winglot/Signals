/**
 * The file is needed to avoid circular dependencies with SignalBase
 */

#include "W_Slot.h"
#include "W_SignalBase.h"

namespace W {

    Slot::Slot() {}

    Slot::Slot(const Slot& hs): MultithreadedLocal(hs) {
        LockBlock lock(this);
        std::set< __SignalBase* >::const_iterator it = hs.m_senders.begin();
        std::set< __SignalBase* >::const_iterator itEnd = hs.m_senders.end();

        while(it != itEnd) {
            (*it)->slot_duplicate(&hs, this);
            m_senders.insert(*it);
            ++it;
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
        std::set< __SignalBase* >::const_iterator it = m_senders.begin();
        std::set< __SignalBase* >::const_iterator itEnd = m_senders.end();

        while(it != itEnd) {
            (*it)->slot_disconnect(this);
            ++it;
        }

        m_senders.erase(m_senders.begin(), m_senders.end());
    }

} /* W */
