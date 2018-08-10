/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   improve_surface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:54:54 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/10 01:49:28 by viclucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_globing.h"

static int		nb_words(char *str)
{
	int i;
	int	ret;

	ret = 0;
	i = 0;
	while (str[i] && str[i] != '*' && str[i] != '?' && str[i] != '[')
		i++;
	ret = (i > 0) ? 1 : 0;
	while (str[i])
	{
		if (str[i] == '*' || str[i] == '?' || str[i] == '[')
		{
			if (str[i] == '[')
				while (str[i] && str[i - 1] != ']')
					i++;
			else if (str[i] == '?' || str[i] == '*')
				while (str[i] && (str[i] == '?' || str[i] == '*'))
					i++;
			if (str[i] && str[i] != '*' && str[i] != '?' && str[i] != '[')
				ret++;
		}
		else if (str[i])
			i++;
	}
	return (ret);
}

static int		nb_char(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '*' && str[i] != '?' && str[i] != '[')
		i++;
	return (i);
}

int				ft_pass_theses(int o, char *str)
{
	if (str[o] && (str[o] == '*' || str[o] == '?' || str[o] == '['))
	{
		if (str[o] == '[')
		{
			while (str[o] && str[o] != ']')
				o += 1;
			if (str[o] == ']')
				o += 1;
		}
		else if (str[o] == '?' || str[o] == '*')
			o += 1;
	}
	return (o);
}

static char		*ft_end_of_fct(int *o, char *str)
{
	char	*ret;
	int		i;

	i = 0;
	if (!(ret = (char*)malloc(sizeof(char) * (nb_char(str + *o) + 1))))
		return (NULL);
	while (str[*o] && str[*o] != '*' && str[*o] != '?' && str[*o] != '[')
	{
		ret[i++] = str[*o];
		*o += 1;
	}
	ret[i] = '\0';
	*o = ft_pass_theses(*o, str);
	return (ret);
}

char			**ft_strsplit_globing(char *str)
{
	int		i;
	char	**ret;
	int		o;

	ret = NULL;
	if (!str)
		return (NULL);
	i = nb_words(str);
	if (!(ret = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	o = ft_pass_theses(0, str);
	while (str[o])
	{
		if (str[o] != '*' && str[o] != '?' && str[o] != '[')
			ret[i++] = ft_end_of_fct(&o, str);
		else
			o = ft_pass_theses(o, str);
	}
	ret[i] = 0;
	return (ret);
}
