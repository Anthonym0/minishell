/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:45:53 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:33:29 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

char	*user_directory(void)
{
	char	*usr_dir;

	usr_dir = malloc(sizeof(char) * 2);
	if (usr_dir == NULL)
		return (NULL);
	usr_dir[0] = '~';
	usr_dir[1] = '\0';
	return (usr_dir);
}

char	*extract_last_dir(char *ap_name, int ap_len, int cwd_index)
{
	char	*last_dir;
	int		i;

	if (ap_name == NULL || ap_len == -1 || cwd_index == -1)
		return (NULL);
	if (count_slashes(ap_name, cwd_index) == 2)
	{
		last_dir = user_directory();
		return (last_dir);
	}
	last_dir = malloc(sizeof(char) * (ap_len - cwd_index + 1));
	if (last_dir == NULL)
		return (NULL);
	ap_name += cwd_index;
	i = 0;
	while (*ap_name != '\0')
	{
		last_dir[i] = *ap_name;
		i++;
		ap_name++;
	}
	last_dir[i] = '\0';
	return (last_dir);
}

char	*ft_getcwd(void)
{
	char	*ap_name;
	int		ap_len;
	int		cwd_index;
	char	*cwd_name;

	ap_name = getcwd(NULL, 0);
	if (ap_name == NULL)
		return (NULL);
	ap_len = ft_strlen(ap_name);
	cwd_index = find_lastdir(ap_name);
	cwd_name = extract_last_dir(ap_name, ap_len, cwd_index);
	free(ap_name);
	return (cwd_name);
}

char	*generate_prompt(void)
{
	char	*cwd;
	char	*temp;
	char	*arrows;
	char	*prompt;

	cwd = ft_getcwd();
	if (cwd == NULL)
		return (NULL);
	temp = add_color(cwd, HIGH_GREEN_BCKGRND);
	free(cwd);
	if (temp == NULL)
		return (NULL);
	arrows = add_color(">> ", HIGH_GREEN);
	if (arrows == NULL)
	{
		free(temp);
		return (NULL);
	}
	prompt = ft_strjoin(temp, arrows);
	free(temp);
	free(arrows);
	return (prompt);
}

char	*prompt(void)
{
	char	*prompt;
	char	*line;

	prompt = NULL;
	prompt = generate_prompt();
	if (prompt == NULL)
		return (NULL);
	line = readline(prompt);
	if (is_empty(line) == 0)
		add_history(line);
	free(prompt);
	return (line);
}
