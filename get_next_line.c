/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthabit <mthabit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:30:17 by mthabit           #+#    #+#             */
/*   Updated: 2023/02/12 16:37:27 by mthabit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *store)
{
	char	*buffer;
	int		count;

	if (fd == -1 || read(fd, 0, 0) == -1)
		return (free(store), NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!store)
		store = ft_strdup("");
	count = 1;
	while (count > 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (!*store && count <= 0)
			return (free(buffer), free(store),
				store = NULL, buffer = NULL, NULL);
		buffer[count] = '\0';
		store = ft_strjoin(store, buffer);
		if (ft_check(store) >= 0)
			return (free(buffer), store);
	}
	return (free(buffer), store);
}

char	*take_line(char *store)
{
	int		i;
	char	*newstorage;

	if (!store)
		return (NULL);
	i = ft_check(store);
	if (i == -1)
	{
		newstorage = ft_strdup(store);
	}
	else
	{
		newstorage = malloc(i + 2);
		if (!newstorage)
			return (free(store), NULL);
		ft_strlcpy(newstorage, store, i + 2);
	}
	return (newstorage);
}

char	*updated_data(char *store)
{
	int		i;
	char	*updated_data;

	if (!store)
		return (NULL);
	i = ft_check(store);
	if (i == -1)
		return (free(store), NULL);
	else
		updated_data = ft_strdup(store + (i + 1));
	return (free(store), store = NULL, updated_data);
}

char	*get_next_line(int fd)
{
	static char		*store;
	char			*line;

	line = NULL;
	store = read_file(fd, store);
	line = take_line(store);
	if (line && !*line)
		return (NULL);
	store = updated_data(store);
	return (line);
}
