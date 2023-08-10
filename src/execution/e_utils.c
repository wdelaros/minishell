#include "../../include/execution.h"

t_e_data	*e_struc(void)
{
	static t_e_data	e_data;

	return (&e_data);
}
