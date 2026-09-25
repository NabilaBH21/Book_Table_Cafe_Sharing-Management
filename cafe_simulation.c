#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#define CUSTOMERS 10
#define BOOKS 5
#define TABLES 3

// Book structure
typedef struct
{
    int id;
    int available;
} Book;

// Shared resources
Book books[BOOKS];

sem_t table_semaphore;
pthread_mutex_t book_mutex;

/*
 * Searches for an available book.
 * Mutex prevents multiple processes from
 * accessing the book inventory at the same time.
 */
int borrow_book(int customer_id)
{
    int book_id = -1;

    pthread_mutex_lock(&book_mutex);

    for (int i = 0; i < BOOKS; i++)
    {
        if (books[i].available)
        {
            books[i].available = 0;
            book_id = books[i].id;

            printf("Customer %d borrowed Book %d\n",
                   customer_id, book_id);

            break;
        }
    }

    pthread_mutex_unlock(&book_mutex);

    return book_id;
}

/*
 * Returns a book safely using a mutex.
 */
void return_book(int customer_id, int book_id)
{
    pthread_mutex_lock(&book_mutex);

    if (book_id >= 0 && book_id < BOOKS)
    {
        books[book_id].available = 1;

        printf("Customer %d returned Book %d\n",
               customer_id, book_id);
    }

    pthread_mutex_unlock(&book_mutex);
}

/*
 * Simulates a customer's experience
 * inside the cafe.
 */
void customer_process(int customer_id)
{
    printf("Customer %d is waiting for a table...\n",
           customer_id);

    // Wait for an available table
    sem_wait(&table_semaphore);

    printf("Customer %d got a table.\n",
           customer_id);

    // Try to borrow a book
    int book_id = borrow_book(customer_id);

    if (book_id == -1)
    {
        printf("Customer %d could not find an available book.\n",
               customer_id);
    }
    else
    {
        // Simulate reading time: 1–5 seconds
        srand(getpid());
        int reading_time = (rand() % 5) + 1;

        printf("Customer %d is reading Book %d for %d seconds.\n",
               customer_id, book_id, reading_time);

        sleep(reading_time);

        // Return the book
        return_book(customer_id, book_id);
    }

    // Customer leaves the cafe
    printf("Customer %d left the cafe and released the table.\n",
           customer_id);

    // Release the table
    sem_post(&table_semaphore);

    exit(0);
}

int main()
{
    pid_t pid;

    // Initialize books
    for (int i = 0; i < BOOKS; i++)
    {
        books[i].id = i;
        books[i].available = 1;
    }

    /*
     * Initialize semaphore.
     * Only TABLES customers can use tables
     * at the same time.
     */
    if (sem_init(&table_semaphore, 1, TABLES) != 0)
    {
        perror("Semaphore initialization failed");
        return 1;
    }

    /*
     * Initialize mutex for book inventory.
     */
    if (pthread_mutex_init(&book_mutex, NULL) != 0)
    {
        perror("Mutex initialization failed");
        return 1;
    }

    printf("============================================\n");
    printf("     BOOK & TABLE SHARING CAFE SIMULATION\n");
    printf("============================================\n");
    printf("Customers: %d\n", CUSTOMERS);
    printf("Books:     %d\n", BOOKS);
    printf("Tables:    %d\n", TABLES);
    printf("============================================\n\n");

    /*
     * Create customer processes using fork().
     */
    for (int i = 0; i < CUSTOMERS; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            return 1;
        }

        if (pid == 0)
        {
            // Child process
            customer_process(i + 1);
        }
    }

    /*
     * Parent process waits for all
     * customer processes.
     */
    for (int i = 0; i < CUSTOMERS; i++)
    {
        waitpid(-1, NULL, 0);
    }

    printf("\n============================================\n");
    printf("All customers have completed their visit.\n");
    printf("Cafe simulation finished successfully.\n");
    printf("============================================\n");

    // Clean up resources
    sem_destroy(&table_semaphore);
    pthread_mutex_destroy(&book_mutex);

    return 0;
}
```
