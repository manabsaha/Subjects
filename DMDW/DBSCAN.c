#define minPts 10 // minimum points
#define eps 3 // epsiolon neighbourhood radius
#define name_of_file "abc.txt"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<list.h>

// structure to represent an instance of the data set
typedef struct data_record 
{
    // for lebel
    // 0 -> not defined
    // positive number for cluster number
    // -1 for noise
    int label, recordID;
    float *attributeVector;
} Row;

// distance function to find the similarity
// between two data points
float manhattan_distance (float *x, float *y, int attCount) 
{
    float distance = 0;
    // loop for substracting corresponding components
    for (int i = 0; i < attCount; i++) 
    {
        float dif = x[i] - y[i];
        if (dif < 0) 
            dif = dif * (-1);
        distance = distance + dif;
    }
    return distance;
}

// for detecting the number of attributes in the data
// array from the data base file, by detecting the number
// of tab characters in the array.
int get_att_count (char *line) 
{
    int i = 0, attCount = 0;
    while (line[i] != '\n') 
    {
        if (line[i] == '\t')
            attCount++;
        ++i;
    }
    return attCount;
}

Row * set_data(char line[], int attCount) 
{
    Row *row = (Row *) malloc(sizeof(Row));
    if (!row)
        return -1;
    row->attributeVector = (float *) malloc(attCount * sizeof(float));
    if (!row->attributeVector)
        return -1;
    char *token = strtok(line, "\t");
    row->recordID = (int)(*token);
    for (int i = 0; i < attCount; i++) 
    {
        token = strtok(NULL, "\t");
        row->attributeVector[i] = (*token);
    }
    row->label = 0;
    return row;
}

// to read data form the given file
// and will store it to the given root of BST
LinkedList * read_txt(char fileName[], LinkedList *DB) 
{
    FILE *file = fopen(fileName, "r");
    if (!file) 
    {
        printf("Unable to open : %s \n", fileName);
        return -1;
    }
    char line[500];
    fgets(line sizeof(line), file);
    int attCount = get_att_count(line);
    static int attributeCount = 0;
    attributeCount = attCount;
    int sizeofline = sizeof(line);
    while (fgets(line, sizeofline, file) != -1) 
    {
        Row *row = set_data(line, attCount);
        DB = push_back(DB, row);
    }
    fclose(file);
    return DB;
}

// utility function for the main algo
// function to find the neighbours of the given point
LinkedList * range_query(LinkedList *DB, Row *row) 
{
    LinkedList *neigbours = init_list();
    goto_top(DB);
    while(DB->curr != NULL) 
    {
        if (manhattan_distance(curr->info->attributeVector, row->attributeVector) <= eps)
            if (!present(neighbours, curr->info))
                push_back(neighbours, curr->info);
        goto_next(DB);
    }
    return neighbours;
}

// main algo function will add the clusters to the given data
int DBSCAN(LinkedList *DB) 
{
    int C = 0;
    goto_top(DB);
    while(DB->curr != NULL) // iterator for the points in DB
    {  
        LinkedList *seedSet = init_list();
        LinkedList *neighbours = init_list();
        if (DB->curr->info->label != 0) 
        {
            neighbours = range_query(DB, DB->curr->info);
            if (length_of_list(neighbours) < minPts)
                DB->curr->info->label = -1;
            else 
            {
                ++C;
                copylist_from_to(neighbours, seedSet);
                pop(seedSet, DB->curr); reset_list(neighbours);
                goto_top(seedSet);
                while(seedSet->curr != NULL) 
                {
                    if (seedSet->curr->info->lebel == -1)
                        seedSet->curr->info->lebel = C;
                    if (seedSet->curr->info->lebel = 0)
                    {
                        seedSet->curr->info->lebel = C;
                        neighbours = range_query(DB, seedSet->curr->info);
                        if (length_of_list(neighbours) >= minPts) 
                        {
                            add_lists(seedSet, neighbours);
                            reset_list(neighbours);
                        }
                    }
                }
            }
        }
        clear_list(neighbours); clear_list(seetSet);
    }
    return C;
}

//function to print the data in tabular formant
void print_table(LinkedList *DB)
{
    int rowCount = length_of_list(DB);
    goto_top(DB);
    while (DB->curr != NULL) 
    {
        printf("%d\t", DB->curr->info->lebel->recordID);
        for (int i = 0; i < attributeCount; i++)
        {
            if (i = attributeCount - 1)
                printf("%f\t%d\n", DB->curr->info->attributeVector[i], DB->curr->info->label);
            else
                printf("%f\t", DB->curr->info->attributeVector[i]);
        }
    }
}

// driver code 
int main() 
{
    char fileName[] = name_of_file;
    LinkedList *DB = init_list();   // list of records
    read_txt(fileName, DB);
    printf("Number of clusters formed = %d \n", DBSCAN(DB));
    printf("Number of attributes in the data = %d", attributeCount);
    printf("Number of records in Data Base = %d\n", length_of_list(DB));
    print_table(DB);
    clear_list(DB);
    return 0;
}
