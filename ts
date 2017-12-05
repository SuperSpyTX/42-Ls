#!/bin/bash
PREFIX="/tmp";
touch ftls sysls
$HOME/Documents/42/ft_ls/ft_ls $@ >$PREFIX/ftls 2>/dev/null >$PREFIX/ftls
ls $@ 2>/dev/null >$PREFIX/sysls
diff -U3 $PREFIX/ftls $PREFIX/sysls
EC=$?
rm -f $PREFIX/ftls $PREFIX/sysls
exit $EC
