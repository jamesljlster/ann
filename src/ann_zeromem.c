
#include "ann.h"
#include "ann_private.h"

#include "debug.h"

void ann_config_zeromem(struct ANN_CONFIG_STRUCT* cfgPtr)
{
	cfgPtr->inputs = 0;
	cfgPtr->outputs = 0;
	cfgPtr->layers = 0;
	cfgPtr->transferFuncIndex = 0;
	
	cfgPtr->learningRate = 0;
	cfgPtr->mementumCoef = 0;

	cfgPtr->nodeList = NULL;
}
