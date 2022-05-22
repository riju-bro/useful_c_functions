#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char* buff;
	size_t size;
}string;

// function that return the content of a file and the size.
// If you need to input from stdin you need to use '\n' character instead of EOF
string* get_file(FILE* fd){
	size_t offset = 0;
	size_t buffsize = 10;
	char* buff;
	char* temp_buff;

	if((buff = malloc(buffsize)) == NULL)
		return NULL;
	int c;
	while((c = fgetc(fd)) != EOF){
		
		// buffsize - 2 because one byte for '\0' character
		if(offset == buffsize-2){
			// Increasing the buffer size and error checking
			if((temp_buff = realloc(buff, buffsize * 2)) == NULL)
				return NULL;

			// new buffer and buffer size
			buffsize *= 2;
			buff = temp_buff;
		}
		buff[offset++] = c;
		}

	// Shrink to fit
	// buffsize - 1 because one byte for '\0' character
	if(offset < buffsize - 1){
		// one byte for '\0' character
		if((temp_buff = realloc(buff, offset+1)) == NULL)
			return NULL;
		buffsize = offset + 1;
		buff = temp_buff;
	}
	buff[offset] = '\0';
	string* s = malloc(sizeof(string));
	s->buff = buff;
	s->size = offset;
	return s;

}
