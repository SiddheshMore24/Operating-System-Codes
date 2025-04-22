#include<iostream>
int n,m;
int maxi[10][10];
int alloc[10][10];
int need[10][10];
int Available[10];
int safeSeq[10];
using namespace std;
void isSafe()
{
    int finish[10];
    int work[10];
    for(int i=0;i<m;i++)
    {
        work[i]=Available[i];
    }
    for (int i = 0; i < n; i++) {
       finish[i]=0; 
    }

    int count=0;
    while(count<n)
    {
        int found =0;
        for(int i=0;i<n;i++)
        {
            if(finish[i]==0)
            {
                int j;
                for(j=0;j<m;j++)
                {
                    if(need[i][j]>work[j])
                    {
                        break;
                    }
                }

                if(j==m)
                {
                    for(int k=0;k<m;k++)
                    {
                        work[k]=work[k]+alloc[i][k];
                    }
                    found=1;
                        safeSeq[count++]=i;
                        finish[i]=1;
                }
            }
        }

        if(found==0)
        {
            cout<<"No safe sequence exists"<<endl;
            return;
        }

        
    }

    for(int i=0;i<n;i++)
    {
        cout<<safeSeq[i]<<endl;
    }


   
}

int main ()
{
    cout<<"Enter number of processes"<<endl;
    cin>>n;
    cout<<"Enter number of resources"<<endl;
    cin>>m;

    cout<<"Enter max need matrix :"<<endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin>>maxi[i][j];
        }
    }
    cout<<"Enter allocation matrix: "<<endl;
    for (int i=0;i<n;i++)
    {
        for (int j = 0; j < m; j++) {
            cin>>alloc[i][j];
            
        }
    }
    cout<<"Enter avaiable resources"<<endl;
    for (int i=0;i<m;i++)
    {
        cin>>Available[i];
    }

    for(int i=0;i<n;i++)
    {
        for (int j = 0; j < m; j++) {
            need[i][j]=maxi[i][j]-alloc[i][j];
        }
    }

    isSafe();
    return 0;
}
