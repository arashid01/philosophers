/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:45:19 by amal              #+#    #+#             */
/*   Updated: 2025/07/06 11:59:52 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	create_philos_threads(data);
	pthread_create(&data->monitor, NULL, monitor_routine, data);
	// if (data->args.num_of_philos == 1)
	// {
	// 	pthread_mutex_lock(&data->death_mutex);
	// 	data->stop_flag = 1;
	// 	pthread_mutex_unlock(&data->death_mutex);
	// }
	printf("Death flag: %d\n", data->stop_flag);
	join_philos_threads(data);
	pthread_join(data->monitor, NULL);
	destroy_data(data);
	free(args);
	return (0);
}
