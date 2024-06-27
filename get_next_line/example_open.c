#include <fcntl.h>    // For open()
#include <unistd.h>   // For read(), close()
#include <stdio.h>    // For perror()
#include <stdlib.h>   // For exit()

int main() {
    // Open the file "example.txt" in read-only mode
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Buffer to store the read data
    char buffer[1024];
    ssize_t bytesRead;

    // Read the contents of the file
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Null-terminate the buffer to safely print it as a string
    buffer[bytesRead] = '\0';

    // Print the read data
    printf("Read %zd bytes: %s\n", bytesRead, buffer);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
	// if want to actually open the file visually, uncomment:
	// system("xdg-open example.txt");
    return 0;
}
