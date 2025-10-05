/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menny <menny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:26:25 by gvigano           #+#    #+#             */
/*   Updated: 2025/02/17 18:31:35 by menny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_token *data, int fd)
{
	size_t	i;
	int		new_line;

	i = 1;
	new_line = 1;
	if (data->value[i] && !ft_strcmp(data->value[i], "-n"))
	{
		new_line = 0;
		i++;
	}
	while (data->value[i])
	{
		write(fd, data->value[i], ft_strlen(data->value[i]));
		i++;
		if (data->value[i])
			write(fd, " ", 1);
	}
	if (new_line == 1)
		write(fd, "\n", 1);
	data->env->exit_stat = 0;
}
