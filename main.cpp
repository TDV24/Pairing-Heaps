#include <bits/stdc++.h>

struct NodHeap{
    int cheie;
    NodHeap *copil;//valoarea din partea stanga a cheii
    NodHeap *vecin;//urmatoarea valoare crescatoare din heap

    NodHeap():
        copil(NULL), vecin(NULL) {}//declar valorile initiale pentru copil si vecin

    //initializam un nod nou
    NodHeap(int cheie_, NodHeap *copil_, NodHeap *vecin_):
        cheie(cheie_), copil(copil_), vecin(vecin_) {}

    //ii adaugam nodului copilul si vecinul acestuia
    void adauga_detalii_nod(NodHeap *nod)
    {
        if(copil==NULL)
        {
            copil=nod;
        }
        else
        {
            nod->vecin=copil;
            copil=nod;
        }
    }
};
//verific daca heapul are elemente
bool Verificare_Heap(NodHeap *nod)
{
    if(nod==NULL)
        return false;
    else
        return true;
}
//functia care imi reuneste doua heapuri
NodHeap *Merge(NodHeap *nod1, NodHeap *nod2)
{
    if(nod1==NULL)
    {
        return nod2;
    }
    if(nod2==NULL)
    {
        return nod1;
    }
    if(nod1->cheie < nod2->cheie)
    {
        nod1->adauga_detalii_nod(nod2);
        return nod1;
    }
    else
    {
        nod2->adauga_detalii_nod(nod1);
        return nod2;
    }
    return NULL;
}
//imi afiseaza elementul minim din heap(radacina)
int Elem_Minim(NodHeap *nod)
{
    return nod->cheie;
}
//inseram un nod now in heap
NodHeap *Insert(NodHeap *nod, int cheie)
{
    return Merge(nod, new NodHeap(cheie, NULL, NULL));
}
//ne trebuie un merge separat pentru cand stergem radacina
NodHeap *Merge2(NodHeap *nod)
{
    if(nod==NULL || nod->vecin==NULL)
    {
        return nod;
    }
    else
    {
        NodHeap *a, *b, *c;
        a=nod;
        b=nod->vecin;
        c=nod->vecin->vecin;
        a->vecin=NULL;
        b->vecin=NULL;
        return Merge(Merge(a,b), Merge2(c));
    }
    return NULL;
}

NodHeap *Delete(NodHeap *nod)
{
    return Merge2(nod->copil);
}

struct PairingHeap{
    NodHeap *root;
    PairingHeap():
        root(NULL){}

    bool Verificare_Heap()
    {
        return ::Verificare_Heap(root);
    }
    int Elem_Minim()
    {
        return ::Elem_Minim(root);
    }
    void Insert(int cheie){
        root=::Insert(root, cheie);
    }
    void Delete(){
        root=::Delete(root);
    }
    void Merge(PairingHeap Heap)
    {
        root=::Merge(root, Heap.root);
    }
    void Build(int n, int v[])
    {
        if(root==NULL)
        {
            for(int i=0; i<n; i++)
                root=::Insert(root, v[i]);
        }
        else
        {
            std::cout<<"Acest heap deja exista."<<'\n';
        }
    }
};

int main() {
    PairingHeap heap1, heap2, heap3;
    heap2.Insert(21);
    heap2.Insert(18);
    heap2.Insert(9);
    heap1.Insert(6);
    heap1.Insert(90);
    heap1.Insert(4);
    heap1.Merge(heap2);
    int v[]={22,14,8,7,23};
    heap3.Build(5, v);
    std::cout << heap3.Elem_Minim() << '\n';
    std::cout << heap1.Elem_Minim() << '\n';
    heap1.Delete();
    std::cout << heap1.Elem_Minim() << '\n';
    return 0;
}
