#include "ann.h"
#include "ann_file_proc.h"
#include "ann_file_header.h"

#include "debug.h"

char* ann_file_header[] = {
	"Application",
	"Topology",
	"Training information",
	"Total node",
	"Threshold value",
	"Weight factor"
};

char* ann_header_application[] = {
	"Name=Visual Gene Developer - Neural Network"
};

char* ann_header_topology[] = {
	"Total input",
	"Total output",
	"Total layer",
	"Transfer function"
};

char* ann_header_training_info[] = {
	"learning rate",
	"momentum coefficient"
};

char* ann_header_total_node[] = {
	"layer=total node"
};

char* ann_header_threshold_value[] = {
	"layer-node=threshold value"
};

char* ann_header_weight_factor[] = {
	"layer-node(layer n-1)-node(layer n)=weight factor"
};

int ann_get_topology_content_id(char* src)
{
	int iResult;
	int retValue = ANN_INFO_NOT_FOUND;
	int i;

	LOG("enter");

	for(i = 0; i < ANN_HEADER_TOPOLOGY_LIST_COUNT; i++)
	{
		iResult = ann_strcmp(src, ann_header_topology[i]);
		if(iResult == ANN_NO_ERROR)
		{
			retValue = i;
			break;
		}
	}

	LOG("exit");

	return retValue;
}

int ann_get_training_content_id(char* src)
{
	int iResult;
	int retValue = ANN_INFO_NOT_FOUND;
	int i;
	
	LOG("enter");

	for(i = 0; i < ANN_HEADER_TRAINING_INFO_LIST_COUNT; i++)
	{
		iResult = ann_strcmp(src, ann_header_training_info[i]);
		if(iResult == ANN_NO_ERROR)
		{
			retValue = i;
			break;
		}
	}

	LOG("exit");

	return retValue;
}

