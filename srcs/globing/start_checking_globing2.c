/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_checking_globing2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 03:29:47 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/14 06:07:27 by viclucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_globing.h"

int			start_checking_globing_norm(int o, char **line, char **save,
		t_list ***ret)
{
	if (o == 0)
	{
		ft_strdel(line);
		ft_fill_ret(*save, *ret);
		ft_strdel(save);
		return (1);
	}
	return (0);
}
