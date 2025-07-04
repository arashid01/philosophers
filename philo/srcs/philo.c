/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:45:19 by amal              #+#    #+#             */
/*   Updated: 2025/07/04 00:14:20 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int parse_args(int argc, char **argv, t_args *args)
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

int main(int argc, char **argv)
{
	t_args	*args;
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Usage: ./philo \"n_philo\" \"time_to_die\" \"time_to_eat\" \"time_to_sleep\" [n_meals]", 2);
		return (1);
	}
	argc--;
	argv++;
	if (!correct_args(argc, argv))
	{
		ft_putendl_fd("Invalid arguments", 2);
		return (1);
	}
	args = malloc(sizeof(t_args));
	if (!args)
		return (1);
	memset(args, 0, sizeof(t_args));
	if (!parse_args(argc, argv, args))
	{
		free(args);
		ft_putendl_fd("Invalid arguments", 2);
		return(1);
	}
	data = init_data(args);
	if (!data)
	{
		free(args);
		return (1);
	}
	// here
	int i = 0;
	while (i < data->args.num_of_philos)
	{
		printf("Philo[%d] | L = %d | R = %d\n", data->philos[i].id, i, (i + 1) % data->args.num_of_philos);
		i++;
	}
	destroy_data(data);
	free(args);
	// here
	return (0);
}
