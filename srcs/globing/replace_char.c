/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:29 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/14 06:07:38 by viclucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_globing.h"

char			*get_prev_string(char *surface)
{
	int					o;
	char				*prev;

	o = 0;
	if (ft_strchr(surface, '/') == NULL)
		return (NULL);
	while (surface[o] && surface[o] != '?' && surface[o] != '[' &&
			surface[o] != '*')
		o++;
	while (o > 0 && surface[o] != '/')
		o--;
	if (surface[o] == '/' && o > 0)
		o--;
	if (o == 0)
		return (NULL);
	prev = ft_strndup(surface, o + 1);
	return (prev);
}

static int		glob_compare(char *test, char *name, char **known, t_glob *x)
{
	if (test[x->i] && test[x->i] != '*' && test[x->i] != '?' &&
			test[x->i] != '[')
	{
		if (ft_strnequ(name + x->u, known[x->o], ft_strlen(known[x->o])))
		{
			x->i = x->i + ft_strlen(known[x->o]);
			x->u = x->u + ft_strlen(known[x->o]);
			x->o += 1;
		}
		else if (x->i > 0 && test[x->i - 1] && test[x->i - 1] == '*')
		{
			if ((x->plus = ft_globing_star(test, name, known, *x)) != -1)
			{
				x->i = x->i + ft_strlen(known[x->o]);
				x->u = x->u + x->plus;
				x->o += 1;
			}
			else
				return (-1);
		}
		else
			return (-1);
	}
	else
	{
		if (test[x->i] == '*')
			x->i++;
		else
		{
			x->i = ft_pass_theses(x->i, test);
			x->u += 1;
		}
	}
	return (0);
}

static char		**send_it(char *name, char **ret, char *test, char **known)
{
	t_glob	x;

	ft_bzero(&x, sizeof(t_glob));
	if (ft_strequ("..", name) || ft_strequ(".", name) || ft_strchr(name, '?'))
		return (ret);
	if (ft_strchr(test, '*') == NULL)
		if (ft_strlen_glob(test) != ft_strlen(name))
			return (ret);
	while (test[x.i] && known[x.o])
	{
		if (glob_compare(test, name, known, &x) < 0)
			return (ret);
	}
	ret = ft_glob_db(ret, name);
	return (ret);
}

char			**replace_char(char *surface, char *test, char **known)
{
	char			*prev;
	struct dirent	*g;
	DIR				*dir;
	char			**ret;
	int				o;

	ret = NULL;
	o = 0;
	if (!(prev = get_prev_string(surface)))
		prev = ft_strdup(".");
	if ((dir = opendir(prev)) == NULL)
	{
		ft_putendl("Erreur d'opendir");
		return (NULL);
	}
	ft_strdel(&prev);
	while ((g = readdir(dir)) != NULL)
		ret = send_it(g->d_name, ret, test, known);
	ft_free_db_tab(known);	
	closedir(dir);
	return (ret);
}
