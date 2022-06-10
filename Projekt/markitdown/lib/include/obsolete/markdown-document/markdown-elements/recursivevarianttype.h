#ifndef RECURSIVEVARIANTTYPE_H
#define RECURSIVEVARIANTTYPE_H

#include <memory>

template<class T>
using Recursive = std::shared_ptr<T>;

template<class T, typename... _Args>
Recursive<T> make_recursive(_Args &&... __args) {
    return std::make_shared<T>(std::forward<_Args>(__args)...);
}

#endif //RECURSIVEVARIANTTYPE_H
