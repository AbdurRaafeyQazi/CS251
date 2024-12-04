class ChainingHashMap {
 public:
  struct Entry {
    int k;
    int v;
    Entry* next;
  };

  Entry** buckets;
  int size;
  int capacity;

  ChainingHashMap();
  ChainingHashMap(int capacity);
  ~ChainingHashMap();
  void insert(int key, int value);
  int at(int key);

 private:
  int get_bucket(int key);
  // Tests if the table needs to be resized, and executes the resize
  void maybe_resize();
};
