#pragma once
#ifndef _Container_HPP_
#define _Container_HPP_

#include <vector>
#include "./Iterator.hpp"

template <class T>
class Container
{

    friend class Iterator<T, Container>;

private:
    std::vector<T> m_data;

public:
    void Add(T a)
    {
        m_data.push_back(a);
    }

    Iterator<T, Container> *CreateIterator()
    {
        return new Iterator<T, Container>(this);
    }
};

#endif /* _Container_HPP_ */