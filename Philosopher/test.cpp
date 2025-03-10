#include <iostream>
#include <pthread.h>
#include <unistd.h>  // For sleep()
#include <cstdlib>   // For rand()

int NUM_PHILOSOPHERS = 5

// Philosopher states
enum { THINKING, HUNGRY, EATING };

// Mutex and condition variables
pthread_mutex_t mutex;
pthread_cond_t condition[NUM_PHILOSOPHERS];

// Philosopher state array
int state[NUM_PHILOSOPHERS];

// Fork ownership tracking
int fork_owner[NUM_PHILOSOPHERS] = {-1, -1, -1, -1, -1}; 

// Philosopher thread IDs
pthread_t philosophers[NUM_PHILOSOPHERS];
int philosopher_ids[NUM_PHILOSOPHERS] = {1, 2, 3, 4, 5};

// Function prototypes
void* philosopher(void* arg);
void pickup_forks(int philosopher_number);
void return_forks(int philosopher_number);
void test(int philosopher_number);
void print_fork_status();

void* philosopher(void* arg) {
    int id = *(int*)arg;

    while (true) {
        // Thinking
        int thinking_time = (1 + rand() % 3); // 1-3 seconds
        std::cout << "Philosopher #" << id << " is THINKING for " << thinking_time << "s.\n";
        usleep(thinking_time);

        // Try to pick up forks
        pickup_forks(id);

        // Eating
        int eating_time = 1000 * (1 + rand() % 3); // 1-3 seconds
        std::cout << "Philosopher #" << id << " is EATING for " << eating_time << "ms.\n";
        usleep(eating_time * 1000);

        // Return forks
        return_forks(id);
    }
}

void pickup_forks(int philosopher_number) {
    pthread_mutex_lock(&mutex);

    state[philosopher_number] = HUNGRY;
    std::cout << "Philosopher #" << philosopher_number << " is HUNGRY.\n";

    // Attempt to pick up forks
    test(philosopher_number);

    // If unable to eat, wait
    while (state[philosopher_number] != EATING)
        pthread_cond_wait(&condition[philosopher_number], &mutex);

    // Assign forks to the philosopher
    int left_fork = philosopher_number;
    int right_fork = (philosopher_number + 1) % NUM_PHILOSOPHERS;
    fork_owner[left_fork] = philosopher_number;
    fork_owner[right_fork] = philosopher_number;

    print_fork_status(); // Print fork assignment

    pthread_mutex_unlock(&mutex);
}

void return_forks(int philosopher_number) {
    pthread_mutex_lock(&mutex);

    state[philosopher_number] = THINKING;
    std::cout << "Philosopher #" << philosopher_number << " has finished EATING and is now THINKING.\n";

    // Release forks
    int left_fork = philosopher_number;
    int right_fork = (philosopher_number + 1) % NUM_PHILOSOPHERS;
    fork_owner[left_fork] = -1;
    fork_owner[right_fork] = -1;

    // Notify neighbors they may be able to eat
    test((philosopher_number + 4) % NUM_PHILOSOPHERS); // Left neighbor
    test((philosopher_number + 1) % NUM_PHILOSOPHERS); // Right neighbor

    print_fork_status(); // Print fork assignment

    pthread_mutex_unlock(&mutex);
}

void test(int philosopher_number) {
    int left = (philosopher_number + 4) % NUM_PHILOSOPHERS;
    int right = (philosopher_number + 1) % NUM_PHILOSOPHERS;

    if (state[philosopher_number] == HUNGRY &&
        state[left] != EATING &&
        state[right] != EATING) {
        
        state[philosopher_number] = EATING;
        pthread_cond_signal(&condition[philosopher_number]);
    }
}

void print_fork_status() {
    std::cout << "Fork Status:\n";
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (fork_owner[i] == -1)
            std::cout << "Fork #" << i << " is free.\n";
        else
            std::cout << "Fork #" << i << " is with Philosopher #" << fork_owner[i] << ".\n";
    }
    std::cout << "---------------------------\n";
}

int main() {
    pthread_mutex_init(&mutex, nullptr);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_cond_init(&condition[i], nullptr);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_create(&philosophers[i], nullptr, philosopher, &philosopher_ids[i]);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosophers[i], nullptr);

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_cond_destroy(&condition[i]);

    return 0;
}
