#ifndef BASE_SINGLETON_H
#define BASE_SINGLETON_H

#include <new>

template <typename Type> class Singleton {
private:
    friend Type* Type::getInstance();

    static Type* get()
    {
        if (!_instance)
        {
            _instance = new Type();
        }

        return _instance;
    }

    static Type* _instance;
};

template <typename Type> Type* Singleton<Type>::_instance = nullptr;

#endif