/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:45:19 by amal              #+#    #+#             */
/*   Updated: 2025/07/17 03:03:21 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	print_usage(void)
{
	ft_putstr_fd("Usage: ./philo \"n_philo\" ", 2);
	ft_putstr_fd("\"time_to_die\" \"time_to_eat\" ", 2);
	ft_putendl_fd("\"time_to_sleep\" [n_meals]", 2);
}

static int	validate_arguments(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		print_usage();
		return (0);
	}
	if (!correct_args(argc - 1, argv + 1))
	{
		ft_putendl_fd("Invalid arguments", 2);
		return (0);
	}
	return (1);
}

static t_args	*create_args(int argc, char **argv)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	memset(args, 0, sizeof(t_args));
	if (!parse_args(argc - 1, argv + 1, args))
	{
		free(args);
		ft_putendl_fd("Invalid arguments", 2);
		return (NULL);
	}
	return (args);
}

static void	run_simulation(t_data *data)
{
	if (!create_philos_threads(data))
	{
		ft_putendl_fd("Error: Failed to create philosopher threads", 2);
		return;
	}
	if (pthread_create(&data->monitor, NULL, monitor_routine, data) != 0)
	{
		ft_putendl_fd("Error: Failed to create monitor thread", 2);
		join_philos_threads(data);
		return;
	}
	join_philos_threads(data);
	if (pthread_join(data->monitor, NULL) != 0)
		ft_putendl_fd("Error: Failed to join monitor thread", 2);
}

int	main(int argc, char **argv)
{
	t_args	*args;
	t_data	*data;

	if (!validate_arguments(argc, argv))
		return (1);
	args = create_args(argc, argv);
	if (!args)
		return (1);
	data = init_data(args);
	if (!data)
	{
		free(args);
		return (1);
	}
	run_simulation(data);
	destroy_data(data);
	free(args);
	return (0);
}
