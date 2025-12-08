#ifndef DISJOINT_SET
#define DISJOINT_SET

#include <vector>

class disjoint_set {
    std::vector<int> parent;
    std::vector<int> size;

    public:
    disjoint_set(int n): parent(n), size(n,1) {
        for(int i=0;i<n;i++) parent[i]=i; 
    }

    int find(int a) {
        if(parent[a]==a) return a;
        return parent[a]=find(parent[a]);
    }

    bool unite(int a, int b) {
        int fa = find(a);
        int fb = find(b);
        if(fa==fb) return false;
        /* Unions are to be kept flat as possible */
        if(size[fa]<size[fb]) std::swap(size[fa],size[fb]);
        parent[fb]=fa;
        size[fa]+=size[fb];
        return true;
    }

    int get_size(int i) {
        return size[find(i)];
    }
};

#endif /* DISJOINT_SET */