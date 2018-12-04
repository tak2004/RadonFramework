#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Canvas3DServiceConfig.hpp"
#include "RadonFramework/Drawing/Canvas3DServiceLocator.hpp"
#include "RadonFramework/Core/Types/Convert.hpp"

using namespace RadonFramework::Drawing;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;

Int32 LowestFirst(const Pair<Size,String>& A,const Pair<Size,String>& B)
{
    if (A.First==B.First)
        return 0;
    else
        if (A.First>B.First)
            return 1;
        else
            return -1;
}

String Canvas3DServiceConfig::DefaultDriver;
Array<Pair<Size,String> > Canvas3DServiceConfig::FallbackDriver;

void Canvas3DServiceConfig::Set(DataTree::NodeType& TreeNode)
{
    DataTree::NodeType* node=&TreeNode;
    do
    {
        if (node->Data().First == "default"_rfs)
            DefaultDriver=node->Data().Second;
        else
            if (node->Data().First == "fallback"_rfs)
            {
                String serviceName;
                Size prio;
                if (Fallback(*node->FirstChild(),prio,serviceName))
                {
                    Pair<Size,String> pair(prio,serviceName);
                    if (FallbackDriver.Count()==0)
                        FallbackDriver=Array<Pair<Size,String> >(1);
                    else
                        FallbackDriver.Resize(FallbackDriver.Count()+1);
                    FallbackDriver(FallbackDriver.Count()-1)=pair;
                }
            }
    }
    while(0!=(node=node->Next()));

    if (FallbackDriver.Count()>0)
    {
        Delegate2<Int32(const Pair<Size, String>&, const Pair<Size, String>&)> callback(&LowestFirst);
        FallbackDriver.Sort(callback);
    }

    if (Canvas3DServiceLocator::Find(DefaultDriver).Name() != "NullService"_rfs)
        Canvas3DServiceLocator::SetDefault(DefaultDriver);
    else
        for (Size i=0;i<FallbackDriver.Count();++i)
            if(Canvas3DServiceLocator::Find(FallbackDriver(i).Second).Name() != "NullService"_rfs)
            {
                Canvas3DServiceLocator::SetDefault(FallbackDriver(i).Second);
                break;
            }
}

Bool Canvas3DServiceConfig::Fallback(DataTree::NodeType& TreeNode,
                                     Size& Priority,
                                     String& Parameter)
{
    Bool isPriorityExist=false, isValueExist=false;
    DataTree::NodeType* node=&TreeNode;
    do
    {
        if (node->Data().First == "priority"_rfs)
        {
            if (node->Data().Second.IsNumber())
            {
                Convert::ToSize(node->Data().Second, Priority);
                isPriorityExist=true;
            }
        }
        else
        if (node->Data().First == "value"_rfs)
        {
            Parameter=node->Data().Second;
            isValueExist=true;
        }
    }
    while(0!=(node=node->Next()));
    return isPriorityExist && isValueExist;
}
