#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<codecvt>


string UnicodeToUTF8(const wstring& wstr)
{

    string ret;
    try {

        wstring_convert< codecvt_utf8<wchar_t> > wcv;
        ret = wcv.to_bytes(wstr);
    }
    catch (const exception& e) {

        cerr << e.what() << endl;
    }
    return ret;
}

wstring UTF8ToUnicode(const string& str)
{
    wstring ret;
    try {
        wstring_convert< codecvt_utf8<wchar_t> > wcv;
        ret = wcv.from_bytes(str);
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return ret;
}

string UnicodeToANSI(const wstring& wstr)
{

    string ret;
    mbstate_t state = {
    };
    const wchar_t* src = wstr.data();
    size_t len = wcsrtombs(nullptr, &src, 0, &state);
    if (static_cast<size_t>(-1) != len) {

        unique_ptr< char[] > buff(new char[len + 1]);
        len = wcsrtombs(buff.get(), &src, len, &state);
        if (static_cast<size_t>(-1) != len) {

            ret.assign(buff.get(), len);
        }
    }
    return ret;
}
//编译器码（GBK）转UTF-8
std::string StringToUTF8(const std::string& gbkData)
{
    const char* GBK_LOCALE_NAME = "CHS";  //GBK在windows下的locale name(.936, CHS ), linux下的locale名可能是"zh_CN.GBK"

    std::wstring_convert<std::codecvt<wchar_t, char, mbstate_t>>
        conv(new std::codecvt<wchar_t, char, mbstate_t>(GBK_LOCALE_NAME));
    std::wstring wString = conv.from_bytes(gbkData);    // string => wstring

    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::string utf8str = convert.to_bytes(wString);     // wstring => utf-8

    return utf8str;
}

//UTF8转编译器码（GBK）
std::string UTF8ToString(const std::string& utf8Data)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::wstring wString = conv.from_bytes(utf8Data);    // utf-8 => wstring

    std::wstring_convert<std::codecvt< wchar_t, char, std::mbstate_t>>
        convert(new std::codecvt< wchar_t, char, std::mbstate_t>("CHS"));
    std::string str = convert.to_bytes(wString);     // wstring => string

    return str;
}
