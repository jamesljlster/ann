
#include "ann.h"
#include "ann_private.h"

#include "debug.h"

void ann_zero_struct(struct ANN_STRUCT* asPtr)
{
	asPtr->layerList = NULL;
	ann_config_zeromem(&asPtr->config);
}

void ann_config_zeromem(struct ANN_CONFIG_STRUCT* cfgPtr)
{
	cfgPtr->inputs = 0;
	cfgPtr->outputs = 0;
	cfgPtr->layers = 0;
	cfgPtr->transferFuncIndex = 0;
	
	cfgPtr->learningRate = 0;
	cfgPtr->momentumCoef = 0;

	cfgPtr->nodeList = NULL;
}
