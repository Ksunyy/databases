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
        int heigth;
        Node() {
            left = nullptr;
            right = nullptr;
            data = Entry();
            heigth = 0;
        }
        int countHeigth() {
            int l,r;
            if (this->left == nullptr) {
                l = 0;
            }
            else {
                l = this->left->heigth;
            }
            if (this->right == nullptr) {
                r = 0;
            }
            else {
                r = this->right->heigth;
            }

            return 1+std::max(r, l);
        }
        int countBalance() {
            int l, r;
            if (this->left == nullptr) {
                l = 0;
            }
            else {
                l = this->left->heigth;
            }
            if (this->right == nullptr) {
                r = 0;
            }
            else {
                r = this->right->heigth;
            }
            return l - r;
        }
    };
    Node* root;
    
    void recInsert(Node* node, Entry& d) {
        if (node != root) {
            if (d.name < node->data.name) {
                if (node->left == nullptr) {
                    node->left = new Node();
                    node->left->data = d;
                    return;
                }
                recInsert(node->left, d);
                node->heigth = node->countHeigth();
                int balance = node->countBalance();
                if (balance == -2) {
                    if (node->left->countBalance() == -1) {
                        node.leftTurn();

                    }
                    if (node->left->countBalance() == 1) {
                        node->right.rightTurn();
                        node.leftTurn();
                    }
                }
                if (balance == 2) {
                    if (node->left->countBalance() == 1) {
                        Node* l = node->left;
                        Node* r = node->right;
                        node.rightTurn();
                        l->heigth = l->countHeigth();
                        r->heigth = l->countHeigth();
                        node->heigth = node->countHeigth();


                    }
                    if (node->left->countBalance() == -1) {
                        node->left.leftTurn();
                        node.rightTurn();
                    }

                }
            }
            if (d.name > node->data.name) {
                if (node->right == nullptr) {
                    node->right = new Node();
                    node->right->data = d;
                    return;
                }
                recInsert(node->right, d);
            }
            if (d.name == node->data.name) {
                throw "same name";
            }
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
        recInsert(root, d);
        return 0;
    }
    void print() {

    }
};