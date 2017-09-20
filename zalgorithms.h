#ifndef ZALGORITHMS_H
#define ZALGORITHMS_H


template <typename ForwardIterator>
 void zDeleteAll(ForwardIterator begin, ForwardIterator end)
{
    while (begin != end) {
        if(*begin)
            delete *begin;
        ++begin;
    }
}

template <typename Container>
inline void zDeleteAll(const Container &c)
{
    zDeleteAll(c.begin(), c.end());
}

#endif // ZALGORITHMS_H
