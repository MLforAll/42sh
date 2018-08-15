/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   improve_surface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:54:54 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/14 23:22:08 by viclucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_globing.h"

static int	ft_length(char *path, char *surface)
{
	int i;

	if (!path)
		i = 0;
	else
		i = ft_strlen(path);
	if (surface[i] == '/')
		i++;
	while (surface[i] && surface[i] != '/')
		i++;
	return (i);
}

char		*ft_improve_expend(char *ret, char *tmp2, char *tmp, char *path)
{
	(void)path;
	if (tmp)
		ft_strdel(&tmp);
	if (tmp2)
	{
		if (ret)
			tmp = ft_souder(ret, tmp2, " ");
		else
			tmp = ft_strdup(tmp2);
		ft_strdel(&tmp2);
	}
	if (ret)
		ft_strdel(&ret);
	return (tmp);
}

static int	glob_last_test_ext(int *i, char *surface, char *test)
{
	char		*o;
	int			ret;

	ret = 0;
	o = fuck_stars(test, *i, surface);
	*i += 1;
	while (surface[*i] != ']')
	{
		ret++;
		*i += 1;
	}
	if (ret != 0)
	{
		if (ft_glob_parsing(ft_strndup(surface + *i - ret, ret), o) == -1)
			return (-1);
	}
	return (0);
}

static int	glob_last_test(char *test, char *surface)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	if (!surface)
		return (-1);
	if (surface[i] && surface[i] == '/')
		i++;
	while (surface[i] && surface[i] != '/')
	{
		if (surface[i] == '[')
		{
			if (glob_last_test_ext(&i, surface, test) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

char		*improve_surface(char *surface, char **test, char *path, int *o)
{
	int		i;
	char	*ret;
	char	*tmp;
	char	*tmp2;
	int		length;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	ret = NULL;
	if (!path)
		length = 0;
	else
		length = ft_strlen(path) + 1;
	while (test[i])
	{
		if (glob_last_test(test[i], surface + length) == 0)
		{
			if (path)
			{
				tmp = ft_souder(path, test[i], "/");
				tmp2 = ft_strjoin(tmp, surface + ft_length(path, surface));
			}
			else
				tmp2 = ft_strjoin(test[i], surface + ft_length(path, surface));
			if (customs_officer(tmp2) == 0)
			{
				if (!surface[ft_length(path, surface)] || add_one(surface, ft_length(path, surface)))
					*o += 1;
				ret = ft_improve_expend(ret, tmp2, tmp, path);
			}
		}
		i++;
	}
	ft_free_db_tab(test);
	if (path)
		ft_strdel(&path);
	return (ret);
}
