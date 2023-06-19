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
	return (count);
}

static void	sizeof_each_command(t_input **ih, t_conv *data)
{
	t_input	*temp;
	int		i;
	int		size;

	temp = (*ih);
	i = 0;
	size = 1;
	while (temp->next)
	{
		if (temp->next && temp->next->token == 3)
		{
			data->sizeofcom[i] = size;
			i++;
			size = 0;
		}
		if (temp->token == 3)
		{
			data->sizeofcom[i] = size;
			i++;
			size = 0;
		}
		temp = temp->next;
		size++;
	}
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
	printf ("\nNOMBRE DE COMPLETE COMMAND: %d\n", count);
	data->res = ft_calloc(count + 1, sizeof(char **));
	// data->res = NULL;
	if (!data->res)
		Ct_debug(-1, "nb_command_malloc", "error.txt");
	data->sizeofcom = ft_calloc(count, sizeof(int));
	sizeof_each_command(ih, data);
	while (i < count)
	{
		data->res[i] = ft_calloc(data->sizeofcom[i] + 1, sizeof(char *));
		printf ("NOMBRE DE STRING MALLOC: %d\n", data->sizeofcom[i]);
		i++;
	}
	printf ("MALLOC DU NOMBRE DE STRING DANS CHACUNE DES COMMAND COMPLETE!\n");
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
	while (temp)
	{
		if (k == data.sizeofcom[data.i])
		{
			if (!temp->next)
				return (data.res);
			printf ("ARRIVER A LA FIN DE LA COMMANDE\n");
			data.i++;
			data.j = 0;
			k = 0;
		}
		data.res[data.i][data.j] = ft_strdup(temp->input);
		printf ("STRING QUI A ÉTÉ COPIER:%s:FIN:\n", data.res[data.i][data.j]);
		data.j++;
		k++;
		temp = temp->next;
	}
	free(data.sizeofcom);
	return (data.res);
}
