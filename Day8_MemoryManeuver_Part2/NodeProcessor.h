#pragma once

template<size_t Size>
class NodeProcessor
{
public:
    NodeProcessor(_In_ typename std::array<unsigned short, Size>::const_iterator nodeStart) :
        m_nodeStart(nodeStart)
    {
        typename std::array<unsigned short, Size>::const_iterator iter = nodeStart;
        m_countOfChildren = *iter;
        iter++;
        m_countOfMetadataEntries = *iter;
        iter++;

        for (unsigned short child = 0; child < m_countOfChildren; child++)
        {
            m_childrenNodeStarts.push_back(iter);
            iter = GetEndOfNode(iter);
        }

        m_metadataEntriesStart = iter;
    }

    unsigned short GetValue()
    {
        if (m_countOfChildren == 0)
        {
            return GetValueChildless();
        }
        else
        {
            return GetValueOfChildren();
        }
    }

private:
    unsigned short GetValueChildless()
    {
        // If a node has no child nodes, its value is the sum of its metadata entries.
        typename std::array<unsigned short, Size>::const_iterator metadataEntriesEnd = m_metadataEntriesStart;
        metadataEntriesEnd += m_countOfMetadataEntries;

        unsigned short value = std::accumulate(m_metadataEntriesStart, metadataEntriesEnd, static_cast<unsigned short>(0));
        return value;
    }

    unsigned short GetValueOfChildren()
    {
        // However, if a node does have child nodes, the metadata entries become indexes which refer to those child nodes.
        // A metadata entry of 1 refers to the first child node, 2 to the second, 3 to the third, and so on. The value of
        // this node is the sum of the values of the child nodes referenced by the metadata entries. If a referenced child
        // node does not exist, that reference is skipped. A child node can be referenced multiple time and counts each time
        // it is referenced. A metadata entry of 0 does not refer to any child node.
        typename std::array<unsigned short, Size>::const_iterator iter = m_metadataEntriesStart;
        typename std::array<unsigned short, Size>::const_iterator metadataEntriesEnd = m_metadataEntriesStart;
        metadataEntriesEnd += m_countOfMetadataEntries;
        std::map<unsigned short, unsigned short> cachedChildValues;

        unsigned short value = 0;
        while (iter != metadataEntriesEnd)
        {
            unsigned short childNodeIndex = *iter; // This is 1-indexed
            if (childNodeIndex == 0)
            {
                iter++;
                continue;
            }

            if (childNodeIndex > m_countOfChildren)
            {
                iter++;
                continue;
            }

            typename std::map<unsigned short, unsigned short>::const_iterator cached = cachedChildValues.find(childNodeIndex);
            if (cached != cachedChildValues.end())
            {
                value += cached->second;
            }
            else
            {
                typename std::array<unsigned short, Size>::const_iterator childNodeStart = m_childrenNodeStarts[childNodeIndex - 1];
                NodeProcessor childNode(childNodeStart);
                unsigned short childValue = childNode.GetValue();
                value += childValue;
                cachedChildValues.insert({ childNodeIndex, childValue });
            }

            iter++;
        }

        return value;
    }

    static typename std::array<unsigned short, Size>::const_iterator GetEndOfNode(_In_ typename std::array<unsigned short, Size>::const_iterator nodeStart)
    {
        typename std::array<unsigned short, Size>::const_iterator iter = nodeStart;
        unsigned short countOfChildren = *iter;
        iter++;
        unsigned short countOfMetadataEntries = *iter;
        iter++;

        for (unsigned short child = 0; child < countOfChildren; child++)
        {
            iter = GetEndOfNode(iter);
        }

        iter += countOfMetadataEntries;

        return iter;
    }

    typename std::array<unsigned short, Size>::const_iterator m_nodeStart;
    unsigned short m_countOfChildren;
    unsigned short m_countOfMetadataEntries;
    std::vector<typename std::array<unsigned short, Size>::const_iterator> m_childrenNodeStarts;
    typename std::array<unsigned short, Size>::const_iterator m_metadataEntriesStart;
};
