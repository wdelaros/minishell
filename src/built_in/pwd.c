#include "../../include/built_in.h"

int	pwd(void)
{
	char	*str;

	struc()->exit_code = 0;
	str = getcwd(NULL, 0);
	if (!str)
	{
		perror(str);
		struc()->exit_code = 1;
	}
	return (ft_printf("%s\n", str), free(str), struc()->exit_code);
}
