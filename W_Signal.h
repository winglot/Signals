#ifndef W_SIGNAL_H
#define W_SIGNAL_H

#include <list>

#include "W_SignalBase.h"
#include "W_Connection.h"

namespace W {

    template <typename ...T>
    class Signal: public SignalBase<T...> {
        public:
            Signal() {}

            Signal(const Signal<T...> &s): SignalBase<T...>(s) {}

            virtual ~Signal() {}

            void connect(void (*memfun)(T...)) {
                LockBlock lock(this);

                ConnectionFunction<T...>* conn = new ConnectionFunction<T...>(memfun);

                SignalBase<T...>::m_connected_slots.push_back(conn);
            }

            template <typename DestType>
            void connect(DestType* pclass, void (DestType::*memfun)(T...)) {
                LockBlock lock(this);

                Connection<DestType, T...>* conn = new Connection<DestType, T...>(pclass, memfun);
                SignalBase<T...>::m_connected_slots.push_back(conn);

                pclass->signal_connect(this);
            }

            void emit(T ...t) {
                LockBlock lock(this);

                for(auto &connection: SignalBase<T...>::m_connected_slots) {
                    connection->emit(t...);
                }
            }
    };

} /* W */

#endif /* end of include guard: W_SIGNAL_H */
