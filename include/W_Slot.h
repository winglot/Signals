#ifndef WE_SLOT_H
#define WE_SLOT_H

#include <set>

#include "W_MultithreadedLocal.h"

namespace W {
    class __SignalBase;

    class Slot : public MultithreadedLocal {
        public:
            Slot();
            Slot(const Slot& hs);
            virtual ~Slot();

            void signal_connect(__SignalBase* sender);
            void signal_disconnect(__SignalBase* sender);
            void disconnect_all();

        private:
            std::set< __SignalBase* > m_senders;
    };

}
#endif /* end of include guard: WE_SLOT_H */
