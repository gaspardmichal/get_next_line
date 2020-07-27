/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gamichal <gamichal@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/26 15:04:15 by gamichal     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/17 11:48:42 by gamichal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

t_fd	*set_fd(t_fd **begin, int fd)
{
	t_fd	*new;
	t_fd	*tmp;

	new = *begin;
	while (new)
	{
		tmp = new;
		if (fd == new->fd)
			return (new);
		new = new->next;
	}
	if (!(new = malloc(sizeof(t_fd))))
		return (NULL);
	new->fd = fd;
	if (!(new->buffer = malloc(BUFFER_SIZE + 1)))
		return (NULL);
	*new->buffer = 0;
	new->next = NULL;
	if (!*begin)
		*begin = new;
	else
		tmp->next = new;
	return (new);
}

void	update_buffer(char **buffer)
{
	char *tmp;

	if (endl(*buffer) != -1)
	{
		tmp = *buffer;
		*buffer = stringdup(*buffer + endl(*buffer) + 1);
		free(tmp);
	}
}

int		get_line(t_fd *new, char **line)
{
	int		res;

	res = 1;
	*line = 0;
	if (endl(new->buffer) == -1)
	{
		*line = line_join(*line, new->buffer);
		while (endl(new->buffer) == -1 &&
				(res = read(new->fd, new->buffer, BUFFER_SIZE)) > 0)
		{
			new->buffer[res] = 0;
			*line = line_join(*line, new->buffer);
		}
	}
	else
		*line = line_join(*line, new->buffer);
	update_buffer(&new->buffer);
	if (!*line || !new->buffer || res == -1)
		return (-1);
	return (res > 0 ? 1 : 0);
}

void	del_fd(t_fd **begin, t_fd *to_del)
{
	t_fd	*prev;
	t_fd	*current;

	current = *begin;
	prev = current;
	while (current != to_del)
	{
		prev = current;
		current = current->next;
	}
	if (prev == current)
		*begin = current->next;
	else
		prev->next = current->next;
	free(current->buffer);
	current->buffer = NULL;
	free(current);
	current = NULL;
}

int		get_next_line(int fd, char **line)
{
	static t_fd	*begin = NULL;
	t_fd		*new;
	int			ret;

	if (fd == -1 || BUFFER_SIZE < 0)
		return (-1);
	if (!(new = set_fd(&begin, fd)))
		return (-1);
	ret = get_line(new, line);
	if (!*line)
		*line = stringdup("");
	if (!ret || ret == -1)
		del_fd(&begin, new);
	return (ret);
}
