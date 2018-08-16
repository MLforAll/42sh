/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_export_bltncmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 05:55:10 by kdumarai          #+#    #+#             */
/*   Updated: 2018/08/16 07:26:24 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "sh.h"

static int	export_usage(char a)
{
	ft_putstr_fd("export: illegal option -- ", STDERR_FILENO);
	ft_putchar_fd(a, STDERR_FILENO);
	ft_putendl_fd("\nusage: [name[=value] ...] or export -p", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static void	print_vars(void)
{
	extern char		**environ;
	extern t_list	*g_var_expwait;
	char			**bw;
	t_list			*ewbw;

	bw = environ;
	while (*bw)
	{
		ft_putstr("export ");
		ft_putendl(*(bw++));
	}
	ewbw = g_var_expwait;
	while (ewbw)
	{
		ft_putstr("export ");
		ft_putendl((const char*)ewbw->content);
		ewbw = ewbw->next;
	}
}

static void	export_lvar(const char *name)
{
	char	*value;

	if ((value = get_lvar(name)))
	{
		(void)set_env_var(NULL, name, value);
		del_lvar(name);
	}
	else if (!get_env_var(NULL, name))
		(void)set_lvar_exported(name);
}

int			export_bltn(int ac, char **av)
{
	int		idx;
	int		export_opts;
	int		exval;

	idx = 1;
	if ((export_opts = ft_args_opts(av, &idx, "p", NULL)) < 0)
		return (export_usage((char)-export_opts));
	if ((idx == 1 || (export_opts & 0x1)) && !av[idx])
	{
		print_vars();
		return (EXIT_SUCCESS);
	}
	exval = EXIT_SUCCESS;
	while (ac > 1 && av[idx])
	{
		if (!ft_strchr(av[idx], '='))
			export_lvar(av[idx]);
		else if (!set_env_from_str(NULL, av[idx]))
			exval = EXIT_FAILURE;
		idx++;
	}
	return (exval);
}
