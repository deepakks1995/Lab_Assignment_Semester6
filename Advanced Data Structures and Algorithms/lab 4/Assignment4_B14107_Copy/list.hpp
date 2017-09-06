#ifndef _list_H_
#define _list_H_
#include <cassert>

namespace abc{
   
     template <typename T>
     class list {
 
                private:
                     class Node {
                             friend class list<T>;

                             private:
                             T data;
                             T key;
                            // int probe;
                             Node* next;

                             public:
                             Node(T k,T d, Node* n = NULL) : key(k),data(d), next(n) {}
                             };

                     Node* head; 
                     Node* tail; 
                     int count;
                     int c;  

               public:
                     list(const list<T>& x);  
                     ~list(void); 
                     list(void) : head(NULL), tail(NULL), count(0),c(0) {}
                     inline int length(void) {
                                     return count;
                     }
                     inline bool empty(void) {
                                     return count == 0;
                     }
                     void cons(const T& key,const T& value);
                     void remove(int x);
                     void append(const T& key,const T& value );
                     void append(list<T>& x);
                     void dump(void);
                      T& front(void) {
                           assert (head != NULL);
                           return head->data;
                     }
                   T& next(void){
                            assert(head != NULL);
                            Node* temp;
                            temp=head;
                            head=head->next;
                            count--;
                            return temp->data;
                               }
                  T& next1(void){
                            assert(head != NULL);
                            Node* temp;
                            temp=head;
                            int t=0;
                         while(c!=t){
                            temp=temp->next;
                            t++;
                         }
                          c++;
                            //count--;
                            if(temp)
                               return temp->key;
                           //  else 
                             //  return ;
                               }
                 T& next2(void){
                            assert(head != NULL);
                            Node* temp;
                            temp=head;
                            int t=0;
                         while(c!=t){
                            temp=temp->next;
                            t++;
                         }
                          c++;
                            //count--;
                            if(temp)
                               return temp->data;
                            // else 
                              // return "Not Found";
                               }
                 
                 
      };

      template<typename T>
      void list<T>:: cons(const T& key,const T& value){

                  Node* new_head = new Node(key,value,head);

                    if(this->empty()){
                            head = new_head;
                            tail = new_head;
                     }
                   else {
                            head = new_head;
                   }
                  count++;

       }

       template<typename T>
       void list<T>:: remove(int x){

                 assert(head != NULL); 
                 Node  *current = head;

	         for (int  i=1;  i < x-1;  i++){
			current = current -> next;
	         }
	         Node  *p = head;
                 if(x==1){
                      head=head->next;
                 }
                else{        
	              p = current -> next;
	              current -> next = p -> next;
                }
	        delete  p;
                count--;
       }

       template<typename T>
       void list<T>::append(const T& key,const T& value){ 

                Node* new_tail = new Node(key,value, NULL);

                if(this->empty()) {
                          head = new_tail;
                } 
               else {
                         tail->next = new_tail;
               }

               tail = new_tail;
               count++;
       }

       template<typename T>
       void list<T>::append(list<T>& x){

               Node *temp ;

               if ( head == NULL )
                      head = x.head ;
               else{
                     if ( x.head != NULL ){
                                temp = head ;
                                while ( temp -> next != NULL )
                                        temp = temp -> next ;
                                temp -> next= x.head ;  

                     }
               }       

        }

        template<typename T>
        list<T>::~list(){
 
                int k=count;
                while(!this->empty()){
                         this->remove(k);
                         k--;
                }
        }

        template<typename T>
        list<T>::list(const list<T> & x) : count(0),head(NULL), tail(NULL){
 
                  Node* current = x.head;

                  while(current != NULL){
                        this->append(current->data);
                        current=current->next;
                  }
         }

        template <typename T>
        void list<T>::dump() {
    
        // std::cout << "(";

        Node* current = head;

     if (current != NULL) {
   
        while (current->next != NULL) {
            std::cout <<current->key<<","<<current->data <<std::endl;
            current = current->next;
        }
        //std::cout << current->data;
        std::cout <<current->key<<","<<current->data <<std::endl;
    }

    //std::cout << ")"<<std:: endl;
     }

   


           
}    


#endif


