#include <dlfcn.h>
#include <sys/errno.h>
#include <stdlib.h>

#ifndef LIMIT
# define LIMIT 0
#endif

/*
	Since libc is a dynamic library, we can overwrite it's functions.
	What we do is fetch the real malloc function in the library.
	Then we can either return the value of the real malloc function, or 0.
	Just like malloc, in case of failure we set errno to ENOMEM.
*/
void	*malloc(size_t size)
{
	static void *(*real_malloc)(size_t) = 0;
	static int counter = 0;

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
