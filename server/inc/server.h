#ifndef __SERVER_H__
#define __SERVER_H__

#include "threads_handle.h"
#include "common.h"

int ipv4_socket_fd;

// Flag to indicate if server is finished
extern volatile sig_atomic_t finished;

/**
 * @brief Signal handler
 * 
 * @param sig Signal number
 * @param info Signal info
 * @param context Context
 */
void signal_handler(int sig, siginfo_t *info, void* context);

/**
 * @brief Initialize signal handler
 * 
 */
void signal_handler_init(void);

/**
 * @brief Create and asign new handle thread for a new client
 * 
 * @param args Client file descriptor
 */
void *connection_handler(void *args);

/**
 * @brief End connection with client
 * 
 * @param client_fd Client file descriptor
 */
void connection_end(int *client_fd);

/**
 * @brief Create IPV4 server socket
 * 
 * @param socket_port Socket port
 * @return error_code Error code
 */
error_code create_ipv4_socket(const uint16_t socket_port);

/**
 * @brief Accept new client connection
 * 
 * @param client_fd Client file descriptor
 * @return error_code Error code
 */
error_code accept_connection(int *client_fd);

/**
 * @brief Initialize server
 * 
 */
void init(void);

/**
 * @brief End server
 * 
 */
void end(void);

#endif // __SERVER_H__