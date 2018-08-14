/*
** get_newpath_init (static)
**
** char *curr -> pwd
** char *path -> cd's argument
*/

inline static char	*get_newpath_init(char *curr, char *path)
{
	if ((*path == '/' || !curr || ft_strequ(curr, "/")))
		return (ft_strdup(""));
	return (ft_strdup(curr));
}
