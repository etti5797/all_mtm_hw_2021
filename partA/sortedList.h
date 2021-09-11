#ifndef SORTEDLIST_H
#define SPRTEDLIST_H

#include <iostream>
#include <stdexcept>
using std::out_of_range;


namespace mtm
{
    template<class T>
    class SortedList
    {
        friend class const_iterator;
        private:
        class Node
        {
            friend class SortedList::const_iterator;
            private:
            T data;
            Node* next;
            friend class SortedList;

            public:
            explicit Node(const T& data): data(data),next(nullptr)
            {                                                          
            }
            ~Node()=default;
            Node(const Node& node)=delete;
            Node& operator=(const Node& node)=delete;
            Node* getNext()
            {
                return this->next;
            }

        };

        Node* head;
        Node* tail;

        void insertAtStart(T element)
        {
            if(head==nullptr) //the list is empty
            {
                Node* new_node=new Node(element);  
                head=new_node;
                tail=new_node;
            }
            else //there is at least one element in the list
            {
                Node* new_node=new Node(element);
                new_node->next=head;
                head=new_node;
            }
            return;
        }

        void insertAtEnd(T element)
        {
            if(head==nullptr) //the list is empty so adding as last is also adding as first
            {
                Node* new_node=new Node(element);
                head=new_node;
                tail=new_node;
            }
            else //there is at least one element in the list
            {
                Node* new_node=new Node(element);
                tail->next=new_node;
                tail=new_node;
            }
            return;
        }
        
        void removeFromStart()
        {
            Node* to_remove=head;
            head=head->next;
            delete to_remove;
        }

        void removeFromEnd()
        {
            Node* to_remove=tail;
            Node* before_last=head;
            while(before_last!=nullptr)
            {
                if(before_last->next==tail)
                {
                    break;
                }
                before_last=before_last->next;
            }
            tail=before_last;
            tail->next=nullptr;
            delete to_remove;
        }

        public:
        SortedList(): head(nullptr),tail(nullptr){};
        ~SortedList()
        {
            if(head!=nullptr) //if the list is not empty we need to delete the data inside
            {
                Node* current=head;
                Node* to_delete=nullptr;
                while(current!=nullptr)
                {
                    to_delete=current;
                    current=current->next;
                    delete to_delete;
                }
                head=nullptr;
                tail=nullptr; 
            }
        }

        SortedList(const SortedList& copy_list) //copy the recived copy_list into this
        {
            this->head=nullptr;
            this->tail=nullptr;
            Node* to_copy=copy_list.head;
            while(to_copy!=nullptr)
            {
                this->insert(to_copy->data);     
                to_copy=to_copy->next;
            }
        }

        SortedList& operator=(const SortedList& list)
        {
            if(this==&list) //it's the same list
            {
                return *this;
            }
            if(head!=nullptr) //the list isn't empty and need to be emptied
            {
                Node* current=head;
                Node* to_delete=nullptr;
                while(current!=nullptr)
                {
                    to_delete=current;
                    current=current->next;
                    delete to_delete;
                }
            }
            //now copy the new data 
            head=nullptr;
            tail=nullptr;
            Node* to_copy=list.head;
            while(to_copy!=nullptr)
            {
                insert(to_copy->data); 
                to_copy=to_copy->next;
            }
            return *this;
        }

        void insert(T element)  
        {
            if(head==nullptr) //list is empty
            {
                insertAtStart(element);
                return;
            }      
            if(element < (head->data))  
            {
                insertAtStart(element);
                return;
            }
            if( !( (element) <  (tail->data) ) )
            {
                insertAtEnd(element);
                return;
            }
            Node* current=head;
            Node* new_node=new Node(element);
            while(current!=tail)
            {  
                if(element < (current->next->data) && (!(element< current->data) )) //element<next && element>=current
                {
                    new_node->next=current->next;
                    current->next=new_node;
                    break;
                }
                current=current->next;
            }
            return;           
        }

        int length()const
        {
            int num_elements=0;
            Node* current=head;
            while(current!=NULL)
            {
                num_elements++;
                current=current->next;
            }
            return num_elements;
        }

        class const_iterator
        {
            friend class SortedList;
            private:
            Node* node_ptr;
            explicit const_iterator(Node* node):node_ptr(node){};
            public:
            const_iterator():node_ptr(nullptr){};
            ~const_iterator()=default;                                  
            const_iterator(const const_iterator& iterator) = default;
            bool operator==(const const_iterator& iterator) const
            {
                return (this->node_ptr== iterator.node_ptr);
            }
            bool operator!=(const const_iterator& iterator) const
            {
                return !(operator==(iterator));
            }
            const T& operator*()const
            {
                return node_ptr->data;  
            }
            const_iterator& operator=(const const_iterator& iterator)=default;
            const_iterator& operator++() //++iterator
            {
                if(node_ptr==nullptr)
                {
                    throw out_of_range("list out of range");                            
                }
                this->node_ptr=this->node_ptr->next;
                return *this;
            }
            const_iterator operator++(int) //iterator++
            {
                const_iterator iterator=const_iterator(*this);
                if(node_ptr==nullptr)
                {
                    throw out_of_range("list out of range");  
                }
                ++(*this);
                return iterator;
            }

        };

        void remove(const_iterator iterator)
        {
            if(head==nullptr) //the list is empty
            {
                return;
            }
            if(iterator.node_ptr==head) //remove the first
            {
                removeFromStart();
                return;
            }
            if(iterator.node_ptr==tail) //remove the last
            {                                     
                removeFromEnd(); 
                return;
            }
                //remove from somewhere in between head and tail (not the first and not the last!)
            Node* to_erase=head;
            Node* before_erase=nullptr;
            while(to_erase!= iterator.node_ptr)
            {
                before_erase=to_erase;
                to_erase=to_erase->next;
            }
            before_erase->next=to_erase->next;
            delete to_erase;
            return;
        }
        
        const_iterator begin() const
        {
            return const_iterator(head);
        }

        const_iterator end() const
        {
            return const_iterator(tail->getNext()); 
        }

        template<class predicate> 
        SortedList filter(predicate condition) const
        {
            SortedList new_list=SortedList();   
            for(const_iterator iterator=begin(); iterator!=end(); ++iterator)
            {
                if(condition(*iterator))
                {
                    new_list.insert(*iterator);
                }
            }
            return new_list;
        }

           
        template<class function>    
        SortedList apply(function change)const   
        {
            SortedList new_list=SortedList();                                     
            for(const_iterator iterator=begin(); iterator!=end(); ++iterator)
            {
                new_list.insert(change(*iterator));
            }
            return new_list;                                     
        }

     
    };
}

#endif
