/*##########################################################################*/
/*                                                                          */
/* HW10_Taha_Atakan_Ipekci_141044011                                        */
/*                                                                          */
/* Created on 05/05/2016 by Taha Atakan Ipekci                              */
/*                                                                          */
/*                                                                          */
/*Description                                                               */
/* -------------------------------------------------------------------------*/
/* Reads data(students,lecturers,lectures,schedule and courses) from a .dat */
/*file and prints some relations about the data to a txt file.              */
/* 	                                                                        */
/* 																            */
/*													                        */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*##########################################################################*/

/*--------------------------------------------------------------------------*/
/*                            Includes                                      */
/*--------------------------------------------------------------------------*/

#include <stdio.h>
/*--------------------------------------------------------------------------*/
/*                             Defines                                      */
/*--------------------------------------------------------------------------*/
#define maxNameLength 30
#define maxStudents 20
#define numberOfStructs 5


struct students
{
	int id;
	char name[maxNameLength];
	char surname[maxNameLength];
};

struct lecturers
{
	char degree[maxNameLength];
	int id;
	char name[maxNameLength];
	char surname[maxNameLength];
};

struct lectures
{
	int code;
	char name[maxNameLength];
	int id;
};

struct schedule
{
	char classroomName[maxNameLength];
	char day[maxNameLength];
	int startTime;
	int duration;
	int code;
};

struct courses
{
	int id;
	int code;
};
/*Reads data from input file to struct arrays*/
void readData(struct students stu[],
			  struct lecturers lecturer[maxStudents],
			  struct lectures lects[maxStudents],
			  struct schedule sch[maxStudents],
			  struct courses crs[maxStudents],
			  int total[numberOfStructs]);
/*Prints some relations about the data in the input file*/
void printData(struct students stu[],
			   struct lecturers lecturer[],
			   struct lectures lects[],
			   struct schedule sch[],
			   struct courses crs[],
			   int total[numberOfStructs]);




int main(){

	struct students stu[maxStudents];
	struct lecturers lecturer[maxStudents];
	struct lectures lects[maxStudents];
	struct schedule sch[maxStudents];
	struct courses crs[maxStudents];
	int total[numberOfStructs];
	

		readData(stu,lecturer,lects,sch,crs,total);
		printData(stu,lecturer,lects,sch,crs,total);
}





void readData(struct students stu[],
			  struct lecturers lecturer[],
			  struct lectures lects[],
			  struct schedule sch[],
			  struct courses crs[],
			  int total[numberOfStructs]){


	/*Simple integer value for loops*/
	int k;
	/*Opening the input file for reading*/
	FILE *fp;
	fp=fopen("input.dat","r");
	/*Reads the amount of students and puts it into the first element of total*/
	fread(&total[0],sizeof(total[0]),1,fp);
	/*Reads the data to struct array till k reaches total number of students*/
	for(k=0; k<total[0]; k++){		
		fread(&(stu[k]),sizeof(stu[k]),1,fp);		
		}
	/*Reads the amount of lecturers and puts it into the second element of */
	/*total*/
	fread(&total[1],sizeof(total[1]),1,fp);	
	
	/*Reads the data to struct array till k reaches total number of lecturers*/
	for(k=0; k<total[1]; k++){
		fread(&(lecturer[k]),sizeof(lecturer[k]),1,fp);			
		}
	/*Reads the amount of lectures and puts it into the third element of */
	/*total*/
	fread(&total[2],sizeof(total[2]),1,fp);
	
	/*Reads the data to struct array till k reaches total number of lectures*/
	for(k=0; k<total[2]; k++){
		fread(&(lects[k]),sizeof(lects[k]),1,fp);	
		}
	/*Reads the amount of schedules and puts it into the fourth element of*/
	/*total*/	
	fread(&total[3],sizeof(total[3]),1,fp);
	/*Reads the data to struct array till k reaches total number of schedules*/
	for(k=0; k<total[3]; k++){
		fread(&(sch[k]),sizeof(sch[k]),1,fp);	
		}
	/*Reads the amount of courses and puts it into the fifth element of*/
	/*total*/
	fread(&total[4],sizeof(total[4]),1,fp);
	/*Reads the data to struct array till k reaches total number of courses*/
	for(k=0; k<total[4]; k++){
		fread(&(crs[k]),sizeof(crs[k]),1,fp);	
		}
/*Closing the input file*/
fclose(fp);
}

void printData(struct students stu[],
			   struct lecturers lecturer[],
			   struct lectures lects[],
			   struct schedule sch[],
			   struct courses crs[],
			   int total[numberOfStructs]){

	/*i,j and k are used for loops. */
	int i,j,k,count,count2;
	FILE *fp;
	fp=fopen("output.txt","w");

	fprintf(fp,"Lecture-Lecturer\n");

	
	for(i=0; i<total[2]; i++){
	
		fprintf(fp,"%s " ,lects[i].name);

		for(j=0; j<total[1]; j++){

			if(lects[i].id == lecturer[j].id)

				fprintf(fp,"%s %s ", lecturer[j].name,lecturer[j].surname);

		}

		count=0;
		for(k=0; k<total[4]; k++){

			if(crs[k].code == lects[i].code)
				
				count++;
			}

		fprintf(fp,"%d\n",count);


	}

	fprintf(fp,"\nStudent-Lecture\n");

	for(i=0; i<total[0]; i++){

		fprintf(fp,"%d %s %s ", stu[i].id,stu[i].name,stu[i].surname);

		count=0;

		for(j=0; j<total[4]; j++){

			if(crs[j].id == stu[i].id)

			count++;
			}
		
		fprintf(fp,"%d\n",count);

}
	
	fprintf(fp,"\nStudent-Day\n");

	for(i=0; i<total[0]; i++){

		fprintf(fp,"%d %s %s ", stu[i].id,stu[i].name,stu[i].surname);

		count=0;
		
		for(j=0; j<total[4]; j++){

			if(crs[j].id == stu[i].id)

			count++;
			}

			

		for(count2=0,k=0; k<total[4]; k++){

			if(crs[k].id == stu[i].id){

				for(j=0; j<total[3]; j++){

					if(crs[k].code == sch[j].code){
						/*If it is not the last day prints ','*/
						count2++;

						if(count2<count)
				
							fprintf(fp,"%s, ", sch[j].day);


						else 
			
							fprintf(fp,"%s\n", sch[j].day);

						}
					}

				}

			}

	}
fclose(fp);
}












