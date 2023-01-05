#include <dlfcn.h>
#include <sys/errno.h>
#include <stdlib.h>

#ifndef LIMIT
# define LIMIT 0
#endif

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
