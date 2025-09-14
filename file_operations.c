#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "file_operations.h"

int create_and_write_file(const char *filename, const char *content) {
    int fd;                 // file descriptor
    ssize_t bytes_written;  // number of bytes written

    printf("Creating file: %s\n", filename);
    printf("Content to write: %s\n", content);

    // Open or create file for writing
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }

    printf("File descriptor: %d\n", fd);

    // Write content
    bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return -1;
    }

    printf("Wrote %zd bytes to '%s'\n", bytes_written, filename);
    close(fd);
    return 0;
}

int read_file_contents(const char *filename) {
    int fd;                  // file descriptor
    ssize_t bytes_read;      // number of bytes read
    char buffer[1024];       // buffer to store file contents

    printf("Reading file: %s\n", filename);

    // open file for reading
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }

    // read contents in chunks
    while ((bytes_read = read(fd, buffer, sizeof(buffer)-1)) > 0) {
        buffer[bytes_read] = '\0';  // null terminate
        printf("%s", buffer);       // print to screen
    }

    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        return -1;
    }

    printf("\nFinished reading file '%s'\n", filename);
    close(fd);
    return 0;
}

