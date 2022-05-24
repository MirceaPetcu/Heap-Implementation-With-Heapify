#include<fstream>
#include <vector>
using namespace std;

class Heap {
public:
    void del_heap(){heap.clear();}
    void urca(long long poz);
    void coboara(long long poz);
    long long get_max() const{return heap[0];}
    long long get_size() {return heap.size()-1;}
    void baga(long long x);
    void scoate();
    vector<long long > get_heap(){return heap;}
    void heapify(long long i,long long size);
    void build_heap(long long size);
    void merge(Heap h);

private:
    vector<long long> heap;

};

void Heap::urca(long long int poz) {
    while (poz) {
        if (heap[(poz - 1) / 2] < heap[poz]) {
            swap(heap[poz], heap[(poz - 1) / 2]);
            poz = (poz - 1) / 2;
        } else
            break;
    }
}

void Heap::merge(Heap h) {
    for(auto i = 0;i<h.get_size()+1;i++)
        heap.push_back(h.get_heap()[i]);
    build_heap(heap.size());

}

void Heap::build_heap(long long int size) {
    for(auto i = size/2-1;i>=0;i--)
        heapify(i,size);
}

void Heap::heapify(long long int i, long long int size) {
    if(i>size)
        return;
    long long tata = i;
    if(2*i+1<size && heap[2*i+1]>heap[tata])
        tata = 2*i+1;
    if(2*i+2<size && heap[2*i+2]>heap[tata])
        tata = 2*i+2;
    if(tata != i)
    {
        swap(heap[i],heap[tata]);
        heapify(tata,size);
    }

}

void Heap::scoate() {
    heap[0] = heap[get_size()];
    heap.pop_back();
    coboara(0);
}

void Heap::baga(long long int x) {
    heap.push_back(x);
    urca(get_size());
}

void Heap::coboara(long long int poz) {
    while (poz * 2 + 1 < heap.size()) {
        if(heap[poz*2+1]<heap[poz] && heap[poz*2+2]<heap[poz] && poz*2+2<heap.size())
            break;
        if(heap[poz*2+1]<heap[poz])
            break;
        if (poz * 2 + 2 < heap.size()) {
            if (heap[poz * 2 + 2] > heap[poz * 2 + 1]) {
                if(heap[poz*2+2]>heap[poz]) {
                    swap(heap[poz * 2 + 2], heap[poz]);
                    poz = poz * 2 + 2;
                }
            }
            else  if(heap[poz*2+1]>heap[poz]){
                swap(heap[poz * 2 + 1], heap[poz]);
                poz = poz * 2 + 1;
            } else break;
        } else if (heap[poz * 2 + 1] > heap[poz]) {
            swap(heap[poz * 2 + 1], heap[poz]);
            poz = poz * 2 + 1;
        } else break;
    }
}

int main()
{
    ifstream f("mergeheap.in");
    ofstream g("mergeheap.out");
    long long n,q,op,m,x,a,b;
    f>>n>>q;
    Heap v[n+1];
    vector<long long >sol;
    for(auto i = 0;i<q;i++) {
        f >> op;
        switch (op) {
            case 1: {
                f >> m >> x;
                v[m].baga(x);
                break;
            }
            case 2:
            {
                f>>m;
                sol.push_back(v[m].get_max());
                v[m].scoate();
                break;
            }
            case 3:
            {
                f>>a>>b;
                v[a].merge(v[b]);
                v[b].del_heap();
                break;
            }
        }
    }
   for(auto i = 0;i<sol.size();i++)
       g<<sol[i]<<'\n';
    f.close();g.close();
    return 0;

}