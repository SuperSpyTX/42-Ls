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
divert(-1)

# ------------- Real Configuration ------------------ #
define(MK_NUM_OF_TARGETS, 1)
define(MK_FCLEAN_ON_RE, 0)
define(MK_DEBUG, 1)

define(MK_FT_LS_NAME, ft_ls)
define(MK_FT_LS_ISLIB, 0)
define(MK_FT_LS_INCLUDE_DIRS, includes)
define(MK_FT_LS_SRC_DIRS, src libft)
define(MK_FT_LS_DEBUG, 0)
define(MK_FT_LS_LITE, 0)

# ------------ Automated Variables ------------------ #
define(MK_AUTO_ISLINUX, ifelse(esyscmd(uname -s | tr -d '\n'), `Darwin', 0, 1))
define(MK_AUTO_COMPILER,ifelse(MK_AUTO_ISLINUX, 1, clang, gcc))

define(MK_FT_LS_AUTO_SRC_DIR, patsubst(MK_FT_LS_SRC_DIRS,` ',`````,'''''))
pushdef(`MK_FT_LS_AUTO_SRC_DIR', ifelse(MK_FT_LS_SRC_DIRS,.,.,{MK_FT_LS_AUTO_SRC_DIR}))
define(MK_FT_LS_AUTO_SRC, esyscmd(bash -c 'find MK_FT_LS_AUTO_SRC_DIR -type f -name "*.c" | sed -e "s/$/ \\\/g"'))
define(MK_FT_LS_AUTO_SRC_DIR, patsubst(MK_FT_LS_SRC_DIRS,` ',```,'''))
define(MK_FT_LS_AUTO_INCLUDE_DIR, -I patsubst(MK_FT_LS_INCLUDE_DIRS,` ',``` -I '''))

divert(0)
# ------------- Automated Configuration ------------- #
CFLAGS = ifelse(MK_DEBUG, 1,-g) ifelse(MK_AUTO_ISLINUX,1,-fPIC) -Wall -Werror -Wextra
FT_LS_NAME = ifelse(MK_FT_LS_ISLIB, 1, MK_FT_LS_NAME.a, MK_FT_LS_NAME)
CFLAGS += MK_FT_LS_AUTO_INCLUDE_DIR
FT_LS_SRC = MK_FT_LS_AUTO_SRC
FT_LS_OBJ = $(subst .c,.o, $(FT_LS_SRC))

# ------------------- Targets ----------------------- #

all: $(FT_LS_NAME)

%.o: %.c
	MK_AUTO_COMPILER $(CFLAGS) -c $? -o $@

$(FT_LS_NAME): $(FT_LS_OBJ)
	ifelse(MK_FT_LS_ISLIB, 0,MK_AUTO_COMPILER $(FT_LS_OBJ) -o $(FT_LS_NAME),
	/bin/rm -f $(FT_LS_NAME)
	ar rcs $(FT_LS_NAME) $(FT_LS_OBJ))dnl


re: ifelse(MK_FCLEAN_ON_RE, 1,f)clean all dnl


clean:
	/bin/rm -f $(FT_LS_OBJ)

fclean: clean
	/bin/rm -f $(FT_LS_NAME)
