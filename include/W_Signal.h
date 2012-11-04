#ifndef WE_SIGNAL_H
#define WE_SIGNAL_H

#include <list>

#include "W_SignalBase.h"
#include "W_Connection.h"

namespace W {

    template <typename ...T>
    class Signal: public SignalBase<T...> {
        public:
            Signal() {}

            Signal(const Signal<T...> &s): SignalBase<T...>(s) {}

            template <typename DestType>
            void connect(DestType* pclass, void (DestType::*memfun)(T...)) {
                LockBlock lock(this);

                Connection<DestType, T...>* conn = new Connection<DestType, T...>(pclass, memfun);
                SignalBase<T...>::m_connected_slots.push_back(conn);

                pclass->signal_connect(this);
            }

            void emit(T ...t) {
                LockBlock lock(this);

                typename std::list< ConnectionBase<T...>* >::const_iterator itNext;

                typename std::list< ConnectionBase<T...>* >::const_iterator it = SignalBase<T...>::m_connected_slots.begin();
                typename std::list< ConnectionBase<T...>* >::const_iterator itEnd = SignalBase<T...>::m_connected_slots.end();

                while(it != itEnd) {
                    itNext = it;
                    itNext++;

                    (*it)->emit(t...);

                    it = itNext;
                }
            }
    };

} /* W */

#endif /* end of include guard: WE_SIGNAL_H */
