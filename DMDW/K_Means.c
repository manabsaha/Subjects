#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct record{
	int id;
	int attr;
	float *data;
	int cluster_no;
	int prev_cluster;
};

void input_data(struct record *r,int id,int attr,FILE *dataset){
	int i;
	char c;
	float value;
	r[id].id = id+1;
	r[id].attr = attr;
	r[id].data = (float*) malloc(sizeof(float)*attr);
	c = fgetc(dataset);
	while(c!='\t'){
		c = fgetc(dataset);
	}
	for(i=0;i<attr;i++){
		fscanf(dataset,"%f",&value);
		r[id].data[i] = value;
	}
	r[id].cluster_no = -1;
	r[id].prev_cluster = -1;
}

float distance(float* p1,float* p2,int attr){
	int i;
	float dist = 0;
	for(i=0;i<attr;i++){
		dist += abs(p1[i]-p2[i]);
	}
	return dist;
}

void kmean(struct record *r,int rows,int attr,float *p,float *q){
	float sum1=0,sum2=0,count1=0,count2=0,y,x;
	int i,j,set=1;
	float *u = (float*) malloc(sizeof(float)*attr);
	float *v = (float*) malloc(sizeof(float)*attr);
	for(i=0;i<rows;i++){
		x = distance(r[i].data,p,attr);
		y = distance(r[i].data,q,attr);
		if(x<=y){
			r[i].cluster_no = 1;
			for(j=0;j<attr;j++){
				u[j] += r[i].data[j];
			}
			count1++;
		}
		else{
			r[i].cluster_no = 2;
			for(j=0;j<attr;j++){
				v[j] += r[i].data[j];
			}
			count2++;
		}
	}
	for(i=0;i<attr;i++){
		u[i] /= count1;
		v[i] /= count2;
	}
	for(i=0;i<rows;i++){
		if(r[i].prev_cluster != r[i].cluster_no){
			set = 0;
			break;
		}
	}
	if(set==0){
		for(i=0;i<rows;i++){
			r[i].prev_cluster = r[i].cluster_no;
		}
		kmean(r,rows,attr,u,v);
	}
	else{
		printf("Clustered!!\n");
		return;
	}
}

int main(){
	FILE *dataset;
	struct record *r;
	int rows = 1,attr = 0,mid,i;
	char c;
	float min_cost;
	dataset = fopen("dataset.txt","r");
	c = fgetc(dataset);
    while (c != EOF)
    {
    	if(c=='\n'){
    		rows += 1;
		}
        c = fgetc(dataset);
    }
    fclose(dataset);
    dataset = fopen("dataset.txt","r");
    c = fgetc(dataset);
    while(c!='\n'){
    	if(c=='\t'){
    		attr += 1;
		}
		c = fgetc(dataset);
	}
	fclose(dataset);
	r = (struct record*) malloc(sizeof(struct record)*rows);
	dataset = fopen("dataset.txt","r");
	for(i=0;i<rows;i++){
		input_data(r,i,attr,dataset);
	}
	fclose(dataset);
	mid = rows/2;
	kmean(r,rows,attr,r[mid].data,r[mid+1].data);
	for(i=0;i<rows;i++){
		printf("ID %d Cluster : %d\n",r[i].id,r[i].cluster_no);
	}
	return 0;
}
