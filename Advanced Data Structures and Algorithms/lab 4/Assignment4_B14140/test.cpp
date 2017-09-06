#include<iostream>
// #include "OpenMap.hpp"
// #include "DoubleHashMap.hpp"
#include "ChainedMap.hpp"
#include "Dictionary.hpp"
#include<cstring>
#include<string.h>


using namespace std;
using namespace abc;

int main(){
     
       ChainedMap<int, int> ch;

      
      int inp1,key, value,check=0;
      while (check==0){
             
             cout<<endl;          
             cout<<endl;
             cout << "1.Insert\n2.Delete\n3.Exists?\n4.Get Value\n5.Exit\n";
             cin >> inp1;      
             switch(inp1){
	               
                  case 1:
	                 cout << "Enter Key and Value" << endl;
	                 cin >> key >> value;
	                 ch.put (key, value);
	                 break;
	         case 2:
	                 cout << "Enter key associated with value to delete it\n";
	                 cin >> key;
	                 ch.remove (key);
	                 break;
	         case 3:
	                 cout <<"Enter key associated with value to be searched for its presence"<< endl;
	                 cin >> key;
	                 if (ch.has (key) == 1){	  
	                         cout << "Value is present for given value" << endl;
	                 }
	                 else{	    
	                         cout << "Not Present" << endl;
	                 }
                         break;
	         case 4:
	                 cout << "Enter key associated with value to be searched" << endl;
	                 cin >> key;
	                 if (ch.has (key) == 1){
	                         cout << key << " : " << ch.get (key) << endl;
	                 }
	                 else{
	                         cout << "Not present";
	                 }
	                 break;
          case 5:
          {
	               cout<<"Exiting....."<<endl;
                       cout<<endl;
                       check=1;
                       break;
                     }
	}

    }
}
