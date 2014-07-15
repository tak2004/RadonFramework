#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Random.hpp"

using namespace RadonFramework::Math;
using namespace RadonFramework::Core::Types;

Random::Random(const Int32 Seed)
:m_Seed(Seed),
 m_J(Seed),
 m_K(1),
 m_Index(0)
{
    m_Buffer[BUFFER_ELEMENT_COUNT - 1] = m_Seed;
    for (Int32 i=0;i<165;++i)//walk three times through the buffer
        Sample();
}

Int32 Random::Next()
{
    return Int32(Sample()*(Float32)Int32Max);
}

Int32 Random::Next(const Int32 MaxValue)
{
    return Int32(Sample()*MaxValue);
}

Int32 Random::Next(const Int32 MinValue, const Int32 MaxValue)
{
    return Int32(MinValue+(Float32)(Sample()*(MaxValue-MinValue)));
}

Float32 Random::NextFloat()
{
    return Sample();
}

Float32 Random::Sample()
{
    /*
        For more information, see D. E. Knuth. "The Art of Computer Programming,
        volume 2: Seminumerical Algorithms".
        Addison-Wesley, second edition, Page 171-173 .
    */
    Int32 index = (21 * m_Index) % BUFFER_ELEMENT_COUNT;
    m_Buffer[index]=m_K;
    m_K=m_J-m_K;
    if (m_K<0)
        m_K+=Int32Max;
    m_J=m_Buffer[index];

    m_Index++;
    if(m_Index == BUFFER_ELEMENT_COUNT) m_Index = 0;

    return (Float32)m_J/(Float32)Int32Max;
}
