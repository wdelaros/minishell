#include "../../include/error.h"

int	mul_red_error(t_err *error_data)
{
	int	i;

	i = 0;
	while (error_data->input[i] && error_data->error_code == 0)
	{
		if (error_data->input[i] == '<' || error_data->input[i] == '>')
		{
			i++;
			while (ft_isspace(error_data->input[i]) == YES)
				i++;
			if (error_data->input[i] == RD_I && (error_data->input[i + 1]
					&& error_data->input[i + 1] == RD_I))
				error_data->error_code = 6;
			else if (error_data->input[i] == RD_O && (error_data->input[i + 1]
					&& error_data->input[i + 1] == RD_O))
				error_data->error_code = 7;
			else if (error_data->input[i] == RD_I)
				error_data->error_code = 4;
			else if (error_data->input[i] == RD_O)
				error_data->error_code = 5;
		}
		i++;
	}
	return (error_data->error_code);
}
