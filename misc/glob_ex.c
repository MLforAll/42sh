/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 15:43:48 by kdumarai          #+#    #+#             */
/*   Updated: 2018/07/15 15:59:01 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glob.h>
#include "libft.h"

int		main(int ac, char **av)
{
	glob_t	data;

	if (ac < 2 || glob(av[1], 0, NULL, &data))
		return 1;
	ft_puttab(data.gl_pathv, "gl_pathv");
	globfree(&data);
	return 0;
}
