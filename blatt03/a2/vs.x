struct return_twice{
  string str1<>;
  string str2<>;
};

struct dir_node{
  string desc<>;
  string type<>;
  struct dir_node *next;
};

struct quad_array {
  int size;
  int elements<>;
};

program VS11SERVER {
  version VS11SERVER {
    quad_array vs_quad(int)=1;
    return_twice vs_twice(string name)=2;
    string vs_readdir(string dirname)=3;
    void vs_shutdown(void)=6;
  }=1;
}= 0x20005123;
