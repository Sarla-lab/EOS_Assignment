#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int fd_src, fd_dst;
    struct stat st;
    void *src_addr, *dst_addr;
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }
    fd_src = open(argv[1], O_RDONLY);
    if (fd_src < 0) {
        perror("open source");
        return 1;
    }
    if (fstat(fd_src, &st) < 0) {
        perror("fstat");
        close(fd_src);
        return 1;
    }
    if (st.st_size == 0) {
        printf("Source file is empty.\n");
        close(fd_src);
        return 0;
    }
    if (st.st_size > (1ULL << 30)) {  
        printf("Error: File size exceeds 1 GB limit.\n");
        close(fd_src);
        return 1;
    }
    src_addr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd_src, 0);
    if (src_addr == MAP_FAILED) {
        perror("mmap source");
        close(fd_src);
        return 1;
    }
    fd_dst = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd_dst < 0) {
        perror("open destination");
        munmap(src_addr, st.st_size);
        close(fd_src);
        return 1;
    }
    if (ftruncate(fd_dst, st.st_size) < 0) {
        perror("ftruncate");
        munmap(src_addr, st.st_size);
        close(fd_src);
        close(fd_dst);
        return 1;
    }
    dst_addr = mmap(NULL, st.st_size, PROT_WRITE, MAP_SHARED, fd_dst, 0);
    if (dst_addr == MAP_FAILED) {
        perror("mmap destination");
        munmap(src_addr, st.st_size);
        close(fd_src);
        close(fd_dst);
        return 1;
    }
    memcpy(dst_addr, src_addr, st.st_size);
    munmap(src_addr, st.st_size);
    munmap(dst_addr, st.st_size);
    close(fd_src);
    close(fd_dst);
    printf("✅ File copied successfully! (%ld bytes)\n", st.st_size);
    return 0;
}
