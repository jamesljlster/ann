#include <stdio.h>

#define QUEUE_SIZE 5

int main()
{
	int i, j;

	int queue[QUEUE_SIZE + 1] = {0};

	int queueSize = QUEUE_SIZE + 1;
	int queueHead = 0;
	int queueTail = 0;

	int queueLen = 0;
	int queIndex, quePreIndex;

	for(i = 0; i < 32; i++)
	{
		// Update queue
		queueHead = (queueHead + 1) % queueSize;
		if(queueHead == queueTail)
		{
			queueTail = (queueTail + 1) % queueSize;
		}

		// Find queue length
		queueLen = queueHead - queueTail;
		if(queueLen < 0)
		{
			queueLen = queueLen + queueSize;
		}

		// Set queue value
		queue[queueHead] = i;

		// Print queue information
		printf("Insert %d: queueHead = %d, queueTail = %d, queueLen = %d\n", i, queueHead, queueTail, queueLen);

		// Access queue
		for(j = queueLen - 1; j >= 0; j--)
		{
			queIndex = (j + queueTail + 1) % queueSize;
			quePreIndex = (j + queueTail) % queueSize;
			printf("queue[%d] = %d, queue[%d] = %d\n", j, queue[queIndex], j - 1, queue[quePreIndex]);
		}
		printf("\n");
	}

	return 0;
}
