/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 14:59:44 by rpicot        #+#    #+#                 */
/*   Updated: 2022/10/31 00:24:19 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../philo.h"

void	config_eating_option(t_philo *philo, int *need_to_eat)
{
	if (philo->header[MEAL_SIZE])
	{
		philo->need_to_eat = 1;
		*need_to_eat = 1;
	}
	else
	{
		philo->need_to_eat = 0;
		*need_to_eat = 0;
	}
}

int	config_mutexes(t_global_container *box, int philo_amount)
{
	int	i;

	i = 0;
	pthread_mutex_init(&box->printer, NULL);
	pthread_mutex_init(&box->done_eating, NULL);
	box->dying_lock = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * philo_amount);
	if (!box->dying_lock)
		return (0);
	while (i < philo_amount)
	{
		box->philo[i].simulation_stops = 0;
		pthread_mutex_init(&box->dying_lock[i], NULL);
		box->philo[i].dying_lock = &box->dying_lock[i];
		box->philo[i].printer = &box->printer;
		if (!config_left_fork(&box->philo[i]))
			return (0);
		i++;
	}
	config_right_forks(philo_amount, box);
	box->existence = 1;
	return (1);
}

int	configure_container(char **argv, int argc, int *header)
{
	int	i;
	int	check;

	i = 0;
	if (argc == 5)
		header[4] = 0;
	while (argc - 1)
	{
		check = ft_atoi(argv[i + 1]);
		if (check <= 0)
			return (0);
		header[i] = check;
		argc--;
		i++;
	}
	return (1);
}

int	configure_philo(t_global_container *container)
{
	int	philo_index;

	philo_index = 0;
	container->philo = malloc(sizeof(t_philo) * container->header[PHILO_SIZE]);
	if (!(container->philo))
		return (0);
	if (!config_mutexes(container, container->header[PHILO_SIZE]))
		return (0);
	while (philo_index < container->header[PHILO_SIZE])
	{
		config_printer(container->philo[philo_index].printer_data);
		config_header(container, philo_index);
		config_eating_option(&container->philo[philo_index],
			&container->need_to_eat);
		config_global_clock(&container->philo[philo_index], container);
		philo_index++;
	}
	return (1);
}
