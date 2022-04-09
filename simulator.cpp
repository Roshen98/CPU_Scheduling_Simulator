#include <iostream> // input and output
#include <fstream>  // read from file
#include <string>   // string library
#include <algorithm> // sort

using namespace std;

// define constant
#define SIZE 20

// function declaration
void FCFS(int[],int[],int[],int[]); 
void SJF(int[],int[],int[],int[]);
void PPS(int[],int[],int[],int[]);
void RR(int[],int[],int[],int[],int);
int sizeOfArray(int[]);
double average(int[], int);
double rate(int[],int[],int);
void idChange(int[],int[],int[],int[],int);
void SJFChange(int[],int[],int[],int[],int);
void swap(int[],int,int,int);
bool isEmpty(int[],int);
void swapEnd(int[],int);
int getNonZeroIndex(int[],int);
void removeRepetition(int[],int);
bool allZero(int[],int);

int main()
{
    // variables and array declaration
    int pid[SIZE] = {0}, arrivalTime[SIZE], burstTime[SIZE], priority[SIZE];
    string info[SIZE];
    int number,option = 0,timeQuantum = 0;
   
    // welcome message
    cout << "Welcome to the CPU Scheduling Simulator!" << endl;
    
    
    // open file to read
    ifstream file("input.txt");
    
    // assign each value to the specified arrays
    for(int i = 0; i < SIZE; i++ ){
        file >> pid[i] >> arrivalTime[i] >> burstTime[i] >> priority[i];
    }
    
    // close the file
    file.close();
    
    // ask for a specific scheduling algorithm
    while(option < 1 || option > 4){
        cout << "Choose a scheduling algorithm[1-4]:" << endl;
        cout << "1) First Come First Serve (FCFS)\n2) Shortest Job First (SJF)";
        cout << "\n3) Preemptive Priority Scheduling\n4) Round Robin (RR)" << endl;
        cin >> option;
    }
    
    // ask for a time time quantum if Round Robin I 
    if(option == 4){
        cout << "Time-quantum: ";
        cin >> timeQuantum;
    }
    
    switch(option){
        
        case 1:
            FCFS(pid,arrivalTime,burstTime,priority); // First Come Fist Serve
            break;
        
        case 2:
            SJF(pid,arrivalTime,burstTime,priority); // Shortest Job First
            break;
            
        case 3:
            PPS(pid,arrivalTime,burstTime,priority); //  Preemptive Priority Scheduling
            break;
            
        case 4:
            RR(pid,arrivalTime,burstTime,priority,timeQuantum); // Round Robin
            break;
       
    }
    
    
    
    return 0;
}

// get the length of the array
int sizeOfArray(int array[]){
    int counter = 0;
    for(int i = 0; i < SIZE; i++){
        if(array[i] == 0)
            break;
        counter++;
    }
    return counter;
}

// returns the average of an integer array
double average(int array[], int size){
    double result;
    for(int i  = 0; i < size; i++){
            result+=array[i];
    }
    return result/size;
}

// returns the CPU utilization rate 
double rate(int burst[],int end[],int size){
    int sum = 0,max = 0;
    for(int i = 0; i < size; i++){
        sum += burst[i];
        if(end[i]>max)
            max = end[i];
    }
    return 100* sum / max ;
}

// switch the id index since FCFS depends on arrival time 
void idChange(int id[],int arrive[],int burst[],int priority[],int size){
    int arr = 0, index = 0;
    for(int i = 0; i < size; i++){
        index = i;
        arr = arrive[i];
        for(int j = i+1; j < size; j++){
            
            if(arrive[j]<arr){
                index = j;
                arr = arrive[j];
            }
        }
        swap(id,i,index,size);
        swap(arrive,i,index,size);
        swap(burst,i,index,size);
        swap(priority,i,index,size);
    }


}

bool allZero(int array[],int size){
    for(int i = 0; i < size; i++){
        if(array[i]!=0)
            return false;
    }
    return true;
}

// switch the id index since SJF depends on arrival time and shorter burst time
void SJFChange(int id[],int arrive[],int burst[],int priority[],int size){

    int queue[SIZE] = {0},indexq[SIZE] = {0},time, arr = 0, index = 0, counter =0,queueSize,burstTime;

    if(allZero(arrive,size)){
        int maxBurst = 0,index;
        for(int i = 0; i < size;i++){
            maxBurst = burst[i];
            for(int j = i+1; j < size;j++){
                if(burst[j] > maxBurst){
                    maxBurst=burst[j];
                    index = j;
                }
            }

            if(maxBurst != burst[i]){
                swap(id,i,index,size);
                swap(arrive,i,index,size);
                swap(burst,i,index,size);
                swap(priority,i,index,size);
                
            }    
        }
    }

    else{
        arr = arrive[0];
        for(int i = 1; i < size; i++){
            if(arrive[i]<arr){
                arr = arrive[i];
                index = i;
            }
        }

        swap(id,0,index,size);
        swap(arrive,0,index,size);
        swap(burst,0,index,size);
        swap(priority,0,index,size);
        
        for(int i = 1; i < size; i++){
            for(int j = i+1; j < size; j++){
                if(arrive[j]<=burst[i-1]){
                    
                    queue[counter] = burst[j];
                    indexq[counter] = j;
                
                }
                counter++;
                
            }
            queueSize = sizeOfArray(queue);
            if(queueSize != 0){
                burstTime = queue[0];
                index = 0;
                for(int j = 1; j < queueSize; j++){
                    if(queue[j] <  burstTime){
                        burstTime = queue[j];
                        index = j;
                    }   
                }  
            
                swap(id,i,indexq[index],size);
                swap(arrive,i,indexq[index],size);
                swap(burst,i,indexq[index],size);
                swap(priority,i,indexq[index],size);
            }

        
            
            
        }
    }
}


// swap array index
void swap(int array[],int index1, int index2, int size){
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

void FCFS(int pid[],int arrivalTime[],int burstTime[],int priority[]){
    // whichever arrives first gets implemented first
    int size = 0, start = 0,end = 0;
    
    size = sizeOfArray(pid);

    int startTime[size],endTime[size],turnaroundTime[size],waitingTime[size],responseTime[size];
    double averageWaitingTime, averageResponseTime, averageTurnaroundTime, CPUUtilizationRate;
    
    idChange(pid,arrivalTime,burstTime,priority,size);

    for(int i = 0; i < size; i++){
        start = end;
        startTime[i] = start;
        end += burstTime[i];
        endTime[i] = end;
        
        for(int j = start; j < end; j++)
            cout << "P" << pid[i] << " is running!\t" << j+1 << "ms" << endl;
        cout << "P" << pid[i] << " is done!" << endl;

        turnaroundTime[i] = endTime[i] - arrivalTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
        responseTime[i] = startTime[i] - arrivalTime[i];
       
    }  

    cout << "\nAverage waiting time: " << average(waitingTime,size) << " ms" << endl;
    cout << "Average response time: " << average(responseTime,size) << " ms" << endl;
    cout << "Average turnaround time: " << average(turnaroundTime,size) << " ms" << endl;
    cout << "CPU utilization rate: " << rate(burstTime,endTime,size) << "%" << endl;
    
    
}



void SJF(int pid[],int arrivalTime[],int burstTime[],int priority[]){
    int size = 0, start = 0,end = 0;
    
    size = sizeOfArray(pid);

    int startTime[size],endTime[size],turnaroundTime[size],waitingTime[size],responseTime[size];
    double averageWaitingTime, averageResponseTime, averageTurnaroundTime, CPUUtilizationRate;
    
    SJFChange(pid,arrivalTime,burstTime,priority,size);

    for(int i = 0; i < size; i++){
        start = end;
        startTime[i] = start;
        end += burstTime[i];
        endTime[i] = end;
        
        for(int j = start; j < end; j++)
            cout << "P" << pid[i] << " is running!\t" << j+1 << "ms" << endl;
        cout << "P" << pid[i] << " is done!" << endl;

        turnaroundTime[i] = endTime[i] - arrivalTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
        responseTime[i] = startTime[i] - arrivalTime[i];
       
    }  

    cout << "\nAverage waiting time: " << average(waitingTime,size) << " ms" << endl;
    cout << "Average response time: " << average(responseTime,size) << " ms" << endl;
    cout << "Average turnaround time: " << average(turnaroundTime,size) << " ms" << endl;
    cout << "CPU utilization rate: " << rate(burstTime,endTime,size) << "%" << endl;
}

void PPS(int pid[],int arrivalTime[],int burstTime[],int priority[]){
    int size = 0, start = 0,end = 0;
    
    size = sizeOfArray(pid);

    int startTime[size],endTime[size],turnaroundTime[size],waitingTime[size],responseTime[size];
    double averageWaitingTime, averageResponseTime, averageTurnaroundTime, CPUUtilizationRate;
    int burst[size],time=0,arrive[SIZE]={0},id[SIZE]={0},counter=0,wait[SIZE]={0},arriveC=0;


    // get all the burst time in an array
    for(int i = 0; i < size;i++){
        burst[i] = burstTime[i];
    }

    while(!isEmpty(burst,size)){ 
        for(int i = 0; i < size; i++){
            if(arrivalTime[i] == time){
            
                arrive[arriveC] = pid[i];
                arriveC++;
                
            }
            
        }

        int arrSize = sizeOfArray(arrive);
        
        if(arrSize>1){
            for(int i = 0; i < arrSize; i++){
                for(int j = i+1; j < arrSize; j++){
                    if(priority[arrive[i]-1] > priority[arrive[j]-1])
                        swap(arrive,i,j,arrSize);
                }
            }
            
        }

        cout << "P" << arrive[0] << " is running!\t" << time+1 << "ms" << endl;
        burst[arrive[0]-1] -= 1;

        if(burst[arrive[0]-1]==burstTime[arrive[0]-1]-1)
            startTime[arrive[0]-1] = time;

        if(burst[arrive[0]-1] == 0){
            endTime[arrive[0]-1] = time+1;
            cout << "P" << arrive[0] << " is done!" << endl;
            if(arrSize == 1){
                arrive[0] = 0;
                
            }

            else{
                for(int i = 1; i < arrSize; i++){
                    arrive[i-1] = arrive[i];
                }
                
            }
            arriveC--;
        }
        
        time++;
    }

    for(int i = 0; i < size; i++){
        turnaroundTime[i] = endTime[i] - arrivalTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
        responseTime[i] = startTime[i] - arrivalTime[i];
       
    }  

    cout << "\nAverage waiting time: " << average(waitingTime,size) << " ms" << endl;
    cout << "Average response time: " << average(responseTime,size) << " ms" << endl;
    cout << "Average turnaround time: " << average(turnaroundTime,size) << " ms" << endl;
    cout << "CPU utilization rate: " << rate(burstTime,endTime,size) << "%" << endl;

}


void RR(int pid[],int arrivalTime[],int burstTime[],int priority[],int quantum){
    int size = 0, start = 0,end = 0;
    
    size = sizeOfArray(pid);

    int startTime[size],endTime[size],turnaroundTime[size],waitingTime[size],responseTime[size];
    double averageWaitingTime, averageResponseTime, averageTurnaroundTime, CPUUtilizationRate;

    int burst[size],time=0,arrive[SIZE]={0},id[SIZE]={0},counter=0,wait[SIZE]={0},arriveC=0;
    int maxTime=0,arrSize;

    // get all the burst time in an array
    for(int i = 0; i < size;i++){
        burst[i] = burstTime[i];
    }
 
  
    while(!isEmpty(burst,size)){ 

        for(int i = 0; i < size; i++){
            
            if(arrivalTime[i] == time){
                
                arrive[arriveC] = pid[i];
                arriveC++;
            }
        }
        maxTime++;
        arrSize = sizeOfArray(arrive);
        
        if(maxTime > quantum){
            maxTime = 1;
            swapEnd(arrive,arrSize);
        }
      
        cout << "P" << arrive[0] << " is running!\t" << time+1 << "ms" << endl;
        burst[arrive[0]-1] -= 1;
        

        if(burst[arrive[0]-1]==burstTime[arrive[0]-1]-1)
            startTime[arrive[0]-1] = time;

        if(burst[arrive[0]-1] == 0){
            endTime[arrive[0]-1] = time+1;
            cout << "P" << arrive[0] << " is done!" << endl;
            maxTime = 0;

            int element = arrive[0];
            while(true){
                if(element != arrive[0]||isEmpty(burst,size))
                    break;
                for(int i = 1; i < arrSize; i++){
                    arrive[i-1] = arrive[i];
                }

            }
      
            arriveC--;
        }
        
        time++;
    }

    

    for(int i = 0; i < size; i++){
        turnaroundTime[i] = endTime[i] - arrivalTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
        responseTime[i] = startTime[i] - arrivalTime[i];
       
    }  

    cout << "\nAverage waiting time: " << average(waitingTime,size) << " ms" << endl;
    cout << "Average response time: " << average(responseTime,size) << " ms" << endl;
    cout << "Average turnaround time: " << average(turnaroundTime,size) << " ms" << endl;
    cout << "CPU utilization rate: " << rate(burstTime,endTime,size) << "%" << endl;

}

bool isEmpty(int array[],int size){
    for(int i = 0; i < size; i++){
        if(array[i] != 0){
            return false;
        }
    }
    return true;
}


// swap the element to the end of the array
void swapEnd(int array[],int size){

    for(int i = 1; i < size; i++){
        
        int temp = array[i-1];
        array[i-1] = array[i];
        array[i] = temp;
        

    }

}
