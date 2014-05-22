#ifndef RF_SINGLETON_HPP
#define RF_SINGLETON_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework {
/**
    * \brief Template based singleton pattern.
    * This singleton implementation will clean up it's self at program exit.
    * use: class MyClass:public Singleton<MyClass>{}; or
    *      Singleton<MyClass>::GetInstance().foo();
    */
template <class T>
class Singleton
{
    public:
        static T& GetInstance();
        static T* Instance();
        /** \brief Manually destroy an existing instance.
            * This function can be very dangerous in combination with
            * multi threaded usage or access the pointer/reference after
            * calling it.
            */
        static void DestroyInstance();
    protected:
        Singleton(){}
        virtual ~Singleton(){}
        static T* m_Instance;
    private:
        class WatchDog
        {
            public:
                ~WatchDog();
        };
        friend class WatchDog;
            
        Singleton(const Singleton&);
        Singleton& operator=( const Singleton& );
};

template<class T>
T* Singleton<T>::m_Instance = 0;

template<class T>
Singleton<T>::WatchDog::~WatchDog()
{
    if(Singleton<T>::m_Instance != 0)
    {
        delete Singleton<T>::m_Instance;
        Singleton<T>::m_Instance = 0;
    }
}

template<class T>
T& Singleton<T>::GetInstance()
{
    return *Instance();
}

template<class T>
T* Singleton<T>::Instance()
{
    static WatchDog wd;
    // If the singleton wasn't created yet then do it.
    if(m_Instance == 0)
        m_Instance = new T();
    return m_Instance;
}

template<class T>
void Singleton<T>::DestroyInstance()
{
    if(m_Instance != 0)
    {
        delete m_Instance;
        m_Instance = 0;
    }
}

}

#endif // RF_SINGLETON_HPP
