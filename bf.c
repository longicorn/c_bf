#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gc.h>

#define malloc GC_malloc
#define calloc GC_calloc 
#define realloc GC_realloc
#define free

void *xmalloc(size_t size){
	void *ret;

	ret = malloc(size);
	if(ret == NULL){
		exit(EXIT_FAILURE);
	}

	return ret;
}

void *xrealloc(void *ptr, size_t size){
	void *ret;

	ret = realloc(ptr, size);
	if(ret == NULL){
		exit(EXIT_FAILURE);
	}

	return ret;
}

char *freadall(char *file){
	FILE *fp;
	char *ret;
	size_t rs;
	size_t size, max;
	const size_t step = 1024;

	fp = fopen(file, "r");
	if(fp == NULL){
		return NULL;
	}

	ret = 0;
	size = 0;
	max = step;
	ret = xmalloc(max);
	while(1){
		rs = fread(ret, 1, step, fp);
		if(rs <= 0){
			ret = NULL;
			break;
		}
		size += rs;
		if(size <= max){
			break;
		}

		max += step;
		ret = xrealloc(ret, max);
	}

	fclose(fp);

	return ret;
}

int main(int argc, char **argv){
	char *file;
	char *stack, *data;
	int c, fpos;
	size_t len, pos, max;
	const size_t step = 1024;

	//get file name
	if(argc <= 1){
		return 1;
	}
	file = argv[1];

	data = freadall(file);
	len = strlen(data);

	stack = xmalloc(step);
	memset(stack, 0, step);
	max = step;
	pos = 0;
	fpos = 0;
	while(1){
		if(pos >= max){
			break;
		}

		if(fpos >= len){
			break;
		}
		c = data[fpos++];

		switch(c){
			case '>':
				pos++;
				break;
			case '<':
				pos--;
				break;
			case '+':
				stack[pos]++;
				break;
			case '-':
				stack[pos]--;
				break;
			case '.':
				printf("%c", (char)stack[pos]);
				break;
			case ',':
				c = fgetc(stdin);
				fgetc(stdin);
				stack[pos] = (char)c;
				break;
			case '[':
				if(stack[pos] == 0){
					//jump next ']'
					while(1){
						if(fpos >= len){
							break;
						}
						c = data[fpos++];
						if(c == ']'){
							break;
						}
					}
				}
				break;
			case ']':
				while(1){
					if(fpos < 0){
						break;
					}
					c = data[--fpos];
					if(c == '['){
						break;
					}
				}
				break;
			default:
				//ignore other character
				break;
		}
	}

	return 0;
}
