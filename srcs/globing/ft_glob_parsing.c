/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 11:29:41 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/10 05:28:40 by viclucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_globing.h"

int			remove_some(char *str, int ref)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	while (str[i] && i < ref)
	{
		if (str[i] == '[' && str[i + 1] && i + 1 < ref)
		{
			while (i < ref && str[i] && str[i] != ']')
			{
				i++;
				ret++;
			}
		}
		else
			i++;
	}
	return (ret);
}

int			ft_with_5f(char *str, char *test, int j)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] == '-' && str[i + 2])
			if (test[j] >= str[i] && test[j] <= str[i + 2])
				return (0);
		i += 3;
	}
	return (-1);
}

int			ft_without_5f(char *str, char *test, int j)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == test[j])
			return (0);
		i++;
	}
	return (-1);
}

int			ft_destroy_5f(char *str, char *test, int j)
{
	int i;

	i = 1;
	if (ft_strchr(str, '-'))
	{
		while (str[i])
		{
			if (str[i + 1] == '-' && str[i + 2])
				if (test[j] >= str[i] && test[j] <= str[i + 2])
					return (-1);
			i += 3;
		}
	}
	else
	{
		while (str[i])
		{
			ft_putchar(str[i]);
			if (str[i] == test[j])
				return (-1);
			i++;
		}	
	}
	return (0);
}

int			ft_glob_parsing(char *str, char *test, int i)
{
	if (!str || !str[0])
		return (-1);
	if (str[0] == '!')
			return (ft_destroy_5f(str, test, i));
	if (ft_strchr(str, '-'))
		return (ft_with_5f(str, test, i));
	else
		return (ft_without_5f(str, test, i));
}
