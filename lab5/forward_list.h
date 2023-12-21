#pragma once

#include <iostream>
#include "allocator.h"

template <typename T, size_t Block_size, typename Allocator = MyAllocator<T, Block_size>>
class MyForwardList {
private:
    

public:
    struct Node {
        T value;
        Node* next;
    };
    class MyIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using reference = T&;
        using pointer = T*;
        using const_reference = const T&;
        using const_pointer = const T*;
        using value_type = T;

        MyIterator(Node* ptr_) : ptr(ptr_) {};

        reference operator*() const {
            return ptr->value;
        }

        pointer operator->() const {
            return &(ptr->value);
        }

        MyIterator& operator++() {
            if (ptr == nullptr) {
                throw std::out_of_range("Out of range");
            }
            ptr = ptr->next;
            return *this;
        }

        MyIterator operator++(int) {
            MyIterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const MyIterator& rhs) const {
            return ptr == rhs.ptr;
        }

        bool operator!=(const MyIterator& rhs) const {
            return !(*this == rhs);
        }

        Node* getPtr() const { //for insert_after
            return ptr;
        }

    private:
        Node* ptr;
    };

public:
    using iterator = MyIterator;
    using const_iterator = MyIterator;
    using allocator_type = MyAllocator<T, Block_size>;
    using NodeAllocator = typename allocator_type::template rebind<Node>::other;

    MyForwardList() {
        head = allocator.allocate(1);
        head->next = nullptr;
    }

    ~MyForwardList() {
        clear();
        allocator.deallocate(head, 1);
    }

    T front() const {
        if (head->next == nullptr) {
            throw std::out_of_range("List is empty");
        }
        return head->next->value;
    }

    void push_front(const T& value) {
        Node* newNode = allocator.allocate(1);
        newNode->value = value;
        newNode->next = head->next;
        head->next = newNode;
    }

    void pop_front() {
        if (head->next == nullptr) {
            return;
        }
        Node* tmp = head->next;
        head->next = tmp->next;
        allocator.deallocate(tmp, 1);
    }

    bool empty() const {
        return head->next == nullptr;
    }

    void clear() {
        Node* current = head->next;
        while (current != nullptr) {
            Node* tmp = current;
            current = current->next;
            allocator.deallocate(tmp, 1);
        }
        head->next = nullptr;
    }

    iterator insert_after(iterator pos, const T& value) {
        Node* curr = head;
        while (curr != nullptr && curr != pos.getPtr()) {
            curr = curr->next;
        }
        if (curr == nullptr) {
            throw std::out_of_range("Iterator not found in the list");
        }

        Node* newNode = allocator.allocate(1);
        newNode->value = value;
        newNode->next = curr->next;
        curr->next = newNode;

        return iterator(newNode);
    }

    iterator before_begin() {
        return iterator(head);
    }

    iterator begin() {
        return iterator(head->next);
    }

    iterator end() {
        return iterator(nullptr);
    }

    const_iterator cbefore_begin() const {
        return const_iterator(head);
    }

    const_iterator cbegin() const{        
        return const_iterator(head->next);
    }

    const_iterator cend() const {
        return const_iterator(nullptr);
    }

private:
    Node* head;
    NodeAllocator allocator;
};