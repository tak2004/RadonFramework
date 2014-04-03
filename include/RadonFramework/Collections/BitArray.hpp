#ifndef RF_COLLECTIONS_BitArray_HPP
#define RF_COLLECTIONS_BitArray_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <type_traits>

#include <RadonFramework/System/ICloneable.hpp>
#include <RadonFramework/Threading/ISynchronize.hpp>

#include <RadonFramework/Core/Policies/LazyResize.hpp>
#include <RadonFramework/Core/Policies/CMemoryOperation.hpp>
#include <RadonFramework/Core/Policies/CPPAllocator.hpp>
#include <RadonFramework/Threading/Policies/NoSynchronization.hpp>

namespace RadonFramework
{
    namespace Collections
    {
        template<typename RB=Core::Policies::LazyResize<1,8>,
            typename SP=Threading::Policies::NoSynchronization, 
            typename MA=Core::Policies::CPPAllocator,
            typename MO=Core::Policies::CMemoryOperation>
        class _BitArray:public System::ICloneable<_BitArray<RB,SP,MA,MO> >
        {
            template <typename,typename,typename,typename>
            friend class _BitArray;
            public:
            // Constructor and destructor
                    
                /** 
                 * Create an instance of the _BitArray class.
                 */
                _BitArray();

                /** 
                 * \brief Create a copy of a given _BitArray.
                 *
                 * The copy constructor make a deep copy.
                 *
                 * \param Copy The object from which the copy will be done.
                 */
                _BitArray(const _BitArray<RB,SP,MA,MO>& Copy);

                /**
                 * Create a _BitArray.
                 *
                 * \param Length The size of the _BitArray to create.
                 */
                _BitArray(const RFTYPE::UInt32 Length);

                /**
                 * \brief Creates a _BitArray of the specified length. 
                 *        The data of the _BitArray are copied from the c array.
                 *
                 * \param CArray An array which was created by C.
                 * \param Length Specify the length of the _BitArray.
                 */
                static Memory::AutoPointer<_BitArray<RB,SP,MA,MO> > 
                    CreateInstance(const char CArray[], 
                                   const RFTYPE::UInt32 Length);

                ~_BitArray();
            // Properties
                /**
                 * Gets the number of elements contained in the _BitArray.
                 */
                RFTYPE::UInt32 Count()const;
            // Methods
                /**
                 * \brief Creates a deep copy of the _BitArray.
                 *
                 * A deep copy of an _BitArray copies the elements
                 * and everything directly or indirectly referenced by the 
                 * elements.
                 *
                 * This method is an O(n) operation, where n is Count/8.
                 */
                Memory::AutoPointer<_BitArray<RB,SP,MA,MO> > Clone()const;

                /**
                 * \brief Copies a range of elements from an _BitArray starting
                 *        at the specified source index and pastes them to 
                 *        another _BitArray starting at the specified destination 
                 *        index. Guarantees that all changes are undone if 
                 *        the copy does not succeed completely.
                 *
                 * \param SourceIndex A 32-bit unsigned integer that represents                      
                 *                    the index in the source _BitArray at which 
                 *                    copying begins.
                 * \param DestinationArray The _BitArray that receives the data.
                 * \param DestinationIndex A 32-bit unsigned integer that 
                 *                         represents the index in the 
                 *                         destination _BitArray at which storing 
                 *                         begins.
                 * \param Length A 32-bit unsigned integer that represents 
                 *               the number of elements to copy.
                 */
                RFTYPE::Bool ConstrainedCopy(
                    RFTYPE::UInt32 SourceIndex,
                    _BitArray<RB,SP,MA,MO>& DestinationArray,
                    RFTYPE::UInt32 DestinationIndex,
                    RFTYPE::UInt32 Length);

                /**
                 * \brief Copies a range of elements from an _BitArray starting
                 *        at the specified source index and pastes them to 
                 *        another _BitArray starting at the specified destination 
                 *        index. Guarantees that all changes are undone if 
                 *        the copy does not succeed completely.
                 *
                 * \param DestinationArray The _BitArray that receives the data.
                 * \param Length A 32-bit unsigned integer that represents 
                 *               the number of elements to copy.
                 */
                RFTYPE::Bool ConstrainedCopy(
                    _BitArray<RB,SP,MA,MO>& DestinationArray, 
                    RFTYPE::UInt32 Length);

                /**
                 * \brief Copies a range of elements from an _BitArray starting 
                 *        at the first element and pastes them into another 
                 *        _BitArray starting at the first element. The length 
                 *        is specified as a 32-bit integer.
                 *
                 * \param DestinationArray The _BitArray that receives the data.
                 * \param Length A 32-bit unsigned integer that represents 
                 *               the number of elements to copy.
                 */
                void Copy(_BitArray<RB,SP,MA,MO>& DestinationArray, 
                    RFTYPE::UInt32 Length);

                /**
                 * \brief Copies a range of elements from an _BitArray starting 
                 *        at the first element and pastes them into another 
                 *        _BitArray starting at the first element. The length 
                 *        is specified as a 32-bit integer.
                 *
                 * \param Index A 32-bit unsigned integer that represents 
                 *              the index in the sourceArray at which 
                 *              copying begins.
                 * \param DestinationArray The _BitArray that receives the data.
                 * \param DestinationIndex A 32-bit unsigned integer that 
                 *                         represents the index in the DestinationArray 
                 *                         at which storing begins.
                 * \param Length A 32-bit unsigned integer that represents 
                 *               the number of elements to copy.
                 */
                void Copy(RFTYPE::UInt32 Index, 
                    _BitArray<RB,SP,MA,MO>& DestinationArray,
                    RFTYPE::UInt32 DestinationIndex, 
                    RFTYPE::UInt32 Length);

                /**
                 * \brief Changes the number of elements of an array to the 
                 *        specified new size.
                 *
                 * \param NewSize The size of the new array.
                 */
                void Resize(RFTYPE::UInt32 NewSize);

                /**
                 * \brief Reverses the sequence of the elements in the entire 
                 *        one-dimensional _BitArray.
                 */
                void Reverse();

                /**
                 * \brief Reverses the sequence of the elements in a range 
                 *        of elements in the one-dimensional _BitArray.
                 *
                 * \param Index The starting index of the section to reverse.
                 * \param Length The number of elements in the section to reverse.
                 */
                void Reverse(RFTYPE::UInt32 Index, 
                    RFTYPE::UInt32 Length);

                void Swap(_BitArray<RB,SP,MA,MO>& Other);

                RFTYPE::UInt8 Get(const RFTYPE::UInt32 Index);

                void Set(const RFTYPE::UInt32 Index,RFTYPE::UInt8);
            // Operators
                _BitArray<RB,SP,MA,MO>& operator=(
                     const _BitArray<RB,SP,MA,MO>& Other);
            protected:
                RB m_ContainerInfo;
                RFTYPE::UInt8* m_Data;
            // helper functions
                /// setup the data part of the class
                RFTYPE::Bool InitArray(const RFTYPE::UInt32 Length);
        };

        typedef _BitArray<> BitArray;

        // Constructor & Destructor

        template<typename RB, typename SP, typename MA, typename MO>
        _BitArray<RB,SP,MA,MO>::_BitArray()
        {
            InitArray(0);
        }

        template<typename RB, typename SP, typename MA, typename MO>
        _BitArray<RB,SP,MA,MO>::_BitArray(const _BitArray<RB,SP,MA,MO>& Copy)
        {
            *this=Copy;
        }

        template<typename RB, typename SP, typename MA, typename MO>
        _BitArray<RB,SP,MA,MO>::_BitArray(const RFTYPE::UInt32 Length)
        {
            InitArray(Length);
        }

        template<typename RB, typename SP, typename MA, typename MO>
        Memory::AutoPointer<_BitArray<RB,SP,MA,MO> > _BitArray<RB,SP,MA,MO>::CreateInstance(
            const char CArray[], 
            const RFTYPE::UInt32 Length)
        {
            typename Memory::AutoPointer<_BitArray<RB,SP,MA,MO> > arr(MA::template New<_BitArray<RB,SP,MA,MO> >());
            if (arr.Get()!=0) // out of memory check
            {
                if (arr->InitArray(Length))
                    MO::Copy(arr->m_Data,CArray,Length);
                else // something was going wrong, clean up
                    arr.Reset();
            }
            return arr;
        }

        template<typename RB, typename SP, typename MA, typename MO>
        _BitArray<RB,SP,MA,MO>::~_BitArray()
        {
            if (m_Data!=0)
            {
                MA::FreeArray(m_Data);
                m_Data=0;
            }
        }

        // Properties

        template<typename RB, typename SP, typename MA, typename MO>
        RFTYPE::UInt32 _BitArray<RB,SP,MA,MO>::Count()const
        {
            return m_ContainerInfo.Count();
        }

        // Methods

        template<typename RB, typename SP, typename MA, typename MO>
        Memory::AutoPointer<_BitArray<RB,SP,MA,MO> > _BitArray<RB,SP,MA,MO>::Clone()const
        {
            Memory::AutoPointer<_BitArray<RB,SP,MA,MO> > result(new _BitArray(m_ContainerInfo.Count()));
            MO::Copy(result->m_Data,m_Data,m_ContainerInfo.Count());
            return result;
        }

        template<typename RB, typename SP, typename MA, typename MO>
        RFTYPE::Bool _BitArray<RB,SP,MA,MO>::ConstrainedCopy(RFTYPE::UInt32 SourceIndex,
            _BitArray<RB,SP,MA,MO>& DestinationArray,
            RFTYPE::UInt32 DestinationIndex,
            RFTYPE::UInt32 Length)
        {
            if (m_ContainerInfo.Count()<SourceIndex+Length)
                return false;
            if (DestinationArray.m_ContainerInfo.Count()<DestinationIndex+Length)
                return false;
            MO::Move(&DestinationArray.m_Data[DestinationIndex],&m_Data[SourceIndex],Length);
            return true;
        }

        template<typename RB, typename SP, typename MA, typename MO>
        RFTYPE::Bool _BitArray<RB,SP,MA,MO>::ConstrainedCopy(
            _BitArray<RB,SP,MA,MO>& DestinationArray, 
            RFTYPE::UInt32 Length)
        {
            return ConstrainedCopy(0,DestinationArray,0,Length);
        }

        template<typename RB, typename SP, typename MA, typename MO>
        void _BitArray<RB,SP,MA,MO>::Copy(_BitArray<RB,SP,MA,MO>& DestinationArray, 
            RFTYPE::UInt32 Length)
        {
            Copy(0,DestinationArray,0,Length);
        }

        template<typename RB, typename SP, typename MA, typename MO>
        void _BitArray<RB,SP,MA,MO>::Copy(RFTYPE::UInt32 Index, 
            _BitArray<RB,SP,MA,MO>& DestinationArray,
            RFTYPE::UInt32 DestinationIndex, 
            RFTYPE::UInt32 Length)
        {
            assert(m_ContainerInfo.Count()>=Index+Length);
            assert(DestinationArray.m_ContainerInfo.Count()>=DestinationIndex+Length);
            MO::Move(&DestinationArray.m_Data[DestinationIndex],&m_Data[Index],Length);
        }

        template<typename RB, typename SP, typename MA, typename MO>
        void _BitArray<RB,SP,MA,MO>::Resize(RFTYPE::UInt32 NewSize)
        {
            if (m_Rank==0)
                InitArray(1,&NewSize);
            assert(m_Rank==1);
            if (NewSize!=m_Length[0])
            {
                T* data=MA::template NewArray<T>(NewSize);
                if (std::is_class<T>::value==true)
                    for (RFTYPE::UInt32 i=0;i<RadonFramework::Math::Math<RFTYPE::UInt32>::Min(m_Length[0],NewSize);++i)
                        data[i]=m_Data[i];
                else
                    MO::Copy(data,m_Data,RadonFramework::Math::Math<RFTYPE::UInt32>::Min(m_Length[0],NewSize));
                MA::FreeArray(m_Data);
                m_Data=data;
                m_Length[0]=NewSize;
                m_ContainerInfo.Count()=NewSize;
            }
        }

        template<typename RB, typename SP, typename MA, typename MO>
        void _BitArray<RB,SP,MA,MO>::Reverse()
        {
            Reverse(0,m_ContainerInfo.Count());
        }

        template<typename RB, typename SP, typename MA, typename MO>
        void _BitArray<RB,SP,MA,MO>::Reverse(RFTYPE::UInt32 Index, 
            RFTYPE::UInt32 Length)
        {
            assert(Index+Length<=m_ContainerInfo.Count());
            RFTYPE::UInt32 end=Index+Length-1;
            RFTYPE::UInt32 halfEnd=Index+Length>>1;
            T* tmp=MA::template New<T>();
            for (RFTYPE::UInt32 i=Index;i<halfEnd;++i)
            {
                MO::Copy(tmp,&m_Data[i],1);
                MO::Move(&m_Data[i],&m_Data[end-i],1);
                MO::Copy(&m_Data[end-i],tmp,1);
            }
            MA::Free(tmp);
        }

        template<typename RB, typename SP, typename MA, typename MO>
        void _BitArray<RB,SP,MA,MO>::Swap(_BitArray<RB,SP,MA,MO>& Other)
        {
            T* tmpData=m_Data;
            m_Data=Other.m_Data;
            Other.m_Data=tmpData;

            RFTYPE::UInt32 tmpCount=m_ContainerInfo.Count();
            m_ContainerInfo.Count()=Other.m_ContainerInfo.Count();
            Other.m_ContainerInfo.Count()=tmpCount;

            RFTYPE::UInt32* tmpLen=m_Length;
            m_Length=Other.m_Length;
            Other.m_Length=tmpLen;

            RFTYPE::UInt32 tmpRank=m_Rank;
            m_Rank=Other.m_Rank;
            Other.m_Rank=tmpRank;

            RFTYPE::Bool tmpSync=m_Synchronized;
            m_Synchronized=Other.m_Synchronized;
            Other.m_Synchronized=tmpSync;

            Threading::ISynchronize* tmpSynchronize=m_SyncRoot;
            m_SyncRoot=Other.m_SyncRoot;
            Other.m_SyncRoot=tmpSynchronize;
        }

        template<typename RB, typename SP, typename MA, typename MO>
        RFTYPE::UInt8 _BitArray<RB,SP,MA,MO>::Get(const RFTYPE::UInt32 Index)
        {

        }

        template<typename RB, typename SP, typename MA, typename MO>
        void _BitArray<RB,SP,MA,MO>::Set(const RFTYPE::UInt32 Index,RFTYPE::UInt8)
        {

        }

        // Operators
        template<typename RB, typename SP, typename MA, typename MO>
        _BitArray<RB,SP,MA,MO>& _BitArray<RB,SP,MA,MO>::operator=(const _BitArray<RB,SP,MA,MO>& Other)
        {
            InitArray(Other.m_Rank,Other.m_Length);
            for (RFTYPE::UInt32 i=0;i<m_ContainerInfo.Count();++i)
                m_Data[i]=Other.m_Data[i];
            return *this;
        }

        // internal helper functions

        template<typename RB, typename SP, typename MA, typename MO>
        RFTYPE::Bool _BitArray<RB,SP,MA,MO>::InitArray(
            const RFTYPE::UInt32 Length)
        {
            m_Synchronized=false;
            m_Data=0;
            m_SyncRoot=MA::template New<SP>();

            if (m_SyncRoot==0)
                return false;

            if (Length>0)
            {
                m_Data=MA::template NewArray<T>(len);
                if (m_Data==0)
                    return false;
                m_ContainerInfo.ElementCount=Length;
            }
            return true;
        }
    }
}

#endif // RF_COLLECTIONS_BitArray_HPP