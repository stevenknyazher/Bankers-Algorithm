#include <stdio.h>
#include <stdlib.h>

int *resource = NULL;
int *available = NULL;
int *maxclaim = NULL;
int *allocation = NULL;
int *need = NULL;

int num_processes;
int num_resources;
int request_release_processor;
int request_release_resource;
int num_units_request_release;
    
void print_resources() {
    printf("\nResources: \n");
    for (int i = 0; i < num_resources; i++) {
        printf("\tr%d", i);
    }
    printf("\n");
    
    for (int i = 0; i < num_resources; i++) {
        printf("\t%d", resource[i]);
    }
    printf("\n");
}

void print_avaliable_resources() {
    printf("\nAvailable: \n");
    for (int i = 0; i < num_resources; i++) {
        printf("\tr%d", i);
    }
    printf("\n");
    
    for (int i = 0; i < num_resources; i++) {
        printf("\t%d", available[i]);
    }
    printf("\n");
}

void print_maxclaims() {
    printf("\nMaximum: \n");
    for (int i = 0; i < num_resources; i++) {
        printf("\tr%d", i);
    }
    
    for (int i = 0; i < num_processes; i++) {
        printf("\np%d\t", i);
        for (int j = 0; j < num_resources; j++) {
            printf("%d\t", maxclaim[i * num_resources + j]);
        }
    }
}

void print_allocation() {
    printf("\n\nAllocated: \n");
    for (int i = 0; i < num_resources; i++) {
        printf("\tr%d", i);
    }
    
    for (int i = 0; i < num_processes; i++) {
        printf("\np%d\t", i);
        for (int j = 0; j < num_resources; j++) {
            printf("%d\t", allocation[i * num_resources + j]);
        }
    }
}

void print_need() {
    printf("\n\nNeed: \n");
    for (int i = 0; i < num_resources; i++) {
        printf("\tr%d", i);
    }
    
    for (int i = 0; i < num_processes; i++) {
        printf("\np%d\t", i);
        for (int j = 0; j < num_resources; j++) {
            printf("%d\t", need[i * num_resources + j]);
        }
    }
}

void print_avaliable_resources_request() {
    printf("\nAvailable: \n");
    for (int i = 0; i < num_resources; i++) {
        printf("\tr%d", i);
    }
    printf("\n");
    
    for (int i = 0; i < num_resources; i++) {
        if (i == request_release_resource) {
            available[i] = available[i] - num_units_request_release;
            printf("\t%d", available[i]);
        } else {
            printf("\t%d", available[i]);
        }
    }
}

void print_allocation_request() {
    printf("\n\nAllocated: \n");
    for (int i = 0; i < num_resources; i++) {
        printf("\tr%d", i);
    }
    
    for (int i = 0; i < num_processes; i++) {
        printf("\np%d\t", i);
        for (int j = 0; j < num_resources; j++) {
            if (i == request_release_processor && j == request_release_resource) {
                allocation[i * num_resources + j] = allocation[i * num_resources + j] + num_units_request_release;
                printf("%d\t", allocation[i * num_resources + j]);
            } else {
                printf("%d\t", allocation[i * num_resources + j]);
            }
        }
    }
}

void print_need_request() {
    printf("\n\nNeed: \n");
    for (int i = 0; i < num_resources; i++) {
        printf("\tr%d", i);
    }
    
    for (int i = 0; i < num_processes; i++) {
        printf("\np%d\t", i);
        for (int j = 0; j < num_resources; j++) {
            if (i == request_release_processor && j == request_release_resource) {
                need[i * num_resources + j] = need[i * num_resources + j] - num_units_request_release;
                printf("%d\t", need[i * num_resources + j]);
            } else {
                printf("%d\t", need[i * num_resources + j]);
            }
        }
    }
}

void print_avaliable_resources_release() {
    printf("\nAvailable: \n");
    for (int i = 0; i < num_resources; i++) {
        printf("\tr%d", i);
    }
    printf("\n");
    
    for (int i = 0; i < num_resources; i++) {
        if (i == request_release_resource) {
            available[i] = available[i] + num_units_request_release;
            printf("\t%d", available[i]);
        } else {
            printf("\t%d", available[i]);
        }
    }
}

void print_allocation_release() {
    printf("\n\nAllocated: \n");
    for (int i = 0; i < num_resources; i++) {
        printf("\tr%d", i);
    }
    
    for (int i = 0; i < num_processes; i++) {
        printf("\np%d\t", i);
        for (int j = 0; j < num_resources; j++) {
            if (i == request_release_processor && j == request_release_resource) {
                allocation[i * num_resources + j] = allocation[i * num_resources + j] - num_units_request_release;
                printf("%d\t", allocation[i * num_resources + j]);
            } else {
                printf("%d\t", allocation[i * num_resources + j]);
            }
        }
    }
}

void print_need_release() {
    printf("\n\nNeed: \n");
    for (int i = 0; i < num_resources; i++) {
        printf("\tr%d", i);
    }
    
    for (int i = 0; i < num_processes; i++) {
        printf("\np%d\t", i);
        for (int j = 0; j < num_resources; j++) {
            if (i == request_release_processor && j == request_release_resource) {
                need[i * num_resources + j] = need[i * num_resources + j] + num_units_request_release;
                printf("%d\t", need[i * num_resources + j]);
            } else {
                printf("%d\t", need[i * num_resources + j]);
            }
        }
    }
}

void enter_parameters() {
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);
    
    resource = (int *) malloc(num_processes * sizeof(int));
    available = (int *) malloc(num_processes * sizeof(int));
    maxclaim = (int *) malloc(num_processes * num_resources * sizeof(int));
    allocation = (int *) malloc(num_processes * num_resources * sizeof(int));
    need = (int *) malloc(num_processes * num_resources * sizeof(int));

    int units;

    printf("Enter number of units for resources (r%d to r%d): ", 0, num_resources - 1);
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &units);
        resource[i] = units;
        available[i] = units;
    }

    for (int i = 0; i < num_processes; i++) {
        printf("Enter maximum number of units process p%d will request from each resource (r%d to r%d): ", i, 0, num_resources - 1);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", & units);
            maxclaim[i * num_resources + j] = units;
            need[i * num_resources + j] = units;
        }
    }
    
    for (int i = 0; i < num_processes; i++) {
        printf("Enter number of units of each resource (r%d to r%d) allocated to process p%d: ", 0, num_resources - 1, i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", & units);
            allocation[i * num_resources + j] = units;
            need[i * num_resources + j] -= units;
            available[j] -= units;
        }
    }
    
    print_resources();
    print_avaliable_resources();
    print_maxclaims();
    print_allocation();
    print_need();
    printf("\n");
}

void request_resource() {
    printf("Enter requesting processor: p");
    scanf("%d", &request_release_processor);
    printf("Enter requested resource: r");
    scanf("%d", &request_release_resource);
    printf("Enter number of units requested from resource r%d: ", request_release_resource);
    scanf("%d", &num_units_request_release);

    print_avaliable_resources_request();
    print_allocation_request();
    print_need_request();
    printf("\n");
}

void release_resource() {
    printf("Enter releasing processor: p");
    scanf("%d", &request_release_processor);
    printf("Enter released resource: r");
    scanf("%d", &request_release_resource);
    printf("Enter number of units to be released from resource r%d: ", request_release_resource);
    scanf("%d", &num_units_request_release);

    print_avaliable_resources_release();
    print_allocation_release();
    print_need_release();
    printf("\n");
}

void bankers_algorithm() {
    int count_sequenced = 0;
    int less_than;
    
    int *sequenced = (int *) calloc(num_processes, sizeof(int));
    
    while (count_sequenced < num_processes) {
        for (int i = 0; i < num_processes; i++) {
            less_than = 1;
            if (sequenced[i] == 0) {
                printf("Comparing: <");
                for (int j = 0; j < num_resources; j++) {
                    printf(" %d", need[i * num_resources + j]);
                }
                printf(" > <= <");
                
                for (int j = 0; j < num_resources; j++) {
                    printf(" %d", available[j]);
                }
                printf(" >");
                
                for (int j = 0; j < num_resources; j++) {
                    less_than &= (need[i * num_resources + j] <= available[j]);
                }
                
                if (less_than == 1) {
                    printf(" : Yes --> p%d can be safely sequenced", i);
                    sequenced[i] = 1;
                    count_sequenced++;
                    
                    for (int j = 0; j < num_resources; j++) {
                        available[j] += allocation[i * num_resources + j];
                        allocation[i *num_resources + j] = 0; 
                        need[i *num_resources + j] = maxclaim[i *num_resources + j];
                    }
                } else {
                    printf(" : No --> p%d cannot be safely sequenced", i);
                }
                printf("\n");
            }
        }
    }
    free(sequenced);
}

int main() {
    int option;
    
    do {
        printf("\nBanker's Algorithm\n");
        printf("--------------------------------\n");
        printf("1) Enter parameters\n");
        printf("2) Request resource\n");
        printf("3) Release resource\n");
        printf("4) Determine safe sequence\n");
        printf("5) Quit program\n");
        printf("\nEnter selection: ");
        scanf("%d", &option);
        
        switch (option) {
            case 1:
                enter_parameters();
                break;
            case 2:
                request_resource();
                break;
            case 3:
                release_resource();
                break;
            case 4:
                bankers_algorithm();
                break;
            case 5:
                printf("Quitting program...");
                break;
            default: 
                printf("\nNot a valid option\n");
        }
    } while (option != 5);
    return 0;
}
