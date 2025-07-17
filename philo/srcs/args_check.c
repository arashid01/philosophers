/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:36:49 by amal              #+#    #+#             */
/*   Updated: 2025/07/15 19:18:56 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_numlen(char *str)
{
	int	i;

	i = 0;
	if (*str == '+')
		str++;
	while (str[i])
		i++;
	return (i);
}

int	correct_args(int argc, char **argv)
{
	int	i;
	int	j;

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

int	ft_atoi(char *nbr)
{
	int		i;
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
		return (-2);
	return (num);
}

int	parse_args(int argc, char **argv, t_args *args)
{
	args->num_of_philos = ft_atoi(argv[0]);
	if (args->num_of_philos == -2)
		return (0);
	args->num_of_forks = args->num_of_philos;
	args->time_to_die = ft_atoi(argv[1]);
	if (args->time_to_die == -2)
		return (0);
	args->time_to_eat = ft_atoi(argv[2]);
	if (args->time_to_eat == -2)
		return (0);
	args->time_to_sleep = ft_atoi(argv[3]);
	if (args->time_to_sleep == -2)
		return (0);
	if (argc == 5)
	{
		args->num_of_meals = ft_atoi(argv[4]);
		if (args->num_of_meals == -2)
			return (0);
	}
	else
		args->num_of_meals = -1;
	return (1);
}
