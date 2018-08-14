/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 00:36:12 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/14 23:20:09 by viclucas         ###   ########.fr       */
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
	if (!(tmp = ft_strsplit(line, ' ')))
		return ;
	while (tmp[i])
	{
		o = ft_strlen(tmp[i]);
		new = ft_lstnew(tmp[i], o + 1 );
		ft_lstadd(ret, new);
		i++;
	}
	ft_free_db_tab(tmp);	
}

char	*return_letters(char **line, char *tmp, char *ret)
{
	char *temp;

	if (tmp && ret)
	{
		temp = ft_strjoin(tmp, *line);
		ft_strdel(&tmp);
		tmp = ft_souder(temp, ret, " ");
		ft_free_thoses(&temp, line, &ret, NULL);
		return (tmp);
	}
	if (tmp)
	{
		temp = ft_strjoin(tmp, *line);
		ft_free_thoses(&tmp, line, &ret, NULL);
		return (temp);
	}
	if (ret)
	{
		temp = ft_souder(*line, ret, " ");
		ft_free_thoses(&ret, line, NULL, NULL);
		return (temp);
	}
	return (*line);
}

char			*replace_letter(char *line, int i, int *o)
{
	char	*tmp;
	char	**surface;
	char	*ret;

	ret = NULL;	
	tmp = NULL;
	surface = surface_of_work(line, &i);
	if (i > 0)
		tmp = ft_strndup(line, i);
	if (surface[1])
			ret = ft_strdup(surface[1]);
	if (!(line = get_elem(surface[0], o)))
	{
		ft_free_db_tab(surface);
		if (tmp && ret)
			return (ft_souder(tmp, ret, " "));
		else if (tmp)
			return (tmp);
		if (ret)
			return (ret);
		return (NULL);
	}
	ft_free_db_tab(surface);
	return (return_letters(&line, tmp, ret));
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
			i = -1;
		}
		i++;
	}
	return (line);
}
