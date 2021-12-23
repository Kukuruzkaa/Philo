/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:13:03 by ddiakova          #+#    #+#             */
/*   Updated: 2021/10/24 17:00:12 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	update_line_and_buffer(char **line, char buffer[BUFFER_SIZE + 1])
{
	int	i;

	i = ft_strchr_g(buffer, '\n');
	*line = ft_joinstr(*line, buffer, i);
	if (!*line)
		return (0);
	ft_getsubstr(buffer, i, BUFFER_SIZE - i);
	return (1);
}

int	free_and_exit(char **line, int ret_value)
{
	if (line && *line && ret_value == -1)
	{
		free(*line);
		*line = NULL;
	}
	return (ret_value);
}

int	buffer_is_empty(char *buffer)
{
	if (ft_strlen(buffer) == 0)
		return (1);
	else
		return (0);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	static char	buffer[FD_MAX][BUFFER_SIZE + 1];

	if (fd < 0 || fd >= FD_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = NULL;
	*line = (char *)malloc(sizeof(char));
	(*line)[0] = '\0';
	if (!update_line_and_buffer(line, buffer[fd]))
		free_and_exit(line, -1);
	while (buffer_is_empty(buffer[fd]))
	{
		ret = read(fd, buffer[fd], BUFFER_SIZE);
		buffer[fd][ret] = '\0';
		if (ret <= 0)
			return (free_and_exit(line, ret));
		if (!update_line_and_buffer(line, buffer[fd]))
			free_and_exit(line, -1);
	}
	ft_getsubstr(buffer[fd], 1, BUFFER_SIZE - 1);
	return (1);
}
