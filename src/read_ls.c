/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 16:23:58 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/04 01:42:30 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** This will replace the full_ls.c and rudimentary_ls.c files.
*/

int						read_ls_arg(char *entry, t_flags *flags)
{
	struct stat			statent;
	int					res;

	res = (flags->detailed == 1 ? lstat(entry, &statent)
			: stat(entry, &statent));
	if (res != 0)
	{
		write_error(entry);
		return (-1);
	}
	else if (filetypeletter(statent.st_mode) == 'd')
		return (2);
	return (1);
}

char					*path_join(char *a, char *b)
{
	if (ft_strlen(a) == 0)
		return (ft_sprintf("%s", b));
	else if (ft_strequ(a, "/") && ft_strstr(b, "/") == 0)
		return (ft_sprintf("%s%s", a, b));
	else
		return (ft_sprintf("%s/%s", a, b));
}

int						count_entries(t_entry **entries)
{
	int					g;
	int					ct;

	g = -1;
	ct = 0;
	while ((entries[++g] != 0))
		ct++;
	return (ct);
}

t_entry					*get_entry(char *file, t_flags *flags)
{
	t_entry				*entry;

	entry = (t_entry*)ft_memalloc(sizeof(t_entry));
	read_entry(entry, file, 0, flags);
	return (entry);
}

t_entry					**get_entries(char *dir, t_flags *flags)
{
	DIR					*s;
	t_entry				**entries;
	int					count;
	int					i;

	i = 0;
	count = count_dir(dir);
	entries = (t_entry**)ft_memalloc(sizeof(t_entry*) * (count + 1));
	s = opendir(dir);
	if (s != 0)
	{
		read_entries(s, entries, dir, flags);
		closedir(s);
	}
	entries[count] = 0;
	return (entries);
}
