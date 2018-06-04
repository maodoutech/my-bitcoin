#include "checkpoints.h"

#include "chainparams.h"
#include "main.h"

namespace Checkpoints {
    int GetTotalBlocksEstimate(const CCheckpointData& data)
    {
        const MapCheckpoints& checkpoints = data.mapCheckpoints;

        if (checkpoints.empty())
            return 0;

        return checkpoints.rbegin()->first;
    }
}
