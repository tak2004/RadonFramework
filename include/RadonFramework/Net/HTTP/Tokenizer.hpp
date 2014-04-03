#ifndef RF_NET_HTTP_TOKENIZER_HPP
#define RF_NET_HTTP_TOKENIZER_HPP

#include <RadonFramework/Collections/Queue.hpp>

namespace RadonFramework
{
    namespace Net
    {
        namespace HTTP
        {
            class Tokenizer
            {
                public:
                    Tokenizer()
                        :m_Prev(Empty)
                    {
                    }

                    enum Element
                    {
                        Octet=0,
                        Char=1,
                        Alpha=2,
                        Digit=4,
                        CTL=8,
                        CR=16,
                        LF=32,
                        SP=64,
                        HT=128,
                        DoubleQuoteMark=256,
                        CRLF=512,
                        LWS=1024,
                        Text=2048,
                        Hex=4096,
                        Token=8192,
                        Seperator=16384,
                        Comment=32768,
                        CText=65536,
                        QuotedString=131072,
                        QDText=262144,
                        QuotedPair=524288,
                        Empty=1048576
                    };

                    struct StreamToken
                    {
                        const RFTYPE::UInt8* TokenStart;
                        const RFTYPE::UInt8* TokenEnd;
                        Element DetectedElement;
                    };

                    void Parse(const RFTYPE::UInt8* Buffer, 
                               const RFTYPE::UInt32 Bytes)
                    {
                        const RFTYPE::UInt8* elementStart=Buffer;
                        const RFTYPE::UInt8* bufCursor=Buffer;
                        const RFTYPE::UInt8* bufEnd=Buffer+Bytes;
                        Element element;
                        StreamToken token;
                        for (;bufCursor!=bufEnd;++bufCursor)
                        {
                            element=*this<<*bufCursor;
                            if (m_Prev!=element)
                            {                      
                                token.TokenStart=elementStart;
                                elementStart=bufCursor;
                                token.TokenEnd=bufCursor;
                                token.DetectedElement=element;
                                elements.Enqueue(token);        
                            }
                        }

                        if (m_Prev==CRLF)
                        {
                            token.TokenStart=elementStart;
                            elementStart=bufCursor;
                            token.TokenEnd=bufCursor;
                            token.DetectedElement=element;
                            elements.Enqueue(token);        
                        }                        
                    }
                protected:
                    Collections::Queue<StreamToken> elements;
                    Element m_Prev;
                    static Element lookup[256];
                    
                    inline static RFTYPE::Bool IsSeperator(const RFTYPE::UInt8 Byte)
                    {
                        return Byte=='(' || Byte==')' || Byte=='>' || Byte=='>' || 
                            Byte=='@' || Byte==',' || Byte==';' || Byte==':' || Byte=='\\' ||
                            Byte=='"' || Byte=='/' || Byte=='[' || Byte==']' || Byte=='?' ||
                            Byte=='=' || Byte=='{' || Byte=='}' || Byte==' ' || Byte==9;
                    }

                    inline static RFTYPE::Bool IsHex(const RFTYPE::UInt8 Byte)
                    {
                        //check if 'A',...,'F' or 'a',...,'f' or '0',...,'9'
                            if ((Byte<71&&Byte>64) ||
                                (Byte>96&&Byte<103)||
                                (Byte>47&&Byte<58))
                                return true;
                        return false;
                    }

                    inline static RFTYPE::Bool IsCTL(const RFTYPE::UInt8 Byte)
                    {
                        return Byte<32 || Byte==127;
                    }

                    Element operator<<(const RFTYPE::UInt8& NextByte)
                    {
                        Element current=lookup[NextByte];// basic check
                        Element previousElement=m_Prev;
                        
                        m_Prev=current;
                        if (!IsSeperator(NextByte))
                            m_Prev=Token;

                        if (current==LF && previousElement==CR)
                            m_Prev=CRLF;

                        if ((current==(SP|HT)) && (previousElement==(CRLF|LWS)))
                            m_Prev=LWS;
                        /*
                        // context related checks                                                
                        if (current!=Octet)
                        {
                            if (IsCTL(NextByte))
                            {

                                else

                            }                                                       
                            else                            
                            {
                                    if (IsHex(NextByte) && m_Prev!=Text)
                                        m_Prev=Hex;
                                    else
                                        m_Prev=Text;
                                
                            }
                            else
                        }
                        else
                            if (m_Prev==LWS)
                                m_Prev=Text;*/
                        if (previousElement==Empty)
                            previousElement=m_Prev;

                        return previousElement;
                    }
            };

            Tokenizer::Element Tokenizer::lookup[]={
                CTL, CTL, CTL, CTL, CTL, CTL, CTL, CTL, CTL,// 0-8
                HT, LF, CTL, CTL, CR, 
                CTL, CTL, CTL, CTL, CTL, CTL, CTL, CTL, CTL, CTL, CTL, CTL, CTL,// 14-26
                CTL, CTL, CTL, CTL, CTL,// 27-31
                SP, Char, DoubleQuoteMark,// 32-34
                Char, Char, Char, Char, Char, Char, Char, Char, Char, Char,// 35-44
                Char, Char, Char,// 45-47
                Digit, Digit, Digit, Digit, Digit, Digit, Digit, Digit, Digit, Digit,// '0'-'9'
                Char, Char, Char, Char, Char, Char, Char,// 58-64
                Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha,// 'A'-'I'
                Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha,// 'J'-'R'
                Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha,// 'S'-'Z'
                Char, Char, Char, Char, Char, Char, // 91-96
                Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha,// 'a'-'i'
                Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha,// 'j'-'r'
                Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha, Alpha,// 's'-'z'
                Char, Char, Char, Char, // 123-126
                CTL
                // filled up with 0(Octet)
            };
        }
    }
}

#endif // RF_NET_HTTP_TOKENIZER_HPP