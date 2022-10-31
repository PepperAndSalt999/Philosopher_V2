/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 02:17:53 by rpicot        #+#    #+#                 */
/*   Updated: 2022/10/31 01:14:20 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../philo.h"

static int	end_simulation(t_global_container *container, int i)
{
	int	j;

	j = 0;
	pthread_mutex_lock(container->philo[i].dying_lock);
	if (container->philo[i].simulation_stops)
	{
		pthread_mutex_unlock(container->philo[i].dying_lock);
		printer(&container->philo[i], die);
		while (j < container->philo[i].header[PHILO_SIZE])
		{
			pthread_mutex_lock(container->philo[j].dying_lock);
			container->philo[j].simulation_stops = 1;
			pthread_mutex_unlock(container->philo[j].dying_lock);
			j++;
		}
		return (FAILURE);
	}
	pthread_mutex_unlock(container->philo[i].dying_lock);
	return (SUCCESS);
}

void	*check_simulation_state(void *contain)
{
	int					i;
	t_global_container	*container;

	i = 0;
	container = (t_global_container *)contain;
	while (1)
	{
		pthread_mutex_lock(&container->done_eating);
		if (container->existence == 0)
		{
			pthread_mutex_unlock(&container->done_eating);
			break ;
		}
		pthread_mutex_unlock(&container->done_eating);
		if (end_simulation(container, i) == FAILURE)
			break ;
		i++;
		if (i == container->header[PHILO_SIZE])
			i = 0;
		usleep(1000);
	}
	return (0);
}

int	monitor_threads(t_global_container *container)
{
	int	j;

	j = 0;
	pthread_mutex_init(&container->start_thread, NULL);
	while (j < container->header[PHILO_SIZE])
	{
		container->philo[j].start_thread = &container->start_thread;
		j++;
	}
	pthread_mutex_lock(&container->start_thread);
	if (!create_threads(container->header[PHILO_SIZE], container))
		return (0);
	init_monitor_time(container->header[PHILO_SIZE], container);
	pthread_mutex_unlock(&container->start_thread);
	if (!wait_threads(container->header[PHILO_SIZE], container))
		return (0);
	free_threads(container);
	if (!wait_monitor_thread(container))
		return (0);
	return (1);
}
