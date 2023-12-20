#include "func.h"

// helper function to manipulate strings for insert and sort
char* getSubstring(char* word, char* sub) {
	// init variables
	char baseS[StringSize];
	memset(baseS, '\0', sizeof(baseS));
	// gets var for index of string
	int a = 0;
	for(int i = 0; i < StringSize; i++) {
		if (word[i] != sub[i]) {
			break;
		}
		a++;
	}
	// get string from differences of inputs
	for (int i = 0; i < strlen(word); i++) {
		if (word[i+a] == '\0') {
			break;
		}
		baseS[i] = word[i+a];
	}
	
	// return pointer to string
	char* baseP = malloc(sizeof(char*));
	strcpy(baseP, baseS);
	return baseP; 
} 

// helper function to manipulate strings for insert and sort
char* getPrefix(char* word, char* sub) {
	// init variables
	char baseS[StringSize];
	memset(baseS, '\0', sizeof(baseS));
	// gets var for index of string
	int a = 0;
	for(int i = 0; i < StringSize; i++) {
		if (word[i] != sub[i]) {
			break;
		}
		a++;
	}
	// get string from similarity of inputs
	for (int i = 0; i < a; i++) {
		baseS[i] = word[i];
	}
	// return pointer to string
	char* baseP = malloc(sizeof(char*));
	strcpy(baseP, baseS);
	return baseP; 
}

// recursively itterate through tree to find input string
int searchWord(char* copyWord) {
	// init variables
	int index;
	struct node* search = root;
	char* word = malloc(sizeof(char*));
	// free and stop if cannot allocate space
	if (word == NULL) {
		free(word);
		return 0;
	}
	strcpy(word, copyWord);
	
	while (strcmp(word, "")) {
		// get index (97 because ascii)
		index = word[0] - 97;
		search = search->nextNode[index];
		// base case
		if (search == NULL) {
			free(word);
			return 0;
		} else {
			// check to find word
			if (strcmp(search->value, word) == 0) {
				free(word);
				return 1;
			} 
			// "remove" node string from search word
			char* temp = getSubstring(word, search->value);
			strcpy(word, temp);
			free(temp);
		}
	}
	free(word);
	return 0;
}

// recursively itterate through tree until an empty node is reached to insert
int insertWord(char* word, struct node* search) {
	// init variable
	int index;
	// input checks
	if (search == NULL) {
		return 0;
	}
	if (strlen(word) < 1) {
		return 0;
	}
	// get index (97 because ascii)
	index = word[0] - 97;
	// check if there is empty node to insert string into
	if (search->nextNode[index] == NULL) {
		// allocate memory  for node
		struct node* newNode = malloc(sizeof(struct node));
		// free and stop if cannot allocate space
		if (newNode == NULL) {
			free(newNode);
			return 0;
		}
		// initialize node
		search->nextNode[index] = newNode;
		strcpy(newNode->value, word);
		for (int i = 0; i < 26; i++) {
			newNode->nextNode[i] = NULL;
		}
		return 1;
	} else {
		// move down tree
		search = search->nextNode[index];
		// insert the differing parts of the strings
		char* wordSub = getSubstring(word, search->value);
		// free and stop if cannot allocate space
		if (wordSub == NULL) {
			free(wordSub);
			return 0;
		}
		insertWord(wordSub, search);
		free(wordSub);
		// insert the differing parts of the strings
		char* searchSub = getSubstring(search->value, word);
		// free and stop if cannot allocate space
		if (searchSub == NULL) {
			free(searchSub);
			return 0;
		}
		insertWord(searchSub, search);
		free(searchSub);
		// change node value for new input nodes
		char* prefSub = getPrefix(word, search->value);
		strcpy(search->value, prefSub); 
		free(prefSub);
		return 0;
	}
	return 0;
}

// function recursively itterate through tree and removes nodes
void emptyTree(struct node* current) {
	if (current != NULL) {
		for (int i = 0; i < 26; i++) {
			// recusive call
			emptyTree(current->nextNode[i]);
			// empty value of nodes
			current->nextNode[i] = NULL;
		}
		// free all node memory except for root
		if (current != root) {
			free(current);
		}
	}
}

/* // does not work
char* lexPrint(struct node* current) {
	char* word = malloc(sizeof(char[StringSize]));
	
	for(int i = 0; i < 26; i++) {
		if (current->nextNode[i] != NULL) {
			strcat(word, lexPrint(current->nextNode[i]));
			printf("%s\n", word);
		} else {
			return word;
		}
	}
	return word;
}
*/

// function that prints number of nodes in tree
int nodeNumber(struct node* current) {
	// init variable
	int num = 1;
	// increment num var for each non-NULL node
	for (int i = 0; i < 26; i++) {
		if (current->nextNode[i] != NULL) {
			// recusion call
			num += nodeNumber(current->nextNode[i]);
		}
	}
	return num;

}

// function that prints number of words in tree (does not actually check if word is valid)
int wordNumber(struct node* current) {
	// init variable
	int num;
	// ignore root node
	if (current != root) {
		num = 1;
	} else {
		num = 0;
	}
	
	for (int i = 0; i < 26; i++) {
		if (current->nextNode[i] != NULL) {
			// recusion call
			num += wordNumber(current->nextNode[i]);
		}
	}
	return num;

}

/* // function for debug
void printTrie(struct node* current) {
	if (current != NULL) {
		if (current == root) {
			printf("root ");
		}
		printf("node val: %s\n", current->value);
		for (int i = 0; i < 26; i++) {
			printf("%c:%d ", i+97, current->nextNode[i] == NULL ? 0 : 1);
		}
		printf("\n");
		for (int i = 0; i < 26; i++) {
			printTrie(current->nextNode[i]);
		}
	}
}
*/
