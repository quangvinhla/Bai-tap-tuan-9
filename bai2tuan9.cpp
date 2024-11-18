#include <iostream>
#include <cstring>

using namespace std;

// Định nghĩa cấu trúc của một node trong danh sách liên kết
struct Node {
    char word[50];
    int count;
    Node* next;
};

// Hàm khởi tạo node mới
Node* createNode(const char* word) {
    Node* newNode = new Node;
    strcpy(newNode->word, word);
    newNode->count = 1;
    newNode->next = nullptr;
    return newNode;
}

// Hàm thêm từ vào danh sách liên kết (nếu từ đã tồn tại thì tăng biến đếm)
void addWord(Node*& head, const char* word) {
    Node* current = head;
    while (current != nullptr) {
        if (strcmp(current->word, word) == 0) {
            current->count++;
            return;
        }
        current = current->next;
    }

    Node* newNode = createNode(word);
    newNode->next = head;
    head = newNode;
}

// Hàm tìm từ xuất hiện nhiều nhất
void findMostFrequentWord(Node* head) {
    Node* current = head;
    Node* mostFrequent = head;
    while (current != nullptr) {
        if (current->count > mostFrequent->count) {
            mostFrequent = current;
        }
        current = current->next;
    }
    if (mostFrequent != nullptr) {
        cout << "Tu xuat hien nhieu nhat: " << mostFrequent->word << " - " << mostFrequent->count << " lan" << endl;
    }
}

// Hàm kiểm tra xem một từ có phải là từ láy hay không
bool isReduplicative(const char* word) {
    int len = strlen(word);
    if (len % 2 != 0) return false;
    int mid = len / 2;
    for (int i = 0; i < mid; i++) {
        if (word[i] != word[mid + i]) return false;
    }
    return true;
}

// Hàm loại bỏ từ láy
void removeReduplicativeWords(Node*& head) {
    Node* current = head;
    Node* prev = nullptr;
    while (current != nullptr) {
        if (isReduplicative(current->word)) {
            if (prev == nullptr) {
                head = current->next;
                delete current;
                current = head;
            } else {
                prev->next = current->next;
                delete current;
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// Hàm đếm số từ vựng
int countWords(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Hàm tách câu thành các từ và lưu vào danh sách liên kết
void splitSentence(Node*& head, const char* sentence) {
    char temp[1000];
    strcpy(temp, sentence);
    char* token = strtok(temp, " ");
    while (token != nullptr) {
        addWord(head, token);
        token = strtok(nullptr, " ");
    }
}

int main() {
    Node* head = nullptr;
    char sentence[1000];

    cout << "Nhap cau: ";
    cin.getline(sentence, 1000);

    splitSentence(head, sentence);

    cout << "So tu vung trong cau: " << countWords(head) << endl;

    findMostFrequentWord(head);

    removeReduplicativeWords(head);
    cout << "So tu vung sau khi loai bo tu lay: " << countWords(head) << endl;

    return 0;
}