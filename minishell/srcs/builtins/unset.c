/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:06:52 by agranjon          #+#    #+#             */
/*   Updated: 2024/03/11 18:09:16 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	to_delete(char *arg, char **env)
{
	int	i;

	if (arg == NULL || env == NULL)
		return (-1);
	if (ft_strcmp("?", arg) == 0)
		return (-2);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strcmp_sep(arg, env[i], '=') == 0)
			return (i);
		i++;
	}
	return (-2);
}

int	*ft_set_index_tab(char **argv, char **env)
{
	int	*tab;
	int	i;
	int	index;

	if (argv == NULL || env == NULL)
		return (NULL);
	tab = create_and_init_tab(get_double_tab_size(env));
	if (tab == NULL)
		return (NULL);
	i = 1;
	while (argv[i] != NULL)
	{
		index = to_delete(argv[i], env);
		if (index == -1)
			return (free(tab), NULL);
		if (index >= 0)
			tab[index] = 0;
		i++;
	}
	return (tab);
}

char	**create_new_env(char **env, int *tab)
{
	char	**new;
	int		i;
	int		j;

	if (env == NULL || tab == NULL)
		return (NULL);
	j = get_double_tab_size(env);
	new = malloc(sizeof(char *) * (sum_int_array(tab, j) + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (tab[i] == 1)
		{
			new[j] = ft_strdup(env[i]);
			if (new[j] == NULL)
				return (ft_reverse_free_tab(new, i), NULL);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	return (new);
}

int	unset(char **argv, char ***my_env)
{
	int		*tab_index;
	char	**new_env;

	if (argv == NULL || my_env == NULL)
		return (-1);
	tab_index = ft_set_index_tab(argv, *my_env);
	if (!tab_index)
		return (-1);
	new_env = create_new_env(*my_env, tab_index);
	if (!new_env)
		return (free(tab_index), -1);
	free(tab_index);
	if (g_signal != 0)
		return (ft_free_tab(new_env), free(tab_index), return_signals());
	ft_free_tab(*my_env);
	*my_env = new_env;
	return (0);
}
