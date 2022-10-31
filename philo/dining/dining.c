/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dining.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 03:02:50 by rpicot        #+#    #+#                 */
/*   Updated: 2022/10/31 01:14:39 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../philo.h"

static int	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printer(philo, forks);
	update_die_time(philo);
	if (check_die_time(philo) == FAILURE)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (FAILURE);
	}
	pthread_mutex_lock(philo->right_fork);
	printer(philo, forks);
	update_die_time(philo);
	if (check_die_time(philo) == FAILURE)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	eating(t_philo *philo)
{
	int	code;

	if (grab_forks(philo) == SUCCESS)
	{
		philo->header[DIE_TIME] = philo->die_time;
		if (philo->need_to_eat)
			philo->header[MEAL_SIZE]--;
		code = act_in_time(philo->header[EAT_TIME], philo, eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (code == FAILURE || (philo->header[MEAL_SIZE] == 0
				&& philo->need_to_eat))
			return (FAILURE);
		return (SUCCESS);
	}
	return (FAILURE);
}

static int	dining_init(t_philo *philo, int think_time)
{
	pthread_mutex_lock(philo->start_thread);
	pthread_mutex_unlock(philo->start_thread);
	if (philo->header[PHILO_ID] % 2 == 0)
	{
		usleep(200);
		think_time = philo->header[EAT_TIME];
	}
	return (think_time);
}

void	*dining(void *void_philo)
{
	t_philo	*philo;
	int		think_time;

	think_time = 0;
	philo = (t_philo *)void_philo;
	think_time = dining_init(philo, think_time);
	while (1)
	{
		if (think_time)
			if (act_in_time(think_time, philo, think) == FAILURE)
				break ;
		if (eating(philo) == FAILURE)
			break ;
		if (act_in_time(philo->header[SLEEP_TIME], philo, sleeping) == FAILURE)
			break ;
		think_time = philo->header[EAT_TIME] - philo->header[SLEEP_TIME];
	}
	return (NULL);
}
