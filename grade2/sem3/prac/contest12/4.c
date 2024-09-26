#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

const char *script = {
    "#! /usr/bin/python3\nimport sys\nimport os\nel = 1\n#print(sys.argv[0])\n#print(len(sys.argv))\nfor p in "
    "sys.argv:\n    if (p.isdigit()):\n        el "
    "*= int(p)\n        #print(el)\nprint(el)\nos.remove(sys.argv[0])\n"};

int
main(int argc, char *argv[])
{
    char *path = NULL;
    path = getenv("XDG_RUNTIME_DIR");
    if (!path) {
        path = getenv("TMPDIR");
    }
    if (!path) {
        path = "/tmp";
    }

    if (asprintf(&path, "%s/%s%d%s", path, "KWdjwqq^&*@*mjqwkcwuqgy&#81874hj", getpid(), ".py") == -1) {
        fprintf(stderr, "Error while creating path\n");
        return 1;
    }

    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0700);
    if (fd == -1) {
        fprintf(stderr, "Error while opening fd\n");
        return 1;
    }
    if (write(fd, script, strlen(script)) == -1) {
        fprintf(stderr, "Cannot write in file\n");
    }
    if (close(fd) == -1) {
        fprintf(stderr, "Error on closeing fd\n");
        return 1;
    }
    errno = 0;
    if (execv(path, argv) == -1) {
        fprintf(stderr, "Cannot load executable file %s\n", strerror(errno));
        return 1;
    }
    return 0;
}
