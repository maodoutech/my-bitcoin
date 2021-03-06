#ifndef BITCOIN_CHECKPOINTS_H
#define BITCOIN_CHECKPOINTS_H

struct CCheckpointData;

/**
 * Block-chain checkpoints are compiled-in sanity checks.
 * They are updated every release or three.
 */
namespace Checkpoints
{
    //! Return conservative estimate of total number of blocks, 0 if unknown
    int GetTotalBlocksEstimate(const CCheckpointData& data);

}  //namespace Checkpoints

#endif // BITCOIN_CHECKPOINTS_H
