#ifndef W_CONNECTIONBASE_H
#define W_CONNECTIONBASE_H

namespace W {
    class Slot;

    template <typename  ...T>
    class ConnectionBase {
        public:
            virtual Slot* getdest() const = 0;
            virtual void emit(T ...t) = 0;
            virtual ConnectionBase* clone() = 0;
            virtual ConnectionBase* duplicate(Slot* pnewdest) = 0;
    };
}

#endif /* end of include guard: W_CONNECTIONBASE_H */
