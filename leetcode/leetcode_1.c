//hash
//leetcode_1
typedef struct HashNode{
	int key;
	int value;
} HashNode;

typedef struct HashMap{
	int size;
	HashNode** storage;
} HashMap;

HashMap* hash_create(int size){
	HashMap* hashMap = (struct HashMap*)malloc(sizeof(struct HashMap));
	hashMap->size = size;
	hashMap->storage = (struct HashNode**)calloc(size, sizeof(struct HashNode*));//
	return hashMap;
}

void hash_set(HashMap *hashMap, int key, int value){
	HashNode *node = (struct HashNode*)malloc(sizeof(struct HashNode));
	int hash = abs(key) % (hashMap->size) ;
	while(hashMap->storage[hash])
	{
		hash++;
		hash = hash % (hashMap->size);
	}
	node->key = key;
	node->value = value;
	hashMap->storage[hash] = node;
}

HashNode* hash_get(HashMap *hashMap, int key){
	int hash = abs(key) % (hashMap->size);
	HashNode* node;
	while((node = hashMap->storage[hash]))
	{
		if (node->key == key)
	        	return node;
		hash++;
		hash = hash % (hashMap->size);
	}
	return NULL;
}

void  hash_destroy(HashMap* hashMap){
	HashNode *node;

	for(int i=0; i < hashMap->size; i++)
		if ((node = hashMap->storage[i]))
			free(node);

        free(hashMap->storage);
	free(hashMap);
}

int* twoSum(int* nums, int numsSize, int target){
	HashNode *node;
	HashMap *hashMap = hash_create(2*numsSize);
        int* result;
	for(int i=0; i < numsSize; i++){
		int value = target - nums[i];
		node = hash_get(hashMap, value);
		if(node)
		{
			result = (int *)malloc(2*sizeof(int));
			result[0] = node->value;
			result[1] = i;
			return result;
		}
		hash_set(hashMap, nums[i], i);
	}
	return result;
}
