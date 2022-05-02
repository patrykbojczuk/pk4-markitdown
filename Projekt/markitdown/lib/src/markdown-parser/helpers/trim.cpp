#include <string_view>
#include <iostream>
#include "trim.h"

using namespace std::string_view_literals;

template<typename _CharT, typename _Traits = std::char_traits<_CharT>>
auto rtrim(std::basic_string_view<_CharT, _Traits> sv,
           std::basic_string<_CharT, _Traits> chars) {
    auto lNO = sv.find_last_not_of(chars);
    if (lNO != std::string_view::npos) {
        sv.remove_suffix(std::min(sv.length() - (lNO + 1), sv.length()));
    }

    return sv;
}

template<typename _CharT, typename _Traits = std::char_traits<_CharT>>
auto ltrim(std::basic_string_view<_CharT, _Traits> sv,
           std::basic_string<_CharT, _Traits> chars) {
    sv.remove_prefix(std::min(sv.find_first_not_of(chars), sv.length()));

    return sv;
}

template<typename _CharT, typename _Traits = std::char_traits<_CharT>>
auto trim(std::basic_string_view<_CharT, _Traits> sv,
          std::basic_string<_CharT, _Traits> chars) {
    return rtrim(ltrim(sv, chars), chars);
}

std::wstring_view wsv_rtrim(std::wstring_view sv, std::wstring chars) {
    return rtrim(sv, chars);
}

std::wstring_view wsv_ltrim(std::wstring_view sv, std::wstring chars) {
    return ltrim(sv, chars);
}

std::wstring_view wsv_trim(std::wstring_view sv, std::wstring chars) {
    return trim(sv, chars);
}
