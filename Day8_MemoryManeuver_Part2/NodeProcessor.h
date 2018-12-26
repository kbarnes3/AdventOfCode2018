#pragma once

template<size_t Size>
class NodeProcessor
{
public:
    typedef std::pair<typename std::array<unsigned short, Size>::const_iterator, unsigned int> ProcessedNode;

    static ProcessedNode ProcessNode(_In_ typename std::array<unsigned short, Size>::const_iterator nodeStart)
    {
        _In_ typename std::array<unsigned short, Size>::const_iterator iter = nodeStart;
        unsigned short countOfChildren = *iter;
        iter++;
        unsigned short countOfMetadataEntries = *iter;
        iter++;

        unsigned long metadataSum = 0;

        for (unsigned short child = 0; child < countOfChildren; child++)
        {
            ProcessedNode results = ProcessNode(iter);
            iter = results.first;
            metadataSum += results.second;
        }

        for (unsigned short metadataEntry = 0; metadataEntry < countOfMetadataEntries; metadataEntry++)
        {
            metadataSum += *iter;
            iter++;
        }

        return { iter, metadataSum };
    }
};
