#include "../../include/built_in.h"

int	pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	return (ft_printf("%s\n", str), free(str), 0);
}
