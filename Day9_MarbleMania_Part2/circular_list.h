#pragma once

class circular_list
{
private:
    struct node;

public:
    class iterator
    {
    public:
        friend circular_list;

        iterator()
        {
        }

        iterator(std::shared_ptr<node> node)
        {
            m_currentNode = node;
        }

        iterator operator++()
        {
            if (std::shared_ptr<node> currentNode = m_currentNode.lock())
            {
                m_currentNode = currentNode->m_next;
                return *this;
            }
            else
            {
                iterator empty;
                return empty;
            }
        }

        iterator operator--()
        {
            if (std::shared_ptr<node> currentNode = m_currentNode.lock())
            {
                m_currentNode = currentNode->m_prev;
                return *this;
            }
            else
            {
                iterator empty;
                return empty;
            }
        }

        int operator*()
        {
            if (std::shared_ptr<node> currentNode = m_currentNode.lock())
            {
                return currentNode->m_value;
            }
            else
            {
                return int();
            }
        }

    private:
        std::weak_ptr<node> m_currentNode;
    };

    iterator begin()
    {
        if (m_startNode == nullptr)
        {
            return iterator();
        }
        else
        {
            return iterator(m_startNode);
        }
    }

    iterator insert(iterator pos, unsigned int value)
    {
        std::shared_ptr<node> newNode = std::make_shared<node>(value);


        if (std::shared_ptr<node> posNode = pos.m_currentNode.lock())
        {
            std::shared_ptr<node> nextNode = posNode->m_next;
            newNode->m_next = nextNode;
            nextNode->m_prev = newNode;
            posNode->m_next = newNode;
            newNode->m_prev = posNode;
        }
        else
        {
            // Special case: an empty iterator is acceptable if the list itself is empty
            if (m_startNode == nullptr)
            {
                // In this case, the new_node is the first and only node in our list
                newNode->m_prev = newNode;
                newNode->m_next = newNode;
                m_startNode = newNode;
            }
        }

        return iterator(newNode);
    }

    iterator erase(iterator pos)
    {
        if (std::shared_ptr<node> posNode = pos.m_currentNode.lock())
        {
            // Special case: last node
            if (posNode->m_next == posNode && posNode->m_prev == posNode)
            {
                m_startNode = nullptr;
                posNode->m_next = nullptr;
                posNode->m_prev = nullptr;
                return begin();
            }

            posNode->m_prev->m_next = posNode->m_next;
            posNode->m_next->m_prev = posNode->m_prev;

            // Special case, the start node was just removed
            if (m_startNode == posNode)
            {
                m_startNode = posNode->m_next;
            }

            return iterator(posNode->m_next);
        }
        else
        {
            return iterator();
        }
    }

private:
    struct node
    {
        node(unsigned int value) :
            m_value(value)
        {

        }

        unsigned int m_value;
        std::shared_ptr<node> m_prev;
        std::shared_ptr<node> m_next;
    };

    std::shared_ptr<node> m_startNode;
};
