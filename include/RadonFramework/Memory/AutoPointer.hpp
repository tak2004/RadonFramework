#ifndef RF_MEMORY_AUTOPOINTER_HPP
#define RF_MEMORY_AUTOPOINTER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Memory
    {
        template <typename T>
        struct AutoPointerReference
        {
            T* m_AutoPointer;
            explicit AutoPointerReference(T *Ptr):m_AutoPointer(Ptr){}
        };

        template <typename T>
        class AutoPointer
        {
            public:
                typedef T ElementType;

                // Constructor
                explicit AutoPointer(ElementType* Ptr=0);
                AutoPointer(AutoPointer& Copy);
                template <typename T1>
                AutoPointer(AutoPointer<T1>& Ref);
                AutoPointer(AutoPointerReference<ElementType> Ref);
                
                // Destructor
                ~AutoPointer();
                
                // Methods
                /// Return the pointer which will be hold by this object.
                ElementType* Get()const;
                /// Return the pointer and set it to 0.
                ElementType* Release();
                /// Replace the pointer by a new one.
                void Reset(ElementType* NewPtr=0);
                
                // Operator overloading
                /// Return the const reference of the pointer.
                const ElementType& operator*()const;
                /// Return the reference of the pointer.
                ElementType& operator*();
                /// Access a const marked member of the pointer.
                const ElementType* operator->()const;
                /// Access a member of the pointer.
                ElementType* operator->();
                /// Release the pointer of Copy and replace it by the one in this object.
                AutoPointer& operator=(const AutoPointer& Copy);
                /// Release the pointer of Copy and replace it by the one in this object.
                template <typename T1>
                AutoPointer& operator=(AutoPointer<T1>& Copy);
                /// Reset the pointer by the pointer holding by Ref object.
                AutoPointer& operator=(AutoPointerReference<ElementType> Ref);
                /// Release the pointer to AutoPointerReference.
                template <typename T1>
                operator AutoPointerReference<T1>();                
                /// Convert to an AutoPointer with an other type.
                template <typename T1>
                operator AutoPointer<T1>();                
                /// Return true if the pointer is 0 else false.
                RFTYPE::Bool operator!();
                /// Convert to Bool to allow boolean operation.
                operator RFTYPE::Bool();
            private:
                mutable T* m_Data;
        };

        template <typename T>
        AutoPointer<T>::AutoPointer(ElementType* Ptr)
        :m_Data(Ptr)
        {
        }

        template <typename T>
        AutoPointer<T>::AutoPointer(AutoPointer& Copy)
        :m_Data(Copy.Release())
        {
        }

        template <typename T>
        template <typename T1>
        AutoPointer<T>::AutoPointer(AutoPointer<T1>& Ref)
        :m_Data(Ref.Release())
        {
        }

        template <typename T>
        AutoPointer<T>::AutoPointer(AutoPointerReference<ElementType> Ref)
        :m_Data(Ref.m_AutoPointer)
        {
        }

        template <typename T>
        AutoPointer<T>::~AutoPointer()
        {
            delete m_Data;
        }

        template <typename T>
        typename AutoPointer<T>::ElementType* AutoPointer<T>::Get()const
        {
            return m_Data;
        }

        template <typename T>
        const typename AutoPointer<T>::ElementType& AutoPointer<T>::operator*()const
        {
            return *m_Data;
        }

        template <typename T>
        typename AutoPointer<T>::ElementType& AutoPointer<T>::operator*()
        {
            return *m_Data;
        }

        template <typename T>
        const typename AutoPointer<T>::ElementType* AutoPointer<T>::operator->()const
        {
            return m_Data;
        }

        template <typename T>
        typename AutoPointer<T>::ElementType* AutoPointer<T>::operator->()
        {
            return m_Data;
        }

        template <typename T>
        AutoPointer<T>& AutoPointer<T>::operator=(const AutoPointer<T>& Copy)
        {
            Reset(Copy.m_Data);
            Copy.m_Data=0;
            return *this;
        }

        template <typename T>
        template <typename T1>
        AutoPointer<T>& AutoPointer<T>::operator=(AutoPointer<T1>& Copy)
        {
            Reset(Copy.Release());
            return *this;
        }

        template <typename T>
        AutoPointer<T>& AutoPointer<T>::operator=(AutoPointerReference<ElementType> Ref)
        {
            if (Ref.m_AutoPointer!=this->Get())
            {
                delete m_Data;
                m_Data=Ref.m_AutoPointer;
            }
            return *this;
        }

        template <typename T>
        typename AutoPointer<T>::ElementType* AutoPointer<T>::Release()
        {
            ElementType* p(m_Data);
            m_Data=0;
            return p;
        }

        template <typename T>
        void AutoPointer<T>::Reset(ElementType* NewPtr)
        {
            if (m_Data)
                delete m_Data;
            m_Data=NewPtr;
        }

        template <typename T>
        template <typename T1>
        AutoPointer<T>::operator AutoPointerReference<T1>()
        {
            return AutoPointerReference<T1>(this->Release());
        }

        template <typename T>
        template <typename T1>
        AutoPointer<T>::operator AutoPointer<T1>()
        {
            return AutoPointer<T1>(this->Release());
        }

        template <typename T>
        RFTYPE::Bool AutoPointer<T>::operator!()
        {
            return 0==m_Data;
        }

        template <typename T>
        AutoPointer<T>::operator RFTYPE::Bool()
        {
            return 0!=m_Data;
        }
    }
}

#endif // RF_MEMORY_AUTOPOINTER_HPP