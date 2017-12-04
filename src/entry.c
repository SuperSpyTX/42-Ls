/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 18:32:46 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/03 22:20:36 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					count_dir(char *dir)
{
	DIR				*s;
	struct dirent	*entry;
	int				count;

	count = 0;
	s = opendir(dir);
	if (s == 0)
	{
		return (0);
	}
	while ((entry = readdir(s)))
		count++;
	closedir(s);
	return (count);
}

int					get_total_blksize(t_entry **entries, t_flags *flags)
{
	int				blks;
	int				i;

	blks = 0;
	i = -1;
	while ((entries[++i] != 0))
	{
		if (entries[i]->name[0] == '.' && flags->hidden_files == 0)
			continue;
		blks += entries[i]->blocks;
	}
	return (blks);
}

void				ft_swap(void **a, void **b)
{
	void			*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void				read_entry(t_entry *entry, char *name,
							char *d, t_flags *flags)
{
	entry->name = ft_strdup(name);
	entry->directory = (d ? ft_sprintf("%s", d) : ft_strdup(""));
	read_detailed(entry, flags);
}

void				read_entries(DIR *ptr, t_entry **entries,
							char *d, t_flags *flags)
{
	struct dirent	*entry;
	int				i;

	i = 0;
	while ((entry = readdir(ptr)))
	{
		entries[i] = ft_memalloc(sizeof(t_entry));
		read_entry(entries[i], entry->d_name, d, flags);
		i++;
	}
	entries[i] = 0;
}
