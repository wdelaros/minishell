/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_to_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapelcha <rapelcha@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:35:21 by wdelaros          #+#    #+#             */
/*   Updated: 2023/09/28 14:35:36 by rapelcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	nb_of_complete_command(t_input **ih)
{
	t_input	*temp;
	int		count;

	temp = (*ih);
	count = 0;
	while (temp)
	{
		if (temp->token == 0 || temp->token == 3)
			count++;
		temp = temp->next;
	}
	if ((*ih)->input != NULL && count == 0)
		count++;
	return (count);
}

static void	sizeof_each_command(t_input **ih, t_conv *data, int count)
{
	t_input	*temp;
	int		i;
	int		size;

	temp = (*ih);
	i = 0;
	size = 1;
	while (temp->next)
	{
		if ((temp->next && temp->next->token == 3)
			|| temp->token == 4 || (temp->token == 3 && temp->input[0] == PIPE)
			|| temp->token == 5)
		{
			data->sizeofcom[i] = size;
			i++;
			size = 0;
		}
		temp = temp->next;
		size++;
	}
	if (i < count)
		data->sizeofcom[i] = size;
}

static void	malloc_everything(t_input **ih, t_conv *data)
{
	int	i;
	int	count;

	i = 0;
	data->i = 0;
	data->j = 0;
	count = nb_of_complete_command(ih);
	data->res = ft_calloc(count + 1, sizeof(char **));
	data->sizeofcom = ft_calloc(count, sizeof(int));
	sizeof_each_command(ih, data, count);
	while (i < count)
	{
		data->res[i] = ft_calloc(data->sizeofcom[i] + 1, sizeof(char *));
		i++;
	}
}

static char	**redirection_tranfer(char **dest, char *red)
{
	free (dest);
	dest = ft_calloc(3, sizeof(char *));
	dest[0] = ft_strdup(red);
	return (dest);
}

char	***convert_list_to_string(t_input **ih, int k)
{
	t_input	*temp;
	t_conv	data;

	put_in_order(ih);
	temp = (*ih);
	malloc_everything(ih, &data);
	while (temp->next)
	{
		if (k == data.sizeofcom[data.i])
		{
			data.i++;
			data.j = 0;
			k = 0;
		}
		if (temp->input[0] == RD_I || temp->input[0] == RD_O)
			data.res[data.i] = redirection_tranfer(data.res[data.i],
					temp->input);
		else
			data.res[data.i][data.j] = ft_strdup(temp->input);
		data.j++;
		k++;
		temp = temp->next;
	}
	ft_xfree(data.sizeofcom);
	return (data.res);
}
