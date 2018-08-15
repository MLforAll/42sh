/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 05:29:22 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/15 01:30:06 by viclucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_globing.h"

static int		ft_pass_it(char *surface, int i)
{
	if (surface[i] == ']')
	{
		i--;
		while (surface[i] != '[' && i > 0)
			i--;
		if (surface[i] == '[' && i > 0)
			i--;
	}
	else
		i--;
	return (i);
}

char			*ft_get_the_prev(int i, char *surface)
{
	int		ret;
	char	*prev;

	prev = NULL;
	ret = 0;
	i--;
	if (i < 0)
		return (0);
	while (i > 0 && (surface[i] == ']' || surface[i] == '?' || surface[i] == '*') && surface[i] != '/')
		i = ft_pass_it(surface, i);	
	while (i > 0 && surface[i] != ']' && surface[i] != '?' && surface[i] != '*' && surface[i] != '/')
		i--;
	if (i > 0)
		i++;
//	ft_putendl(surface + i);
	while (surface[i] && surface[i] != '[' && surface[i] != '?' && surface[i] != '*' && surface[i] != '/')
	{
		ret++;
		i++;
	}
	if (ret)
		return (prev = ft_strndup(surface + i - ret, ret));
//	ft_putendl(surface + i);
	return (NULL);
}

char	*ft_get_the_past(int i, char *surface)
{
	int		ret;
	char	*past;

	past = NULL;
	ret = 0;
	while (surface[i] && (surface[i] == '[' || surface[i] == '?' || surface[i] == '*') && surface[i] != '/')
		i = ft_pass_theses(i, surface);	
	while (surface[i] && surface[i] != '[' && surface[i] != '?' && surface[i] != '*' && surface[i] != '/')
	{
		i++;
		ret++;
	}
	if (!surface[i - ret])
		return (NULL);
	if (ret)
		past = ft_strndup(surface + i - ret, ret);	
	return (past);
}
//need algo pour check si a la fin de la chaine si past existe pas si il y  a pas detoile ne pas donner de range trop grosse / renvoyer NULL


char			*fuck_stars(char *test, int i, char *surface)
{
	char	*prev;
	char	*past;
	char	*ret;
	char	*final;
	int		j;

	ret = NULL;
	j = 0;
	prev = ft_get_the_prev(i, surface);
	past = ft_get_the_past(ft_pass_theses(i, surface), surface);
	ft_putstr("prev = |");ft_putendl(prev);ft_putchar('|');
	ft_putstr("past = ");ft_putendl(past);
	
	while (test[j])
	{
		if (!prev)
			break ;
		if (ft_strnequ(test + j, prev, ft_strlen(prev)))
		{
			ret = ft_strdup(test + j + ft_strlen(prev));
			break ;
		}	
		j++;
	}
	if (!ret)
		ret = ft_strdup(test);	
	if (!past)
		return (ret);
	while (ret[j])
	{
		if (ft_strnequ(ret + j, past, ft_strlen(past)))
		{
			final = ft_strndup(ret, j); 
			ft_putstr("final = "); ft_putendl(final);
			return (ret);
		}
		j++;
	}
	return (NULL);
}

int				customs_officer(char *tmp2)
{
	int i;

	i = 0;
	if (ft_strchr(tmp2, '*') || ft_strchr(tmp2, '[') || ft_strchr(tmp2, '?'))
		return (0);
	if (access(tmp2, F_OK) == 0)
		return (0);
	return (1);
}


int				ft_globing_star(char *test, char *name, char **known, t_glob x)
{
	(void)test;
	x.n = x.u;
	while (name[x.n])
	{
		if (ft_strnequ(name + x.n, known[x.o], ft_strlen(known[x.o])))
		{
			return (x.n - x.u + ft_strlen(known[x.o]));
		}
		else
			x.n++;
	}
	return (-1);
}
