/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_checking_globing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 03:29:47 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/15 06:57:26 by viclucas         ###   ########.fr       */
/*   Updated: 2018/08/14 06:07:27 by viclucas         ###   ########.fr       */
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
				ft_free_thoses(&test, &path, NULL, NULL);
				return (NULL);
			}
			ft_strdel(&test);
			return (surface = improve_surface(surface, board, path, var));
		}
		path = ft_add_path(path, test);
		if (move_into_surface(path, surface, &i, o) == -1)
		{
			ft_strdel(&path);
			return (NULL);
		}
	}
	ft_putendl("PAAAA");
	return (surface);
}

int			start_checking_globing(t_list **ret, char *line)
{
	char	*save;
	int		o;
	
	o = 0;
	if (!ft_strchr(line, '?') && !ft_strchr(line, '[') && !ft_strchr(line, '*'))
		return (FALSE);
	line = ft_strdup(line);
	save = ft_strdup(line);
	if (parsing_glob(line, save) == -1)
		return (FALSE);
	if (!(line = start_exp(line, &o)))
	{
		ft_fill_ret(save, ret);
		ft_strdel(&save);
		return (FALSE);
	}
	if (o == 0)
	{
		ft_strdel(&line);
		ft_fill_ret(save, ret);
		ft_strdel(&save);
		return (FALSE);
	}
	ft_strdel(&save);
	if (line)
		ft_fill_ret(line, ret);
	ft_strdel(&line);
	return (TRUE);
}
