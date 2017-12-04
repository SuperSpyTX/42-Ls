#* ************************************************************************** */
#*                                                                            */
#*                                                        :::      ::::::::   */
#*   Makefile                                           :+:      :+:    :+:   */
#*                                                    +:+ +:+         +:+     */
#*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
#*                                                +#+#+#+#+#+   +#+           */
#*   Created: 2017/04/18 03:42:42 by jkrause           #+#    #+#             */
#*   Updated: 2017/06/11 02:45:14 by jkrause          ###   ########.fr       */
#*                                                                            */
#* ************************************************************************** */
# ----------------- Version 1.5 --------------------- #

# ------------- Automated Configuration ------------- #
CFLAGS = -g  -Wall -Werror -Wextra
FT_LS_NAME = ft_ls
CFLAGS += -I includes
FT_LS_SRC = src/path.c \
src/parse_flags.c \
src/ft_ls.c \
src/read_ls.c \
src/print.c \
src/ls_stack.c \
src/system.c \
src/entry.c \
src/file_stack.c \
src/recursive.c \
src/comparators.c \
src/sort.c \
src/freebird.c \
libft/expand_functions/expand_write.c \
libft/expand_functions/expand_pad.c \
libft/expand_functions/expand_get_next_line_until.c \
libft/printf_functions/ft_printf.c \
libft/printf_functions/modules/parse_module.c \
libft/printf_functions/modules/string_module.c \
libft/printf_functions/modules/bufferwrite_module.c \
libft/printf_functions/modules/asterisks_module.c \
libft/printf_functions/modules/integer_module.c \
libft/printf_functions/modules/format_module.c \
libft/printf_functions/modules/bufferstring_module.c \
libft/printf_functions/modules/memorywrite_module.c \
libft/printf_functions/module_manager.c \
libft/standard_functions/ft_strrchr.c \
libft/standard_functions/ft_putstr.c \
libft/standard_functions/ft_strcmp.c \
libft/standard_functions/ft_strlcat.c \
libft/standard_functions/ft_memcpy.c \
libft/standard_functions/ft_no.c \
libft/standard_functions/ft_ltostr_base.c \
libft/standard_functions/ft_is_whitespace.c \
libft/standard_functions/ft_memmove.c \
libft/standard_functions/ft_strsplit.c \
libft/standard_functions/ft_strncpy.c \
libft/standard_functions/ft_lstmap.c \
libft/standard_functions/ft_lstadd.c \
libft/standard_functions/ft_striter.c \
libft/standard_functions/ft_atol.c \
libft/standard_functions/ft_strstr.c \
libft/standard_functions/ft_isdigit.c \
libft/standard_functions/ft_putnbr.c \
libft/standard_functions/ft_memccpy.c \
libft/standard_functions/ft_strdel.c \
libft/standard_functions/ft_memchr.c \
libft/standard_functions/ft_bzero.c \
libft/standard_functions/ft_isalnum.c \
libft/standard_functions/ft_putstr_fd.c \
libft/standard_functions/ft_lstiter.c \
libft/standard_functions/ft_lstdelone.c \
libft/standard_functions/ft_toupper.c \
libft/standard_functions/ft_strcpy.c \
libft/standard_functions/ft_lstnew.c \
libft/standard_functions/ft_strdup.c \
libft/standard_functions/ft_putnbr_fd.c \
libft/standard_functions/ft_striteri.c \
libft/standard_functions/ft_strmap.c \
libft/standard_functions/ft_putendl_fd.c \
libft/standard_functions/ft_memdel.c \
libft/standard_functions/ft_strnstr.c \
libft/standard_functions/ft_putchar.c \
libft/standard_functions/ft_isascii.c \
libft/standard_functions/ft_strlen.c \
libft/standard_functions/ft_strsub.c \
libft/standard_functions/ft_strnew.c \
libft/standard_functions/ft_memalloc.c \
libft/standard_functions/ft_putendl.c \
libft/standard_functions/ft_strncat.c \
libft/standard_functions/ft_strnchr.c \
libft/standard_functions/ft_itoa.c \
libft/standard_functions/ft_strncmp.c \
libft/standard_functions/ft_memcmp.c \
libft/standard_functions/ft_strtrim.c \
libft/standard_functions/ft_strequ.c \
libft/standard_functions/ft_putchar_fd.c \
libft/standard_functions/get_next_line.c \
libft/standard_functions/ft_memset.c \
libft/standard_functions/ft_isalpha.c \
libft/standard_functions/ft_itoa_base.c \
libft/standard_functions/ft_strcat.c \
libft/standard_functions/ft_tolower.c \
libft/standard_functions/ft_strnequ.c \
libft/standard_functions/ft_strjoin.c \
libft/standard_functions/ft_atoi.c \
libft/standard_functions/ft_strclr.c \
libft/standard_functions/ft_strmapi.c \
libft/standard_functions/ft_isprint.c \
libft/standard_functions/ft_lstdel.c \
libft/standard_functions/ft_strchr.c \
libft/standard_functions/ft_ishex.c \

FT_LS_OBJ = $(subst .c,.o, $(FT_LS_SRC))

# ------------------- Targets ----------------------- #

all: $(FT_LS_NAME)

%.o: %.c
	gcc $(CFLAGS) -c $? -o $@

$(FT_LS_NAME): $(FT_LS_OBJ)
	gcc $(FT_LS_OBJ) -o $(FT_LS_NAME)

re: clean all 

clean:
	/bin/rm -f $(FT_LS_OBJ)

fclean: clean
	/bin/rm -f $(FT_LS_NAME)
