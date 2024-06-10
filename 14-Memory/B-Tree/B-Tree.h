#include <fstream>
#include <functional>
#include <string>
#include <vector>

template <typename DataType, std::function<bool(DataType, DataType)> compare>
class Btree {
public:
    Btree(std::string filename) : filename(filename) {}
    Btree<DataType, compare>& insert(DataType data);
    Btree<DataType, compare>& erase(DataType data);
    const DataType& find(DataType key) const;
private:
    std::string filename;
    class Node {
        public:
            Node(int t) : t(t) {}
        private:
            // The number of the key is in [t-1, 2t-1]
            // So the number of child nodes is in [t, 2t]
            int t;
            std::vector<DataType> keys;
            std::vector<Node*> children;
    };
};