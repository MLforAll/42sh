/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 00:36:12 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/12 03:37:56 by viclucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_globing.h"

void		ft_fill_ret(char *line, t_list **ret)
{
	char	**tmp;
	int		i;
	t_list	*new;

	i = 0;
	tmp = ft_strsplit(line, ' ');
	while (tmp[i])
	{
		new = ft_lstnew(tmp[i], ft_strlen(tmp[i]));
		ft_lstadd(ret, new);
		i++;
	}
}

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
			ft_putendl(line);
			i = -1;
		}
		i++;
	}
	return (line);
}
