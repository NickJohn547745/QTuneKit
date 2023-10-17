#ifndef ID3_H
#define ID3_H

#include <QString>

class ID3
{
public:
    ID3();

private:
    bool unsynchronized;
    bool hasExtendedHeader;
    bool hasFooter;
    bool isExperimental;
};

#endif // ID3_H
