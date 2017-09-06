#include<iostream>
#include "OpenMap.hpp"
#include "DoubleHashMap.hpp"
#include "ChainedMap.hpp"
#include "Dictionary.hpp"
#include<cstring>
#include<string.h>


using namespace std;
using namespace eni;
using namespace abc;

int main(){
     
       int inp=0,inp1=0;
       string key,value;
       Dictionary<string,string> *ht1;
       ChainedMap<string,string> ht2;
       OpenMap<string,string> ht3;
       DoubleHashMap<string,string> ht4;
       cout<<"\t\t\t\t\t\t\t\t\tHASHING SYSTEM"<<endl;
       cout<<endl;
       cout<<"Choose which Collision Method You want to Apply : \n";
       cout<<"1.Chaining\n2.Linear Probing\n3.Double Hashing\n";
       cin>>inp;
       switch(inp){
          
            case 1:
                   ht1=&ht2;
                   break;
            case 2:
                   ht1=&ht3;
                   break;
            case 3:
                   ht1=&ht4;
                   break;
            default:
                   cout<<"Enter valid input\n";
                   break;
 
      }
      
      
      while (1){
             
             cout<<endl;          
             cout<<endl;
             cout << "1.Insert\n2.Delete\n3.Exists?\n4.Search\n5.Display\n6.Exit\n";
             cin >> inp1;      
             switch(inp1){
	               
                  case 1:
	                 cout << "Enter Key and Value" << endl;
	                 cin >> key >> value;
	                 ht1->put (key, value);
	                 break;
	         case 2:
	                 cout << "Enter key associated with value to delete it\n";
	                 cin >> key;
	                 ht1->remove (key);
	                 break;
	         case 3:
	                 cout <<"Enter key associated with value to be searched for its presence"<< endl;
	                 cin >> key;
	                 if (ht1->has (key) == 1){	  
	                         cout << "Value is present for given value" << endl;
	                 }
	                 else{	    
	                         cout << "Not Present" << endl;
	                 }
                         break;
	         case 4:
	                 cout << "Enter key associated with value to be searched" << endl;
	                 cin >> key;
	                 if (ht1->has (key) == 1){
	                         cout << key << " : " << ht1->get (key) << endl;
	                 }
	                 else{
	                         cout << "Not present";
	                 }
	                 break;
	         case 5:
                       cout<<endl;          
	               ht1->Display ();
	               break;
	
                case 6:
	               cout<<"Exiting....."<<endl;
                       cout<<endl;
                       exit(1);
	}

    }
}
