// implementing a linked list in go making use of some polymorphism to implement the
// data structure 

// Svita Kiran
// CS333
// 10/30/2025

package main
import "fmt"

type Node[T any] struct {
    data T
    next *Node[T]
}

type LinkedList[T any] struct {
    head *Node[T]
    size int
}

// new linked list
func NewLinkedList[T any]() *LinkedList[T] {
    return &LinkedList[T]{}
}

func (l *LinkedList[T]) Push(data T) {
    node := &Node[T]{data: data, next: l.head}
    l.head = node
    l.size++
}

func (l *LinkedList[T]) Pop() *T {
    if l.head == nil {
        return nil
    }
    node := l.head
    l.head = node.next
    l.size--
    return &node.data
}

func (l *LinkedList[T]) Append(data T) {
    node := &Node[T]{data: data}
    if l.head == nil {
        l.head = node
    } else {
        current := l.head
        for current.next != nil {
            current = current.next
        }
        current.next = node
    }
    l.size++
}

func (l *LinkedList[T]) Find(target T, cmp func(a, b T) bool) *T {
    current := l.head
    for current != nil {
        if cmp(current.data, target) {
            return &current.data
        }
        current = current.next
    }
    return nil
}

func (l *LinkedList[T]) Remove(target T, cmp func(a, b T) bool) *T {
    var prev *Node[T]
    current := l.head
    for current != nil {
        if cmp(current.data, target) {
            if prev == nil {
                l.head = current.next
            } else {
                prev.next = current.next
            }
            l.size--
            return &current.data
        }
        prev = current
        current = current.next
    }
    return nil
}

func (l *LinkedList[T]) Map(f func(data T)) {
    current := l.head
    for current != nil {
        f(current.data)
        current = current.next
    }
}

func (l *LinkedList[T]) Size() int {
    return l.size
}

// clear the list
func (l *LinkedList[T]) Clear() {
    l.head = nil
    l.size = 0
}


// test program
func main() {
	intList := NewLinkedList[int]()
    for i := 0; i < 5; i++ {
        intList.Push(i)
    }
    fmt.Println("integer list:")
    intList.Map(func(i int) { fmt.Println(i) })

	strList := NewLinkedList[string]()
    words := []string{"car", "bike", "train"}
    for _, w := range words {
        strList.Append(w)
    }
    fmt.Println("\nstring list:")
    strList.Map(func(s string) { fmt.Println(s) })

	found := intList.Find(3, func(a, b int) bool { return a == b })
    if found != nil {
        fmt.Println("\nfound:", *found)
    }

	removed := strList.Remove("bike", func(a, b string) bool { return a == b })
    if removed != nil {
        fmt.Println("\nremoved:", *removed)
    }
    fmt.Println("\nafter removal:")
    strList.Map(func(s string) { fmt.Println(s) })
}