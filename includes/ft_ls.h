/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:16:56 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/04 19:20:03 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"

# include <sys/acl.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/errno.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

typedef struct			s_entry
{
	char				*directory;
	char				*perms;
	char				*username;
	char				*groupname;
	char				*date;
	char				*name;
	char				*filelink;
	char				*bsize;
	int					blocks;
	struct timespec		timpls;
	time_t				mtim;
	int					links;
	int					skip;
}						t_entry;

typedef	struct			s_flags
{
	int					hidden_files;
	int					detailed;
	int					time_sort;
	int					recursion;
	int					reverse;
}						t_flags;

typedef union			u_freebird_entry
{
	char				*addresses[8];
	t_entry				entry;
}						t_freebird_entry;

typedef int				(*t_cmp)(void*, void*);

/*
** Unsorted.
*/

void					parse_arg(char *arg, t_flags *flags);
t_flags					*init_flags(void);
void					rudimentary_ls(char *dir, t_flags *flags);
void					full_ls(char *dir, t_flags *flags);
int						count_dir(char *dir);
void					sort_entries(void **entries, int low,
							int high, t_cmp qsort_cmp);
t_cmp					getcmp(t_flags *flags);
void					read_entries(DIR *ptr, t_entry **entries, char *dir,
							t_flags *flags);
void					read_entry(t_entry *entry, char *name,
							char *d, t_flags *flags);
void					read_detailed(t_entry *entry, t_flags *flags);
void					ft_swap(void **a, void **b);
int						get_total_blksize(t_entry **entries, t_flags *flags);
void					get_full_date_str(t_entry *entry,
							time_t mtime, struct timespec spec);
void					print_entry(t_entry *entry, t_flags *flags,
							size_t *widths);
void					print_entries(t_entry **entries, t_flags *flags);
int						read_ls_arg(char *entry, t_flags *flags);
int						filetypeletter(int mode);
void					add_filestack(t_entry *arg);
void					add_ls_stack(t_entry *arg, t_entry ***ls_stack,
							int *ls_stacksize);
t_entry					*get_entry(char *file, t_flags *flags);
t_entry					**get_filestack(void);
int						get_filestack_count(void);
int						getwidth(int t);
t_entry					**get_entries(char *dir, t_flags *flags);
void					sort_ls_stack_alpha(t_entry **ls_stack,
							int ls_stacksize);
void					finish_ls_stack(t_entry ***ls_stack, int *ls_stacksize);
void					process_clusterfuck(t_entry **ls_stack,
							int ls_stack_size, t_flags *flags, int argc);
void					process_ls_stack_entries(t_entry **entries,
							t_flags *flags);
void					freebird_entry(t_entry *entry);
void					freebird_entries(t_entry **entries);
void					free_filestack(void);
char					*path_join(char *a, char *b);
int						count_entries(t_entry **entries);
void					write_error(char *name);

#endif
