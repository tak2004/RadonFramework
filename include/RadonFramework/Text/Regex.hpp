#ifndef RF_TEXT_REGEX_HPP
#define RF_TEXT_REGEX_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Text {

class Regex
{
public:
    struct Matcher 
    {
        RF_Type::Size ID()const{return m_ID;}
    private:
        friend class Regex;
        RF_Type::Size m_ID = static_cast<RF_Type::Size>(-1);
        Matcher(RF_Type::Size ID):m_ID(ID){};
    };

    Regex(const RF_Type::String& Pattern);

    static RF_Type::Bool Matches(const RF_Type::String& Pattern,
                                 const RF_Type::String& Text);

    Matcher GenerateMatcher(const RF_Type::String& Text);
    RF_Type::Bool ReleaseMatcher(Matcher Instance);

    RF_Type::Bool Matches(Matcher Instance);
    RF_Type::Bool Replace(Matcher Instance, const RF_Type::String& ByText, 
                          RF_Type::String& Out);
    RF_Type::Bool Search(Matcher Instance);
private:
    RF_Idiom::PImpl<Regex> m_PImpl;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_TEXT
#define RF_SHORTHAND_NAMESPACE_TEXT
namespace RF_Text = RadonFramework::Text;
#endif

#endif // RF_TEXT_REGEX_HPP