#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// data structure
struct Store{
    char nameStore[20];
    long long sale;
    char numPhone[10];
};
struct NodeStore{
    NodeStore *nextSto;
    NodeStore *prevSto;
    Store Store;
};
struct NodeCity{
    NodeCity *nextCt;
    NodeCity *prevCt;
    NodeStore *headSto;
    NodeStore *tailSto;

    char nameCity[30];
};

//Linear Search
NodeCity *search_nameCity(NodeCity *headCity, char nameCt[]){
	NodeCity *ct = headCity;
	while(ct != NULL){
		if(strcmp(ct->nameCity, nameCt) == 0)
			return ct;
		ct = ct->nextCt;
	}
	return NULL;
}
NodeStore *search_nameStore(NodeStore *headStore, char nameSto[]){
    NodeStore *sto = headStore;
	while( sto != NULL){
		if(strcmp(sto->Store.nameStore, nameSto) == 0)
			return sto;
		sto = sto->nextSto;
	}
	return NULL;
}

//Contrustor
void __initStore__(NodeStore *&sto, char nameSto[], long sale, char numPhone[]){
	sto = new NodeStore;
	strcpy(sto->Store.nameStore, nameSto);
	sto->Store.sale = sale;
	strcpy(sto->Store.numPhone, numPhone);
	sto->nextSto = NULL;
	sto->prevSto = NULL;
}
void __initCity__(NodeCity *&ct, char nameCt[]){
	ct = new NodeCity;
    ct->nextCt = NULL;
	ct->prevCt = NULL;
	ct->headSto = NULL;
    ct->tailSto = NULL;
	strcpy(ct->nameCity, nameCt);
}

//Create Node
void append_nodeStore(NodeStore *sto, NodeStore *&headStore, NodeStore *&tailStore){
	if(headStore == NULL){
		headStore = sto;
		tailStore = sto;
	}else{
		NodeStore *n = headStore;
		while(n != NULL){
			if(n->Store.sale > sto->Store.sale){
				if(n == headStore){
					headStore->prevSto = sto;
					sto->nextSto = headStore;
					headStore = sto;
					return;
				}
				NodeStore *q = n->prevSto;
				q->nextSto = sto;
				sto->prevSto = q;
				n->prevSto = sto;
				sto->nextSto = n;
				return;
			}
			n = n->nextSto;
		}

		sto->prevSto = tailStore;
		tailStore->nextSto = sto;
		tailStore = sto;
	}
}
void append_nodeCity(NodeCity *ct, NodeCity *&headCity, NodeCity *&tailCity){
	if(headCity == NULL){
		headCity = ct;
		tailCity = ct;
	}else{
		NodeCity *n = headCity;
		while(n != NULL){
			if(strcmp(n->nameCity, ct->nameCity) > 0){
				if(n == headCity){
					headCity->prevCt = ct;
					ct->nextCt = headCity;
					headCity = ct;
					return;
				}
				NodeCity *q = n->prevCt;
				q->nextCt = ct;
				ct->prevCt = q;
				n->prevCt = ct;
				ct->nextCt = n;
				return;
			}
			n = n->nextCt;
		}
		ct->prevCt = tailCity;
		tailCity->nextCt = ct;
		tailCity = ct;
		tailCity->nextCt = NULL;
	}
}

// Display Node
void print_store(NodeStore *headSto){
    NodeStore *sto = headSto;
	while(sto != NULL){
		printf("\n\tThe store: %s", sto->Store.nameStore);
		printf("\n\tSale: %ld", sto->Store.sale);
		printf("\n\tNumber phone: %s\n", sto->Store.numPhone);
		sto = sto->nextSto;
	}
}
void print_city(NodeCity *headCity){
	NodeCity *ct = headCity;
	if(ct == NULL){
		printf("Data is empty!!!\n");
		return;
	}
	while(ct != NULL){
		printf("\nThe city: %s", ct->nameCity);
		print_store(ct->headSto);
		ct = ct->nextCt;
	}
}

// Input info Node
NodeCity *input_city(NodeCity *&headCity, NodeCity *&tailCity){
    NodeCity *city;
    char nameCt[20];
    printf("\nEnter City's name: ");  fflush(stdin);  gets(nameCt);
    
    NodeCity *ct = search_nameCity(headCity, nameCt);
    if(ct != NULL)
        return ct;
    
    __initCity__(city, nameCt); 
    return city;
}
NodeStore *input_store(NodeStore *&headStore, NodeStore *&tailStore){
    NodeStore *store;
    char nameSto[20], numPhone[10];
    long sale;

    printf("\n\tStore's name: ");    fflush(stdin);  gets(nameSto);
    printf("\tStore's sale: ");   fflush(stdin);  scanf("%ld", &sale);
    printf("\tStore's number phone: "); fflush(stdin);  gets(numPhone);
    if(headStore != NULL)
        if(search_nameStore(headStore, nameSto) != NULL)
            return NULL;
    __initStore__(store, nameSto, sale, numPhone);
    
    return store;
}
void input_name(char nameCity[]){
    fflush(stdin);
    gets(nameCity);
}

// Change info store
void swap_store(Store &sto1, Store &sto2){
    Store tmp = sto1; sto1 = sto2; sto2 = tmp;
}
void change_store(NodeCity *headCity, NodeCity *tailCity){
    NodeCity *city;
    NodeStore *store, *sto;
    char nameCity[20];

    printf("\nEnter name of the city that contains the store changed: ");   fflush(stdin);  gets(nameCity);
    city = search_nameCity(headCity, nameCity);
    if(city == NULL){
        printf("Error: Not found %s", nameCity); return;
    }
    printf("\nName of the city: %s", city->nameCity);
	print_store(city->headSto);

    printf("\nEnter name of the store changed: ");  fflush(stdin);  gets(nameCity);
    store = search_nameStore(city->headSto, nameCity);
    if(city == NULL){
        printf("Error: Not found %s", nameCity); return;
    }
    printf("\tEnter Store's placed name: ");
    fflush(stdin);
    gets(store->Store.nameStore);
    printf("\tStore's placed sale: ");
    fflush(stdin);
    scanf("%ld", &store->Store.sale);
    printf("\tStore's placed number phone: ");
    fflush(stdin);
    gets(store->Store.numPhone);
    
    sto = city->headSto;
    while(sto != NULL){
        if(sto->Store.sale > store->Store.sale){
            swap_store(sto->Store, store->Store);
            break;
        }
        sto = sto->nextSto;
    }
}

// Delete
int del_city(NodeCity *&headCity, NodeCity *&tailCity, char nameCity[]){
	NodeCity *city = search_nameCity(headCity, nameCity);
	if(city == NULL)
		return 0;
	else{
		if(headCity == city){       // Delete head node
            if(headCity == tailCity)
                headCity = tailCity = NULL;
            else{
                headCity = city->nextCt;
                headCity->prevCt = NULL;
	        }
            delete city;
        }
		else if(tailCity == city){ // Delete tail node
            tailCity = city->prevCt;
	        tailCity->nextCt = NULL;
	        delete city;
        }
		else{                       // Delete mid node
            NodeCity *tmp;
            tmp = city->nextCt;
            tmp->prevCt = city->prevCt;
            city->prevCt->nextCt = tmp;
            delete city;
        }
		return 1;
	}
}
int del_store(NodeStore *&headStore, NodeStore *&tailStore, char nameStore[]){
	NodeStore *store = search_nameStore(headStore, nameStore);
	if(store == NULL)
		return 0;
	else{
		if(headStore == store){     // Delete head_node
            if(headStore == tailStore)
                headStore = tailStore = NULL;
            else{
                headStore = store->nextSto;
                headStore->prevSto = NULL;
	        }
            delete store;
        }
		else if(tailStore == store){ // Delete tail_node
            tailStore = store->prevSto;
	        tailStore->nextSto = NULL;
	        delete store;
        }
		else{                       // Delete mid_node                        
            NodeStore *tmp;
            tmp = store->nextSto;
            tmp->prevSto = store->prevSto;
            store->prevSto->nextSto = tmp;
            delete store;
        }
		return 1;
	}
}

// Report
void border(int length){
    for(int i = 0; i < length; i++)
		printf("-");
}
void report_store(NodeStore *headStore, char title[]){  
    NodeStore *store = headStore;
	long totalOfSale = 0;
    int stt = 1;
    printf("\n%30s\n", title); 
    border(59);
    printf("\n|%5s |%15s |%15s |%15s |\n", "STT","Store's name", "Sale", "Number phone");
    while(store != NULL){
        totalOfSale += store->Store.sale;
        printf("|%5d |%15s |%15ld |%15s |\n", stt++, store->Store.nameStore, store->Store.sale, store->Store.numPhone);
        store = store->nextSto;
    }
    border(59);
    printf("\n| %5s  %8s  Total Revenue: %ld  %20s |\n", "", "", totalOfSale, "");
	border(59);
}
void rank_store(NodeStore *headStore, NodeStore *rank, char title[]){
    NodeStore *store = headStore;
    int stt = 1;
    printf("\n%38s\n", title);
    border(59);
   printf("\n|%5s |%15s |%15s |%15s |\n", "STT","Store's name", "Sale", "Number phone");
    while(store != NULL){
        if(store->Store.sale == rank->Store.sale)
            printf("|%5d |%15s |%15ld |%15s |\n", stt++, store->Store.nameStore, store->Store.sale, store->Store.numPhone);
        store = store->nextSto;
    }
    border(59);
}
void report(NodeCity *headCity, NodeCity *tailCity){
	NodeCity *city = headCity;
    int stt;
	if(city == NULL){
		printf("Data is empty!!!\n");
		return;
	}
    printf("\n");
	border(121);
	printf("\n|%5s |%20s |\t%20s |\t%15s |\t%16s |\t%15s |", "STT", "List of City", "The number of store", "Total Revenue", "The highest sale", "The lowest sale");
	
    stt = 1;
	while(city != NULL){
		NodeStore *store = city->headSto;
		long totalOfSale = 0;
		int totalOfStore = 0;
		while(store != NULL){
			totalOfSale += store->Store.sale;
			store = store->nextSto;
			totalOfStore++;
		}
		store = city->headSto;
		printf("\n|%5d |%20s |\t%20d |\t%15ld |\t%16ld |\t%15ld |",  stt++, city->nameCity, totalOfStore, totalOfSale, city->tailSto->Store.sale, city->headSto->Store.sale);
		city = city->nextCt;
	}
    
    printf("\n"); 
	border(121);
	printf("\n");
}
void report_nameCity(NodeCity *headCity, NodeCity *tailCity, char nameCity[]){
	NodeCity *city = search_nameCity(headCity, nameCity);
    char title[50];

	if(city == NULL)
		printf("\nError 404: Not found %s\n", nameCity);
	else{
        report_store(city->headSto, city->nameCity);
		printf("\n");
		
        printf("\n");
        strcpy(title, "The Highest Sale");
        rank_store(city->headSto, city->tailSto, title);

        printf("\n");
        strcpy(title, "The Lowest Sale");
        rank_store(city->headSto, city->headSto, title);
	}
}

int main(){
    
    NodeCity *headCity = NULL, *tailCity = NULL;
    NodeCity *city; 
    NodeStore *store;
    int choice, quantityOfCity, quantityOfStore, error;
    char nameCity[20], nameStore[20];

    do{
        printf("\n\n1. Create a list of cities \n2. Insert a city \n3. Insert a store \n4. Change a store \n5. Delete a city \n6. Delete a store \n7. Show data \n8. Making a report \n9. Making a report for a city");
		printf("\n10. Exit \nEnter: ");
		scanf("%d", &choice);
        switch (choice){
            case 1:
                printf("Enter the number of city list: ");  scanf("%d", &quantityOfCity);
                for(int i = 0; i < quantityOfCity; i++){
                    city = input_city(headCity, tailCity);
                    printf("Enter the number of store: "); scanf("%d", &quantityOfStore);
                    for(int ii = 0; ii < quantityOfStore; ii++){
                        store = input_store(city->headSto, city->tailSto);
                        if(store == NULL)
                            printf("\n\tAvailable store!!!");
                        else
                            append_nodeStore(store, city->headSto, city->tailSto);
                    }
                    append_nodeCity(city, headCity, tailCity);
                }
                
                break;
            case 2:
                city = input_city(headCity, tailCity);
                printf("Enter the number of store: "); scanf("%d", &quantityOfStore);
                    for(int i = 0; i < quantityOfStore; i++){
                        store = input_store(city->headSto, city->tailSto);
                        if(store == NULL)
                            printf("\n\tAvailable store!!!");
                        else
                            append_nodeStore(store, city->headSto, city->tailSto);
                    }
                append_nodeCity(city, headCity, tailCity);
                break;
            case 3:                
                printf("\nEnter city's name to put store in: ");
                fflush(stdin);
                gets(nameCity);
                city = search_nameCity(headCity, nameCity);
                if(city == NULL){
                    __initCity__(city, nameCity);
                    append_nodeCity(city, headCity, tailCity);
                }
                store = input_store(city->headSto, city->tailSto);
                if(store == NULL)
                    printf("\nAvailable store!!!");
                else
                    append_nodeStore(store, city->headSto, city->tailSto);

                break;
            case 4:
                change_store(headCity, tailCity);

                break;
            case 5:
                printf("\nEnter a city name to delete: ");
                input_name(nameCity);
                city = search_nameCity(headCity, nameCity);
                if(city == NULL)
                    printf("Unvailable city!!!");
                error = del_city(headCity, tailCity, nameCity);
                if(error == 0)
                    printf("\nError 404: Not found %s", nameCity);
                else
                    printf("***Completion!!!****");
                break;
            case 6:
                printf("\nEnter a city name that contains store deleted: ");
                input_name(nameCity);
                city = search_nameCity(headCity, nameCity);
                if(city == NULL)
                    printf("Unvailable city!!!");
                else{
                    printf("\nEnter a store name to delete: ");
                    input_name(nameStore);
                    store = search_nameStore(city->headSto, nameStore);
                    if(store == NULL)
                        printf("Unvailable store!!!");
                    else{
                        error = del_store(city->headSto, city->tailSto, nameStore);
                        if(error == 0)
                            printf("Error 404: Not found %s", nameCity);
                        else
                            printf("***Completion!!!****");
                    } 
                }
                
                break;
            case 7:
                print_city(headCity);

                break;
            case 8:
                report(headCity, tailCity);

                break;
            case 9:
                printf("\nEnter a city name to make report: ");
                input_name(nameCity);
                report_nameCity(headCity, tailCity, nameCity);

                break;
        }
    }while(choice > 0 && choice < 10);
    
    return 0;
}