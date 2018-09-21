#include <stdio.h>
#include <stdlib.h>

typedef struct majority_result
{
	int majorityFound;
	int majorityValue;
} majorityResult;

majorityResult* newMajorityResult(int majorityFound, int majorityValue)
{
	majorityResult* result = malloc(sizeof(majorityResult));
	result->majorityFound = majorityFound;
	result->majorityValue = majorityValue;
	return result;
}

int getMajorityFound(majorityResult* result){return result->majorityFound;}
int getMajorityValue(majorityResult* result){return result->majorityValue;}

void printMajorityResult(majorityResult* result)
{
	if (result->majorityFound) printf("Majority element: %d\n", result->majorityValue);
	else                       printf("No majority element exists.\n");
}

int countValue(int value, int* values, int length)
{
	int count = 0;
	for (int i = 0; i < length; ++i)
		if (value == values[i]) ++count;
	return count;
}

/*
 * Time complexity of length
 * Space complexity of approximately 2*length
 */
majorityResult* findMajorityValueHelper(int* values, const int length, int* partition, int partLength)
{
	if (partLength % 2 == 1)
	{
		int candidate = partition[partLength - 1];
		if (countValue(candidate, values, length) > length / 2)
		{
			majorityResult* result = newMajorityResult(1, candidate);
			return result;
		}
		else --partLength; //Don't examine the element we just looked at
	}

	//There is no majority element
	if (partLength == 0)
	{
		majorityResult* result = newMajorityResult(0, 1 << 31);	
		return result;
	}

	int* newPartition = malloc(sizeof(int) * partLength/2);
	int newPartLength = 0;
	for (int i = 0; i < length; i += 2)
	{
		if (values[i] == values[i+1])
		{
			newPartition[newPartLength] = values[i];
			++newPartLength;
		}	
	}
	majorityResult* result = findMajorityValueHelper(values, length, newPartition, newPartLength);
	free(newPartition);
	return result;
}

majorityResult* findMajorityValue(int* values, int length)
{
	return findMajorityValueHelper(values, length, values, length);
}

int main(void)
{
	int caseA[] = {5, 6, 8, 2, 4, 12};
	int caseB[] = {5, 6, 8, 2, 4, 12, 26};
	int caseC[] = {1, 3, 6, 3, 3, 3};

	majorityResult* resultA = findMajorityValue(caseA, sizeof(caseA)/sizeof(int));
	printMajorityResult(resultA);
	free(resultA);

	majorityResult* resultB = findMajorityValue(caseB, sizeof(caseB)/sizeof(int));
	printMajorityResult(resultB);
	free(resultB);

	majorityResult* resultC = findMajorityValue(caseC, sizeof(caseC)/sizeof(int));
	printMajorityResult(resultC);
	free(resultC);

	return 0;
}
	
		
