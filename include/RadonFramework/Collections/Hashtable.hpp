#ifndef RF_HASHTABLE_HPP
#define RF_HASHTABLE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
  namespace Collections
  {
// TODO (Thomas#1#): improve the performance by changing the hashing
    //simple hashtable
    class Hashtable
    {/*
      struct Slot{
        Object* Key;
        Object* Value;
      };

      protected:
        Slot m_List[];
        void CheckRange(const unsigned int Index){
          if (Index>=L)
            throw ArgumentOutOfRangeException();
        }
        unsigned int Hash(const unsigned int Value){
          return Value%L;
        }
      public:
        Hashtable(const unsigned int Size);
        void Add(const Object *Key, const Object *Data){
          unsigned int key=Hash(HashValue);
          for (unsigned int i=0;i<m_List[key].Count();i++)
            if (m_List[key][i]==Data)
              return;
          m_List[key].Add(Data);
        }
        Object* Get(const Object *Key){
          unsigned int key=Hash(HashValue);
          int firsthit=-1;
          //look for first element with the hashvalue
          for (unsigned int i=0;i<m_List[key].Count();i++)
            if (m_Lists[key][i]==HashValue)
            {
              firsthit=i;
              break;
            }
          //no element was found with the hashvalue
          if (firsthit==-1)
            return 0;

        }
        void Remove(const Object *Key);
        unsigned int Count();
        Object* Item(const unsigned int Index);*/
    };
  }
}

#endif
