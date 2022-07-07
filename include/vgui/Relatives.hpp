#pragma once

#include <algorithm>
#include <vector>

#include "Exception.hpp"
#include "unique_vector.hpp"


namespace vgui
{
//CRTP class like a tree for widgets, DOM and so on
template<typename T>
class Relatives
{
public:

    using ptr_type = T*;
    using const_ptr_type = const ptr_type;
    using vector_type = vgui::unique_vector<ptr_type>;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = typename vector_type::size_type;
    static constexpr size_type MaxIndex { std::numeric_limits<size_type>::max() };

    Relatives() = default;

    ~Relatives()
    {
        ClearChildren();
    }

    ptr_type Parent() const
    {
        return m_parent;
    }

    size_type ChildIndex() const
    {
        return m_childindex;
    }

    reference Child(size_type index)
    {
        return *m_children[index];
    }

    size_type Childs()
    {
        return m_children.size();
    }

    size_type Siblings()
    {
        if(Parent())
            return Parent()->Childs();
        else
            return 0;
    }

    reference Sibling(size_type index)
    {
        return Parent()->Child(index);
    }

    ptr_type PrevSibling()
    {
        size_type childindex = ChildIndex();

        if(childindex != MaxIndex && childindex > 0)
            return &Parent()->Child(childindex - 1);
        else
            return nullptr;
    }

    ptr_type NextSibling()
    {
        size_type childindex = ChildIndex();

        if(childindex != MaxIndex && childindex + 1 < Parent()->Childs())
            return &Parent()->Child(childindex +1);
        else
            return nullptr;
    }

    reference SetParent(ptr_type newparent, size_type newchildindex = MaxIndex)
    {
        OnParentChanging(newparent, newchildindex);

        ptr_type parent = Parent();

        if(parent)
        {
            if(newchildindex == MaxIndex)
                newchildindex = Childs();

            if(parent == newparent && m_childindex != newchildindex)
            {
                SetChildIndex(newchildindex);
                OnParentChanged(newparent, newchildindex);
                return Derived();
            }

            parent->RemoveChild(ChildIndex());
            //Now don't have parent.
        }

        if(newparent)
            newparent->Relatives<T>::InsertChild(Derived(), newchildindex);

        OnParentChanged(newparent, newchildindex);
        return Derived();
    }

    reference SetChildIndex(size_type newchildindex = MaxIndex)
    {
        OnChildIndexChanging(newchildindex);

        ptr_type parent = Parent();

        if(!parent)
            throw ExceptionInfo << "The child must have a parent to change the index.";

        if(newchildindex == MaxIndex)
            newchildindex = Childs();

        if(parent->m_children[m_childindex] != &Derived())
            throw ExceptionInfo << "Current child index is not correct.";

        parent->Relatives<T>::InsertChild(Derived(), newchildindex);

        OnChildIndexChanged(newchildindex);
        return Derived();
    }

    reference InsertChild(reference child, size_type newchildindex = MaxIndex)
    {
        OnInsertChild(child, newchildindex);

        ptr_type parentofchild = child.Parent();

        //Child have other parent
        if(parentofchild && parentofchild != this)
            parentofchild->RemoveChild(child);

        //Insert to the end
        if(newchildindex == MaxIndex)
            newchildindex = Childs();

        //Insert and update
        m_children.insert(newchildindex, &child);
        UpdateChildren();

        OnChildInserted(child, newchildindex);
        return Derived();
    }

    reference RemoveChild(size_type childindex)
    {
        OnRemoveChild(childindex);

        if(childindex >= Childs())
            throw ExceptionInfo << "Removing child with too large index.";

        ptr_type child = m_children[childindex];
        child->m_parent = nullptr;
        child->m_childindex = MaxIndex;
        m_children.erase(childindex);
        UpdateChildren();

        OnChildRemoved(childindex);
        return Derived();
    }

    reference RemoveChild(reference child)
    {
        size_type childindex = child.ChildIndex();
        RemoveChild(childindex);
        return Derived();
    }

    reference ClearChildren()
    {
        OnClearChildren();

        for(size_type i = 0; i < m_children.size(); ++i)
        {
            m_children[i]->ClearChildren();
            m_children[i]->m_parent = nullptr;
            m_children[i]->m_childindex = MaxIndex;
        }

        m_children.clear();

        OnChildrenCleared();
        return Derived();
    }

protected:

    virtual void OnParentChanging(ptr_type newparent, size_type& newchildindex){}
    virtual void OnParentChanged(ptr_type newparent, size_type newchildindex){}
    virtual void OnChildIndexChanging(size_type& newchildindex){}
    virtual void OnChildIndexChanged(size_type newchildindex){}
    virtual void OnInsertChild(reference child, size_type& newchildindex){}
    virtual void OnChildInserted(reference child, size_type newchildindex){}
    virtual void OnRemoveChild(size_type& childindex){}
    virtual void OnChildRemoved(size_type childindex){}
    virtual void OnClearChildren(){}
    virtual void OnChildrenCleared(){}

private:

    ptr_type m_parent {nullptr};
    size_type m_childindex { MaxIndex };
    vector_type m_children;

    void UpdateChildren()
    {
        for(size_type i = 0; i < m_children.size(); ++i)
        {
            m_children[i]->m_childindex = i;
            m_children[i]->m_parent = &Derived();
        }
    }

    reference Derived()
    {
        return static_cast<reference>(*this);
    }
};//class Relatives

}//namespace vgui


