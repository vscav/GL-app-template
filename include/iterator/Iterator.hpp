#pragma once
#ifndef _Iterator_HPP_
#define _Iterator_HPP_

#include <vector>

template <typename T, typename U>
class Iterator
{
public:
    typedef typename std::vector<T>::iterator iter_type;
    Iterator(U *p_data, bool reverse = false) : m_p_data(p_data)
    {
        m_it = m_p_data->m_data.begin();
    }

    void first()
    {
        m_it = m_p_data->m_data.begin();
    }

    void next()
    {
        m_it++;
    }

    bool isDone()
    {
        return (m_it == m_p_data->m_data.end());
    }

    iter_type current()
    {
        return m_it;
    }

private:
    U *m_p_data;

    iter_type m_it;
};

#endif /* _Iterator_HPP_ */