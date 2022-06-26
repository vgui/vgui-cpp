#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <vgui/Exception.hpp>


namespace vgui
{

/**
    The vgui::unique_vector container class have unique elements as std::set and random access to elements as std::vector.
    If a new element is inserted with the value existing in the container, but with a different index,
    the existing item is moved to the new index, and if the new index is equal to the old one, nothing is done.
    If a new element is inserted with index more than size of container, vgui::Exception will be throws.
    This class can be used to implement Tree class, TreeView class, DOM class and similar but with unique elements.
*/
template<typename T>
class unique_vector
{
public:

    using vector_type = std::vector<T>;
    using pointer = typename vector_type::pointer;
    using const_pointer = typename vector_type::const_pointer;
    using value_type = typename vector_type::value_type;
    using reference = typename vector_type::reference ;
    using const_reference = typename vector_type::const_reference;
    using iterator = typename vector_type::iterator;
    using const_iterator= typename vector_type::const_iterator;
    using reverse_iterator = typename vector_type::reverse_iterator;
    using const_reverse_iterator = typename vector_type::const_reverse_iterator;
    using size_type = typename vector_type::size_type;

    iterator begin()
    {
        return m_vec.begin();
    }

    const_iterator begin() const
    {
        return m_vec.begin();
    }

    iterator end()
    {
        return m_vec.end();
    }

    const_iterator end() const
    {
        return m_vec.end();
    }

    size_type size() const
    {
        return m_vec.size();
    }

    reference operator[](size_type index)
    {
        return m_vec.at(index);
    }

    const_reference operator[](size_type index) const
    {
        return m_vec.at(index);
    }

    /**
        Find the value in the vector and return its index.
    */
    size_t find(const value_type& value) const
    {
        iterator i = std::find(m_vec.begin(), m_vec.end(), value);

        if(i == m_vec.end())
            return -1;
        else
            return i - m_vec.begin();
    }

    /**
        Insert a value at the specified index.
        If the index is greater than the size of the container, raise an exception.
        If the specified index contains an equal value, return an iterator pointing to it.
        Otherwise, try to find a new value in the container.
        If missing, insert it at the specified index.
        If presented, move the old elements to insert a new one.

        @brief Insert value at specified index
        @param index
        @param value        
        @return Iterator pointing to the inserted value.
    */
    iterator insert(size_type index, const value_type& value)
    {
        size_t vec_size = m_vec.size();

        //We can insert in zero index with size()==0, i.e. new index may be equal to size of vector but no greater
        //if(index > vec_size)
            //throw ExceptionInfo << "The index " << index <<  " is too big for inserting. Vector size = " << size() << ".";
        //This checking is in the std::vector::insert

        //This line of code make guarantee of valid index(std::vector::at() method)
        if(index < vec_size && m_vec.at(index) == value)//old_index = index
            return m_vec.begin() + index;

        iterator oldi = std::find(m_vec.begin(), m_vec.end(), value);//iterator of equal old value

        if(oldi != m_vec.end())//value exist
        {
            if(index > vec_size - 1)
                throw ExceptionInfo << "Trying to insert an existing value on too big index. The index = "
                                    << index <<  ". Vector size = " << size() << ".";

            iterator newi = m_vec.begin() + index;//new iterator

            if(oldi < newi)
                std::move(oldi + 1, newi + 1, oldi);//move left
            else
                std::move_backward(newi, oldi , oldi + 1);//move right

            m_vec[index] = value;//copy value to the new place
            return m_vec.begin() + index;
        }
        else//insert new value
            return m_vec.insert(m_vec.begin() + index, value);
    }

    /**
        Erase the value by index.If the index is bigger than the vector size.
        @brief Erase the value by index.
        @param index
    */
    void erase(size_type index)
    {
        m_vec.erase(m_vec.begin() + index);
    }

    iterator push_back(const value_type& value)
    {
        return insert(size(), value);
    }

    void pop_back()
    {
        m_vec.pop_back();
    }

    void clear()
    {
        m_vec.clear();
    }

    /**
        Print the contents of a vector separated by the delimeter symbol, if the element type can be passed to std::to_string.
    */
    virtual void print(char delimeter, std::string_view str)
    {
        if constexpr(std::is_integral<T>::value)
        {
            for(auto v : m_vec)
                std::cout << std::to_string(v) << delimeter;

            if(str.length())
                std::cout << str << std::endl;
        }
    }

private:

    vector_type m_vec;
};//class unique_vector

}//namespace vgui
