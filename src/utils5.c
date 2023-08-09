/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 01:19:20 by ale-sain          #+#    #+#             */
/*   Updated: 2023/01/13 19:28:54 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!big)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j]
			&& (i + j) < len && big[i + j])
		{
			j++;
			if (little[j] == '\0')
			{
				return ((char *)&big[i]);
			}
		}
		i++;
	}
	return (0);
}

char	*building_path(char *cmd, char **e)
{
	int		i;
	char	*path;
	char	*p;

	i = 0;
	while (e[i])
	{
		p = ft_strjoin(e[i], "/");
		path = ft_strjoin(p, cmd);
		free(p);
		if (access (path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
