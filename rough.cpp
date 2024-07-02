#include <bits/stdc++.h>
#include"SerialPort.cpp"
using namespace std;

//using namespace SerialPort;
char output[MAX_DATA_LENGTH];
char incomingData[MAX_DATA_LENGTH];

// change the name of the port with the port name of your computer
// must remember that the backslashes are essential so do not remove them
char *port = "\\\\.\\COM10";

int main(){
	SerialPort arduino(port);
	if(arduino.isConnected()){
		cout<<"Connection made"<<endl<<endl;
	}
	else{
		cout<<"Error in port name"<<endl<<endl;
	}
	while(arduino.isConnected()){
		cout<<"Enter your command: "<<endl;
		string data;
        int i=5;
        data="44";
        data[0]='0'+i;
        data[1]='0'+6;
        //cout<<info<<endl;
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
	return 0;
}


