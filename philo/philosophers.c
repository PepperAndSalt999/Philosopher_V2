/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 14:59:44 by rpicot        #+#    #+#                 */
/*   Updated: 2022/10/31 01:25:20 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	free_all(t_global_container *container)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&container->printer);
	pthread_mutex_destroy(&container->done_eating);
	pthread_mutex_destroy(&container->start_thread);
	while (i < container->header[PHILO_SIZE])
	{
		pthread_mutex_destroy(container->philo[i].dying_lock);
		pthread_mutex_destroy(container->philo[i].left_fork);
		free(container->philo[i].left_fork);
		i++;
	}
	free(container->dying_lock);
	free(container->philo);
}

int	main(int argc, char **argv)
{
	int					error_code;
	t_global_container	container;

	error_code = 0;
	if (argc >= 5 && argc <= 6)
	{
		if (configure_container(argv, argc, container.header))
		{
			if (configure_philo(&container))
			{
				error_code = monitor_threads(&container);
				free_all(&container);
			}
		}
	}
	if (!error_code)
		printf("Error\n");
	return (0);
}
