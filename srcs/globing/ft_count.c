/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 05:29:22 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/11 23:48:05 by viclucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_globing.h"

int				count_name2(char *name)
{
	int i;

	i = 0;
	while (name[i])
		i++;
	return (i);
}

int				check_star(char *test, int i)
{
	while (test[i] != '*')
	{
		i--;
		if (test[i] == '*')
			return (1);
	}
	return (0);
}

int				count_name(char *test, int i)
{
	int ret;

	ret = i;
	if (check_star(test, i) == 0)
	{
		while (test[ret])
		{
			ret++;
			if (test[ret] == '*')
				return (1);
		}
	}
	return (0);
}
