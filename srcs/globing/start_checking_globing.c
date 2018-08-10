/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_checking_globing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 03:29:47 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/10 05:28:39 by viclucas         ###   ########.fr       */
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

char			*replace_letter(char *line, int i, int *o)
{
	char	*tmp;
	char	**surface;

	tmp = NULL;
	surface = surface_of_work(line, &i);
	if (i > 0)
		tmp = ft_strndup(line, i);
	if (!(line = get_elem(surface[0], o)))
	{
		if (tmp && surface[1])
			return (ft_souder(tmp, surface[1], " "));
		else if (tmp)
			return (tmp);
		if (surface[1])
			return (surface[1]);
		return (NULL);
	}
	return (return_letters(line, tmp, surface));
}

char			*start_checking_globing(char *line)
{
	char	*save;
	int		o;

	o = 0;
	if (!ft_strchr(line, '?') && !ft_strchr(line, '[') && !ft_strchr(line, '*'))
		return (line);
	if (parsing_glob(line) == -1)
		return (NULL);
	save = ft_strdup(line);
	if (!(line = start_exp(line, &o, save)))
		return (NULL);
	if (o == 0)
	{
		ft_error("42sh: no matches found: ", line);
		ft_strdel(&save);
		return (NULL);
	}
	ft_strdel(&save);
	return (line);
}
