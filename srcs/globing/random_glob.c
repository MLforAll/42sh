/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 00:36:12 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/10 04:25:10 by viclucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_globing.h"

char			*start_exp(char *line, int *o, char *save)
{
	int		i;
	t_tabv	x;

	ft_bzero(&x, sizeof(t_tabv));
	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			ft_quotes_check(&x, line[i]);
		if ((line[i] == '?' || line[i] == '[' || line[i] == '*') &&
				x.flag1 == 0 && x.flag2 == 0)
		{
			if (!(line = replace_letter(line, i, o)))
			{
				ft_error("42sh: no matches found: ", save);
				ft_strdel(&save);
				return (NULL);
			}
			i = -1;
		}
		i++;
	}
	return (line);
}
