class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        int n = grid.size();
        UnionFind uf(4 * n * n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                int root = 4 * (i * n + j);
                char ch = grid[i][j];
                if(ch == '/') {
                    uf.unite(root + 0, root + 3);
                    uf.unite(root + 1, root + 2);
                } else if(ch == '\\') {
                    uf.unite(root + 0, root + 1);
                    uf.unite(root + 2, root + 3);
                } else {
                    uf.unite(root + 0, root + 1);
                    uf.unite(root + 1, root + 2);
                    uf.unite(root + 2, root + 3)
                }
                if(j + 1 < n) {
                    uf.unite(root + 1, 4 * (i * n + (j + 1)) + 3);
                }
                if(i + 1 < n) {
                    uf.unite(root + 2, 4 * ((i + 1) * n + j) + 0);
                }
            }
        }
        return uf.getCount();
    }
private:
    class UnionFind {
    public:
        UnionFind(int size) : parent(size), rank(size, 1), count(size) {
            iota(parent.size(), parent.end(), 0);
        }
        int find(int x) {
            if(parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        void unite(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if(rootX != rootY) {
                if(rank[rootX] > rank[rootY]) {
                    parent[rootY] = rootX;
                } else if(rank[rootX] < rank[rootY]) {
                    parent[rootX] = rootY;
                } else {
                    parent[rootY] = rootX;
                    rank[rootX]++;
                }
                count--;
            }
        }
        int getCount() const {
            return count;
        }
    private:
        vector<int> parent;
        vector<int> rank;
        int count;
    };
};
