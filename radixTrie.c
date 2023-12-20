#include "func.h"

int main() {
	// create root node
	root = malloc(sizeof(struct node));
	// free and stop if cannot allocate space
	if (root == NULL) {
		free(root);
		return 0;
	}
	// root initialization
	memset(root->value, '\0', sizeof(root->value));
	for (int i = 0; i < 26; i++) {
		root->nextNode[i] = NULL;
	}
	// var initialization
	char input;
	char word[StringSize];

	do {
		// get command
		do {
			scanf("%c", &input);
		} while(isspace(input));

		switch (input) {  
			// insert        
			case 'i': 
				// get word
				scanf("%s", word);
				// insert only if word is not in tree
				if (!searchWord(word)) {
					insertWord(word, root);
				}
				break;

			// search
			case 's':
				// get word
				scanf("%s", word);
				// search tree for word
				if (searchWord(word)) {
					printf("%s is present\n", word); 
				} else {
					printf("%s is missing\n", word);
				}
				break;

			// empty tree
			case 'e': 
				emptyTree(root);
				break;
				
			// lexicographical print (does not work)
			case 'P':
				//lexPrint(root);
				break;
			
			// print number of node
			case 'n':
				printf("Trie contains %d nodes\n", nodeNumber(root));
				break;
				
			// print nuber of words
			case 'w':
				printf("Trie contains %d words\n", wordNumber(root));
				break;

			// quit
			case 'q':
				printf("-quitting program-\n");
				break;
			
			/* // this is helpful debugging code
			case 'p':
				printTrie(root);
				break;
			*/
				
			default:            
				printf("Oi! That's not a legal command\n");
		}

	} while (input != 'q');
	// remove tree and free nodes
	emptyTree(root);
	free(root);
	return 0;
}
