/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 05:29:22 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/14 02:49:25 by viclucas         ###   ########.fr       */
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

int				ft_get_the_prev(int i, char *surface, char *test)
{
	int		ret;
	char	*prev;

	ret = 0;
	i--;
	if (i < 0)
		return (0);
	while (i > 0 && (surface[i] == ']' || surface[i] == '?' || surface[i] == '*'))
		i = ft_pass_it(surface, i);	
	while (i > 0 && surface[i] != ']' && surface[i] != '?' && surface[i] != '*')
		i--;
	if (i > 0)
		i++;
		while (surface[i] && surface[i] != '[' && surface[i] != '?' && surface[i] != '*')
		{
			ret++;
			i++;
		}
	prev = ft_strndup(surface + i - ret, ret);
	i = 0;
	while (test[i])
	{
		if (ft_strnequ(prev, test + i, ft_strlen(prev)))
				return (i + ft_strlen(prev));
		i++;
	}
	return (-1);
}

int				ft_get_the_past(int i, char *surface, char *test)
{
	int		ret;
	char	*past;

	ret = 0;
	while (surface[i] && (surface[i] == '[' || surface[i] == '?' || surface[i] == '*'))
		i = ft_pass_theses(i, surface);	
	while (surface[i] && surface[i] != '[' && surface[i] != '?' && surface[i] != '*')
	{
		i++;
		ret++;
	}
	if (!surface[i - ret])
		return (ft_strlen(test) - 1);
	past = ft_strndup(surface + i - ret, ret);	
		i = 0;
	while (test[i])
	{
		if (ft_strnequ(past, test + i, ft_strlen(past)))
				return (i - ft_strlen(past));
		i++;
	}
	return (i);
}

char			*fuck_stars(char *test, int i, char *surface)
{
	int		prev;
	int		past;
	
	prev = ft_get_the_prev(i, surface, test);
	past = ft_get_the_past(ft_pass_theses(i, surface), surface, test);
//	printf("int prev = %d\nint past = %d\n", prev,past);
//	ft_putendl(ft_strndup(test + prev, past - prev + 1));
	return (ft_strndup(test + prev, (past - prev) + 1));
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
