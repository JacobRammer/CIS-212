#include <stdio.h>

int main(int argc, char ** argv)
{
    if (argc < 3)
    {
        fprintf(stdout, "Usage: %s binaryfile textfile\n", argv[0]);
        return 1;
    }

    int a[4] = {1, 2, 3, 4};
    char b[4] = {'1', '2', '3', '4'};

    FILE *binary_file=fopen(argv[1], "w+");
    FILE *text_file = fopen(argv[2], "w+");

    fwrite(a, sizeof *a, 4, binary_file);
    fwrite(b, sizeof *b, 4, text_file);

    fprintf(text_file, "\n");
    for (int i = 0; i < 4; i++)
        fprintf(text_file, "%c\n", b[i]);

    rewind(binary_file);
    fseek(binary_file, 2 * sizeof(int), SEEK_SET);
    int buffer[2];
    fread(buffer, sizeof *buffer, 2, binary_file);

    // for (int i = 0; i < 0; i++)
    //     fprintf(text_file, "%d\n", buffer[i]);


    fclose(binary_file);
    fclose(text_file);
}