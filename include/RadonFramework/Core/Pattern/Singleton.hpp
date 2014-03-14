#ifndef RF_SINGLETON_HPP
#define RF_SINGLETON_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework
{
    // template based
    // use: class MyClass:public Singleton<MyClass>{}; or
    //      Singleton<MyClass>::GetInstance().foo();

    template <class T>
    class Singleton
    {
        public:
            static T& GetInstance();
            static T* Instance();
            static void DestroyInstance();//very dangerous if you use it wrong
        private:
            class WatchDog
            {
                public:
                    ~WatchDog();
            };
            friend class WatchDog;
            
            Singleton(const Singleton&);
            Singleton& operator=( const Singleton& );
        protected:
            Singleton(){}
            virtual ~Singleton(){}
            static T* m_Instance;
    };
}

template<class T> 
T* RadonFramework::Singleton<T>::m_Instance=0;

template<class T> 
RadonFramework::Singleton<T>::WatchDog::~WatchDog()
{
    if (Singleton<T>::m_Instance!=0)
        delete Singleton<T>::m_Instance;
}

template<class T> 
T& RadonFramework::Singleton<T>::GetInstance()
{
    return *Instance();
}

template<class T> 
T* RadonFramework::Singleton<T>::Instance()
{
    static WatchDog wd;
    if (m_Instance==0)
        m_Instance=new T();
    return m_Instance;
}

template<class T> 
void RadonFramework::Singleton<T>::DestroyInstance()
{
    if (m_Instance!=0)
    {
        delete m_Instance;
        m_Instance=0;
    }
}

#endif // RF_SINGLETON_HPP
