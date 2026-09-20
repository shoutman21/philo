*This project has been created as part of the 42 curriculum by shoutman.*

## Description

Philosophers simulates philosophers sharing forks around a table. Each
philosopher is a thread, and mutexes protect the forks. A philosopher who
doesn't eat in time dies, and the simulation stops.

## Instructions

```sh
cd philo
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```sh
./philo 5 800 200 200
```

## Resources

- [Dining philosophers problem – Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- `man pthread_create`, `man pthread_mutex_init`

**AI usage**: AI was used to help write robust tests for this project.
