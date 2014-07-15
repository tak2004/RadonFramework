#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/HTTP/Tokenizer.hpp"

using namespace RadonFramework::Net::HTTP;

Tokenizer::Element Tokenizer::lookup[] = {
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