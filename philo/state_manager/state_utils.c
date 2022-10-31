/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 02:19:35 by rpicot        #+#    #+#                 */
/*   Updated: 2022/10/31 01:23:44 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../philo.h"

int	check_die_time(t_philo *philo)
{
	if (philo->header[PHILO_SIZE] == 1)
	{
		printer(philo, die);
		return (FAILURE);
	}
	pthread_mutex_lock(philo->dying_lock);
	if (philo->header[DIE_TIME] <= 0 || philo->simulation_stops)
	{
		philo->simulation_stops = 1;
		pthread_mutex_unlock(philo->dying_lock);
		return (FAILURE);
	}
	pthread_mutex_unlock(philo->dying_lock);
	return (SUCCESS);
}

void	printer(t_philo *philo, int action)
{	
	unsigned int	time;
	char			*time_to_free;
	char			*header_to_free;

	time = compute_time(philo);
	pthread_mutex_lock(philo->printer);
	time_to_free = ft_itoa(time);
	header_to_free = ft_itoa(philo->header[4]);
	printf("%s ms philosopher %s %s \n", time_to_free,
		header_to_free, philo->printer_data[action]);
	free(time_to_free);
	free(header_to_free);
	pthread_mutex_unlock(philo->printer);
}

int	another_philo_dying(t_philo *philo)
{
	pthread_mutex_lock(philo->dying_lock);
	if (philo->simulation_stops)
	{
		pthread_mutex_unlock(philo->dying_lock);
		return (FAILURE);
	}
	pthread_mutex_unlock(philo->dying_lock);
	return (SUCCESS);
}
