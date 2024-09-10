malloctest: malloc.c malloc_tester.c
	gcc malloc_tester.c malloc.c -o malloctest.exe -Wall -Wextra -ggdb -O0