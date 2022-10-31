/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 14:59:44 by rpicot        #+#    #+#                 */
/*   Updated: 2022/10/27 01:06:31 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../philo.h"

void	config_printer(char **printer_data)
{
	printer_data[0] = "is thinking\n";
	printer_data[1] = "has taken a fork\n";
	printer_data[2] = "is eating\n";
	printer_data[3] = "is sleeping\n";
	printer_data[4] = "has died\n";
	printer_data[5] = "think and die\n";
}

void	config_header(t_global_container *box, int philo_index)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		box->philo[philo_index].header[i] = box->header[i];
		i++;
	}
	box->philo[philo_index].header[PHILO_SIZE] = box->header[PHILO_SIZE];
	box->philo[philo_index].header[MEAL_SIZE] = box->header[4];
	box->philo[philo_index].header[PHILO_ID] = philo_index + 1;
}

int	config_left_fork(t_philo *philo)
{
	philo->left_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo->left_fork)
		return (0);
	pthread_mutex_init(philo->left_fork, NULL);
	return (1);
}

void	config_right_forks(int philo_amount, t_global_container *box)
{
	int	i;

	i = 0;
	if (philo_amount != 1)
	{
		box->philo[philo_amount - 1].right_fork = box->philo[0].left_fork;
		box->philo[0].right_fork = box->philo[1].left_fork;
		while (i < (philo_amount - 1))
		{
			box->philo[i].right_fork = box->philo[i + 1].left_fork;
			i++;
		}
	}
	else
		box->philo[0].right_fork = NULL;
}

void	config_global_clock(t_philo *philo, t_global_container *box)
{
	philo->die_time = box->philo[0].header[DIE_TIME];
}
