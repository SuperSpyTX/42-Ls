/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 19:22:21 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/04 01:41:39 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char					*unixmask(int bits)
{
	if (bits == 1)
		return ("--x");
	else if (bits == 2)
		return ("-w-");
	else if (bits == 3)
		return ("-wx");
	else if (bits == 4)
		return ("r--");
	else if (bits == 5)
		return ("r-x");
	else if (bits == 6)
		return ("rw-");
	else if (bits == 7)
		return ("rwx");
	return ("---");
}

int						filetypeletter(int mode)
{
	char				c;

	if (S_ISREG(mode))
		c = '-';
	else if (S_ISBLK(mode))
		c = 'b';
	else if (S_ISCHR(mode))
		c = 'c';
	else if (S_ISFIFO(mode))
		c = 'p';
	else if (S_ISLNK(mode))
		c = 'l';
	else if (S_ISSOCK(mode))
		c = 's';
	else if (S_ISDIR(mode))
		c = 'd';
	else
		c = '?';
	return (c);
}

char					*perms(int mode)
{
	char				*bits;

	bits = (char*)ft_memalloc(12);
	bits[0] = filetypeletter(mode);
	ft_strcpy(&bits[1], unixmask((mode >> 6) & 7));
	ft_strcpy(&bits[4], unixmask((mode >> 3) & 7));
	ft_strcpy(&bits[7], unixmask(mode & 7));
	if (mode & S_ISUID)
		bits[3] = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
		bits[6] = (mode & S_IXGRP) ? 's' : 'l';
	if (mode & S_ISVTX)
		bits[9] = (mode & S_IXOTH) ? 't' : 'T';
	bits[10] = ' ';
	bits[11] = '\0';
	return (bits);
}

void					suffix(char *path, t_entry *entry)
{
	acl_t				acl;
	acl_entry_t			dummy;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl = 0;
	}
	if (listxattr(path, 0, 0, 0) > 0)
		entry->perms[10] = '@';
	else if (acl != 0)
		entry->perms[10] = '+';
	(acl ? acl_free(acl) : 0);
	if (entry->perms[0] == 'l')
	{
		entry->filelink = (char*)ft_memalloc(500);
		readlink(path, entry->filelink, 500);
	}
}

void					read_detailed(t_entry *entry, t_flags *flags)
{
	struct stat			file;
	char				*join;

	join = path_join(entry->directory, entry->name);
	if ((flags->detailed == 1 ? lstat(join, &file) : stat(join, &file)) != 0)
	{
		write_error(entry->name);
		entry->skip = 1;
		free(join);
		return ;
	}
	entry->skip = 0;
	entry->perms = perms(file.st_mode);
	suffix(join, entry);
	free(join);
	entry->links = file.st_nlink;
	entry->username = ft_strdup(getpwuid(file.st_uid)->pw_name);
	entry->groupname = ft_strdup(getgrgid(file.st_gid)->gr_name);
	entry->bsize = file.st_size;
	entry->blocks = file.st_blocks;
	entry->mtim = file.st_mtime;
	entry->timpls = file.st_mtimespec;
	get_full_date_str(entry, file.st_mtime, file.st_mtimespec);
}
