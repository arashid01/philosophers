/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:47:27 by amal              #+#    #+#             */
/*   Updated: 2025/07/01 13:21:16 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int ft_numlen(char *str)
{
	int i;

	i = 0;
	if (*str == '+')
		str++;
	while (str[i])
		i++;
	return (i);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int correct_args(int argc, char **argv)
{
	int i;
	int j;

	i = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '+')
				j++;
			if (!ft_isnum(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int ft_atoi(char *nbr)
{
	int	 i;
	long	num;

	i = 0;
	num = 0;
	if (nbr[i] == '+')
		i++;
	while (nbr[i])
	{
		num = (num * 10) + (nbr[i] - '0');
		i++;
	}
	if (ft_numlen(nbr) > 10 || num > INT_MAX || num <= 0)
		return(-2);
	return (num);
}

void ft_putendl_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}