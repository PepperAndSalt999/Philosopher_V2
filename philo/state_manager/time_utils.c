/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 14:59:44 by rpicot        #+#    #+#                 */
/*   Updated: 2022/10/31 00:19:57 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../philo.h"

int	compute_time(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_usec / 1000
		+ current_time.tv_sec * 1000 - philo->start_time);
}

void	update_die_time(t_philo *philo)
{
	unsigned int	swap_time;

	swap_time = compute_time(philo);
	if (philo->previous_origin_time == philo->start_time)
		philo->header[DIE_TIME] -= swap_time;
	else
		philo->header[DIE_TIME] -= (swap_time - philo->previous_origin_time);
	philo->previous_origin_time = swap_time;
}

int	act_in_time(int action_duration, t_philo *philo, int action)
{
	int		start_time;

	if (action_duration >= philo->header[DIE_TIME])
		action_duration = philo->header[DIE_TIME];
	start_time = compute_time(philo);
	printer(philo, action);
	while ((compute_time(philo) - start_time) < action_duration)
	{
		usleep(1000);
		if (another_philo_dying(philo) == FAILURE)
			return (FAILURE);
	}
	update_die_time(philo);
	return (check_die_time(philo));
}
