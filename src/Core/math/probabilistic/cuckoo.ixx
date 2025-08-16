module;
#include <concepts>
export module rf.core.math.probabilistic:cuckoo;
import rf.core.types;

export namespace rf {
template<class T>
concept CuckooFilterType = requires{
	std::_Is_any_of_v<u32,u64>;
};

    template<CuckooFilterType T>
    struct Cuckoo {
        mem pool;
        u64 capacity;
        T* entries[2];

        void init(mem Arena) {
            this->pool = Arena;
            this->capacity = (this->pool.bytes>>1)/sizeof(CuckooFilterType);
            this->entries[0] = reinterpret_cast<T*>(this->pool.address);
            this->entries[1] = reinterpret_cast<T*>(this->pool.address)+this->capacity;
        }

        [[nodiscard]] bool populate(T Key){
            auto h1 = Key % this->capacity;
            auto h2 = (Key / this->capacity)%this->capacity;
            if (this->entries[0][h1] != 0){

            }
        }
    private:
        //bool place(T Key, )
    };
}