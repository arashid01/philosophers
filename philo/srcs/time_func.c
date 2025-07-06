/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:08:09 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/05 22:37:45 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static long timestamp_ms(void)
{
    struct timeval  tv;
	long			time;

    gettimeofday(&tv, NULL);
    time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

long	init_timer(void)
{
	return (timestamp_ms());
}

long    current_time(long start_time)
{
	return (timestamp_ms() - start_time);
}
