/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gamichal <gamichal@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/21 10:01:53 by gamichal     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/17 11:56:23 by gamichal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_fd
{
	int				fd;
	char			*buffer;
	struct s_fd		*next;
}					t_fd;

int					endl(const char *s);
size_t				ft_strlen(const char *s);
char				*line_cat(char *dst, const char *src);
char				*line_join(char *line, const char *buffer);
char				*stringdup(const char *src);
int					get_next_line(int fd, char **line);

#endif
