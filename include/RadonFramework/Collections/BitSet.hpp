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

    BitSetReference& operator=(const RFTYPE::Bool Other);

    BitSetReference& operator&=(const RFTYPE::Bool Other);
    BitSetReference& operator|=(const RFTYPE::Bool Other);
    BitSetReference& operator^=(const RFTYPE::Bool Other);
    BitSetReference& Set();
    BitSetReference& Flip();
    BitSetReference operator~()const;
    RFTYPE::Bool operator !()const;
    BitSetReference& Reset();

    operator RFTYPE::Bool()const;
            
    RFTYPE::Bool operator &&(const RFTYPE::Bool Other)const;
    RFTYPE::Bool operator ||(const RFTYPE::Bool Other)const;
    RFTYPE::Bool operator !=(const RFTYPE::Bool Other)const;
    RFTYPE::Bool operator ==(const RFTYPE::Bool Other)const;
protected:
    BitSet<Bits>* m_BitSet;
    RFTYPE::Size m_Index;
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
    BitSet& operator<<=(RFTYPE::Size Shift);
    BitSet& operator>>=(RFTYPE::Size Shift);
    BitSet operator<<(RFTYPE::Size Shift)const;
    BitSet operator>>(RFTYPE::Size Shift)const;
    BitSet& Set();
    BitSet& Flip();
    BitSet operator~()const;
    BitSet& Reset();
    BitSet& Set(RFTYPE::Size Index);
    BitSet& Reset(RFTYPE::Size Index);
    BitSet& Flip(RFTYPE::Size Index);

    RFTYPE::Size Size()const;
    RFTYPE::Size Count()const;
    RFTYPE::Bool Any()const;
    RFTYPE::Bool None()const;
    RFTYPE::Bool Test(RFTYPE::Size Index)const;
    BitSetReference<Bits> operator[](RFTYPE::Size Index);
    RFTYPE::Bool operator[](RFTYPE::Size Index)const;
    RFTYPE::Bool operator==(const BitSet& Other)const;
    RFTYPE::Bool operator!=(const BitSet& Other)const;
protected:
    RFTYPE::UInt8 m_Data[((Bits-1)/8)+1];
};

template<int Bits>
BitSetReference<Bits>& BitSetReference<Bits>::operator=(const RFTYPE::Bool Other)
{
    if (Other)
        m_BitSet->Set(m_Index);
    else
        m_BitSet->Reset(m_Index);
    return *this;
}

template<int Bits>
BitSetReference<Bits>& BitSetReference<Bits>::operator&=(const RFTYPE::Bool Other)
{
    RFTYPE::UInt32 index=((m_Index-1)/8)+1;
    if (Other)
        m_BitSet->m_Data[index]&=255;
    else
        m_BitSet->m_Data[index]&=~(1<<(m_Index%8));
}

template<int Bits>
BitSetReference<Bits>& BitSetReference<Bits>::operator|=(const RFTYPE::Bool Other)
{
    RFTYPE::Size index=((m_Index-1)/8)+1;
    if (Other)
        m_BitSet->m_Data[index]|=1<<(m_Index%8);
}

template<int Bits>
BitSetReference<Bits>& BitSetReference<Bits>::operator^=(const RFTYPE::Bool Other)
{
    if(Other)
        m_BitSet->Flip(m_Index);
}

template<int Bits>
BitSetReference<Bits>& BitSetReference<Bits>::Set()
{
    m_BitSet->Set(m_Index);
}

template<int Bits>
BitSetReference<Bits>& BitSetReference<Bits>::Flip()
{
    m_BitSet->Flip(m_Index);
}

template<int Bits>
BitSetReference<Bits> BitSetReference<Bits>::operator~()const
{
    m_BitSet->Flip(m_Index);
}

template<int Bits>
RFTYPE::Bool BitSetReference<Bits>::operator!()const
{
    return !m_BitSet->Test(m_Index);
}

template<int Bits>
BitSetReference<Bits>& BitSetReference<Bits>::Reset()
{
    m_BitSet->Reset(m_Index);
}

template<int Bits>
BitSetReference<Bits>::operator RFTYPE::Bool()const
{
    return m_BitSet->Test(m_Index);
}
       
template<int Bits>
RFTYPE::Bool BitSetReference<Bits>::operator&&(const RFTYPE::Bool Other)const
{
    return Other && m_BitSet->Test(m_Index);
}

template<int Bits>
RFTYPE::Bool BitSetReference<Bits>::operator||(const RFTYPE::Bool Other)const
{
    return Other || m_BitSet->Test(m_Index);
}

template<int Bits>
RFTYPE::Bool BitSetReference<Bits>::operator==(const RFTYPE::Bool Other)const
{
    return Other == m_BitSet->Test(m_Index);
}

template<int Bits>
RFTYPE::Bool BitSetReference<Bits>::operator!=(const RFTYPE::Bool Other)const
{
    return Other != m_BitSet->Test(m_Index);
}

//
//
//

template<int Bits>
BitSet<Bits>::BitSet()
{
    for (RFTYPE::Size i = 0; i < ((Bits-1)/8)+1; ++i)
        m_Data[i] = 0;
}

template<int Bits>
BitSet<Bits>::BitSet(const BitSet<Bits>& Copy)
{
    for (RFTYPE::Size i = 0; i < ((Bits-1)/8)+1; ++i)
        m_Data[i] = Copy.m_Data[i];
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::operator=(const BitSet<Bits>& Other)
{
    for (RFTYPE::Size i = 0; i < ((Bits-1)/8)+1; ++i)
        m_Data[i] = Other.m_Data[i];
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::operator&=(const BitSet<Bits>& Other)
{
    for (RFTYPE::Size i=0;i<((Bits-1)/8)+1;++i)
        m_Data[i]&=Other.m_Data[i];
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::operator|=(const BitSet<Bits>& Other)
{
    for (RFTYPE::Size i=0;i<((Bits-1)/8)+1;++i)
        m_Data[i]|=Other.m_Data[i];
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::operator^=(const BitSet<Bits>& Other)
{
    for (RFTYPE::Size i=0;i<((Bits-1)/8)+1;++i)
        m_Data[i]^=Other.m_Data[i];
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::operator<<=(RFTYPE::Size Shift)
{            
    const RFTYPE::Size byteSize=Size();
    if (Shift>=Bits)
    {
        for (RFTYPE::Size i = 0; i < byteSize; ++i)
            m_Data[i] = 0;
    }
    else
    {
        const RFTYPE::Size bitOffset=Shift%8;
        const RFTYPE::Size indOffset=Shift>>3;
        const RFTYPE::Size changeSize=((Shift-1)>>3)+1;

        if (changeSize>1)
        {
            const RFTYPE::Size last=(Bits>>3)-indOffset;
            RFTYPE::UInt8 tmp;
            for (RFTYPE::Int32 i=0;i<last;++i)
            {
                tmp=m_Data[i+indOffset+1]>>bitOffset;
                m_Data[i]=(m_Data[i+indOffset]<<bitOffset)|tmp;
            }
        }
        const RFTYPE::Size bitPadding=(byteSize<<3)-Bits;
        const RFTYPE::Size lastChangedByte=(Bits>>3)-indOffset;
        m_Data[lastChangedByte]=m_Data[(Bits>>3)]<<bitOffset;
        if (bitPadding>0)
            m_Data[lastChangedByte]&=~((1<<(bitPadding+bitOffset))-1);
        if (changeSize>1)
        {
            for (RFTYPE::Size i = 0; i < indOffset; ++i)
                (m_Data+(byteSize-indOffset))[i] = 0;
        }
    }            
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::operator>>=(RFTYPE::Size Shift)
{
    const RFTYPE::Size byteSize=Size();
    if (Shift>=Bits)
    {
        for (RFTYPE::Size i = 0; i < byteSize; ++i)
            m_Data[i] = 0;
    }
    else
    {
        const RFTYPE::Size bitOffset=Shift%8;
        const RFTYPE::Size indOffset=Shift>>3;
        const RFTYPE::Size changeSize=((Shift-1)>>3)+1;

        if (changeSize>1)
        {
            const RFTYPE::Size first=changeSize;
            const RFTYPE::Size last=Bits>>3;
            RFTYPE::UInt8 tmp;                    
            for (RFTYPE::Size i=last;i>first;--i)
            {
                tmp=m_Data[i-indOffset]>>bitOffset;
                m_Data[i]=(m_Data[i-indOffset]<<bitOffset)|tmp;
            }                    
        }
        m_Data[indOffset]=m_Data[0]>>bitOffset;                
        if (changeSize>1)
        {
            for (RFTYPE::Size i = 0; i < indOffset; ++i)
                m_Data[i] = 0;
        }
    }  
    return *this;
}

template<int Bits>
BitSet<Bits> BitSet<Bits>::operator<<(RFTYPE::Size Shift)const
{
    BitSet<Bits> result(*this);
    result<<=Shift;
    return result;
}

template<int Bits>
BitSet<Bits> BitSet<Bits>::operator>>(RFTYPE::Size Shift)const
{
    BitSet<Bits> result(*this);
    result>>=Shift;
    return result;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::Set()
{
    for (RFTYPE::Size i = 0; i < ((Bits-1)/8)+1; ++i)
        m_Data[i] = 255;
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::Flip()
{
    for (RFTYPE::UInt32 i=0;i<((Bits-1)/8)+1;++i)
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
    for (RFTYPE::Size i = 0; i < ((Bits-1)/8)+1; ++i)
        m_Data[i] = 0;
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::Set(RFTYPE::Size Index)
{
    Assert(Index<Bits, "Out of bound.");
    m_Data[Index/8]|=128>>(Index%8);
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::Reset(RFTYPE::Size Index)
{
    Assert(Index<Bits, "Out of bound.");
    m_Data[Index/8]&=~(128>>(Index%8));
    return *this;
}

template<int Bits>
BitSet<Bits>& BitSet<Bits>::Flip(RFTYPE::Size Index)
{
    Assert(Index<Bits, "Out of bound.");
    const RFTYPE::Size ind=Index/8;
    m_Data[ind]=m_Data[ind]^(128>>(Index%8));
    return *this;
}

template<int Bits>
RFTYPE::Size BitSet<Bits>::Size()const
{
    return ((Bits-1)/8)+1;
}

template<int Bits>
RFTYPE::Size BitSet<Bits>::Count()const
{
    return Bits;
}

template<int Bits>
RFTYPE::Bool BitSet<Bits>::Any()const
{
    for (RFTYPE::Size i=0;i<((Bits-1)/8)+1;++i)
        if (m_Data[i]!=255)
            return false;
    return true;
}

template<int Bits>
RFTYPE::Bool BitSet<Bits>::None()const
{
    for (RFTYPE::Size i=0;i<((Bits-1)/8)+1;++i)
        if(m_Data[i]!=0)
            return false;
    return true;
}

template<int Bits>
RFTYPE::Bool BitSet<Bits>::Test(RFTYPE::Size Index)const
{
    Assert(Index<Bits, "Out of bound.");
    RFTYPE::Size ind=Index/8;
    if ( ( m_Data[ind] & ( 128>>( Index%8 ) ) )>0)
        return true;
    else
        return false;
}

template<int Bits>
BitSetReference<Bits> BitSet<Bits>::operator[](RFTYPE::Size Index)
{
    Assert(Index<Bits, "Out of bound.");
    BitSetReference<Bits> result;
    result.m_BitSet=this;
    result.m_Index=Index;
    return result;
}

template<int Bits>
RFTYPE::Bool BitSet<Bits>::operator[](RFTYPE::Size Index)const
{
    Assert(Index<Bits, "Out of bound.");
    RFTYPE::Size ind=((Index-1)/8)+1;
    m_Data[ind]=m_Data[ind]&(~(1<<Index%8));
    if (m_Data[ind]>0)
        return true;
    else
        return false;
}

template<int Bits>
RFTYPE::Bool BitSet<Bits>::operator==(const BitSet<Bits>& Other)const
{
    RFTYPE::Bool result = true;
    for (RFTYPE::Size i = 0; i < ((Bits-1)/8)+1; ++i)
        result &= m_Data[i] == Other.m_Data[i];
    return result;
}

template<int Bits>
RFTYPE::Bool BitSet<Bits>::operator!=(const BitSet<Bits>& Other)const
{
    RFTYPE::Bool result = true;
    for (RFTYPE::Size i = 0; i < ((Bits-1)/8)+1; ++i)
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

#endif // RF_COLLECTIONS_BITSET_HPP