#ifndef RF_MATH_GEOMETRY_VECTOR_HPP
#define RF_MATH_GEOMETRY_VECTOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>
#include <RadonFramework/Math/MathOfType.hpp>

namespace RadonFramework::Math::Geometry {

template <typename T,RF_Type::Size SIZE>
class Vector
{
public:
    typedef T ArrayType[SIZE];
    typedef T Type;
    static const RF_Type::Size Count = SIZE;

    Vector()
    {
        for (RF_Type::Size i=0;i<SIZE;++i)
        Value[i]=0;
    }

    Vector(const Vector& Val)
    {
        RadonFramework::System::Memory::Copy(Value, Val.Value, sizeof(T)*SIZE);
    }

    Vector(const ArrayType& Values)
    {
        RadonFramework::System::Memory::Copy(Value, Values, sizeof(T)*SIZE);
    }

    Vector(T a)
    {
        //why you use a Vector of size zero ?
        static_assert(SIZE>=1,"Vector dimension isn't large enough");
        Value[0]=a;
        for (RF_Type::Size i=1;i<SIZE;++i)
            Value[i]=0;
    }

    Vector(T a, T b)
    {
        //if you get an error on this line you use to much parameter for a too small vector
        static_assert(SIZE>=2,"Vector dimension isn't large enough");
        Value[0]=a;
        Value[1]=b;
        for (RF_Type::Size i=2;i<SIZE;++i)
            Value[i]=0;
    }

    Vector(T a, T b, T c)
    {
        //if you get an error on this line you use to much parameter for a too small vector
        static_assert(SIZE>=3,"Vector dimension isn't large enough");
        Value[0]=a;
        Value[1]=b;
        Value[2]=c;
        for (RF_Type::Size i=3;i<SIZE;++i)
            Value[i]=0;
    }

    Vector(T a, T b, T c, T d)
    {
        //if you get an error on this line you use to much parameter for a too small vector
        static_assert(SIZE>=4,"Vector dimension isn't large enough");
        Value[0]=a;
        Value[1]=b;
        Value[2]=c;
        Value[3]=d;
        for (RF_Type::Size i=4;i<SIZE;++i)
            Value[i]=0;
    }

    ArrayType Value;

    Vector& operator =(const Vector& op)
    {
        Assert(this!=&op,"Self assignment is forbidden.");
        RadonFramework::System::Memory::Copy(Value, op.Value, sizeof(T)*SIZE);
        return *this;
    }

    T& operator [](RF_Type::Size Index)
    {
        Assert(Index<SIZE,"Index out of bounds.");
        return Value[Index];
    }

    T operator [](RF_Type::Size Index)const
    {
        Assert(Index<SIZE,"Index out of bounds.");
        return Value[Index];
    }

    //Vector operation with a vector
    #define Operation(_A_)\
        Vector operator _A_(const Vector& op)const{\
        Vector out(*this);\
        for (RF_Type::Size i=0;i<SIZE;++i)\
            out.Value[i] _A_##= op.Value[i];\
        return out;\
        }
    Operation(+)
    Operation(-)
    Operation(*)
    Operation(/)
    #undef Operation

    //Vector assign operation with a vector
    #define AssignOperator(_A_)\
        const Vector& operator _A_(const Vector& op){\
        for (RF_Type::Size i=0;i<SIZE;++i)\
            Value[i] _A_ op.Value[i];\
        return *this;\
        }
    AssignOperator(+=)
    AssignOperator(-=)
    AssignOperator(*=)
    AssignOperator(/=)
    #undef AssignOperator

    //Vector operation with single value
    #define Operation(_A_)\
        Vector operator _A_(const T op){\
        Vector out(*this);\
        for (RF_Type::Size i=0;i<SIZE;++i)\
            out.Value[i] _A_##=op;\
        return out;\
        }
    Operation(+)
    Operation(-)
    Operation(*)
    Operation(/)
    #undef Operation

    //Vector assign operation with single value
    #define AssignOperator(_A_)\
        const Vector& operator _A_(const T op){\
        for (RF_Type::Size i=0;i<SIZE;++i)\
            Value[i] _A_ op;\
        return *this;\
        }
    AssignOperator(+=)
    AssignOperator(-=)
    AssignOperator(*=)
    AssignOperator(/=)
    #undef AssignOperator

    #define CompareOperator(_A_)\
        const bool operator _A_(const Vector& op)const{\
        bool b=true;\
        for (RF_Type::Size i=0;i<SIZE;++i)\
            b=b && Value[i] _A_ op.Value[i];\
        return b;\
        }
    CompareOperator(==)
    CompareOperator(!=)
    #undef CompareOperator

    T Sum()const
    {
        T out=0;
        for (RF_Type::Size i=0;i<SIZE;++i)
        out+=Value[i];
        return out;
    }

    T Length()const
    {
        T out=0;
        for (RF_Type::Size i=0;i<SIZE;++i)
        out+=(Value[i]*Value[i]);
        return RF_Math::MathOfType<T>::Sqrt(out);
    }

    T Distance(const Vector &Other)const
    {
        return ((*this)-Other).Length();
    }

    Vector& Normalize()
    {
        T len=Length();
        for (RF_Type::Size i=0;i<SIZE;++i)
            Value[i]/=len;
        return *this;
    }

    static Vector Normalize(const Vector& Vec)
    {
        Vector vec(Vec);
        return vec.Normalize();
    }

    static Vector Min(const Vector& V1,const Vector& V2)
    {
        Vector v;
        for (RF_Type::Size i=0;i<SIZE;++i)
            v.Value[i]=V1.Value[i]<V2.Value[i]?V1.Value[i]:V2.Value[i];
        return v;
    }

    static Vector Max(const Vector& V1,const Vector& V2)
    {
        Vector v;
        for (RF_Type::Size i=0;i<SIZE;++i)
            v.Value[i]=V1.Value[i]>V2.Value[i]?V1.Value[i]:V2.Value[i];
        return v;
    }

    T DotProduct(const Vector& Vec)const
    {
        T alpha=0;
        for (RF_Type::Size i=0;i<SIZE;++i)
            alpha+=this->Value[i]*Vec.Value[i];
        return alpha;
    }

    Vector CrossProduct(const Vector& Vec)const
    {
        Vector v;
        int nextnext,next;
        for (RF_Type::Size i=0;i<SIZE;++i)
        {
            next=(i+1)%SIZE;
            nextnext=(i+2)%SIZE;
            v.Value[i]=Value[next]*Vec.Value[nextnext]-Value[nextnext]*Vec.Value[next];
        }
        return v;
    }

    void Negate()
    {
        for (RF_Type::Size i=0;i<SIZE;++i)
            Value[i]*=-1.0;
    }
};

typedef Vector<RF_Type::Float32,2> Vec2f;
typedef Vector<RF_Type::Float32,3> Vec3f;
typedef Vector<RF_Type::Float32,4> Vec4f;
      
}

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif // RF_MATH_GEOMETRY_VECTOR_HPP
