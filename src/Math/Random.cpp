#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Random.hpp"

namespace RadonFramework { namespace Math {

Random::Random(const RF_Type::Int32 Seed)
:m_Seed(Seed)
,m_J(Seed)
,m_K(1)
,m_Index(0)
{
    m_Buffer[BUFFER_ELEMENT_COUNT - 1] = m_Seed;
    for (RF_Type::Int32 i=0;i<165;++i)//walk three times through the buffer
        Sample();
}

RF_Type::Int32 Random::Next()
{
    return RF_Type::Int32(Sample()*(RF_Type::Float32)RF_Type::Int32Max);
}

RF_Type::Int32 Random::Next(const RF_Type::Int32 MaxValue)
{
    return RF_Type::Int32(Sample()*MaxValue);
}

RF_Type::Int32 Random::Next(const RF_Type::Int32 MinValue, const RF_Type::Int32 MaxValue)
{
    return RF_Type::Int32(MinValue+(RF_Type::Float32)(Sample()*(MaxValue-MinValue)));
}

RF_Type::Float32 Random::NextFloat()
{
    return Sample();
}

RF_Type::Float32 Random::Sample()
{
    /*
        For more information, see D. E. Knuth. "The Art of Computer Programming,
        volume 2: Seminumerical Algorithms".
        Addison-Wesley, second edition, Page 171-173 .
    */
    RF_Type::Int32 index = (21 * m_Index) % BUFFER_ELEMENT_COUNT;
    m_Buffer[index]=m_K;
    m_K=m_J-m_K;
    if (m_K<0)
        m_K+= RF_Type::Int32Max;
    m_J=m_Buffer[index];

    m_Index++;
    if(m_Index == BUFFER_ELEMENT_COUNT) m_Index = 0;

    return (RF_Type::Float32)m_J/(RF_Type::Float32)RF_Type::Int32Max;
}

} }