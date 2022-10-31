/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 14:59:44 by rpicot        #+#    #+#                 */
/*   Updated: 2022/10/31 00:10:32 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../philo.h"

void	init_monitor_time(int philo_size, t_global_container *container)
{
	struct timeval	start_time;
	int				j;

	j = 0;
	gettimeofday(&start_time, NULL);
	container->time = start_time.tv_usec / 1000 + start_time.tv_sec * 1000;
	while (j < philo_size)
	{
		container->philo[j].start_time = container->time;
		container->philo[j].previous_origin_time = container->time;
		j++;
	}
}

int	wait_threads(int philo_size, t_global_container *container)
{
	void	*retval;
	int		j;

	j = 0;
	while (j < philo_size)
	{
		if (pthread_join(container->philo[j].thread, &retval))
			return (0);
		j++;
	}
	return (1);
}

int	create_threads(int philo_size, t_global_container *container)
{
	int	j;

	j = 0;
	while (j < philo_size)
	{
		if (pthread_create(&(container->philo[j].thread), NULL,
				&dining, &(container->philo[j])))
			return (0);
		else
			j++;
	}
	if (pthread_create(&container->monitor_thread, NULL,
			&check_simulation_state, container))
		return (0);
	return (1);
}

void	free_threads(t_global_container *container)
{
	pthread_mutex_lock(&container->done_eating);
	container->existence = 0;
	pthread_mutex_unlock(&container->done_eating);
}

int	wait_monitor_thread(t_global_container *container)
{
	void	*retval;

	if (pthread_join(container->monitor_thread, &retval))
		return (0);
	return (1);
}
