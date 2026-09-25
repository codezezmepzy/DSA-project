#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 10
#define MAX_QUEUE 50
#define MAX_STACK 50

// 1. Structure Definition
typedef struct Movie {
    int id;
    char title[50];
    char genre[30];
    int year;
    float rating;
    int watched;   // 0: Unwatched, 1: Watched
    int favorite;  // 0: Not Favorite, 1: Favorite
    struct Movie *prev; // For Doubly Linked List
    struct Movie *next; // For Doubly Linked List
} Movie;

// Hash Table Node for Separate Chaining
typedef struct HashNode {
    int id;
    Movie *moviePtr;
    struct HashNode *next;
} HashNode;

// BST Node for Ratings
typedef struct BSTNode {
    Movie *moviePtr;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

// Global pointers/structures for data management
Movie *head = NULL;
Movie *tail = NULL;
HashNode *hashTable[HASH_SIZE] = {NULL};
BSTNode *bstRoot = NULL;

// Queue for Next Movies to Watch (Array-based)
Movie *watchQueue[MAX_QUEUE];
int qFront = 0, qRear = -1, qSize = 0;

// Stack for Recently Watched Movies (Array-based)
Movie *watchStack[MAX_STACK];
int sTop = -1;

// Function Prototypes
void clearInputBuffer();
void addMovie();
void deleteMovie();
void updateMovie();
void displayWatchlist();
void searchMovie();
void sortMovies();
void enqueueMovie();
void viewNextMovie();
void watchNextMovie();
void displayRecentlyWatched();
void toggleFavorite();
void displayFavorites();
void bstOperations();
void hashTableSearch();
void showStatistics();
void freeAllMemory();

// Hash Function
int hashFunction(int id) {
    return id % HASH_SIZE;
}

// Hash Table Operations
void insertHash(int id, Movie *movie) {
    int index = hashFunction(id);
    HashNode *newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->id = id;
    newNode->moviePtr = movie;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

Movie* searchHash(int id) {
    int index = hashFunction(id);
    HashNode *curr = hashTable[index];
    while (curr != NULL) {
        if (curr->id == id) return curr->moviePtr;
        curr = curr->next;
    }
    return NULL;
}

void deleteHash(int id) {
    int index = hashFunction(id);
    HashNode *curr = hashTable[index];
    HashNode *prev = NULL;
    while (curr != NULL) {
        if (curr->id == id) {
            if (prev == NULL) hashTable[index] = curr->next;
            else prev->next = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// BST Operations
BSTNode* insertBST(BSTNode *root, Movie *movie) {
    if (root == NULL) {
        BSTNode *newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->moviePtr = movie;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (movie->rating < root->moviePtr->rating)
        root->left = insertBST(root->left, movie);
    else
        root->right = insertBST(root->right, movie);
    return root;
}

void inorderBST(BSTNode *root) {
    if (root != NULL) {
        inorderBST(root->left);
        printf("ID: %d | Title: %s | Rating: %.1f\n", root->moviePtr->id, root->moviePtr->title, root->moviePtr->rating);
        inorderBST(root->right);
    }
}

void preorderBST(BSTNode *root) {
    if (root != NULL) {
        printf("ID: %d | Title: %s | Rating: %.1f\n", root->moviePtr->id, root->moviePtr->title, root->moviePtr->rating);
        preorderBST(root->left);
        preorderBST(root->right);
    }
}

void postorderBST(BSTNode *root) {
    if (root != NULL) {
        postorderBST(root->left);
        postorderBST(root->right);
        printf("ID: %d | Title: %s | Rating: %.1f\n", root->moviePtr->id, root->moviePtr->title, root->moviePtr->rating);
    }
}

BSTNode* deleteBSTNode(BSTNode *root, float rating) {
    if (root == NULL) return root;
    if (rating < root->moviePtr->rating)
        root->left = deleteBSTNode(root->left, rating);
    else if (rating > root->moviePtr->rating)
        root->right = deleteBSTNode(root->right, rating);
    else {
        if (root->left == NULL) {
            BSTNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode *temp = root->left;
            free(root);
            return temp;
        }
        BSTNode *curr = root->right;
        while (curr && curr->left != NULL) curr = curr->left;
        root->moviePtr = curr->moviePtr;
        root->right = deleteBSTNode(root->right, curr->moviePtr->rating);
    }
    return root;
}

// Utility to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int choice;
    
    printf("\n==============================\n");
    printf("      MOVIE WATCHLIST         \n");
    printf("==============================\n");
    printf("1. Add Movie\n");
    printf("2. Delete Movie\n");
    printf("3. Update Movie\n");
    printf("4. Display Watchlist\n");
    printf("5. Search Movie\n");
    printf("6. Sort Movies\n");
    printf("7. Add Movie to Watch Queue\n");
    printf("8. View Next Movie\n");
    printf("9. Watch Next Movie\n");
    printf("10. Recently Watched\n");
    printf("11. Add/Remove Favorite\n");
    printf("12. Display Favorites\n");
    printf("13. BST Operations\n");
    printf("14. Hash Table Search\n");
    printf("15. Statistics\n");
    printf("16. Exit\n");
    do{
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch(choice) {
            case 1: addMovie(); break;
            case 2: deleteMovie(); break;
            case 3: updateMovie(); break;
            case 4: displayWatchlist(); break;
            case 5: searchMovie(); break;
            case 6: sortMovies(); break;
            case 7: enqueueMovie(); break;
            case 8: viewNextMovie(); break;
            case 9: watchNextMovie(); break;
            case 10: displayRecentlyWatched(); break;
            case 11: toggleFavorite(); break;
            case 12: displayFavorites(); break;
            case 13: bstOperations(); break;
            case 14: hashTableSearch(); break;
            case 15: showStatistics(); break;
            case 16: 
                freeAllMemory();
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please choose between 1 and 16.\n");
        }
    } while(choice != 16);

    return 0;
}

// 2. Doubly Linked List - Add Movie
void addMovie() {
    Movie *newMovie = (Movie*)malloc(sizeof(Movie));
    if (!newMovie) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Movie ID: ");
    scanf("%d", &newMovie->id);
    clearInputBuffer();

    if (searchHash(newMovie->id) != NULL) {
        printf("Error: Movie ID already exists!\n");
        free(newMovie);
        return;
    }

    printf("Enter Title: ");
    fgets(newMovie->title, sizeof(newMovie->title), stdin);
    newMovie->title[strcspn(newMovie->title, "\n")] = 0;

    printf("Enter Genre: ");
    fgets(newMovie->genre, sizeof(newMovie->genre), stdin);
    newMovie->genre[strcspn(newMovie->genre, "\n")] = 0;

    printf("Enter Release Year: ");
    scanf("%d", &newMovie->year);

    printf("Enter Rating (0.0 - 10.0): ");
    scanf("%f", &newMovie->rating);

    printf("Is it favourite? (1-yes 0-no): ");
    scanf("%d", &newMovie->favorite);

    clearInputBuffer();

    newMovie->watched = 0;
    newMovie->prev = NULL;
    newMovie->next = NULL;

    // Insert into DLL
    if (head == NULL) {
        head = tail = newMovie;
    } else {
        tail->next = newMovie;
        newMovie->prev = tail;
        tail = newMovie;
    }

    // Insert into Hash Table and BST
    insertHash(newMovie->id, newMovie);
    bstRoot = insertBST(bstRoot, newMovie);

    printf("Movie added successfully!\n");
}

// Delete Movie by ID
void deleteMovie() {
    if (head == NULL) {
        printf("Watchlist is empty!\n");
        return;
    }

    int id;
    printf("Enter Movie ID to delete: ");
    scanf("%d", &id);
    clearInputBuffer();

    Movie *target = searchHash(id);
    if (target == NULL) {
        printf("Movie with ID %d not found!\n", id);
        return;
    }

    // Remove from DLL
    if (target == head && target == tail) {
        head = tail = NULL;
    } else if (target == head) {
        head = head->next;
        head->prev = NULL;
    } else if (target == tail) {
        tail = tail->prev;
        tail->next = NULL;
    } else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }

    // Remove from Hash Table and BST
    deleteHash(id);
    bstRoot = deleteBSTNode(bstRoot, target->rating);

    free(target);
    printf("Movie deleted successfully!\n");
}

// Update Movie
void updateMovie() {
    int id;
    printf("Enter Movie ID to update: ");
    scanf("%d", &id);
    clearInputBuffer();

    Movie *target = searchHash(id);
    if (target == NULL) {
        printf("Movie not found!\n");
        return;
    }

    printf("Updating Movie: %s\n", target->title);
    printf("Enter new Title: ");
    fgets(target->title, sizeof(target->title), stdin);
    target->title[strcspn(target->title, "\n")] = 0;

    printf("Enter new Genre: ");
    fgets(target->genre, sizeof(target->genre), stdin);
    target->genre[strcspn(target->genre, "\n")] = 0;

    printf("Enter new Release Year: ");
    scanf("%d", &target->year);

    printf("Enter new Rating: ");
    scanf("%f", &target->rating);
    clearInputBuffer();

    printf("Movie updated successfully!\n");
}

// Display Watchlist
void displayWatchlist() {
    if (head == NULL) {
        printf("Watchlist is empty!\n");
        return;
    }
    printf("\n--- MOVIE WATCHLIST ---\n");
    Movie *curr = head;
    while (curr != NULL) {
        printf("ID: %d | Title: %s | Genre: %s | Year: %d | Rating: %.1f | Status: %s | Fav: %s\n",
               curr->id, curr->title, curr->genre, curr->year, curr->rating,
               curr->watched ? "Watched" : "Unwatched",
               curr->favorite ? "Yes" : "No");
        curr = curr->next;
    }
}

// Search Movie by Title
void searchMovie() {
    if (head == NULL) {
        printf("Watchlist is empty!\n");
        return;
    }
    char title[50];
    printf("Enter title to search: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    Movie *curr = head;
    int found = 0;
    while (curr != NULL) {
        if (strcasecmp(curr->title, title) == 0) {
            printf("Found -> ID: %d | Title: %s | Genre: %s | Year: %d | Rating: %.1f\n",
                   curr->id, curr->title, curr->genre, curr->year, curr->rating);
            found = 1;
        }
        curr = curr->next;
    }
    if (!found) printf("Movie '%s' not found in watchlist.\n", title);
}

// 7. Merge Sort Implementation
void merge(Movie *arr[], int left, int mid, int right, int criteria, int asc) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Movie **L = (Movie**)malloc(n1 * sizeof(Movie*));
    Movie **R = (Movie**)malloc(n2 * sizeof(Movie*));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        int condition = 0;
        if (criteria == 1) { // Rating
            condition = asc ? (L[i]->rating <= R[j]->rating) : (L[i]->rating >= R[j]->rating);
        } else if (criteria == 2) { // Year
            condition = asc ? (L[i]->year <= R[j]->year) : (L[i]->year >= R[j]->year);
        } else { // Title
            condition = asc ? (strcasecmp(L[i]->title, R[j]->title) <= 0) : (strcasecmp(L[i]->title, R[j]->title) >= 0);
        }

        if (condition) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(Movie *arr[], int left, int right, int criteria, int asc) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, criteria, asc);
        mergeSort(arr, mid + 1, right, criteria, asc);
        merge(arr, left, mid, right, criteria, asc);
    }
}

void sortMovies() {
    if (head == NULL) {
        printf("Watchlist is empty!\n");
        return;
    }
    int count = 0;
    Movie *curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }

    Movie **arr = (Movie**)malloc(count * sizeof(Movie*));
    curr = head;
    for (int i = 0; i < count; i++) {
        arr[i] = curr;
        curr = curr->next;
    }

    int criteria, asc;
    printf("Sort by:\n1. Rating\n2. Release Year\n3. Title\nEnter choice: ");
    scanf("%d", &criteria);
    printf("Order:\n1. Ascending\n2. Descending\nEnter choice: ");
    scanf("%d", &asc);
    clearInputBuffer();

    mergeSort(arr, 0, count - 1, criteria, asc == 1);

    // Rebuild DLL pointers
    head = arr[0];
    head->prev = NULL;
    for (int i = 0; i < count - 1; i++) {
        arr[i]->next = arr[i+1];
        arr[i+1]->prev = arr[i];
    }
    tail = arr[count - 1];
    tail->next = NULL;

    free(arr);
    printf("Movies sorted successfully!\n");
    displayWatchlist();
}

// 3. Queue Operations (Next Movies to Watch)
void enqueueMovie() {
    if (qSize >= MAX_QUEUE) {
        printf("Queue is full!\n");
        return;
    }
    int id;
    printf("Enter Movie ID to add to Watch Queue: ");
    scanf("%d", &id);
    clearInputBuffer();

    Movie *m = searchHash(id);
    if (!m) {
        printf("Movie not found!\n");
        return;
    }

    qRear = (qRear + 1) % MAX_QUEUE;
    watchQueue[qRear] = m;
    qSize++;
    printf("Added '%s' to watch queue.\n", m->title);
}

void viewNextMovie() {
    if (qSize == 0) {
        printf("Watch Queue is empty!\n");
        return;
    }
    Movie *m = watchQueue[qFront];
    printf("Next Movie to Watch -> ID: %d | Title: %s | Rating: %.1f\n", m->id, m->title, m->rating);
}

// Watch Next Movie Action Behavior
void watchNextMovie() {
    if (qSize == 0) {
        printf("Watch Queue is empty! No movies to watch.\n");
        return;
    }
    // 1. Dequeue
    Movie *m = watchQueue[qFront];
    qFront = (qFront + 1) % MAX_QUEUE;
    qSize--;

    // 2. Mark as watched
    m->watched = 1;

    // 3. Push onto recently-watched stack
    if (sTop < MAX_STACK - 1) {
        watchStack[++sTop] = m;
    } else {
        printf("Watch history stack full! Oldest history overwritten.\n");
        // Shift stack down if necessary or handle
    }

    printf("Success! Watched movie: '%s' and moved to history.\n", m->title);
}

// 4. Stack Operations (Recently Watched)
void displayRecentlyWatched() {
    if (sTop == -1) {
        printf("Recently watched history is empty!\n");
        return;
    }
    printf("\n--- RECENTLY WATCHED HISTORY (Top to Bottom) ---\n");
    for (int i = sTop; i >= 0; i--) {
        printf("ID: %d | Title: %s | Genre: %s\n", watchStack[i]->id, watchStack[i]->title, watchStack[i]->genre);
    }
}

// Favorites Management
void toggleFavorite() {
    int id;
    printf("Enter Movie ID to toggle favorite status: ");
    scanf("%d", &id);
    clearInputBuffer();

    Movie *m = searchHash(id);
    if (!m) {
        printf("Movie not found!\n");
        return;
    }
    m->favorite = !m->favorite;
    printf("Movie '%s' favorite status updated to: %s\n", m->title, m->favorite ? "Favorite" : "Not Favorite");
}

void displayFavorites() {
    Movie *curr = head;
    int found = 0;
    printf("\n--- FAVORITE MOVIES ---\n");
    while (curr != NULL) {
        if (curr->favorite) {
            printf("ID: %d | Title: %s | Rating: %.1f\n", curr->id, curr->title, curr->rating);
            found = 1;
        }
        curr = curr->next;
    }
    if (!found) printf("No favorite movies added yet.\n");
}

// 6. BST Operations Menu
void bstOperations() {
    int choice;
    printf("\n--- BST OPERATIONS ---\n");
    printf("1. Inorder Traversal (Sorted by Rating)\n");
    printf("2. Preorder Traversal\n");
    printf("3. Postorder Traversal\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (bstRoot == NULL) {
        printf("BST is empty!\n");
        return;
    }

    switch(choice) {
        case 1: inorderBST(bstRoot); break;
        case 2: preorderBST(bstRoot); break;
        case 3: postorderBST(bstRoot); break;
        default: printf("Invalid choice!\n");
    }
}

// 5. Hash Table Search Option
void hashTableSearch() {
    int id;
    printf("Enter Movie ID for fast search: ");
    scanf("%d", &id);
    clearInputBuffer();

    Movie *m = searchHash(id);
    if (m) {
        printf("Found via Hash Table -> ID: %d | Title: %s | Genre: %s | Year: %d | Rating: %.1f\n",
               m->id, m->title, m->genre, m->year, m->rating);
    } else {
        printf("Movie with ID %d not found in Hash Table.\n", id);
    }
}

// Statistics
void showStatistics() {
    int total = 0, watched = 0, favorites = 0;
    float sumRating = 0;
    Movie *curr = head;
    while (curr != NULL) {
        total++;
        if (curr->watched) watched++;
        if (curr->favorite) favorites++;
        sumRating += curr->rating;
        curr = curr->next;
    }

    printf("\n--- WATCHLIST STATISTICS ---\n");
    printf("Total Movies: %d\n", total);
    printf("Watched Movies: %d\n", watched);
    printf("Unwatched Movies: %d\n", total - watched);
    printf("Favorite Movies: %d\n", favorites);
    printf("Average Rating: %.2f\n", total > 0 ? sumRating / total : 0.0);
}

// Memory Cleanup
void freeAllMemory() {
    Movie *curr = head;
    while (curr != NULL) {
        Movie *next = curr->next;
        free(curr);
        curr = next;
    }
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *hCurr = hashTable[i];
        while (hCurr != NULL) {
            HashNode *hNext = hCurr->next;
            free(hCurr);
            hCurr = hNext;
        }
    }
}