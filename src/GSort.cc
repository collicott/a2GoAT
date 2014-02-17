
#include "GSort.h"


GSort::GSort(TFile &TreeFile)   :
    GTreeParticleManager(TreeFile)
{

}

GSort::~GSort()
{
}

void	GSort::Reconstruct()
{
    for(int i=0; i<MultiplicityList.size(); i++)
    {
        if(GetNParticles() == MultiplicityList[i])
            return GTreeParticleManager::Reconstruct();
    }
}
