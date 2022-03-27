#include <string>

struct ListNode {
    ListNode *      prev;
    ListNode *      next;
    ListNode *      rand; // указатель на произвольный элемент данного списка либо NULL
    std::string     data;
};

class List {
public:

class Iterator{
    public:
        Iterator(const List * list);

        const ListNode* get() const;
        void set(const std::string &value, ListNode* const rand = nullptr);

        void next();

        bool has_next() const;

    private:
        ListNode* start_from_head = nullptr;
    };

    List();
    ~List();

    void InsertHead(const std::string &str, ListNode* const rand = nullptr);
    void InsertTail(const std::string &str, ListNode* const rand = nullptr);

    ListNode* AtIndex(int index);
    int Size() const;

    // For testing reasons
    void PrintList();

    void Serialize   (FILE * file);
    void Deserialize (FILE * file);

    const Iterator iterator() const {
        return Iterator(this);
    }

private:
    List(const List&);
    List& operator=(const List&);


    ListNode *      head = nullptr;
    ListNode *      tail = nullptr;
    int             count = 0;
};