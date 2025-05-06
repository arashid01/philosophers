/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:45:19 by amal              #+#    #+#             */
/*   Updated: 2025/05/07 01:11:43 by amal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_arguments(t_arguments *args, int argc, char **argv)
{
	args->num_of_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->num_of_meals = ft_atoi(argv[5]);
	else
		args->num_of_meals = -1;
	args->start_time = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_arguments	args;
	
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo <philos> <die> <eat> <sleep> [meals]\n");
		return (1);
	}
	if (!is_valid_number(argc, argv))
	{
		printf("Invalid number\n");
		return (1);
	}
	if (init_arguments(&args, argc, argv) != 0)
		return (1);

	printf("Philosophers: %d\n", args.num_of_philos);
	printf("Die time: %ldms\n", args.time_to_die);
	printf("Eat time: %ldms\n", args.time_to_eat);
	printf("Sleep time: %ldms\n", args.time_to_sleep);
	if (argc == 6)
		printf("Must eat: %d\n", args.num_of_meals);
	
	return (0);
}
