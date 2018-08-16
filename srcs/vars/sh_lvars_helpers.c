/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lvars_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 06:27:56 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/16 07:17:23 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

extern t_list	*g_var_expwait;
t_list			*g_var_expwait = NULL;

t_uint8			set_lvar_exported(const char *name)
{
	t_list	*new;

	if (!(new = ft_lstnew(name, ft_strlen(name) + 1)))
		return (FALSE);
	ft_lstpush(&g_var_expwait, new);
	return (TRUE);
}

t_uint8			is_lvar_exported(const char *name, t_uint8 del)
{
	t_list	**bw;

	bw = &g_var_expwait;
	while (*bw)
	{
		if (ft_strequ((const char*)(*bw)->content, name))
		{
			if (del)
				ft_lstdelone(bw, &ft_lstnodefree);
			return (TRUE);
		}
		bw = &(*bw)->next;
	}
	return (FALSE);
}

inline void		del_lvar_exported(const char *name)
{
	(void)is_lvar_exported(name, YES);
}
