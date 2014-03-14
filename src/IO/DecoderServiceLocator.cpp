#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/IO/DecoderServiceLocator.hpp>

using namespace RadonFramework::IO;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;


DecoderServiceLocator::Iterator DecoderServiceLocator::FindNameOrFourCC(const String& Name, const UInt32 FCC)
{
    for (DecoderServiceLocator::Iterator it=DecoderServiceLocator::m_Services.Begin();
         it!=DecoderServiceLocator::m_Services.End();++it)
    {
        if ( ((*it)->Name()==Name) || ((*it)->FourCC()==FCC) )
            return it;
    }
    return DecoderServiceLocator::m_Services.End();
}
