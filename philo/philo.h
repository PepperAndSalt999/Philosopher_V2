/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 14:59:44 by rpicot        #+#    #+#                 */
/*   Updated: 2022/10/30 23:57:36 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

enum {
	ERRARG,
	ERRTHREAD,
	ERRJOIN,
	ERRMALLOC,
	SUCCESS,
	FAILURE
};

enum {
	think,
	forks,
	eat,
	sleeping,
	die,
	think_and_die
};

enum {
	PHILO_SIZE,
	DIE_TIME,
	EAT_TIME,
	SLEEP_TIME,
	PHILO_ID,
	MEAL_SIZE
};

typedef struct s_philo
{
	int				start_time;
	int				previous_origin_time;
	int				need_to_eat;
	int				amount_of_philo;
	int				die_time;
	char			*printer_data[6];
	int				simulation_stops;
	pthread_mutex_t	*dying_lock;
	pthread_mutex_t	*printer;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*start_thread;
	pthread_t		thread;
	int				header[6];
}		t_philo;

typedef struct s_global_container
{
	int				time;
	int				need_to_eat;
	int				existence;
	pthread_t		monitor_thread;
	pthread_mutex_t	*dying_lock;
	pthread_mutex_t	done_eating;
	pthread_mutex_t	start_thread;
	pthread_mutex_t	printer;
	t_philo			*philo;
	int				header[5];
}		t_global_container;

//LIBFT UTILS
int		ft_atoi(const char *str);
char	*ft_itoa(int nb);

//CONFIGURATION
//monitor
int		configure_container(char **argv, int argc, int *header);
int		configure_philo(t_global_container *box);
int		config_mutexes(t_global_container *box, int philo_amount);
//philosopher
void	config_printer(char **printer_data);
void	config_header(t_global_container *box, int philo_index);
void	config_eating_option(t_philo *philo, int *need_to_eat);
void	config_right_forks(int philo_amount, t_global_container *box);
void	config_global_clock(t_philo *philo, t_global_container *box);
int		config_left_fork(t_philo *philo);
//monitor
int		monitor_threads(t_global_container *container);

//THREAD EXECUTION
//main
void	*dining(void *phil);
//time
void	update_die_time(t_philo *philo);
int		compute_time(t_philo *philo);
int		act_in_time(int action_duration, t_philo *philo, int action);
//state managment
int		another_philo_dying(t_philo *philo);
int		check_die_time(t_philo *philo);
//Writing Utils
int		print(t_philo *philo, int action);
void	printer(t_philo *philo, int action);

//monitor utils
int		wait_threads(int philo_size, t_global_container *container);
int		create_threads(int philo_size, t_global_container *container);
void	free_threads(t_global_container *container);
int		wait_monitor_thread(t_global_container *container);
void	init_monitor_time(int philo_size, t_global_container *container);

//siimulation managing
void	*check_simulation_state(void *contain);

#endif