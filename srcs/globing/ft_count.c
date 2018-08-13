/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 05:29:22 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/13 22:19:31 by viclucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_globing.h"

int				customs_officer(char *tmp2)
{
	int i;

	i = 0;
	if (ft_strchr(tmp2, '*') || ft_strchr(tmp2, '[') || ft_strchr(tmp2, '?'))
		return (0);
	if (access(tmp2, F_OK) == 0)
		return (0);
	ft_putendl("Pass");
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
