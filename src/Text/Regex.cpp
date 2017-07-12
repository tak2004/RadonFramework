#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/Regex.hpp"
#include "RadonFramework/Collections/HashMap.hpp"
#include "RadonFramework/Collections/AutoVector.hpp"

#include <regex>

struct MatcherObject
{
    std::smatch m_Matches;
    std::string m_Text;
};

namespace RadonFramework::Core::Idioms {
template<>
struct RF_Idiom::PImpl<RF_Text::Regex>::Data
{
    RF_Collect::HashMap<RF_Type::Size, MatcherObject*> m_MatcherLookup;
    RF_Collect::AutoVector<MatcherObject> m_Matcher;
    std::regex m_Pattern;
};
}

namespace RadonFramework::Text {

Regex::Regex(const RF_Type::String& Pattern)
{
    std::regex pattern(Pattern.c_str(), std::regex::optimize | std::regex::ECMAScript);
    m_PImpl->m_Pattern.swap(pattern);
}

RF_Type::Bool Regex::Matches(const RF_Type::String& Pattern, const RF_Type::String& Text)
{
    Regex regex(Pattern);
    Matcher matcher = regex.GenerateMatcher(Text);
    return regex.Matches(matcher);
}

RF_Type::Bool Regex::Matches(Matcher Instance)
{
    RF_Type::Bool result = false;
    if(m_PImpl->m_MatcherLookup.ContainsKey(Instance.ID()))
    {
        auto* matcher = m_PImpl->m_MatcherLookup[Instance.ID()];
        return std::regex_match(matcher->m_Text, matcher->m_Matches, m_PImpl->m_Pattern);
    }
    return result;
}

Regex::Matcher Regex::GenerateMatcher(const RF_Type::String& Text)
{
    RF_Mem::AutoPointer<MatcherObject> matcher(new MatcherObject);
    RF_Type::Size id = reinterpret_cast<RF_Type::Size>(matcher.Get());

    m_PImpl->m_MatcherLookup[id] = matcher.Get();
    matcher->m_Text = Text.c_str();
    m_PImpl->m_Matcher.PushBack(matcher);

    return Regex::Matcher(id);
}


RF_Type::Bool Regex::ReleaseMatcher(Matcher Instance)
{
    RF_Type::Bool result = false;
    if(m_PImpl->m_MatcherLookup.ContainsKey(Instance.ID()))
    {
        auto* matcher = m_PImpl->m_MatcherLookup[Instance.ID()];
        for(RF_Type::Size i = 0; i < m_PImpl->m_Matcher.Count(); ++i)
        {
            if(m_PImpl->m_Matcher[i] == matcher)
            {
                m_PImpl->m_MatcherLookup.Erase(Instance.ID());
                m_PImpl->m_Matcher.Erase(i);
                break;
            }
        }
        
        result = true;
    }
    return result;
}


RF_Type::Bool Regex::Replace(Matcher Instance, const RF_Type::String& ByText, RF_Type::String& Out)
{
    RF_Type::Bool result = false;
    if(m_PImpl->m_MatcherLookup.ContainsKey(Instance.ID()))
    {
        auto* matcher = m_PImpl->m_MatcherLookup[Instance.ID()];
        std::string str = std::regex_replace(matcher->m_Text.c_str(), m_PImpl->m_Pattern, ByText.c_str());
        Out = RF_Type::String(str.c_str(), str.size());
        result = true;
    }
    return result;
}

RF_Type::Bool Regex::Search(Matcher Instance)
{
    RF_Type::Bool result = false;
    if(m_PImpl->m_MatcherLookup.ContainsKey(Instance.ID()))
    {
        auto* matcher = m_PImpl->m_MatcherLookup[Instance.ID()];
        if(!matcher->m_Matches.empty())
            matcher->m_Text = matcher->m_Matches.suffix().str();
        result = std::regex_search(matcher->m_Text, matcher->m_Matches, m_PImpl->m_Pattern);
        if(!result)
            matcher->m_Matches = std::smatch();
    }
    return result;
}

RF_Type::Bool Regex::GetMatches(Matcher Instance, RF_Collect::Array<RF_Type::String>& Out)
{
    RF_Type::Bool result = false;
    if(m_PImpl->m_MatcherLookup.ContainsKey(Instance.ID()))
    {
        auto* matcher = m_PImpl->m_MatcherLookup[Instance.ID()];
        Out.Resize(matcher->m_Matches.size());
        for(RF_Type::Size i = 0; i < matcher->m_Matches.size(); ++i)
        {
            std::string str = matcher->m_Matches[i].str();
            Out(i) = RF_Type::String(str.c_str(), str.size());
        }
        result = true;
    }
    return result;
}

}