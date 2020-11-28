#pragma once
#ifndef _Data_HPP_
#define _Data_HPP_

class Data
{
private:
    int m_data;

public:
    Data(int a = 0) : m_data(a) {}

    inline void set_data(int a) { m_data = a; }

    inline int data() { return m_data; }
};

#endif /* _Data_HPP_ */