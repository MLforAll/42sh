/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_checking_globing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 03:29:47 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/13 02:47:17 by viclucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_globing.h"

int				globing_get_length(char *surface, int i)
{
	int ret;

	ret = 0;
	if (surface[0] && surface[0] == '/' && i == 0)
	{
		ret++;
		i++;
	}
	while (surface[i] && surface[i] != '/')
	{
		ret++;
		i++;
	}
	return (ret);
}

int				move_into_surface(char *path, char *surface, int *i, int o)
{
	if (ft_acces(path) == NULL)
	{
		*i = *i + o;
		while (surface[*i] && surface[*i] == '/' && surface[*i + 1])
			*i += 1;
	}
	else
		return (-1);
	return (0);
}

char			*get_elem(char *surface, int *var)
{
	int				i;
	int				o;
	char			*test;
	char			*path;
	char			**board;

	path = NULL;
	i = 0;
	while (surface[i])
	{
		o = globing_get_length(surface, i);
		test = ft_strndup(surface + i, o);
		if (ft_strchr(test, '?') || ft_strchr(test, '*') ||
				ft_strchr(test, '['))
		{
			if (!(board = replace_char(surface, test,
							ft_strsplit_globing(test))))
			{
				return (NULL);
			}
			return (surface = improve_surface(surface, board, path, var));
		}
		path = ft_add_path(path, test);
		if (move_into_surface(path, surface, &i, o) == -1)
			return (NULL);
	}
	return (surface);
}

char			*start_checking_globing(t_list **ret, char *line)
{
	char	*save;
	int		o;
	
	o = 0;
	if (!ft_strchr(line, '?') && !ft_strchr(line, '[') && !ft_strchr(line, '*'))
		return (line);
	save = ft_strdup(line);
	if (parsing_glob(line) == -1)
		return (save);
	if (!(line = start_exp(line, &o)))
	{
		ft_fill_ret(save, ret);
		return (save);
	}
	if (o == 0)
	{
		//free
		ft_fill_ret(save, ret);
		return (save);
	}
	ft_strdel(&save);
	if (line)
		ft_fill_ret(line, ret);
	return (line);
}
