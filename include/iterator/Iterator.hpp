#pragma once
#ifndef _Iterator_HPP_
#define _Iterator_HPP_

#include <vector>

namespace iterator
{

    /// \class Iterator
    /// \brief Class which can use iterators to move through the contents of its container.
    template <typename T, typename U>
    class Iterator
    {
    public:
        typedef typename std::vector<T>::iterator iter_type;
        /// \brief Constructor.
        Iterator(U *p_data, bool reverse = false) : m_p_data(p_data) { m_it = m_p_data->m_data.begin(); };

        /// \brief Set the iterator to point to the first element in the vector.
        void first() { m_it = m_p_data->m_data.begin(); }

        /// \brief Set the iterator to the next element in the vector.
        void next() { m_it++; };

        /// \brief Set the iterator to the element past the end of the sequence.
        inline bool isDone() { return (m_it == m_p_data->m_data.end()); };

        /// \brief Return the current element.
        inline iter_type current() { return m_it; };

    private:
        U *m_p_data; /*!< A pointer to the data of the container. */

        iter_type m_it; /*!< The vector iterator. */
    };

} // namespace iterator

#endif /* _Iterator_HPP_ */