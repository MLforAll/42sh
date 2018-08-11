/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_globing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:23:15 by viclucas          #+#    #+#             */
/*   Updated: 2018/08/10 23:52:01 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_GLOBING_H
# define SH_GLOBING_H

# include <dirent.h>
# include <unistd.h>
# include <libft.h>
# include <stdlib.h>

typedef struct		s_glob
{
	int i;
	int u;
	int o;
}					t_glob;

int				count_name2(char *name);
int				count_name(char *test, int i);

/*
** sequence
*/

char			*start_exp(char *line, int *o, char *save);
int				remove_some(char *str, int ref);
int				ft_glob_parsing(char *str, char *test, int i);
char			*globing_sequence(char *line, int i);
char			**ft_strsplit_globing(char *str);
int				ft_pass_theses(int o, char *str);
size_t			ft_strlen_glob(char *str);
int				go_to_next_part(int i, char *s);
int				add_one(char *surface, int size);
int				parsing_glob(char *line);	
char			*return_letters(char *line, char *tmp, char **surface);
char			*replace_letter(char *line, int i, int *o);

/*
** old ??
*/

char			**ft_much_questions(char **ret, char *name, char *test);
char			*ft_strndup_glob(const char *s1, int nb);
char			*improve_surface(char *surface, char **test, char *path, int *o);
int				ft_get_on_top(char *line, int i, int c);
char			*ft_add_path(char *path, char *test);
char			**surface_of_work(char *line, int *i);
char 			**replace_char(char *surface, char *test, char **known);
char			**ft_glob_db(char **env, char *board);
char			*get_past_string(char *test, int *u);

#endif