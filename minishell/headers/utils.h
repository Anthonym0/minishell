/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:53:04 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 11:15:11 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

//ft_string_write.c
char	*ft_strdup(char *str);
char	*ft_strndup(char *input, int n);
int		ft_strcpy(char *dest, char *src);
int		ft_strncpy(char *dest, char *src, int n);
char	*ft_strjoin(char *s1, char *s2);

//ft_string.c
int		ft_strcmp(char *s1, char *s2);
int		ft_strcmp_sep(char *s1, char *s2, char sep);
int		ft_strlen(char *str);

//int_array.c
int		sum_int_array(int *tab, int len);
int		*create_and_init_tab(int len);

//double_tab.c
int		get_double_tab_size(char **tab);
int		ft_free_tab(char **tab);
int		ft_reverse_free_tab(char **tab, int index);

//access.c
int		check_file(char *pathname);
int		check_read(char *pathname);
int		check_write(char *pathname);
int		check_execute(char *pathname);

#endif