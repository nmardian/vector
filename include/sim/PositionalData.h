#ifndef POSITIONAL_DATA_H
#define POSITIONAL_DATA_H

namespace vector
{
    namespace sim
    {
        struct PositionalData
        {
            unsigned short heading{0};
            unsigned int xCoord{0};
            unsigned int yCoord{0};
        };
    }
}

#endif // POSITIONAL_DATA_H