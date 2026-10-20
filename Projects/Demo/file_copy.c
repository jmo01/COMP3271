/*
 * copy a file to another file
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // These four header files are necessary to use file i/o functions.
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/* argv[1]: from */
/* argv[2]: to */
int main(int argc, char* argv[]) {
    int in, out;
    char buf[128];
    ssize_t bytes_read;

    // Safety check: Ensure the user provided exactly two file arguments
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(1);
    }

    // Open the source file for reading
    in = open(argv[1], O_RDONLY); // O_RDONLY is defined in /usr/include/sys/types.h
    if (in < 0) {
        printf("Cannot open the file %s\n", argv[1]);
        exit(1);
    }

    // Open the destination file for writing (create if it doesn't exist, truncate if it does)
    out = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    if (out < 0) {
        printf("Cannot create the file %s\n", argv[2]);
        exit(1);
    }

    printf("Copying bytes to %s and printing to screen:\n", argv[2]);
    printf("------------------------------------------------\n");

    // Read bytes from 'in' and write them into 'out'
    while ((bytes_read = read(in, buf, sizeof(buf))) > 0) {
        write(out, buf, bytes_read); // write into the destination file
        write(1, buf, bytes_read);   // print those bytes onto the screen (1 is standard output)
    }

    printf("\n------------------------------------------------\n");

    close(in);
    close(out);

    // Test if the two files have the exactly same contents, and print the result
    in = open(argv[1], O_RDONLY);
    out = open(argv[2], O_RDONLY);
    
    int match = 1;
    char buf_in[128], buf_out[128];
    ssize_t read_in, read_out;
    
    while (match) {
        read_in = read(in, buf_in, sizeof(buf_in));
        read_out = read(out, buf_out, sizeof(buf_out));
        
        // If byte counts differ or the memory block doesn't match, flag as false
        if (read_in != read_out || memcmp(buf_in, buf_out, read_in) != 0) {
            match = 0;
            break;
        }
        if (read_in == 0) break; // End of files reached identically
    }

    if (match) {
        printf("Result: The two files have exactly the same contents.\n");
    } else {
        printf("Result: The files differ.\n");
    }

    close(in);
    close(out);

    return 0;
}
