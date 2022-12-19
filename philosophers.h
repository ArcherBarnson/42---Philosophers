/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:30:18 by bgrulois          #+#    #+#             */
/*   Updated: 2022/09/10 16:46:45 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOSPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_global
{
	pthread_mutex_t	**forks_mutexes;
	pthread_mutex_t	*display;
	struct timeval	*start_time;
	long unsigned	start;
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	int				a_philo_is_dead;
	pthread_mutex_t	*death_mutex;	
}					t_global;

typedef struct s_philo
{
	t_global		*gs;
	pthread_t		*thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	int				id;
	int				meals_eaten;
	pthread_mutex_t	*meals_mutex;
	long unsigned	death_time;
	pthread_mutex_t	*philo_data_race;
}					t_philo;

void			free_all(t_global *global, t_philo **philos);
void			free_global(t_global *global, int size);
void			free_philos(t_philo **philos, int size);
void			reset_global_vals(t_global *global, char **av);
void			set_threads(t_philo **philos);
void			thinking(t_philo *philo);
void			eating(t_philo *philo);
void			sleeping(t_philo *philo);
void			display_ctl(t_philo *philo, int mode);
void			print_msg(t_philo *philo, int mode);
void			init_forks(t_global *global, t_philo **philos, char **av);
size_t			ft_strlen(char *str);
int				ft_atoi(char *str);
int				ft_isdigit(char c);
int				check_args_validity(int ac, char **av);
int				atoi_all_args(int ac, char **av, t_global *global);
int				ft_parsing(int ac, char **av, t_global *global);
int				ft_death(t_philo **philos);
int				meals_limit_reached(t_philo **philos);
int				all_meals_eaten(t_philo *philo);
int				a_philo_died(t_philo *philo);
long unsigned	get_timestamp(t_global *global);
char			*ft_itoa(int n);
void			*ft_routine(void *arg);
void			*ft_alt_routine(void *arg);
t_global		*init_global(char **av);
t_global		*main_check(int ac, char **av);
t_philo			**init_philos(t_global *global, char **av);

#endif
