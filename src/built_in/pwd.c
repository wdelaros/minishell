#include "../../include/built_in.h"

int	pwd(void)
{
	return (ft_printf("%s\n", getcwd(NULL, 0)), 0);
}
