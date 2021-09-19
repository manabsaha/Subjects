#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef float t;
#define FLT_MAX 3.401E+38
#define fileopen fopen("dataset.txt","r")

struct record{
	int id;
	int attr;
	t *data;
	int cluster_no;
};

/*Input from file to store records*/
void input_data(struct record *r,int id,int attr,FILE *dataset){
	int i;
	char c;
	t value;
	r[id].id = id+1;
	r[id].attr = attr;
	r[id].data = (t*) malloc(sizeof(t)*attr);
	c = fgetc(dataset);
	/*skipping the label*/
	while(c!='\t'){
		c = fgetc(dataset);
	}
	/*recording the values*/
	for(i=0;i<attr;i++){
		fscanf(dataset,"%f",&value);
		r[id].data[i] = value;
	}
	r[id].cluster_no = -1;
}

/*calculating the distance -> Manhattan Distance*/
t distance(t* p1,t* p2,int attr){
	int i;
	t dist = 0;
	for(i=0;i<attr;i++){
		dist += abs(p1[i]-p2[i]);
	}
	return dist;
}

/*Distance-cost array for the medoid*/
t cost(struct record *r,int attr,int rows,int p,int q){
	t *cost1;
	t *cost2;
	t d,totalcost = 0;
	int i,j = 0;
	cost1 = (t*) malloc(sizeof(t)*(rows-2));
	cost2 = (t*) malloc(sizeof(t)*(rows-2));
	for(i=0;i<rows;i++){
		if(i!=p && i!=q){
			d = distance(r[i].data,r[p].data,attr);
			cost1[j++] = d;
		}
	}
	j=0;
	for(i=0;i<rows;i++){
		if(i!=p && i!=q){
			d = distance(r[i].data,r[q].data,attr);
			cost2[j++] = d;
		}
	}
	for(i=0;i<rows;i++){
		r[i].cluster_no = -1;
	}
	r[p].cluster_no = 1;
	r[q].cluster_no = 2;
	for(i=0,j=0;i<rows-2;i++,j++){
		if(cost1[i]<cost2[i]){
			totalcost += cost1[i];
			if(j==p || j==q){
				j += 1;
			}
			r[j].cluster_no = 1;
		}
		else{
			totalcost += cost2[i];
			if(j==p || j==q){
				j += 1;
			}
			r[j].cluster_no = 2;
		}
	}
	return totalcost;
}

/*Selection of medoid*/
t medoid(struct record *r,int attr,int rows){
	int i,j,p,q;
	t x,y=FLT_MAX;
	for(i=0;i<rows;i++){
		for(j=0;j<rows;j++){
			if(i!=j){
				x = cost(r,attr,rows,i,j);
				printf("%f\n",x);
				if(x<y){
					y = x;
					p = i;
					q = j;
				}
			}
		}
	}
	/*Setting clusters for the minimum cost.*/
	printf("%d %d\n",p,q);
	x = cost(r,attr,rows,p,q);
	return x;
}

/*Driver function*/
/**/
int main(){
	FILE *dataset;
	struct record *r;
	int rows = 1,attr = 0,i;
	char c;
	t min_cost;
	/*Reading number of rows*/
	dataset = fileopen;
	if(dataset == NULL){
		printf("Cannot open file\n");
		return 0;
	}
	c = fgetc(dataset);
    while (c != EOF)
    {
    	if(c=='\n'){
    		rows += 1;
		}
        printf ("%c", c);
        c = fgetc(dataset);
    }
    fclose(dataset);
    /*Reading number of attributes*/
    dataset = fileopen;
    c = fgetc(dataset);
    while(c!='\n'){
    	if(c=='\t'){
    		attr += 1;
		}
		c = fgetc(dataset);
	}
	fclose(dataset);
	printf("\nRows: %d\n",rows);
    printf("Attributes: %d\n",attr);
    /*Structure pointer*/
	r = (struct record*) malloc(sizeof(struct record)*rows);
	dataset = fileopen;
	for(i=0;i<rows;i++){
		input_data(r,i,attr,dataset);
	}
	fclose(dataset);
	printf("Clustering the dataset with 2 clusters - numbered 1 and 2.\n");
	min_cost = medoid(r,attr,rows);
	for(i=0;i<rows;i++){
		printf("SL Number %d : Cluster %d\n",r[i].id,r[i].cluster_no);
	}
	printf("The minimum cost is: %f\n",min_cost);
	free(r);
	return 0;
}
