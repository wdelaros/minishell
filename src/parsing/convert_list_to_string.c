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
			if ((temp->token == 3 && (temp->input[0] == PIPE
				|| temp->input[0] == RED_IN || temp->input[0] == RED_OUT))
				|| temp->token == 0)
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
		//printf ("SIZE: %d	STR: %s	TOKEN: %d\n", size, temp->input, temp->token);
		if ((temp->next && temp->next->token == 3) || temp->token == 4)
		{
			//printf ("FIN DE LA FUCKING COMMANDE\n");
			data->sizeofcom[i] = size;
			i++;
			size = 0;
		}
		//printf("PROCHAIN TRUC\n");
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
	// printf ("\nNOMBRE DE COMPLETE COMMAND: %d\n", count);
	data->res = ft_calloc(count + 1, sizeof(char **));
	data->sizeofcom = ft_calloc(count, sizeof(int));
	sizeof_each_command(ih, data, count);
	while (i < count)
	{
		data->res[i] = ft_calloc(data->sizeofcom[i] + 1, sizeof(char *));
		// printf ("NOMBRE DE STRING MALLOC: %d\n", data->sizeofcom[i]);
		i++;
	}
	// printf ("MALLOC DU NOMBRE DE STRING DANS CHACUNE DES COMMAND COMPLETE!\n");
}

static char	**redirection_tranfer(char **dest, char *red, char *arg)
{
	free (dest);
	dest = ft_calloc(3, sizeof(char *));
	dest[0] = ft_strdup(red);
	dest[1] = ft_strdup(arg);
	// printf ("STRING QUI A ÉTÉ COPIER DANS RED_TRANSFER:%s:FIN:\n", dest[0]);
	// printf ("STRING QUI A ÉTÉ COPIER DANS RED_TRANSFER:%s:FIN:\n", dest[1]);
	return (dest);
}

char	***convert_list_to_string(t_input **ih)
{
	t_input	*temp;
	t_conv	data;
	int		k;

	data.res = NULL;
	temp = (*ih);
	malloc_everything(ih, &data);
	k = 0;
	while (temp->next)
	{
		if (k == data.sizeofcom[data.i])
		{
			// printf ("SIZECOM: %d\n", data.sizeofcom[data.i]);
			if (!temp->next)
				return (data.res);
			// printf ("ARRIVER A LA FIN DE LA COMMANDE\n");
			data.i++;
			data.j = 0;
			k = 0;
		}
		if (temp->input[0] == RED_IN || temp->input[0] == RED_OUT)
		{
			//printf("REDIRECTION TRANFER:\n");
			data.res[data.i] = redirection_tranfer(data.res[data.i],
					temp->input, temp->next->input);
		}
		else
			data.res[data.i][data.j] = ft_strdup(temp->input);
		//ft_putstr_fd("STRING QUI A ÉTÉ COPIER:", 0);
		//ft_print_double(data.res[data.i]);
		data.j++;
		k++;
		temp = temp->next;
	}
	ft_xfree(data.sizeofcom);
	return (data.res);
}
