#include <bits/stdc++.h> 
using namespace std; 

string encode (string str) { 
	string result="";
	int n = str.length(); 
	string temp;
	temp.push_back(str[0]);
	for (int i = 1; i < n; i++) { 
		if(temp.back()==str[i]){
			temp.push_back(str[i]);
		}
		else{
			result+=temp.back()+to_string(temp.size());
			temp.clear();
			temp.push_back(str[i]);
		}
		if(i==n-1 and temp.size()){
			result+=temp.back()+to_string(temp.size());
		}
		
	} 
	return result;
} 

string decode (string str) {
	string result="";
	int n = str.length();
	int freq=0;
	char last;
	int i=0;
	while(i<n) {
		if(!isalpha(str[i])){
			while(i<n and !isalpha(str[i])){
				freq*=10;
				freq+=(str[i]-'0');
				i++;
			}
			while(freq>0){
				result+=last;
				freq--;
			}
		}
		else{
			last=str[i];
			i++;
		}
	}
	return result;
}

int main() 
{ 
	string data, encoded, decoded;
	
	cout<<"Enter your string"<<endl;
	
	cin>>data;
	
	encoded = encode(data);
	decoded = decode(encoded);
	
	cout<<"Encoded data using Run Length: "<<encoded<<endl;
	cout<<"Decoded data using Run Length: "<<decoded<<endl;
	system("pause");
	
	return 0; 
} 

