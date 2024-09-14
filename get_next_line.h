#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

char *get_next_line(int fd);
char *ft_strjoin(char const *s1, char const *s2);
void ft_strmerge(char **dest, char *src);
char *extract_line(char **stored);
size_t ft_strlen(const char *s);
char *ft_strcpy(char *dst, const char *src);
char *ft_strcat(char *s1, const char *s2);
char *ft_strdup(const char *s1);
char *ft_strchr(const char *s, int c);

#endif
