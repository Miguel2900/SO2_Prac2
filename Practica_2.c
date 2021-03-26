#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>


void create_directory(char *directory_name, char *file_name);
void create_file(char *directory_name, char *file_name);
void make_symbolic_link(char *filename);
void make_hard_link(char *filename);
void list_file_attributes(char *filename);
void list_directory_attributes(char *directory_name);
void check_directory(char *directory_name, char *file_name);

void main(int argc, char **argv)
{
    if (argc > 2)
    {
        check_directory(argv[1], argv[2]);
        create_directory(argv[1], argv[2]);
    }
    else
    {
        printf("Debe ingresar nombre del folder y archivo\n");
    }
    
}

void check_directory(char *directory_name, char *file_name)
{
    DIR *dir = opendir(directory_name);
    FILE *file = fopen(file_name, "r");
    if (dir)
    {
        printf("Ingrese nuevo nombre del folder\n");
        scanf("%s", directory_name);
        closedir(dir);
    }
    if (file)
    {   
        printf("Ingrese nuevo nombre del archivo con el formato: Nombre_del_folder/Nombre_del_archivo.txt\n");            
        scanf("%s", file_name);
        fclose(file);
    }
}
void create_directory(char *directory_name, char *file_name)
{
    int check;
    char *actual_directory = directory_name;
    if (!mkdir(directory_name, 0777))
    {
        create_file(directory_name, file_name);
        make_symbolic_link(file_name);
        make_hard_link(file_name);
        list_file_attributes(file_name);
        list_directory_attributes(directory_name);
    }
    else
    {
        printf("No se pudo crear el directorio");
    }
}   

void create_file(char *directory_name, char *file_name)
{
    char *names = {"Miguel Angel Ledesma Ortiz\nAnibal Emilio Martel Chavez\nLiam Daniel Villa Vazquez\nMayra Antonieta hernangez Galvan\nAndre Jesus Macias Rosriguez\nAramis Quiroz Tapia"};
    FILE* participants = fopen(file_name, "w+");
    if(participants)
    {
        if (fwrite(names, strlen(names), 1, participants))
        {
            printf("Archivo creado correctamente\n");
        }
        else
        {
            printf("No se pudo escribir en el archivo\n");
        }
        fclose(participants);
    }
}

void make_symbolic_link(char *filename)
{
    char *symbolic = {"symbolic_link"};
    if (!symlink(filename, symbolic))
    {
        printf("Enlace simbolico creado\n");
    }
    else
    {
        printf("No se pudo crear el enlace simbolico\n");
    }
}

void make_hard_link(char *filename)
{
    char *hard = {"hard_link"};
    if (!link(filename, hard))
    {
        printf("Enlace fisco creado\n");
    }
    else
    {
        printf("No se pudo crear el enlace fisico\n");
    }
}

void list_file_attributes(char*filename)
{
    struct stat file_stat;
    if (!stat(filename, &file_stat))
    {
        printf("\nAtributos del archivo %s\n", filename);
        printf("Numero de inodo %ld\n", file_stat.st_ino);
        printf("Tamaño en bytes %ld\n", file_stat.st_size);
        printf("Numero de enlaces %ld\n", file_stat.st_nlink);
    }
}

void list_directory_attributes(char *directory_name)
{
    struct dirent* dirInfo;
    DIR* dirPtr = opendir("./");
    if (dirPtr)
    {
        printf("\nContenido de la carpeta:\n");
        while (dirInfo = readdir(dirPtr))
        {
            printf("Nombre del archivo %s\n",dirInfo->d_name);
            printf("Numero del inodo %ld\n\n", dirInfo->d_ino);
        }
        free(dirInfo);
        free(dirPtr);
    }   
}