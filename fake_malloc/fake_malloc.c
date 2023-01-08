#define _GNU_SOURCE
#include <dlfcn.h>
#include <sys/errno.h>
#include <stdlib.h>

#ifndef LIMIT
# define LIMIT 0
#endif

/*
	This code allows us to see what happens in case of malloc failure.

	To use, we just need to add this file to the sources and compile it all together.

	What'll happen is that malloc will be overwritten and each time our project code
	calls malloc or calloc, these functions below will be called instead.

	This allows us to easily automate testing of malloc-failure after a certain number of
	mallocs. One problem with this is that it isn't always obvious to trace back what the i-th malloc is.

	TO DO: add realloc function.
*/

int	counter = 0;

/*
	Beacuse libc is a dynamic library, we can overwrite it's functions.

	What we do is find the real malloc function in the dynamic library.

	Then we can either:
		- return the value of the real malloc function.
		- simulate a malloc failure: set errno to ENOMEM and return 0.
*/
void	*malloc(size_t size)
{
	static void *(*real_malloc)(size_t) = 0;

	if (real_malloc == NULL)
		real_malloc = dlsym(RTLD_NEXT, "malloc");
	if (counter == LIMIT)
	{
		errno = ENOMEM;
		return (0);
	}
	counter++;
	return (real_malloc(size));
}

void	*calloc(size_t count, size_t size)
{
	static void *(*real_calloc)(size_t, size_t) = 0;

	if (real_calloc == NULL)
		real_calloc = dlsym(RTLD_NEXT, "calloc");
	if (counter == LIMIT)
	{
		errno = ENOMEM;
		return (0);
	}
	counter++;
	return (real_calloc(count, size));
}
