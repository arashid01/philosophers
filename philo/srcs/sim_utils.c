/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 03:14:18 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/06 03:15:37 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    print_state(t_philo *philo, const char *str)
{
    long time;

    pthread_mutex_lock(&philo->data->print_mutex);
    if (philo->data->stop_flag == 1)
    {
        pthread_mutex_unlock(&philo->data->print_mutex);
        return ;
    }
    time = current_time(philo->data->start_time);
    printf("%ld ms philo %d %s\n", time, philo->id, str);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void    ft_sleep(t_philo *philo, int time)
{
    long start_time;

    start_time = current_time(philo->data->start_time);
    while(current_time(philo->data->start_time) - start_time < time)
    {
        if (check_stop_flag(philo))
            return ;
        usleep(200);
    }
}
