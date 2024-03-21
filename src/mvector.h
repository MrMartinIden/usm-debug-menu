#pragma once

template<typename T>
struct mVector {
    int field_0;
    int m_size;
    T **m_data;
    int field_C;
    bool field_10;

    struct iterator {
        T **_Ptr;

        bool operator==(const iterator &it) const
        {
            return _Ptr == it._Ptr;
        }

        bool operator!=(const iterator &it) const
        {
            return _Ptr != it._Ptr;
        }

        void operator++()
        {
            ++this->_Ptr;
        }

        auto &operator*()
        {
            return (*this->_Ptr);
        }

        auto &operator*() const
        {
            return (*this->_Ptr);
        }
    };

    auto begin()
    {
        if (this->m_data != nullptr)
        {
            return iterator {this->m_data};
        }

        return iterator {nullptr};
    }

    auto begin() const
    {
        if (this->m_data != nullptr)
        {
            return iterator {this->m_data};
        }

        return iterator {nullptr};
    }

    auto end()
    {
        if (this->m_data != nullptr)
        {
            return iterator {&this->m_data[this->m_size]};
        }

        return iterator {nullptr};
    }

    auto end() const
    {
        if (this->m_data != nullptr)
        {
            return iterator {&this->m_data[this->m_size]};
        }

        return iterator {nullptr};
    }
};
