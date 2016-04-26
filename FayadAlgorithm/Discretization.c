#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define MODE "r"

//data structure to hold class labels
struct ClassList
{
	char *label;
};

//data structure to hold all datasets
struct DataList
{
	double feature;
	char *class;
};

struct ClassList classList[10];
struct DataList dataList[10000];
double probArray[20];
int classLabel[20];
int ic,id;
int boundryPoint[20];
int boundryIndex=0;
int main(int argc,char *argv[])
{
	//function definition area
	int openInputFile(char *);
	int getProbability(int ,int);
	double getEntropy(int ,int );
	double getInformationEntropy(int ,int ,int );
	double getDelta(int ,int ,int );
	double getGain(int ,int ,int );
	int getClassLabels(int ,int );
	void resetClassLabel();
	int checkGain(int ,int ,int );
	void resetProbability();
	int discretizationFI(int ,int );
	int sortDataList();
	int displayOutput();

	int status=openInputFile(argv[1]);
	if(status==-1)
		return -1;
	status=sortDataList();
	if(status==-1)
	{
		printf("Error occurred while sorting\n");
		return -1;
	}
	int k=0;
	//Printing Class List
	/*for(k=0;k<ic;k++)
		printf("%s\n",classList[k].label);
	Printing DataList
	for(k=0;k<id;k++)
		printf("%s\n",dataList[k].class);*/
	double entropyI,entropy1,entropy2;
	double infEntropy=0,temp=0;
	int start,end,result;
	start=0;
	end=id-1;

	result=discretizationFI(start,end);
	displayOutput();
	if(result==0)
		printf("\n\nCompleted successfully\n");
	else
		printf("Some error Occurred\n");

	return 0;
}

/* int openInputFile() method will scan input file and fetches class labels and data sets and stores them into a data strucrture which is used in remaining processing.*/
int openInputFile(char *FILENAME)
{
	FILE *fp;
	char str[80],classes[60],token[2]=",",*temp,tokenNewLine[2]="\n";
	fp=fopen(FILENAME,MODE);
	if(fp==NULL)
	{
		printf("Invalid File!!! Please Enter a valid File name while running!!!\n");
		return -1;
	}
	/*Tokenization method is used to parse the input file on the basis of ","delimiter.
	*/
	memset(str,'\0',sizeof(str));
	fgets(str,60,fp);
	sscanf(str,"%*s %s",classes);
	temp=strtok(classes,token);
	while(temp!=NULL)
	{
		classList[ic].label=(char *)malloc(strlen(temp)*sizeof(char));
		strcpy(classList[ic++].label,temp);
		temp=strtok(NULL,token);
	}
	int j=0;
	fgets(str,60,fp);
	//reading data sets
	while(1)
	{
		memset(str,'\0',sizeof(str));
		fgets(str,60,fp);
		if(feof(fp)) break;
		if(strncmp(str,"End",3)==0) break;
		temp=strtok(str,token);
                dataList[id].feature=atof(temp);
                temp=strtok(NULL,token);
		dataList[id].class=(char *)malloc((strlen(temp)-1)*sizeof(char));
		memset(dataList[id].class,'\0',sizeof(dataList[id].class));
		strncpy(dataList[id].class,temp,(strlen(temp)-1));
		id++;

        }
	return 0;
}

/*This method will get the probability of the set on the basis of start and end parameter and stores it to probArray and returns the status of evaluation whether it was successful or not.return 0 if success*/
int getProbability(int start,int end)
{
	int totalInstance=0;
	double count=0.0;
	totalInstance =(end-start)+1;
	int i,j;

	for(i=0;i<ic;i++)
	{
		count=0;
		for(j=start;j<=end;j++)
		{
			if(strcasecmp(dataList[j].class,classList[i].label)==0)
			{
				count++;
			}
		}
		probArray[i]=count/totalInstance;
	}
return 0;
}
/*Finds  entropy on the basis of start and end index of the datalist data structure and returns it to the calling function*/
double getEntropy(int start,int end)
{
	double entropy=0;
	int j;
	j=0;
	int getProbability(int ,int );
	void resetProbability();
	resetProbability();
	int i;
	getProbability(start,end);
	for(i=0;i<ic;i++)
	{
		if(probArray[i]!=0 && probArray[i]!=1)
		entropy+=(probArray[i]*((log(probArray[i]))/log(2)));
	}
	entropy=entropy*(-1);
	//printf("entropy for %d and %d : %f\n", start, end , entropy);
	return entropy;
}

//calculated information entropy
double getInformationEntropy(int start,int mid,int end)
{
	int S1=0,S2=0,S=0;
	double infEntropy=0;
	S1=(mid-start)+1;
	S2=(end-mid);
	S=(end-start)+1;
	infEntropy=((S1*getEntropy(start,mid))/S)+((S2*getEntropy(mid+1,end))/S);
	return infEntropy;
}

/*getDelta finds the delta value which is used in the gain calculation */
double getDelta(int start,int mid,int end)
{
	double delta=0;
	int getClassLabels(int,int);
	getClassLabels(start,end);
	int calculatePow(int,int);
	int k=0,k1=0,k2=0,i=0;
	while(i<20)
	{
		k+=classLabel[i];
		i++;
	}
	getClassLabels(start,mid);
	i=0;
	while(i<20)
	{
		k1=k1+classLabel[i];
		i++;
	}
	getClassLabels(mid+1,end);
	i=0;
	while(i<20)
	{
		k2=k2+classLabel[i];
		i++;
	}
	delta=(log(pow(3,k)-2)/log(2))-((k*getEntropy(start,end))-(k1*getEntropy(start,mid))-(k2*getEntropy(mid+1,end)));
	return delta;
}

/*finding Gain with respect to start,mid and end */
double getGain(int start,int mid,int end)
{
	double gain=0;
	gain=getEntropy(start,end)-getInformationEntropy(start,mid,end);
	return gain;
}
/*provides unique class labels*/
int getClassLabels(int start,int end)
{
	void resetClassLabel();
	resetClassLabel();
	void resetClassLabel();
	int i=0,j=0;
	char *temp;
	temp=dataList[start].class;
	for(i=0;i<ic;i++)
	{
		for(j=start;j<=end;j++)
		{
			if(strcasecmp(dataList[j].class,classList[i].label)==0)
			{
				classLabel[i]=1;
				break;
			}
		}
	}
	return 0;
}
/*resets the class label array for next processing*/
void resetClassLabel()
{
	int i=0;
	while(i<20)
	{
		classLabel[i]=0;
		i++;
	}
}
/*checks the condition of gain which is resposible to stopping the recursion*/
int checkGain(int start,int mid,int end)
{
	int flag,N;
	N=(end-start)+1;
	double gain = getGain(start,mid,end);
	double delta = ((log(N-1)/log(2))/N)+(getDelta(start,mid,end)/N);
	if(gain > delta)
		flag=0;
	else
		flag=1;
	return flag;
}
/*reset probArray*/
void resetProbability()
{
	int i=0;
	while(i<20)
	{
		probArray[i]=0;
		i++;
	}
}
/*Actual implementation of algirithm*/
int discretizationFI(int start,int end)
{
	int travToDataList,index;
	double temp,infEntropy=10000;
	for(travToDataList=start;travToDataList<end;travToDataList++)
	{
		temp=getInformationEntropy(start,travToDataList,end);
		printf("info_value: %f, cp=%d\n", temp, travToDataList);
		if(temp<=infEntropy)
		{
			infEntropy=temp;
			index=travToDataList;
		}

	}
	if(checkGain(start,index,end)!=1 || start==end || dataList[index].feature==dataList[index+1].feature)
	{
		return 0;
	}
	else
	{
	discretizationFI(start,index);
	boundryPoint[boundryIndex++]=index;
	printf("infoEntropy = %f \n", infEntropy);
	printf("index %d\n", index);
	discretizationFI(index+1,end);
	}
return 0;
}
/*sorting data sets in ascending order before processing*/
int sortDataList()
{

int outerLoop,innerLoop;
struct DataList dataListTemp;
for(outerLoop=0;outerLoop<id; outerLoop++)
{
   for (innerLoop=0;innerLoop<(id-outerLoop-1);innerLoop++)
   {
	if (dataList[innerLoop].feature>dataList[innerLoop+1].feature || (dataList[innerLoop].feature==dataList[innerLoop+1].feature && strcmp(dataList[innerLoop].class,dataList[innerLoop+1].class)<0))
	{
    		dataListTemp= dataList[innerLoop];
		dataList[innerLoop] = dataList[innerLoop+1];
		dataList[innerLoop+1] = dataListTemp;
    	}
    }
}
return 0;
}

/*display output in formatted manner*/
int displayOutput()
{
	system("clear");

	int boundry=0;char *infN="-inf";char *infP="inf";
	int S=1;
char *dash1="-";
char *dash2="_";
	boundry=0;
	char *setLabel="Set No:",*interval="Weka Intervals",*datas="Boundry DataSet",*intv="Actual Interval";
	int j=0;char *nam="Fayyad and Irani,1993";
	for(j=0;j<100;j++)
		printf("%s",dash2);
	printf("\n");
	printf("Implementation of Supervised Discretization of Continuous Feature\n");
	printf("%50s\n",nam);
	for(j=0;j<100;j++)
		printf("%s",dash2);
	printf("\n");
	printf("\n");
	printf("Total number of Classes: %-8.3d\n",ic);
        printf("Total number of DataSets: %-8.3d\n",id);
        printf("Total number of boundry points found: %-8.3d\n\n",boundryIndex);
	j=0;
	while(j<100)
	{
		printf("%s",dash1);
		j++;
	}
	printf("\n");
	printf("%-5s %20s %35s %30s\n",setLabel,interval,datas,intv);
	j=0;
	while(j<100)
	{
		printf("%s",dash1);
		j++;
	}
	printf("\n");
	printf("Set%-5d (%10s  -  %10f] %14f,%-21s %14f - %-14f\n",S++,infN,(dataList[boundryPoint[boundry]].feature+dataList[boundryPoint[boundry]+1].feature)/2,dataList[boundryPoint[boundry]].feature,dataList[boundryPoint[boundry]].class,dataList[0].feature,dataList[boundryPoint[boundry]].feature);
	boundry++;

	while(boundry<boundryIndex)
	{
		printf("Set%-5d (%10f  -  %10f] %14f,%-21s %14f - %-14f\n",S++,(dataList[boundryPoint[boundry-1]].feature+dataList[boundryPoint[boundry-1]+1].feature)/2,(dataList[boundryPoint[boundry]].feature+dataList[boundryPoint[boundry]+1].feature)/2,dataList[boundryPoint[boundry]].feature,dataList[boundryPoint[boundry]].class,dataList[boundryPoint[boundry-1]].feature,dataList[boundryPoint[boundry]].feature);
		boundry++;
	}
	printf("Set%-5d (%10f  -  %10s) %36s %14f - %-14f\n",S,(dataList[boundryPoint[boundry-1]].feature+dataList[boundryPoint[boundry-1]+1].feature)/2,infP," ",dataList[boundryPoint[boundry-1]].feature,dataList[id-1].feature);

printf("\n");
S=1;
//printing tree
boundry=boundryIndex+1;
int count=0;
char *pipe="|";
char *dash="_";
int numOfDash=14*(boundryIndex);
int i=0;
printf(" ");
while(i<(numOfDash-1)/2)
{
	printf(" ");
	i++;
}
printf("%d\n",id);
i=0;
while(i<((numOfDash-1)/2)-10)
{
	printf(" ");
	i++;
}
printf("(Total number of datasets)\n");
i=0;
printf(" ");
while(i<(numOfDash-1)/2)
{
	printf(" ");
	i++;
}
printf("%s\n",pipe);
i=0;
printf(" ");
while(i<numOfDash-1)
{
	if(i==(numOfDash-1)/2)
	{
		printf("%s",pipe);
		i++;
	}
	else
	{
		printf("%s",dash);
		i++;
	}
}
printf("\n");
while(boundry>0)
{
	printf("%-14s",pipe);
	boundry--;
}
printf("\n");i=0;
while(i<boundryIndex)
{
	printf("Set%-11d",S++);
	i++;
}

	printf("Set%-10d",S);
printf("\n");
i=0;char *str="#datasets";
while(i<=boundryIndex)
{
	printf("%-14s",str);
	i++;
}
printf("\n");
boundry=0;
printf("%-14d",(boundryPoint[boundry++])+1);
while(boundry<boundryIndex)
{
	printf("%-14d",boundryPoint[boundry]-boundryPoint[boundry-1]);
	boundry++;
}
printf("%-14d\n",id-boundryPoint[boundry-1]-1);
printf("\n");

return 0;
}