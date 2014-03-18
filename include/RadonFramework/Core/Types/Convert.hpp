                                                                                                                                                                                                                        #ifndef RF_CORE_TYPES_CONVERT_HPP
#define RF_CORE_TYPES_CONVERT_HPP

#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework { namespace Core { namespace Types {
    struct Convert
    {
        static Bool ToBool(const bool Value);

        /** This Function will be return true if the In parameter
            * contains a valid boolean value and can be written to
            * Out else it return false.
            */
        static Bool ToBool(const String& In, Bool& Out);

        /** This Function will be return true if the In parameter
            * contains a valid Int8 value and can be written to
            * Out else it return false.
            */
        static Bool ToInt8(const String& In, Int8& Out);

        /** This Function will be return true if the In parameter
            * contains a valid Int16 value and can be written to
            * Out else it return false.
            */
        static Bool ToInt16(const String& In, Int16& Out);

        /** This Function will be return true if the In parameter
            * contains a valid Int32 value and can be written to
            * Out else it return false.
            */
        static Bool ToInt32(const String& In, Int32& Out);

        /** This Function will be return true if the In parameter
            * contains a valid Int64 value and can be written to
            * Out else it return false.
            */
        static Bool ToInt64(const String& In, Int64& Out);

        /** This Function will be return true if the In parameter
            * contains a valid UInt8 value and can be written to
            * Out else it return false.
            */
        static Bool ToUInt8(const String& In, UInt8& Out);

        /** This Function will be return true if the In parameter
            * contains a valid UInt16 value and can be written to
            * Out else it return false.
            */
        static Bool ToUInt16(const String& In, UInt16& Out);

        /** This Function will be return true if the In parameter
            * contains a valid UInt32 value and can be written to
            * Out else it return false.
            */
        static Bool ToUInt32(const String& In, UInt32& Out);

        /** This Function will be return true if the In parameter
            * contains a valid UInt64 value and can be written to
            * Out else it return false.
            */
        static Bool ToUInt64(const String& In, UInt64& Out);

        /** This Function will be return true if the In parameter
            * contains a valid Float32 value and can be written to
            * Out else it return false.
            */
        static Bool ToFloat32(const String& In, Float32& Out);

        /** This Function will be return true if the In parameter
            * contains a valid Float64 value and can be written to
            * Out else it return false.
            */
        static Bool ToFloat64(const String& In, Float64& Out);

        /** This Function will be return true if the In parameter
            * contains a valid Size value and can be written to
            * Out else it return false.
            */
        static Bool ToSize(const String& In, Size& Out);

        static String ToString(const Bool Value);

        static String ToString(const Int8 Value);

        static String ToString(const Int16 Value);

        static String ToString(const Int32 Value);

        static String ToString(const Int64 Value);

        static String ToString(const UInt8 Value);

        static String ToString(const UInt16 Value);

        static String ToString(const UInt32 Value);

        static String ToString(const UInt64 Value);

        static String ToString(const Float32 Value);

        static String ToString(const Float64 Value);


        template<typename T>
        static Bool StringTo(const String& In, T& Out)
        {
            return false;
        }

        #define STRING_TO(T, COMPARE_OPERATOR, CONVERT_FUNCTION) template<>\
        Bool Convert::StringTo<T>(const String& In, T& Out)\
        {\
            Bool result = false; \
            if (In.COMPARE_OPERATOR())\
                result = CONVERT_FUNCTION(In, Out); \
            return result;\
        }

        STRING_TO(Bool, IsBoolean, ToBool)
        STRING_TO(Int8, IsNumber, ToInt8)
        STRING_TO(Int16, IsNumber, ToInt16)
        STRING_TO(Int32, IsNumber, ToInt32)
        STRING_TO(Int64, IsNumber, ToInt64)
        STRING_TO(UInt8, IsNumber, ToUInt8)
        STRING_TO(UInt16, IsNumber, ToUInt16)
        STRING_TO(UInt32, IsNumber, ToUInt32)
        STRING_TO(UInt64, IsNumber, ToUInt64)
        STRING_TO(Float32, IsFloatingpointNumber, ToFloat32)
        STRING_TO(Float64, IsFloatingpointNumber, ToFloat64)

        #undef STRING_TO
    };
} } }
#endif // RF_CORE_TYPES_CONVERT_HPP