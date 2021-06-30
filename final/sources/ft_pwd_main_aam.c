/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_main_aam.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 11:06:37 by aamarei           #+#    #+#             */
/*   Updated: 2021/06/29 11:06:38 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	write(1, dir, ft_strlen(dir));
	write(1, "\n", 1);
	free(dir);
	return (0);
}
