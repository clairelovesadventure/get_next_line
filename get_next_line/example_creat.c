#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main() {
    const char *filename = "example.txt";
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // 0644 permissions

    int fd = creat(filename, mode);
    
    if (fd == -1) {
        // Error handling
        fprintf(stderr, "Error creating file: %s\n", strerror(errno));
        return 1;
    }

    printf("File '%s' created successfully with file descriptor: %d\n", filename, fd);

    // Write some content to the file
    const char *content = "Hello, this is a test file.\n";
    ssize_t bytes_written = write(fd, content, strlen(content));
    
    if (bytes_written == -1) {
        fprintf(stderr, "Error writing to file: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    printf("Wrote %zd bytes to the file.\n", bytes_written);

    // Close the file
    if (close(fd) == -1) {
        fprintf(stderr, "Error closing file: %s\n", strerror(errno));
        return 1;
    }

    printf("File closed successfully.\n");

    return 0;
}
