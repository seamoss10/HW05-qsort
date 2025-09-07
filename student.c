// ***
// *** You MUST modify this file
// ***

#include "hw5.h"

void StudentPrint(Student *stu, int num)
{
    printf("There are %d students\n", num);
    for (int ind = 0; ind < num; ind++)
    {
        printf("ID = %d, Name = %s\n", stu[ind].ID, stu[ind].name);
    }
}

// count the number of '\n' to determine the number of records
int countNewLine(FILE *fptr)
{
    int numline = 0;
    while (!feof(fptr))
    {
        int onechar = fgetc(fptr);
        if (onechar == '\n')
        {
            numline++;
        }
    }
    return numline;
}

/* This is the first function you need to implement */
bool StudentRead(char *filename, Student **stu, int *numelem) {
    FILE *fp = NULL;
    fp = fopen(filename, "r");

    if(!fp) {
        return false;
    }

    int numline = countNewLine(fp);

    int rtv;
    rtv = fseek(fp, 0, SEEK_SET);
    if (rtv == -1) {
        fclose(fp);
        return false;
    }

    Student *stuptr = NULL;
    stuptr = (Student *) malloc(numline * sizeof(Student)); // Pointer to an array of students

    for (int i = 0; i < numline; i++) {
        int ret = fscanf(fp, "%d %s", &stuptr[i].ID, stuptr[i].name);
        if (ret != 2) {
            fclose(fp);
            return false;
        }
    }

    *numelem = numline;
    *stu = stuptr;
    fclose(fp);
    return true;
}

/* This is the second function you need to implement */
bool StudentWrite(char *filename, Student *stu, int numelem) {
    FILE *fp = NULL;
    fp = fopen(filename, "w");

    if(!fp) {
        return false;
    }

    for (int i = 0; i < numelem; i++) {
        int res = fprintf(fp, "%d %s\n", stu[i].ID, stu[i].name);
        if (res < 0) {
            fclose(fp);
            return false;
        }
    }

    fclose(fp);
    return true;
}

/* This is the third function you need to implement */
void sortStudents(Student *stu, int numelem, int (*compar)(const void *, const void *)) {
    qsort(stu, numelem, sizeof(Student), compar);
}

/* This is the fourth function you need to implement */
int compareID(const void *p1, const void *p2) {
    Student *stu1 = (Student *) p1;
    Student *stu2 = (Student *) p2;

    if (stu1->ID > stu2->ID)  return 1;
    if (stu1->ID < stu2->ID)  return -1;
    return 0;
}

/* This is the fifth function you need to implement */
int compareName(const void *p1, const void *p2) {
    Student *stu1 = (Student *) p1;
    Student *stu2 = (Student *) p2;

    int res = strcmp(stu1->name, stu2->name);

    if (res != 0) {
        return res;
    }

    if (stu1->ID > stu2->ID)  return 1;
    if (stu1->ID < stu2->ID)  return -1;
    return 0;
}

/* This is the sixth function you need to implement */
bool areStudentsSorted(Student *stu, int numelem, int (*compar)(const void *, const void *)) {
    for (int i = 0; i < numelem - 1; i++) {
        int res = compar(&stu[i + 1], &stu[i]);
        if (res < 0) {
            return false;
        }
    }
    return true;
}
