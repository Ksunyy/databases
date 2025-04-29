#include <iostream>
#include <queue>
#include "Polinom.h"

class BasePolinomStorage {
public:
    virtual ~BasePolinomStorage() = default;
    virtual int add() { return 0; };   // Добавить полином
    virtual Polinom find() { return Polinom(); };  // Найти полином
    virtual int remove() { return 0; };
};

class SArray : public BasePolinomStorage {
private:
    struct Entry {
        std::string name;
        Polinom data;
        Entry() {};
        Entry(const std::string& n, const Polinom& d) {
            name = n;
            data = d;
        }
    };
    std::vector<Entry> data;
    bool hasName(std::string n) {
        for (Entry c : data){
            if (c.name == n) {
                return 1;
            }
        }
        return 0;
    }
    bool isSorted() {
        for (int i = 0; i < data.size() - 1; i++) {
            if (data[i].name > data[i + 1].name) {
                return 0;
            }
        }
        return 1;
    }

    int find_int(std::string n) {
        int left = 0, right = data.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (data[mid].name == n) {
                return mid;
            }
            else if (data[mid].name < n) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return -1;
    }
public:

    int add(const std::string& n, const Polinom& d) {
        //O(n)
        if (hasName(n)) {
            throw "this name already in array";
        }
        Entry dat = Entry(n, d);
        //O(c)
        data.push_back(dat);
        //O(n)
        if (isSorted()) {
            std::cout << n << "\n";
            return 0;
        }
        int k = data.size()-1;
        //O(n) (находим i один раз и один раз выполняем while)
        for (int i = 0; i < k; i++) {
            if (data[i].name < n && n < data[i + 1].name) {
                Entry temp = data[i + 1];
                data[i + 1] = data[k];
                data[k] = temp;
                i++;
                while (i<k) {
                    temp = data[i+1];
                    data[i + 1] = data[k];
                    data[k] = temp;
                    i++;
                }
                break;
            }
            if (data[i].name > n) {
                Entry temp = data[i];
                data[i] = data[k];
                data[k] = temp;
                while (i < k) {
                    temp = data[i + 1];
                    data[i + 1] = data[k];
                    data[k] = temp;
                    i++;
                }
                break;
            }
        }
        return 0;
    }
    Polinom find(std::string n) {
        int left = 0, right = data.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2; 

            if (data[mid].name == n) {
                return data[mid].data; 
            }
            else if (data[mid].name < n) {
                left = mid + 1; 
            }
            else {
                right = mid - 1; 
            }
        }
        return NULL;
    }
    int remove(std::string n) {
        int ind = find_int(n);
        if (ind!= -1) {
            int k = ind;
            while (k < data.size()-1) {
                data[k] = data[k + 1];
            }
            data.pop_back();
            return 0;
        }
        return -1;
    }
    void print() {
        for (Entry c : data) {
            std::cout << c.name << ": ";
            c.data.print();
        }
    }
 };

class AVLtree :public BasePolinomStorage {
private:
    struct Entry {
        std::string name;
        Polinom data;
        Entry() {};
        Entry(const std::string& n, const Polinom& d) {
            name = n;
            data = d;
        }
    };
    struct Node {
        Node* left;
        Node* right;
        Entry data;
        int height;
        Node() {
            left = nullptr;
            right = nullptr;
            data = Entry();
            height = 0;
        }
        ~Node() {
            left = nullptr;
            right = nullptr;
        }
        int countHeigth() {
            int l,r;
            if (this->left == nullptr) {
                l = 0;
            }
            else {
                l = this->left->height;
            }
            if (this->right == nullptr) {
                r = 0;
            }
            else {
                r = this->right->height;
            }

            return 1+std::max(r, l);
        }
        int countBalance() {
            int l, r;
            if (this->left == nullptr) {
                l = 0;
            }
            else {
                l = this->left->height;
            }
            if (this->right == nullptr) {
                r = 0;
            }
            else {
                r = this->right->height;
            }
            return l - r;
        }
        Node* leftTurn() {
            std::cout << "Left turt in "<<this->data.name<<"\n";
            Node* newRoot = this->right;  
            Node* leftSubtree = newRoot->left;

            newRoot->left = this;
            this->right = leftSubtree;

            this->height = this->countHeigth();
            newRoot->height = newRoot->countHeigth();

            return newRoot;
        }

        Node* rightTurn() {
            std::cout << "Right turt in " << this->data.name << "\n";
            Node* newRoot = this->left;  
            Node* rightSubtree = newRoot->right;  

            newRoot->right = this;
            this->left = rightSubtree;

            this->height = this->countHeigth();
            newRoot->height = newRoot->countHeigth();

            return newRoot;
        }
        Node* findMin() {
            if (this->left == nullptr) {
                return this;
            }
            Node* res = this->left->findMin();
            return res;
        }
    };
    Node* root;
    
    Node* recInsert(Node* node, Entry& d) {
        if (d.name < node->data.name) {
            if (node->left == nullptr) {
                node->left = new Node();
                node->left->data = d;
                node->left->height = 1;
                node->height = node->countHeigth();
                return node;
            }
            Node* next = recInsert(node->left, d);
            node->left = next;
            node->height = node->countHeigth();
            int balance = node->countBalance();
            if (balance == 2) {
                if (node->left->countBalance() == 1) {
                    Node* ret = node->rightTurn();
                    return ret;
                }
                if (node->left->countBalance() == -1) {
                    node->left = node->left->leftTurn();
                    Node* ret = node->rightTurn();
                    return ret;
                }
            }
            return node;
        }
        if (d.name > node->data.name) {
            if (node->right == nullptr) {
                node->right = new Node();
                node->right->data = d;
                node->right->height = 1;
                node->height = node->countHeigth();
                return node;
            }
            Node* next = recInsert(node->right, d);
            node->right = next;
            node->height = node->countHeigth();
            int balance = node->countBalance();
            if (balance == -2) {
                if (node->right->countBalance() == -1) {
                    Node* ret = node->leftTurn();
                    return ret;
                }
                if (node->right->countBalance() == 1) {
                    node->right = node->right->rightTurn();
                    Node* ret = node->leftTurn();
                    return ret;
                }
            }
            return node;
        }
        if (d.name == node->data.name) {
            throw std::invalid_argument("Same name");
        }
    }
    int recDestructor(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        else{
            recDestructor(node->left);
            recDestructor(node->right);
            delete node;
        }
    }
    Node* recDel(Node* node, std::string name) {
        if (node == nullptr) {
            throw std::invalid_argument("No such name");
        }
        if (name < node->data.name) {
            node->left = recDel(node->left, name);
            node->height = node->countHeigth();
            int balance = node->countBalance();
            if (balance == 2) {
                if (node->left->countBalance() == 1) {
                    Node* ret = node->rightTurn();
                    return ret;
                }
                if (node->left->countBalance() == -1) {
                    node->left = node->left->leftTurn();
                    Node* ret = node->rightTurn();
                    return ret;
                }
            }
            if (balance == -2) {
                if (node->right->countBalance() == -1) {
                    Node* ret = node->leftTurn();
                    return ret;
                }
                if (node->right->countBalance() == 1) {
                    node->right = node->right->rightTurn();
                    Node* ret = node->leftTurn();
                    return ret;
                }
            }
            return node;
        }
        if (name > node->data.name) {
            node->right = recDel(node->right, name);
            node->height = node->countHeigth();
            int balance = node->countBalance();
            if (balance == 2) {
                if (node->left->countBalance() == 1) {
                    Node* ret = node->rightTurn();
                    return ret;
                }
                if (node->left->countBalance() == -1) {
                    node->left = node->left->leftTurn();
                    Node* ret = node->rightTurn();
                    return ret;
                }
            }
            if (balance == -2) {
                if (node->right->countBalance() == -1) {
                    Node* ret = node->leftTurn();
                    return ret;
                }
                if (node->right->countBalance() == 1) {
                    node->right = node->right->rightTurn();
                    Node* ret = node->leftTurn();
                    return ret;
                }
            }
            return node;
        }
        if (name == node->data.name) {
            int k = 0;
            if (node->left != nullptr) {
                k += 1;
            }
            if (node->right != nullptr) {
                k += 1;
            }
            if (k == 0) {
                delete node;
                return nullptr;
            }
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            if (k == 2) {
                Node* minInRight = node->right->findMin();
                node->data.name = minInRight->data.name;
                node->data.data = minInRight->data.data;
                node->right= recDel(node->right, minInRight->data.name);

                node->height = node->countHeigth();
                int balance = node->countBalance();
                if (balance == 2) {
                    if (node->left->countBalance() == 1) {
                        Node* ret = node->rightTurn();
                        return ret;
                    }
                    if (node->left->countBalance() == -1) {
                        node->left = node->left->leftTurn();
                        Node* ret = node->rightTurn();
                        return ret;
                    }
                }
                if (balance == -2) {
                    if (node->right->countBalance() == -1) {
                        Node* ret = node->leftTurn();
                        return ret;
                    }
                    if (node->right->countBalance() == 1) {
                        node->right = node->right->rightTurn();
                        Node* ret = node->leftTurn();
                        return ret;
                    }
                }
                return node;
            }
        }
    }

public:
    AVLtree() {
        root = nullptr;
    }
    ~AVLtree() {
        recDestructor(root);
    }
    int add(std::string name, Polinom pol) {
        Entry d = Entry(name, pol);
        if (root == nullptr) {
            Node* temp = new Node();
            temp->data = d;
            root = temp;
            temp = nullptr;
            return 0;
        }
        root = recInsert(root, d);
        return 0;
    }
    Polinom find(std::string name) {
        Node* cur = root;
        while (cur != nullptr) {
            if (name > cur->data.name) {
                cur = cur->right;
            }
            if (name < cur->data.name) {
                cur = cur->left;
            }
            if (name == cur->data.name) {
                return cur->data.data;
            }
        }
        throw std::invalid_argument("No such name");
    }

    int remove(std::string name) {
        root = recDel(root, name);
        return 0;
    }

    void printTreeByLevels() {
        if (!root) return; // Проверка на пустое дерево

        std::queue<Node*> q;       // Очередь для обхода дерева
        q.push(root);         // Добавляем корень в очередь

        while (!q.empty()) {
            int levelSize = q.size(); // Количество узлов на текущем уровне

            for (int i = 0; i < levelSize; ++i) {
                Node* current = q.front(); // Извлекаем узел из очереди
                q.pop();

                std::cout << current->data.name << " "; // Выводим значение узла

                // Добавляем дочерние узлы в очередь
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
            std::cout << std::endl; // Переход на новую строку после каждого уровня
        }
    }
};