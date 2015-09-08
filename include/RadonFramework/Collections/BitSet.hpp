#ifndef RF_COLLECTIONS_BITSET_HPP
#define RF_COLLECTIONS_BITSET_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Collections {
        
template<int Bits>
class BitSet;

template<int Bits>
struct BitSetReference
{
    friend class BitSet<Bits>;

    BitSetReference& operator=(const RF_Type::Bool Other);

    BitSetReference& operator&=(const RF_Type::Bool Other);
    BitSetReference& operator|=(const RF_Type::Bool Other);
    BitSetReference& operator^=(const RF_Type::Bool Other);
    BitSetReference& Set();
    BitSetReference& Flip();
    BitSetReference operator~()const;
    RF_Type::Bool operator !()const;
    BitSetReference& Reset();

    operator RF_Type::Bool()const;
            
    RF_Type::Bool operator &&(const RF_Type::Bool Other)const;
    RF_Type::Bool operator ||(const RF_Type::Bool Other)const;
    RF_Type::Bool operator !=(const RF_Type::Bool Other)const;
    RF_Type::Bool operator ==(const RF_Type::Bool Other)const;
protected:
    BitSet<Bits>* m_BitSet;
    RF_Type::Size m_Index;
};

template<int Bits>
class BitSet
{
friend struct BitSetReference<Bits>;
public:
    BitSet();
    BitSet(const BitSet& Copy);
    BitSet& operator=(const BitSet& Other);

    BitSet& operator&=(const BitSet& Other);
    BitSet& operator|=(const BitSet& Other);
    BitSet& operator^=(const BitSet& Other);
    BitSet& operator<<=(RF_Type::Size Shift);
    BitSet& operator>>=(RF_Type::Size Shift);
    BitSet operator<<(RF_Type::Size Shift)const;
    BitSet operator>>(RF_Type::Size Shift)const;
    BitSet& Set();
    BitSet& Flip();
    BitSet operator~()const;
    BitSet& Reset();
    BitSet& Set(RF_Type::Size Index);
    BitSet& Reset(RF_Type::Size Index);
    BitSet& Flip(RF_Type::Size Index);

    RF_Type::Size Size()const;
    RF_Type::Size Count()const;
    RF_Type::Bool Any()const;
    RF_Type::Bool None()const;
    RF_Type::Bool Test(RF_Type::Size Index)const;
    BitSetReference<Bits> operator[](RF_Type::Size Index);
    RF_Type::Bool operator[](RF_Type::Size Index)const;
    RF_Type::Bool operator==(const BitSet& Other)const;
    RF_Type::Bool operator!=(const BitSet& Other)const;
protected:
    RF_Type::UInt8 m_Data[((Bits-1)/8)+1];
};

template<int Bits>
BitSetReference<Bits>& BitSetReference<Bits>::operator=(const RF_Type::Bool Other)
{
    if (Other)
        m_BitSet->Set(m_Index);
    else
        m_BitSet->Reset(m_Index);
    return *this;
}

template<int Bits>
BitSetReference<Bits>& BitSetReference<Bits>::operator&=(const RF_Type::Bool Other)
{
    RF_Type::UInt32 index=((m_Index-1)/8)+1;
    if (Other)
        m_BitSet->m_Data[index]&=255;
    else
        m_BitSet->m_Data[index]&=~(1<<(m_Index%8));
    return *this;
}

template<int Bits>
BitSetReference<Bits>& BitSetReference<Bits>::operator|=(const RF_Type::Bool Other)
{
    RF_Type::Size index=((m_Index-1)/8)+1;
    if (Other)
        m_BitSet->m_Data[index]|=1<<(m_Index%8);
    return *this;
}

template<int Bits>
BitSetReference<Bits>& BitSetReference<Bits>::operator^=(const RF_Type::Bool Other)
{
    if(Other)
        m_BitSet->Flip(m_Index);
    return *this;
}

template<int Bits>
BitSetReference<Bits>& BitSetReference<Bits>::Set()
{
    m_BitSet->Set(m_Index);
    return *this;
}

template<int Bits>
BitSetReference<Bits>& BitSetReference<Bits>::Flip()
{
    m_BitSet->Flip(m_Index);
    return *this;
}

template<int Bits>
BitSetReference<Bits> BitSetReference<Bits>::operator~()const
{
    m_BitSet->Flip(m_Index);
}

template<int Bits>
RF_Type::Bool BitSetReference<Bits>::operator!()const
{
    return !m_BitSet->Test(m_Index);
}

template<int Bits>
BitSetReference<Bits>& BitSetReference<Bits>::Reset()
{
    m_BitSet->Reset(m_Index);
    return *this;
}

template<int Bits>
BitSetReference<Bits>::operator RF_Type::Bool()const
{
    return m_BitSet->Test(m_Index);
}
       
template<int Bits>
RF_Type::Bool BitSetReference<Bits>::operator&&(const RF_Type::Bool Other)const
{
    return Other && m_BitSet->Test(m_Index);
}

template<int Bits>
RF_Type::Bool BitSetReference<Bits>::operator||(const RF_Type::Bool Other)const
{
    return Other || m_BitSet->Test(m_Index);
}

template<int Bits>
RF_Type::Bool BitSetReference<Bits>::operator==(const RF_Type::Bool Other)const
{
    return Other == m_BitSet->Test(m_Index);
}

template<int Bits>
RF_Type::Bool BitSetReference<Bits>::operator!=(const RF_Type::Bool Other)const
{
    return Other != m_BitSet->Test(m_Index);
}

//
//
//

template<int Bits>
BitSet<Bits>::BitSet()
{
    for (RF_Type::Size i = 0; i < ((Bits-1)/8)+1; ++i)
        m_Data[i] = 0;
}

template<int Bits>
BitSet<Bits>::BitSet(const BitSet<Bits>& Copy)
{
    for (RF_Type::Size i = 0; i < ((Bits-1)/8)+1; ++i)
        m_Data[i] = Copy.m_Data[i];
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::operator=(const BitSet<Bits>& Other)
{
    for (RF_Type::Size i = 0; i < ((Bits-1)/8)+1; ++i)
        m_Data[i] = Other.m_Data[i];
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::operator&=(const BitSet<Bits>& Other)
{
    for (RF_Type::Size i=0;i<((Bits-1)/8)+1;++i)
        m_Data[i]&=Other.m_Data[i];
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::operator|=(const BitSet<Bits>& Other)
{
    for (RF_Type::Size i=0;i<((Bits-1)/8)+1;++i)
        m_Data[i]|=Other.m_Data[i];
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::operator^=(const BitSet<Bits>& Other)
{
    for (RF_Type::Size i=0;i<((Bits-1)/8)+1;++i)
        m_Data[i]^=Other.m_Data[i];
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::operator<<=(RF_Type::Size Shift)
{            
    const RF_Type::Size byteSize=Size();
    if (Shift>=Bits)
    {
        for (RF_Type::Size i = 0; i < byteSize; ++i)
            m_Data[i] = 0;
    }
    else
    {
        const RF_Type::Size bitOffset=Shift%8;
        const RF_Type::Size indOffset=Shift>>3;
        const RF_Type::Size changeSize=((Shift-1)>>3)+1;

        if (changeSize>1)
        {
            const RF_Type::Size last=(Bits>>3)-indOffset;
            RF_Type::UInt8 tmp;
            for (RF_Type::Int32 i=0;i<last;++i)
            {
                tmp=m_Data[i+indOffset+1]>>bitOffset;
                m_Data[i]=(m_Data[i+indOffset]<<bitOffset)|tmp;
            }
        }
        const RF_Type::Size bitPadding=(byteSize<<3)-Bits;
        const RF_Type::Size lastChangedByte=(Bits>>3)-indOffset;
        m_Data[lastChangedByte]=m_Data[(Bits>>3)]<<bitOffset;
        if (bitPadding>0)
            m_Data[lastChangedByte]&=~((1<<(bitPadding+bitOffset))-1);
        if (changeSize>1)
        {
            for (RF_Type::Size i = 0; i < indOffset; ++i)
                (m_Data+(byteSize-indOffset))[i] = 0;
        }
    }            
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::operator>>=(RF_Type::Size Shift)
{
    const RF_Type::Size byteSize=Size();
    if (Shift>=Bits)
    {
        for (RF_Type::Size i = 0; i < byteSize; ++i)
            m_Data[i] = 0;
    }
    else
    {
        const RF_Type::Size bitOffset=Shift%8;
        const RF_Type::Size indOffset=Shift>>3;
        const RF_Type::Size changeSize=((Shift-1)>>3)+1;

        if (changeSize>1)
        {
            const RF_Type::Size first=changeSize;
            const RF_Type::Size last=Bits>>3;
            RF_Type::UInt8 tmp;                    
            for (RF_Type::Size i=last;i>first;--i)
            {
                tmp=m_Data[i-indOffset]>>bitOffset;
                m_Data[i]=(m_Data[i-indOffset]<<bitOffset)|tmp;
            }                    
        }
        m_Data[indOffset]=m_Data[0]>>bitOffset;                
        if (changeSize>1)
        {
            for (RF_Type::Size i = 0; i < indOffset; ++i)
                m_Data[i] = 0;
        }
    }  
    return *this;
}

template<int Bits>
BitSet<Bits> BitSet<Bits>::operator<<(RF_Type::Size Shift)const
{
    BitSet<Bits> result(*this);
    result<<=Shift;
    return result;
}

template<int Bits>
BitSet<Bits> BitSet<Bits>::operator>>(RF_Type::Size Shift)const
{
    BitSet<Bits> result(*this);
    result>>=Shift;
    return result;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::Set()
{
    for (RF_Type::Size i = 0; i < ((Bits-1)/8)+1; ++i)
        m_Data[i] = 255;
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::Flip()
{
    for (RF_Type::UInt32 i=0;i<((Bits-1)/8)+1;++i)
        m_Data[i]=~m_Data[i];
    return *this;
}

template<int Bits>
BitSet<Bits> BitSet<Bits>::operator~()const
{
    BitSet<Bits> result(*this);
    return result.Flip();
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::Reset()
{
    for (RF_Type::Size i = 0; i < ((Bits-1)/8)+1; ++i)
        m_Data[i] = 0;
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::Set(RF_Type::Size Index)
{
    Assert(Index<Bits, "Out of bound.");
    m_Data[Index/8]|=128>>(Index%8);
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::Reset(RF_Type::Size Index)
{
    Assert(Index<Bits, "Out of bound.");
    m_Data[Index/8]&=~(128>>(Index%8));
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::Flip(RF_Type::Size Index)
{
    Assert(Index<Bits, "Out of bound.");
    const RF_Type::Size ind=Index/8;
    m_Data[ind]=m_Data[ind]^(128>>(Index%8));
    return *this;
}

template<int Bits>
RF_Type::Size BitSet<Bits>::Size()const
{
    return ((Bits-1)/8)+1;
}

template<int Bits>
RF_Type::Size BitSet<Bits>::Count()const
{
    return Bits;
}

template<int Bits>
RF_Type::Bool BitSet<Bits>::Any()const
{
    for (RF_Type::Size i=0;i<((Bits-1)/8)+1;++i)
        if (m_Data[i]!=255)
            return false;
    return true;
}

template<int Bits>
RF_Type::Bool BitSet<Bits>::None()const
{
    for (RF_Type::Size i=0;i<((Bits-1)/8)+1;++i)
        if(m_Data[i]!=0)
            return false;
    return true;
}

template<int Bits>
RF_Type::Bool BitSet<Bits>::Test(RF_Type::Size Index)const
{
    Assert(Index<Bits, "Out of bound.");
    RF_Type::Size ind=Index/8;
    if ( ( m_Data[ind] & ( 128>>( Index%8 ) ) )>0)
        return true;
    else
        return false;
}

template<int Bits>
BitSetReference<Bits> BitSet<Bits>::operator[](RF_Type::Size Index)
{
    Assert(Index<Bits, "Out of bound.");
    BitSetReference<Bits> result;
    result.m_BitSet=this;
    result.m_Index=Index;
    return result;
}

template<int Bits>
RF_Type::Bool BitSet<Bits>::operator[](RF_Type::Size Index)const
{
    Assert(Index<Bits, "Out of bound.");
    RF_Type::Size ind=((Index-1)/8)+1;
    m_Data[ind]=m_Data[ind]&(~(1<<(Index%8)));
    if (m_Data[ind]>0)
        return true;
    else
        return false;
}

template<int Bits>
RF_Type::Bool BitSet<Bits>::operator==(const BitSet<Bits>& Other)const
{
    RF_Type::Bool result = true;
    for (RF_Type::Size i = 0; i < ((Bits-1)/8)+1; ++i)
        result &= m_Data[i] == Other.m_Data[i];
    return result;
}

template<int Bits>
RF_Type::Bool BitSet<Bits>::operator!=(const BitSet<Bits>& Other)const
{
    RF_Type::Bool result = true;
    for (RF_Type::Size i = 0; i < ((Bits-1)/8)+1; ++i)
        result &= m_Data[i] != Other.m_Data[i];
    return result;
}

template<int Bits>
BitSet<Bits> operator&(const BitSet<Bits>& A, const BitSet<Bits>& B)
{
    BitSet<Bits> result(A);
    result&=B;
    return result;
}
        
template<int Bits>
BitSet<Bits> operator|(const BitSet<Bits>& A, const BitSet<Bits>& B)
{
    BitSet<Bits> result(A);
    result|=B;
    return result;
}

template<int Bits>
BitSet<Bits> operator^(const BitSet<Bits>& A, const BitSet<Bits>& B)
{
    BitSet<Bits> result(A);
    result^=B;
    return result;
}

} }

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_BITSET_HPP