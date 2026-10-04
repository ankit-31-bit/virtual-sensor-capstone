#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    int fd;
    char buffer[32];

    fd = open("/dev/vsensor", O_RDONLY);

    if (fd < 0)
    {
        perror("Failed to open /dev/vsensor");
        return 1;
    }

    printf("Virtual Sensor Monitor\n");
    printf("----------------------\n");

    while (1)
    {
        lseek(fd, 0, SEEK_SET);

        int n = read(fd, buffer, sizeof(buffer) - 1);

        if (n > 0)
        {
            buffer[n] = '\0';
            buffer[strcspn(buffer, "\n")] = '\0';
            printf("Temperature: %s°C\n", buffer);           
            fflush(stdout);
        }

        sleep(2);
    }

    close(fd);
    return 0;
}
