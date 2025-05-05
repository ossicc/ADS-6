// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
struct SYM {
  char ch;
  int prior;
};

template <typename T>
class Node {
 public:
  T data;
  Node* next;

  Node(T item) : data(item), next(nullptr) {}
};

template <typename T>
class TPQueue {
 private:
  Node<T>* head;
 public:
  TPQueue() : head(nullptr) {}

  ~TPQueue() {
    while (head) {
      Node<T>* temp = head;
      head = head->next;
      delete temp;
    }
  }

  void push(T item) {
    Node<T>* newNode = new Node<T>(item);

    if (!head || head->data.prior < item.prior) {
      newNode->next = head;
      head = newNode;
      return;
    }

    Node<T>* current = head;
    while (current->next && current->next->data.prior >= item.prior) {
      current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
  }

  T pop() {
    if (!head) {
      throw std::runtime_error("Queue is empty");
    }
    Node<T>* temp = head;
    T result = head->data;
    head = head->next;
    delete temp;
    return result;
  }

  bool isEmpty() const { return head == nullptr; }

  void printQueue() const {
    Node<T>* current = head;
    while (current) {
      std::cout << "(" << current->data.ch << ", " << current->data.prior
                << ") -> ";
      current = current->next;
    }
    std::cout << "nullptr" << std::endl;
  }
};
#endif  // INCLUDE_TPQUEUE_H_
