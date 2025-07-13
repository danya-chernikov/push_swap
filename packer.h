#if !defined(PACKER_H)
# define PACKER_H

#include <stdarg.h>

/* I have the right to use functions
 * from <stdarg.h> since ft_printf()
 * already uses it in my project anyway */
void	**pack_args(int nargs, ...);

#endif
