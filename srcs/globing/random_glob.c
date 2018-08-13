/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 00:36:12 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/13 22:11:01 by viclucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_globing.h"

void		ft_fill_ret(char *line, t_list **ret)
{
	char	**tmp;
	int		i;
	t_list	*new;
	int		o;

	i = 0;
	tmp = ft_strsplit(line, ' ');
	print_db(tmp);
	while (tmp[i])
	{
		o = ft_strlen(tmp[i]);
		new = ft_lstnew(tmp[i], o + 1 );
		ft_lstadd(ret, new);
		i++;
	}
}

char	*return_letters(char *line, char *tmp, char **surface)
{
	char *temp;

	if (tmp && surface[1])
	{
		ft_putendl("1");
		temp = ft_strjoin(tmp, line);
		ft_strdel(&tmp);
		tmp = ft_souder(temp, surface[1], " ");
		ft_free_thoses(&temp, &line, NULL, NULL);
		return (tmp);
	}
	if (tmp)
	{
		ft_putendl("2");
		temp = ft_strjoin(tmp, line);
		ft_free_thoses(&tmp, &line, NULL, NULL);
		return (temp);
	}
	if (surface[1])
	{
		ft_putendl("3");
//		ft_putendl("souder material");
//		ft_putendl(line);
//		ft_putendl(surface[1]);
		
		temp = ft_souder(line, surface[1], " ");
		ft_strdel(&line);
		ft_free_db_tab(surface);
		return (temp);
	}
	ft_putendl("7");
	return (line);
}

char			*replace_letter(char *line, int i, int *o)
{
	char	*tmp;
	char	**surface;

	tmp = NULL;
	surface = surface_of_work(line, &i);
	if (i > 0)
		tmp = ft_strndup(line, i);
	if (!(line = get_elem(surface[0], o)))
	{
		if (tmp && surface[1])
		{
			ft_putendl("4");
			return (ft_souder(tmp, surface[1], " "));
		}
		else if (tmp)
		{
			ft_putendl("5");
			return (tmp);
		}
		if (surface[1])
		{
			ft_putendl("6");
			return (surface[1]);
		}
		return (NULL);
	}
	return (return_letters(line, tmp, surface));
}

char			*start_exp(char *line, int *o)
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
				return (NULL);
	//		ft_putendl("");
	//		ft_putendl(line);
			i = -1;
		}
		i++;
	}
	return (line);
}
