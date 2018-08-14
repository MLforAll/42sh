/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   too_much_fcts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 19:59:21 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/14 00:18:07 by viclucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_globing.h"

int		add_one(char *surface, int size)
{
	if (!surface[size])
		return (1);
	while (surface[size])
	{
		if (surface[size] == '[' ||
				surface[size] == '?' || surface[size] == '*')
			return (0);
		size++;
	}
	return (1);
}

int		parsing_glob(char *line)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '[')
			flag = 1;
		else if (line[i] == ']' && flag == 0)
		{
			ft_putendl_fd("bad pattern", 2);
			return (-1);
		}
		else if (line[i] == ']')
			flag = 0;
		i++;
	}
	if (flag == 0)
		return (0);
	ft_putendl_fd("bad pattern", 2);
	return (0);
}

size_t	ft_strlen_glob(char *str)
{
	size_t i;
	size_t ret;

	ret = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '[')
		{
			ret++;
			while (str[i] && str[i] != ']')
				i++;
			if (str[i])
				i++;
		}
		else
		{
			i++;
			ret++;
		}
	}
	return (ret);
}

int		go_to_next_part(int i, char *s)
{
	int ret;

	ret = i;
	while (s[i] && (s[i] == '?' || s[i] == '*' || s[i] == '['))
	{
		if (s[i] == '[')
		{
			ret++;
			while (s[i] && s[i] != ']')
				i++;
			if (s[i])
				i++;
		}
		else
		{
			i++;
			ret++;
		}
	}
	return (ret);
}
