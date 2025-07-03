#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 4096

// Function declarations
void socket_err(const char *msg);
void handle_request(int client_socket);  // Stub, define your own logic
void server();

int main(){
    server();

}


void server() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        socket_err("Socket creation failed");
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        socket_err("Bind failed");
    }

    // Listen
    if (listen(server_socket, 10) < 0) {
        socket_err("Listen failed");
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        handle_request(client_socket);
        close(client_socket);
    }

    close(server_socket);
}

// Proper definition of socket_err
void socket_err(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

// Example request handler (replace with your actual logic)
void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE - 1);
    printf("Received:\n%s\n", buffer);

    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n\r\n"
        "Hello from SockAuth!\n";
    write(client_socket, response, strlen(response));
}

