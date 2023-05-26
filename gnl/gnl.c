/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 07:37:27 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/26 18:13:22 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_next(char **line, char **str)
{
	int		len;
	char	*tmp;

	len = 0;
	while ((*str)[len] && (*str)[len] != '\n')
		len++;
	if ((*str)[len] == '\n')
	{
		*line = ft_substr(*str, 0, len + 1);
		tmp = ft_strdup(&(*str)[len + 1]);
		free(*str);
		*str = tmp;
		if ((*str)[0] == 0)
		{
			free(*str);
			*str = NULL;
		}
	}
	else
	{
		*line = ft_strdup(*str);
		free(*str);
		*str = NULL;
	}
	return (*line);
}

char	*ft_line(char **line, char **str, int fd, int ret)
{
	if (str[fd] == NULL && ret <= 0)
		return (NULL);
	else
		return (ft_next(line, &str[fd]));
}

char	*get_next_line(int fd)
{
	int			ret;
	static char	*str[10240];
	char		buf[GNL_BUFFER_SIZE + 1];
	char		*tmp;
	char		*line;

	if (fd < 0 || GNL_BUFFER_SIZE <= 0)
		return (NULL);
	ret = read(fd, buf, GNL_BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(str[fd], buf);
			free(str[fd]);
			str[fd] = tmp;
		}
		if (ft_strchr(str[fd], '\n'))
			break ;
		ret = read(fd, buf, GNL_BUFFER_SIZE);
	}
	return (ft_line(&line, str, fd, ret));
}
