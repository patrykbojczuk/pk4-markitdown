#ifndef TRIM_H
#define TRIM_H

#include <string>
#include <string_view>

std::wstring_view wsv_rtrim(std::wstring_view sv, std::wstring chars = L"\t\n\v\f\r ");

std::wstring_view wsv_ltrim(std::wstring_view sv, std::wstring chars = L"\t\n\v\f\r ");

std::wstring_view wsv_trim(std::wstring_view sv, std::wstring chars = L"\t\n\v\f\r ");

#endif //TRIM_H
