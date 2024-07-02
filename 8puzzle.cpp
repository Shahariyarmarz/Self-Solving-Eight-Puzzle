#include <bits/stdc++.h>
#include"SerialPort.cpp"
//using namespace SerialPort;
char output[MAX_DATA_LENGTH];
char incomingData[MAX_DATA_LENGTH];

// change the name of the port with the port name of your computer
// must remember that the backslashes are essential so do not remove them
char *port = "\\\\.\\COM6";

using namespace std;
typedef pair<int,int>p;
void show(int [3][3]);
bool is_equal(int input1[3][3],int input2[3][3]);
void assign(int source[3][3],int destination[3][3]);
int equal_test(int arr1[][3]);
void up(int input[3][3]);
void down(int input[3][3]);
void left(int input[3][3]);
void right(int input[3][3]);
 int goal[3][3]={    {0,1,2},
                        {3,4,5},
                        {6,7,8}
                    };
int h1(int curr[3][3],int gol[3][3]);
int h2(int curr[3][3],int gol[3][3]);

priority_queue <p, vector<p>, greater<p> > cost;

int object=0;

class Node
{
public:
    int id;
    int arr[3][3];
    int parents;
    int cost;
    int zero_x;
    int zero_y;
    string action;

};
Node node[10000];

int main()
{
    SerialPort arduino(port);
	if(arduino.isConnected()){
		cout<<"Connection made"<<endl<<endl;
	}
	else{
		cout<<"Error in port name"<<endl<<endl;
	}
    int current[3][3];
    //int initial[3][3];



      /*
    int goal[3][3]={    {0,1,2},
                        {3,4,5},
                        {6,7,8}
                    };
                    */
    int initial[3][3]={    {7,2,4},
                           {5,0,6},
                           {8,3,1}
                        };

  /*  cout<<"Enter the value in a row-wise fashion :"<<endl;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cin>>initial[i][j];
        }
    }*/

    p pi;
    pi.second=0;
    assign(initial,current);
    assign(initial,node[object].arr);
    int hur1=h1(current,goal);
    int hur2=h2(current,goal);
    node[object].cost=0;
    node[object].parents=0;
    node[object].id=object;
    int c=hur1+hur2;
    pi.first=c;
    cost.push(pi);
    for (int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(current[i][j]==0)
                node[0].zero_x=i;
                node[0].zero_y=j;
        }
    }
    object++;

    show(current);

    cout<<endl;

    while(!cost.empty())
    {
        if(is_equal(current,goal)){
                cout<<"Goal found"<<endl;
        //show(current);
                break;}
        else{

        int rightcost,leftcost,upcost,downcost;

        up(current);
        down(current);
        left(current);
        right(current);

        int ID=cost.top().second;
        assign(node[ID].arr,current);


        cost.pop();

    }
     if(is_equal(current,goal))
    {

        Node PrintID[50];
        Node trace;
       trace=node[object-1];
        int n=1;
         do
         {

              for(int d=0;d<object;d++)
         {
             if(trace.parents==node[d].id)
             {


                 for(int i=0;i<3;i++)
                    {
                        for(int j=0;j<3;j++)
                        {
                            PrintID[n].arr[i][j]=node[d].arr[i][j];

                        }

                    }
                    n++;



                trace=node[d];
                break;
            }
         }
         }

    while(trace.parents!=0);
  int m=n-1;
   int count=1;
    while(m>=1 && arduino.isConnected())
    {
        int l=0;
        string data;
        data="012345678";
        int idnum = equal_test(PrintID[m].arr);
          //cout<<node[idnum].action<<endl;
        cout<<"Step: "<<count<<endl;
         for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                data[l]='0'+PrintID[m].arr[i][j];

                if(PrintID[m].arr[i][j]==0)
                {
                    cout<<"_"<<" ";
                }
                else
                {
                    cout<<PrintID[m].arr[i][j]<<" ";
                }
                l++;
            }
            cout<<endl;
        }
        cout<<data<<endl;

        cout<<endl;

        m--;
        count++;
        char *charArray = new char[data.size() + 1];
		copy(data.begin(), data.end(), charArray);
		charArray[data.size()] = '\0';

		arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
		//Sleep(100);
		arduino.readSerialPort(output, MAX_DATA_LENGTH);

		cout<<">> "<<output<<endl;

		delete [] charArray;
		 Sleep(2000);
    }
    int idnum=equal_test(current);
    cout<<node[idnum].action<<endl;
   cout<<"Step: "<<count<<endl;
     for(int i=0;i<3;i++)
                    {
                        for(int j=0;j<3;j++)
                        {

                             if(current[i][j]==0)
                                {
                                    cout<<"_"<<" ";
                                }
                                else
                                {
                                    cout<<current[i][j]<<" ";
                                }
                        }
                        cout<<endl;
                    }
                    cout<<endl;
                    cout<<"Total number of state explored: "<<object-1<<endl;


    }

    }

    return 0;
}

/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

void show(int input[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<"|"<< input[i][j] <<"|";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
}

/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/


bool is_equal(int input1[3][3],int input2[3][3])
{
    int count=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(input1[i][j]==input2[i][j])
            {
                count++;
            }
        }
    }
    if(count==9) return true;
    return false;
}

/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

void assign(int source[3][3],int destination[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            destination[i][j]=source[i][j];
        }
    }
}

/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

int h1(int curr[3][3],int gol[3][3])
{
    int c=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(curr[i][j]!=gol[i][j])
            {
                c++;
            }
        }
    }
    return c;
}

/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/


int h2(int arr[][3],int g[][3])
{
    int distance=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(arr[i][j]!=g[i][j])
            {

                int misplaced_value=arr[i][j];
                for(int k=0;k<3;k++)
                {
                    for(int l=0;l<3;l++)
                    {
                        if(g[k][l]==misplaced_value)
                        {
                            distance+=abs(k-i)+abs(l-j);
                        }

                    }

                }

            }
        }
    }
    return distance;
}

/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/


void up(int current[][3])
{
    int upcost;
    for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(current[i][j]==0)
                {
                    if(i-1==0 || i-1==1 )
                       {
                           int matched=0;
                           swap(current[i][j],current[i-1][j]);
                           for(int l=0;l<object;l++)
                           {
                               if(is_equal(current,node[l].arr))
                               {
                                   matched=1;
                               }
                           }
                           if(matched==0)
                           {
                            assign(current,node[object].arr);
                           node[object].zero_x=i-1;
                           node[object].zero_y=j;
                           node[object].action="Up";
                           p pi;
                           int hur1=h1(current,goal);
                           int hur2=h2(current,goal);
                           int c;
                           node[object].id=object;
                            pi.second=object;
                           swap(current[i][j],current[i-1][j]);
                           for(int k=0;k<object;k++)
                           {
                               if(is_equal(current,node[k].arr))
                               {
                                   c=node[k].cost;
                                   node[object].parents=k;
                               }
                           }
                           node[object].cost=c+1;
                        upcost=hur1+hur2+node[object].cost;
                        pi.first=upcost;
                           cost.push(pi);
                           object++;
                           }
                           else
                           {
                                swap(current[i][j],current[i-1][j]);
                           }

                       }
                }
            }
        }

}


/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/


void down(int current[3][3])
{
    int downcost;
     for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(current[i][j]==0)
                {
                    if(i+1==1 || i+1==2 )
                       {
                           int matched=0;
                           swap(current[i][j],current[i+1][j]);
                           for(int l=0;l<object;l++)
                           {
                               if(is_equal(current,node[l].arr))
                               {
                                   matched=1;
                               }
                           }
                           if(matched==0)
                           {
                            assign(current,node[object].arr);
                           node[object].zero_x=i+1;
                           node[object].zero_y=j;
                            node[object].action="Down";
                           p pi;
                           int hur1=h1(current,goal);
                           int hur2=h2(current,goal);
                           int c;
                           node[object].id=object;
                            pi.second=object;
                           swap(current[i][j],current[i+1][j]);
                           for(int k=0;k<object;k++)
                           {
                               if(is_equal(current,node[k].arr))
                               {
                                   c=node[k].cost;
                                   node[object].parents=k;
                               }
                           }
                            node[object].cost=c+1;
                        downcost=hur1+hur2+node[object].cost;
                        pi.first=downcost;
                           cost.push(pi);
                           object++;
                           }
                           else
                           {
                                swap(current[i][j],current[i+1][j]);
                           }

                       }
                }
            }
        }
}


/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/


void left(int current[3][3])
{
    int leftcost;
     for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(current[i][j]==0)
                {
                    if(j-1==0 || j-1==1 )
                       {
                           int matched=0;
                           swap(current[i][j],current[i][j-1]);
                           for(int l=0;l<object;l++)
                           {
                               if(is_equal(current,node[l].arr))
                               {
                                   matched=1;
                               }
                           }
                           if(matched==0)
                           {
                               assign(current,node[object].arr);
                           node[object].zero_x=i;
                           node[object].zero_y=j-1;
                           node[object].action="Left";
                           p pi;
                           int hur1=h1(current,goal);
                           int hur2=h2(current,goal);
                           int c;
                           node[object].id=object;
                            pi.second=object;
                           swap(current[i][j],current[i][j-1]);
                           for(int k=0;k<object;k++)
                           {
                               if(is_equal(current,node[k].arr))
                               {
                                   c=node[k].cost;
                                   node[object].parents=k;
                               }
                           }
                            node[object].cost=c+1;
                        leftcost=hur1+hur2+node[object].cost;
                        pi.first=leftcost;
                           cost.push(pi);
                           object++;
                           }
                           else
                           {
                                swap(current[i][j],current[i][j-1]);
                           }

                       }
                }
            }
        }



}


/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/


void right(int current[3][3])
{
    int rightcost;
    for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(current[i][j]==0)
                {
                    if(j+1==1 || j+1==2 )
                       {
                           int matched=0;
                           swap(current[i][j],current[i][j+1]);
                           for(int l=0;l<object;l++)
                           {
                               if(is_equal(current,node[l].arr))
                               {
                                   matched=1;
                               }
                           }
                           if(matched==0)
                           {
                               assign(current,node[object].arr);
                           node[object].zero_x=i;
                           node[object].zero_y=j+1;
                            node[object].action="Right";
                           p pi;
                           int hur1=h1(current,goal);
                           int hur2=h2(current,goal);
                           int c;
                           node[object].id=object;
                            pi.second=object;
                           swap(current[i][j],current[i][j+1]);
                           for(int k=0;k<object;k++)
                           {
                               if(is_equal(current,node[k].arr))
                               {
                                   c=node[k].cost;
                                   node[object].parents=k;
                               }
                           }
                            node[object].cost=c+1;
                        rightcost=hur1+hur2+node[object].cost;
                        pi.first=rightcost;
                           cost.push(pi);
                           object++;
                           }
                           else
                           {
                                swap(current[i][j],current[i][j+1]);
                           }

                       }
                }
            }
        }
}
int equal_test(int arr1[][3]) {
  int inc = 0;
  for (int k = 0; k < object; k++) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (arr1[i][j] == node[k].arr[i][j]) {
          inc++;
        }
      }
    }
    if (inc == 9) {
      return k;
    }
    inc = 0;
  }

}

