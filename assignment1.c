#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void triangle(int width)
{
    unsigned i, j;
    
    for (i = 1; i <= width; i++){
    	for(j = 0; j < i; j++){
    		putchar('*');
    	}
    	putchar('\n');
    }
}
void v_triangle(int width)
{
	for(int i = width; i > 0; i--){
		for(int j = 0; j < i; j++){
			putchar('*');
		}
		putchar('\n');
	}
}
void h_triangle(int width)
{
	for(int i = width; i > 0; i--){
		for(int j = width; j > 0; j--){
			if (j <= i){
				putchar('*');
			}
			else{
				putchar(' ');
			}
		}
		putchar('\n');
	}
}

int main(int argc, char* argv[])
{
	if(argc < 2){
		exit(EXIT_FAILURE);
	}
	int width = atoi(argv[1]);
	if(width <= 0){
		exit(EXIT_FAILURE);
	}
	if(argc < 3){
		triangle(width);
	}
	else if(strcmp(argv[2], "h") == 0){
		h_triangle(width);
	}
	else if(strcmp(argv[2], "v") == 0){
		v_triangle(width);
	}
	else{
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}