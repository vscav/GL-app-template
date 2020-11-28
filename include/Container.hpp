#pragma once
#ifndef _Container_HPP_
#define _Container_HPP_

#include <vector>
#include "./Iterator.hpp"

/// \class Container
/// \brief Class that represents the collection (data) and provides several methods for retrieving
/// fresh iterator instances.
template <class T>
class Container
{
    friend class Iterator<T, Container>; /*!< The Iterator class as a friend class. */

private:
    std::vector<T> m_data; /*!< The vector of data (type T). */

public:
    /// \brief Add a value to the container.
    /// \param a : The value to add to the container.
    inline void add(T a) { m_data.push_back(a); };

    /// \brief Return the size of the container.
    inline int size() const { return m_data.size(); };

    /// \brief Return the value hold by the container at a given index.
    inline T at(unsigned int index) { return m_data.at(index); };

    /// \brief Return a pointer to the first element in the array used internally by the container.
    inline const T *data() const { return m_data.data(); };

    /// \brief Create a new Iterator based on the container.
    inline Iterator<T, Container> *CreateIterator() { return new Iterator<T, Container>(this); };
};

#endif /* _Container_HPP_ */