#ifndef W_CONNECTION_H
#define W_CONNECTION_H

#include "W_ConnectionBase.h"
#include "W_Slot.h"

namespace W {
    template <typename DestType, typename ...T>
    class Connection: public ConnectionBase<T...> {
        public:
            Connection() {
                m_object = nullptr;
                m_memfun = nullptr;
            }

            Connection(DestType* object, void (DestType::*memfun)(T ...t)) {
                m_object = object;
                m_memfun = memfun;
            }

            virtual ConnectionBase<T...>* clone() {
                return new Connection<DestType, T...> (*this);
            }

            virtual ConnectionBase<T...>* duplicate(Slot *pnewdest) {
                return new Connection<DestType, T...>((DestType*)pnewdest, m_memfun);
            }

            virtual void emit(T ...t) {
                (m_object->*m_memfun)(t...);
            }

            virtual Slot* getdest() const {
                return m_object;
            }

        private:
            DestType* m_object;
            void (DestType::*m_memfun)(T ...t);
    };
} /* W */

#endif /* end of include guard: W_CONNECTION_H */
