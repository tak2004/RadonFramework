#ifndef RF_MATH_GEOMETRY_NORMAL_HPP
#define RF_MATH_GEOMETRY_NORMAL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>

namespace RadonFramework::Math::Geometry
{
template <typename T, RF_Type::Size SIZE>
class Normal
{
public:
  typedef T ArrayType[SIZE];
  Normal()
  {
    for(RF_Type::Size i = 0; i < SIZE - 1; ++i)
      m_Value[i] = 0;
    m_Value[SIZE - 1] = 1;
  }

  Normal(const Normal& Val)
  {
    RadonFramework::System::Memory::Copy(m_Value, Val.m_Value,
                                         sizeof(T) * SIZE);
  }

  using Type = T;
  static const RF_Type::Size Count = SIZE;

  Normal& operator=(const Normal& op)
  {
    RF_ASSERT(this != &op, "Self assignment is forbidden.");
    RadonFramework::System::Memory::Copy(m_Value, op.m_Value, sizeof(T) * SIZE);
    return *this;
  }

  T operator[](RF_Type::Size Index) const
  {
    RF_ASSERT(Index < SIZE, "Index out of bounds.");
    return m_Value[Index];
  }

  T Get(RF_Type::Size Index) const
  {
    RF_ASSERT(Index < SIZE, "Index out of bounds.");
    return m_Value[Index];
  }

  const ArrayType& GetArray() const { return m_Value; }

  RF_Type::Bool Set(const RF_Type::Size Index, const T Value)
  {
    RF_Type::Bool result = false;
    if(Value != 0 && Index < SIZE)
    {
      m_Value[Index] = Value;
      result = true;
    }
    else
    {
      if(Index < SIZE)
      {
        if(Sum() - Value != 0)
        {
          m_Value[Index] = Value;
          result = true;
        }
      }
    }
    return result;
  }

// Normal operation with a Normal
#define Operation(_A_)                        \
  Normal operator _A_(const Normal& op) const \
  {                                           \
    Normal out(*this);                        \
    for(RF_Type::Size i = 0; i < SIZE; ++i)   \
      out.m_Value[i] _A_## = op.m_Value[i];   \
    return out;                               \
  }
  Operation(+) Operation(-) Operation(*) Operation(/)
#undef Operation

// Normal assign operation with a Normal
#define AssignOperator(_A_)                    \
  const Normal& operator _A_(const Normal& op) \
  {                                            \
    for(RF_Type::Size i = 0; i < SIZE; ++i)    \
      m_Value[i] _A_ op.m_Value[i];            \
    return *this;                              \
  }
      AssignOperator(+=) AssignOperator(-=) AssignOperator(*=)
          AssignOperator(/=)
#undef AssignOperator

// Normal operation with single value
#define Operation(_A_)                      \
  Normal operator _A_(const T op) const     \
  {                                         \
    Normal out(*this);                      \
    for(RF_Type::Size i = 0; i < SIZE; ++i) \
      out.m_Value[i] _A_## = op;            \
    return out;                             \
  }
              Operation(+) Operation(-) Operation(*) Operation(/)
#undef Operation

// Normal assign operation with single value
#define AssignOperator(_A_)                 \
  const Normal& operator _A_(const T op)    \
  {                                         \
    for(RF_Type::Size i = 0; i < SIZE; ++i) \
      m_Value[i] _A_ op;                    \
    return *this;                           \
  }
                  AssignOperator(+=) AssignOperator(-=) AssignOperator(*=)
                      AssignOperator(/=)
#undef AssignOperator

#define CompareOperator(_A_)                      \
  const bool operator _A_(const Normal& op) const \
  {                                               \
    bool b = true;                                \
    for(RF_Type::Size i = 0; i < SIZE; ++i)       \
      b = b && m_Value[i] _A_ op.m_Value[i];      \
    return b;                                     \
  }
                          CompareOperator(==) CompareOperator(!=)
#undef CompareOperator

                              T Sum() const
  {
    T out = 0;
    for(RF_Type::Size i = 0; i < SIZE; ++i)
      out += m_Value[i];
    return out;
  }

  T Length() const
  {
    T out = 0;
    for(RF_Type::Size i = 0; i < SIZE; ++i)
      out += (m_Value[i] * m_Value[i]);
    return RF_Math::MathOfType<T>::Sqrt(out);
  }

  Normal& Normalize()
  {
    T len = Length();
    for(RF_Type::Size i = 0; i < SIZE; ++i)
      m_Value[i] /= len;
    return *this;
  }

  void Negate()
  {
    for(RF_Type::Size i = 0; i < SIZE; ++i)
      m_Value[i] *= -1.0;
  }

protected:
  ArrayType m_Value;
};

using Norm2f = Normal<RF_Type::Float32, 2>;
using Norm3f = Normal<RF_Type::Float32, 3>;
using Norm4f = Normal<RF_Type::Float32, 4>;

}  // namespace RadonFramework::Math::Geometry

#ifndef RF_SHORTHAND_NAMESPACE_GEO
#define RF_SHORTHAND_NAMESPACE_GEO
namespace RF_Geo = RadonFramework::Math::Geometry;
#endif

#endif  // RF_MATH_GEOMETRY_NORMAL_HPP
